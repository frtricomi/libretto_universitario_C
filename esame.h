#ifndef ESAME_H
#define ESAME_H

typedef struct esame *Esame;

Esame creaEsame(const char nome[50], int cfu);
void liberaEsame(Esame pte);
const char *getNomeEsame(Esame pte);
int getCfuEsame(Esame pte);
int getVotoEsame(Esame pte);
void inserisciVotoEsame(Esame pte, int voto);
int modificaNomeMateria(Esame pte, const char nuovoNome[50]);
int modificaCfuEsame(Esame pte, int nuovoCfu);
void stampaEsame(Esame pte);
#endif
