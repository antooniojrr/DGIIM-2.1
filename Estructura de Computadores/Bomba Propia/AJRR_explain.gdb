# Practica 4, Actividad 4.1: explicacion de la bomba

# CONTRASEÑA: antooniojrr
# PIN: 3737
# MODIFICADA: rrjoinootna
# PIN: 7373

# Describe el proceso logico seguido para:
# 	1: Descubrir las claves de la bomba
# 	2: Cambiarlas
# Ejecución:
#	· "source AJRR_explain.gdb" dentro de gdb
#	· Directamente ejecutando " gdb -q -x AJRR_explain.gdb "
# Se supone que se aplica sobre la compilación original de la bomba. Para recompilarla
# Usar la orden gcc en la primera linea de AJRR_bomba.c
# "gcc -Og AJRR_bomba.c -o bomba -no-pie -fno-guess-branch-probability"

########################################################################################

# Cargar el programa

	file bomba

# Para un vistazo superficial al código ensamblador del programa, ejecutaríamos
#	layout asm
#	layout regs
# Comenzaremos a realizar ejecuciones del programa con breaking points en los puntos que veamos
# relevantes. Poniendo el primero en el main, conseguiremos la declaración de variables globales:

	br main

# A partir de este punto, podemos ver introduciendo valores aleatorios para password y pin,
# por ejemplo, "casa" y 123 respectivamente, llegamos a perder cuando se produce una llamada a
# la función explode (Lo puedes comprobar ejecutando paso a paso con nexti y stepi)

	run

# Ponemos un breakpoint en justo antes de que el código llame a esta función (o la salte) y
# volvemos a ejecutar

#	0x4012d7 <main+136>     lea    0x2da2(%rip),%rsi        # 0x404080 <password>
#	0x4012de <main+143>     callq  0x4010a0 <strncmp@plt>
# --->	0x4012e3 <main+148>     test   %eax,%eax            // Breakpoint aquí
# 	0x4012e5 <main+150>     je     0x4012ec <main+157>
#	0x4012e7 <main+152>     callq  0x4011f6 <explode>

# Podemos eliminar ya de paso el br que teniamos en main
	d 1
	br *main+148
	run
	
# En esta ejecución podemos evitar que explote la bomba cambiando en este breakpoint el valor de
# %eax a 0. De esta forma ZF se activará y se producirá el salto de main+150.
# En este punto, también podemos obtener la contraseña fijándonos en que esta se encuentra en
# la dirección de memoria guardada en %rsi

	p(char*) $rsi
	# Password = antooniojrr		
	set $eax=0
	
# Si avanzamos un poco más en el código, vemos que se produce otra llamada a explode poco después.

#	0x4012f6 <main+167>     callq  0x4010c0 <gettimeofday@plt>
#	0x4012fb <main+172>     mov    0x20(%rsp),%rax
#	0x401300 <main+177>     sub    0x10(%rsp),%rax
# --->	0x401305 <main+182>     cmp    $0x3c,%rax
# 	0x401309 <main+186>     jle    0x401310 <main+193>
#	0x40130b <main+188>     callq  0x4011f6 <explode>

# Poniendo un breakpoint donde hemos marcado, podemos evitar la llamada provocando que se cumpla
# la condición de salto. que es que %rax <= 0x3c = 60

	br *main+182
	cont
	set $rax=0

# Seguimos avanzando en el código y vemos donde se produciría la siguiente llamada a explode:

#	0x401369 <main+282>     mov    0x2d09(%rip),%eax        # 0x404078 <passcode>
# --->	0x40136f <main+288>     cmp    %eax,0xc(%rsp)
#	0x401373 <main+292>     je     0x40137a <main+299>
#	0x401375 <main+294>     callq  0x4011f6 <explode>

# Para evitar esta explosión, ponemos un breakingpoint donde se indica y vemos que se
# esta guardando passcode en la dirección 0x404078, luego podemos verlo y, para que no nos explote
# en esta ejecución, corregiremos %rax, que ahora mismo guarda 3737, por el pin que hemos introducido,
# 123

	br *main+288
	cont
	p*(int) 0x404078
	# Passcode = 3737    	
	set $eax=123

# Por último vemos otra bomba que explotará si el valor de %rax es mayor que 0x3c=60, podemos
# evitarla con el mismo procedimiento usado con la segunda.

# --->	0x401393 <main+324>             cmp    $0x3c,%rax
#	0x401397 <main+328>             jle    0x40139e <main+335>
#	0x401399 <main+330>             callq  0x4011f6 <explode>
#	0x40139e <main+335>             callq  0x401216 <defused>

	br *main+324
	cont
	set $rax=0

# Y con esto habremos terminado la ejecución sin que nos haya explotado la bomba

	cont

# Ahora, una vez sabemos la contraseña y el pin, cambiarlas se realizará de manera muy sencilla
# usando el editor hexadecimal "ghex". Para la contraseña buscaremos "antooniojrr" y solo nos
# saldrá una coincidencia. Cambiaremos esta cadena por una de igual longitud, por ejemplo,
# "rrjoinootna". Para el pin, vemos que 3737=0xE99, luego lo buscaremos en el editor como 99 0E,
# ya que este se representa en little-endian. Lo sustituiremos por otro valor entero, por
# ejemplo, 7373. Así habremos cambiado la contraseña y el pin.

# Si queremos hacer esto también desde gdb, activaríamos primero la escritura:

	set write on

# Abrimos de nuevo el archivo

	file bomba

# Realizamos los cambios
	
	set {char[13]} 0x404080="rrjoinootna\n"
	set {int}	0x404078=7373

# Comprobamos los cambios

	p (char[0xd])password
	p (int)passcode
	
# Terminamos para desbloquear el ejecutable y guardar los cambios

	quit

	
	

