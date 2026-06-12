#!/bin/bash

if [ "$1" == "clean" ]; then
	rm *.o
	rm *.a
	rm main
else
	gcc -c -g esame.c
	gcc -c -g lista_esami.c
	gcc -c -g studente.c
	gcc -c -g lista_studenti.c
	ar -cr libmain.a esame.o lista_esami.o studente.o lista_studenti.o
	gcc -g main.c -L. -lmain -o main
fi
