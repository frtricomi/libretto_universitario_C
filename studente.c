#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "studente.h"
#include "esame.h"
#include "lista_esami.h"

struct studente{
	char *nome;
	char *cognome;
	char *username;
	char *password;
	int matricola;
	ListaEsami prenotati;
	ListaEsami superati;
};

static int matricolaCounter = 568000;

Studente creaStudente(char *nome, char *cognome, char *username, char *password){
	Studente pts = malloc(sizeof(struct studente));
	if (pts == NULL) return NULL;

	pts->nome = malloc(strlen(nome) + 1);
	if (pts->nome == NULL){
		free(pts);
		return NULL;
	}
    	strcpy(pts->nome, nome);

	pts->cognome = malloc(strlen(cognome) + 1);
	if (pts->cognome == NULL){
		free(pts->nome);
		free(pts);
		return NULL;
	}
	strcpy(pts->cognome, cognome);

	pts->username = malloc(strlen(username) + 1);
	if (pts->username == NULL){
		free(pts->cognome);
		free(pts->nome);
		free(pts);
		return NULL;
	}
	strcpy(pts->username, username);

	pts->password = malloc(strlen(password) + 1);
	if (pts->password == NULL){
		free(pts->username);
		free(pts->cognome);
		free(pts->nome);
		free(pts);
		return NULL;
	}
	strcpy(pts->password, password);

	pts->matricola = matricolaCounter++;
	pts->prenotati = creaListaEsami();
	if (pts->prenotati == NULL){
		free(pts->nome);
		free(pts->cognome);
		free(pts->username);
		free(pts->password);
		free(pts);
		return NULL;
	}

	pts->superati = creaListaEsami();
	if (pts->superati == NULL){
		liberaListaEsami(pts->prenotati);
		free(pts->nome);
		free(pts->cognome);
		free(pts->username);
		free(pts->password);
		free(pts);
		return NULL;
	}
	return pts;
}

void liberaStudente(Studente pts){
	if (pts == NULL) return;
	free(pts->nome);
	free(pts->cognome);
	free(pts->username);
	free(pts->password);
	liberaListaEsami(pts->prenotati);
	liberaListaEsami(pts->superati);
	pts->matricola = matricolaCounter--;
	free(pts);
}

char *getUsername(Studente pts){
	if (pts == NULL) return NULL;
	return pts->username;
}

char *getPassword(Studente pts){
	if (pts == NULL) return NULL;
	return pts->password;
}

int getMatricola(Studente pts){
	if (pts == NULL) return 1;
	return pts->matricola;
}

void aggiungiEsamePrenotato(Studente pts, Esame pte){
	if (pts == NULL || pte == NULL) return;
	inserisciEsameInOrdine(pts->prenotati, pte);
}

void aggiungiEsameSuperato(Studente pts, Esame pte){
	if (pts == NULL || pte == NULL) return;
	inserisciEsameInOrdine(pts->superati, pte);
}

ListaEsami getPrenotati(Studente pts){
	if (pts == NULL) return NULL;
	return pts->prenotati;
}

ListaEsami getSuperati(Studente pts){
	if (pts == NULL) return NULL;
	return pts->superati;
}

void stampaStudente(Studente pts){
	if (pts == NULL) return;
	printf("Nome: %s %s | Username: %s | Matricola: %d\n", pts->nome, pts->cognome, pts->username, pts->matricola);
	printf("Esami Prenotati:\n");
	stampaPrenotati(pts->prenotati);
	printf("Esami Superati:\n");
	stampaSuperati(pts->superati);
}
