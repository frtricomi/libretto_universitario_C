#ifndef LISTA_ESAMI_H
#define LISTA_ESAMI_H
#include "esame.h"

typedef struct lista_esami *ListaEsami;

ListaEsami creaListaEsami();
void liberaListaEsami(ListaEsami ptl);
int inserisciEsameInOrdine(ListaEsami ptl, Esame pte);
int rimuoviEsame(ListaEsami ptl, const char *nomeMateria);
Esame cercaEsamePerNome(ListaEsami ptl, const char *nomeMateria);
void stampaPrenotati(ListaEsami ptl);
void stampaSuperati(ListaEsami ptl);
float calcoloMediaAritmetica(ListaEsami ptl);
float calcoloMediaPonderata(ListaEsami ptl);
int calcoloTotaleCfu(ListaEsami ptl);
#endif
