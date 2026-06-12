#ifndef STUDENTE_H
#define STUDENTE_H
#include "esame.h"
#include "lista_esami.h"

typedef struct studente *Studente;

Studente creaStudente(char *nome, char *cognome, char *username, char *password);
void liberaStudente(Studente pts);
char *getUsername(Studente pts);
char *getPassword(Studente pts);
int getMatricola(Studente pts);
void aggiungiEsamePrenotato(Studente pts, Esame pte);
void aggiungiEsameSuperato(Studente pts, Esame pte);
ListaEsami getPrenotati(Studente pts);
ListaEsami getSuperati(Studente pts);
void stampaStudente(Studente pts);
#endif
