#ifndef MAIN_H
#define MAIN_H
#include "lista_studenti.h"


void registra_studente(ListaStudenti lista);
void login_studente(ListaStudenti lista);
void visualizza_studenti(ListaStudenti lista);
int menu_principale();

void menuStudente(Studente pts);
void menuGestioneEsami(Studente pts);

void pulisci_buffer();
void leggi_stringa(char *dest, int dim, const char *msg);
#endif
