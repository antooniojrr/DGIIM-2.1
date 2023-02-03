// gcc -Og AJRR_bomba.c -o bomba -no-pie -fno-guess-branch-probability
#include <stdio.h>	// para printf(), fgets(), scanf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()
#include <sys/time.h>	// para gettimeofday(), struct timeval

#define SIZE 100
#define TLIM 60

char password[]="antooniojrr\n";	// Contraseña
int  passcode  = 3737;			// Pin
int code = 1234;			// Pin falso para despistar en la desactivación de la bomba
char pswd[] = "contraseña_falsa";	// Contraseña falsa para despistar en la desactivación de la bomba

void explode(void){
	printf(	"\n"
		"***************************************************\n"
		"******************** BOOM!!! **********************\n"
		"***************************************************\n"
		"\n");
	exit(-1);
}

void defused(void){
	printf(	"\n"
		"··················································\n"
		"·············· BOMB DEFUSED ······················\n"
		"··················································\n"
		"\n");
	exit(0);
}

void confused(void){
	printf(	"\n"
		"·························································\n"
		"····Upss, la contraseña no es correcta. Busca más...·····\n"
		"·························································\n"
		"\n");
		
}

int main(){
	char pw[SIZE];
	int  pc, n;

	struct timeval tv1,tv2;	// gettimeofday() secs-usecs
	gettimeofday(&tv1,NULL);

	do	printf("\nIntroduce la contraseÃ±a: ");
	while (	fgets(pw, SIZE, stdin) == NULL );
	
	// If para confundir una vez se convierta en lenguaje ensamblador
	if ( !(strncmp(pw,pswd,sizeof(pswd))) )
		confused();
		
	if    (	strncmp(pw,password,sizeof(password)) )
	    explode();
	
	// Segunda bomba. Si no se introduce en 60 segundos la contraseña explota.
	
	gettimeofday(&tv2,NULL);
	if    ( tv2.tv_sec - tv1.tv_sec > TLIM )
	    explode();

	// Tercera bomba, introducir el pin
	do  {	printf("\nIntroduce el pin: ");
	 if ((n=scanf("%i",&pc))==0)
		scanf("%*s")    ==1;         }
	while (	n!=1 );
	if    (	pc == code	)
		confused();
		
	if    (	pc != passcode )
	    explode();

	// Cuarta bomba. Si no se introduce en 60 segundos el pin explotara.
	
	gettimeofday(&tv1,NULL);
	if    ( tv1.tv_sec - tv2.tv_sec > TLIM )
	    explode();

	defused();
}
