/*  Created by Antonio Javier Rodríguez Romero

    Proceso cliente

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define SIZE1 100
#define FIFOCLSRV "Cl-Srv_FIFO"
#define FIFOSRVCL "Srv-Cl_FIFO"

int main(void)
{


    dup2(STDOUT_FILENO,STDOUT_FILENO);
    char buf1[SIZE] = "Mensaje de solicitud de impresión";
    char nombre[SIZE];

    // Espera a que el proceso controlador cree el FIFO, si no está creado
    //sleep(1);

    int fd;

    // Abre el FIFO con permiso de escritura
    
    if((fd=open(FIFOCLSRV,O_WRONLY,S_IWUSR))<0) {
        perror("Error abriendo archivo FIFO1\n");
        exit(-1);
    }

    // Escribe la solicitud en el FIFO

    if ( (write(fd,buf1,SIZE)) < 0) {
            perror ("Write\n");
            exit (-1);

        }

    close(fd);
    // Abre el otro FIFO y lee el PID del PROXY que le atenderá
    int fd2;
    if((fd2=open(FIFOSRVCL,O_RDONLY))<0) {
        perror("Error abriendo archivo FIFO1\n");
        exit(-1);
    }

    
    sleep(1);
    int tam=read(fd2,nombre,SIZE);
    if (tam < 0) {
        perror("Read\n");
        exit(-1);
    }

    // Crea el FIFO con el PID del PROXY que le atenderá y lo abre para escritura
    umask(0);
    mkfifo(nombre,0666);
    
    int fd3=open(nombre,O_WRONLY);
    
    if ( fd3 < 0 ) {
        perror("Error abriendo FIFO PROXY\n");
        exit(-1);
    }

    // Cambiaré la salida estandar del programa por el fd del FIFO y quitare el buffer de salida
    /*write(STDOUT_FILENO,"Bien",5);
    setvbuf(stdout,NULL,_IONBF,0);
    if ( dup2(fd3,STDOUT_FILENO) < 0) {
        perror("Error cambiando la salida estandar\n");
        exit(-1);
    }*/
    
    // Ahora el cliente manda el mensaje que querría escribir por pantalla.
    // Por poner varias escrituras de ejemplo, escribirá:

    char temp[SIZE]="prueba\n";   
    for(int i=1; i< 11; i++) {
        
        write(fd3,"prueba\n",8);

    }
    sprintf(temp,"\nFIN\n",NULL);
    write(fd3,temp,SIZE);
    close(fd3);

    exit(0);

}