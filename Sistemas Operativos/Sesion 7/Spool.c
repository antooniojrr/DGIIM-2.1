/*  Created by Antonio Javier Rodríguez Romero

    Proceso que controlará el spool

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

#define SIZE 1024
#define LONGNOMBRE 50
#define FIFOCLSRV "fifo_srv_cl_e"
#define FIFOSRVCL "fifo_srv_cl_s"
#define BLOQUEO "ScreenBlock"

int main(void)
{
    char buf[SIZE];
    int fd_fifo1;
    int fd_fifo2;

    umask(0);
    mkfifo(FIFOCLSRV,0666);
    mkfifo(FIFOSRVCL,0666);

    // Además, creamos un archivo cuyo único uso será bloquearlo cuando se esté usando
    // la pantalla

    int fd_lck;
    if((fd_lck=open(BLOQUEO,O_RDWR|O_CREAT,S_IRWXU))<0) {
        perror("Error abriendo archivo de bloqueo\n");
        exit(-1);
    }

    struct flock bloq;
    bloq.l_len=0;
    bloq.l_start=0;
    bloq.l_type=F_WRLCK;
    bloq.l_whence=SEEK_SET;

    if((fd_fifo1=open(FIFOCLSRV,O_RDWR))<0) {
        perror("Error abriendo archivo FIFO1\n");
        exit(-1);
    }

    if((fd_fifo2=open(FIFOSRVCL,O_RDWR))<0) {
        perror("Error abriendo archivo FIFO2\n");
        exit(-1);
    }

    while(1) {

        

        dup2(STDOUT_FILENO,STDOUT_FILENO);
        
        // El proceso se bloqueará hasta que haya algo en el FIFO que leer
        if (read(fd_fifo1,buf,SIZE) < 0) {
            perror ("Read1\n");
            exit(-1);
        }

        printf("\nSolicitud recibida\n");

        pid_t pid1;

        // Cuando se recibe el mensaje se crea un PROXY para atenederlo

        pid1 = fork();


        if (pid1 < 0) {
            perror("Fork1\n");
            exit(-1);
        }

        if (pid1==0) // Proceso hijo, PROXY
        {
            int fd_fifo3;
            char buf2[SIZE];
            char buftemp[SIZE]="";
            char nombreproxy[LONGNOMBRE];
            int mipid=getpid();
            
            sprintf(nombreproxy,"fifo.%d",mipid);
            mkfifo(nombreproxy,0666);
            if ((fd_fifo3=open(nombreproxy,O_RDONLY,S_IRWXU))<0) {
                perror("Open2\n");
                exit(-1);
            }

            // Leerá cuando el cliente escriba en el FIFO lo que quiere imprimir
            
            FILE *file;
            file=tmpfile();

            int temp=1024;
            while(read(fd_fifo3,buftemp,SIZE)) 
                fwrite(buftemp,sizeof(char),SIZE,file);
            

            // Quitamos el buffer de salida
            setvbuf(stdout,buftemp,_IOFBF,SIZE);

            // Leemos file entero y lo guardamos en buf2
            while(fread(buf2,sizeof(char),SIZE,file)>0) {
                write(STDOUT_FILENO,buf2,SIZE);
            };

            // Comprobamos que esta disponible la pantalla e imprimimos
            while(fcntl(fd_lck,F_SETLKW,bloq)==-1) {}
            
            // Una vez resuelta la solicitud, eliminamos el FIFO y desbloqueamos el archivo
            close(fd_fifo3);
            unlink(nombreproxy);
            fcntl(fd_lck,F_UNLCK,bloq);

            printf("\nPROXY de PID %i terminando\n\n",getpid());
            exit(0);

        }

        else // Proceso padre (pid1!=0)
        {
            sleep(2);
            if ( write(fd_fifo2,&pid1,sizeof(int)) < 0 ) {
                perror("Write Proc\n");
                exit(-1);
            }
            
        }

    }
}