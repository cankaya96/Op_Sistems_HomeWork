all: myshell mul div rakam

myshell: myshell.c
	gcc myshell.c -o myshell

mul: mul.c
	gcc mul.c -o mul

div: div.c
	gcc div.c -o div

rakam: rakam.c
	gcc rakam.c -o rakam
