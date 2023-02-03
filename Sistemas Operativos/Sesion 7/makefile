#!/bin/bash

#Archivo makefile para compilar el spool y el archivo de clientes
#Para compilar todo, usar comando "make compile"


compile: spool clientes

spool: Spool.c
	gcc -o spool Spool.c
	
clientes: clientes.c
	gcc -o clientes clientes.c

clean:
	rm spool
	rm clientes
	rm fifo*
	rm ScreenBlock

