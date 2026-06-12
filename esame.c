#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esame.h"

struct esame{
	char nome[50];
	int cfu;
	int voto;
};

Esame creaEsame(const char nome[50], int cfu){
	Esame pte = (Esame)malloc(sizeof(struct esame));
	if (pte == NULL) return NULL;
	strncpy(pte->nome, nome, 49);
	pte->nome[49] = '\0';
	pte->cfu = cfu;
	pte->voto = -1;
	return pte;
}

void liberaEsame(Esame pte){
	if (pte != NULL) free(pte);
}

const char *getNomeEsame(Esame pte){
	if (pte == NULL) return NULL;
	return pte->nome;
}

int getCfuEsame(Esame pte){
	if (pte == NULL) return 1;
	return pte->cfu;
}

int getVotoEsame(Esame pte){
	if (pte == NULL) return -2;
	return pte->voto;
}

void inserisciVotoEsame(Esame pte, int voto){
	if (pte != NULL){
		if ((voto >= 0 && voto <= 31) || voto == -1){
            		pte->voto = voto;
        	}
    	}
}


int modificaNomeMateria(Esame pte, const char nuovoNome[50]){
	if (pte == NULL) return 1;
	strncpy(pte->nome, nuovoNome, 49);
	pte->nome[49] = '\0';
	return 0;
}

int modificaCfuEsame(Esame pte, int nuovoCfu){
	if (pte == NULL) return 1;
	pte->cfu = nuovoCfu;
	return 0;
}

void stampaEsame(Esame pte){
	if (pte == NULL) return;
	printf("Materia: %s | CFU: %d | ", pte->nome, pte->cfu);
	if (pte->voto == -1){
		printf("Stato: Prenotato\n");
	} else if (pte->voto < 18){
		printf("Stato: Bocciato\n");
	} else{
		printf("Voto: %d\n", pte->voto);
	}
}
