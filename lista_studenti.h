#ifndef LISTA_STUDENTI_H
#define LISTA_STUDENTI_H
#include "studente.h"

typedef struct lista_studenti *ListaStudenti;

ListaStudenti creaListaStudenti();
void liberaListaStudenti(ListaStudenti lista);
int inserisciStudente(ListaStudenti lista, Studente pts);
Studente cercaPerUsername(ListaStudenti lista, const char *username);
void stampaTuttiStudenti(ListaStudenti lista);
#endif
