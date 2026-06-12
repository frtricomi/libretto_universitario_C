#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_esami.h"
#include "esame.h"

struct nodo_esame{
	Esame pte;
	struct nodo_esame *next;
};

struct lista_esami{
	struct nodo_esame *head;
};


ListaEsami creaListaEsami(){
	ListaEsami ptl = (ListaEsami) malloc(sizeof(struct lista_esami));
	if (ptl == NULL) return NULL;
	ptl->head = NULL;
	return ptl;
}

void liberaListaEsami(ListaEsami ptl){
	if (ptl == NULL) return;
	struct nodo_esame *nCorrente = ptl->head;
	while (nCorrente != NULL){
		struct nodo_esame *nTemporaneo = nCorrente;
		nCorrente = nCorrente->next;
		liberaEsame(nTemporaneo->pte);
		free(nTemporaneo);
	}
	free(ptl);
}

int inserisciEsameInOrdine(ListaEsami ptl, Esame pte){
	if (ptl == NULL || pte == NULL) return 1;
	struct nodo_esame *nuovo = (struct nodo_esame*) malloc(sizeof(struct nodo_esame));
	if (nuovo == NULL) return 1;
	nuovo->pte = pte;
	nuovo->next = NULL;

	if (ptl->head == NULL || strcmp(getNomeEsame(ptl->head->pte), getNomeEsame(pte)) > 0){
		nuovo->next = ptl->head;
		ptl->head = nuovo;
		return 0;
	}

	struct nodo_esame *nCorrente = ptl->head;
	while (nCorrente->next != NULL && strcmp(getNomeEsame(nCorrente->next->pte), getNomeEsame(pte)) < 0){
		nCorrente = nCorrente->next;
	}

	nuovo->next = nCorrente->next;
	nCorrente->next = nuovo;
	return 0;
}

int rimuoviEsame(ListaEsami ptl, const char *nomeMateria){
	if (ptl == NULL || nomeMateria == NULL) return 1;

	struct nodo_esame *nCorrente = ptl->head;
	struct nodo_esame *nPrecedente = NULL;

	while (nCorrente != NULL){
		if (strcmp(getNomeEsame(nCorrente->pte), nomeMateria) == 0){
			if (nPrecedente == NULL){
				ptl->head = nCorrente->next;
			} else{
				nPrecedente->next = nCorrente->next;
			}
			free(nCorrente);
			return 0;
		}
		nPrecedente = nCorrente;
		nCorrente = nCorrente->next;
    	}
	return 1;
}

Esame cercaEsamePerNome(ListaEsami ptl, const char *nomeMateria){
	if (ptl == NULL || nomeMateria == NULL) return NULL;
	struct nodo_esame *nCorrente = ptl->head;
	while (nCorrente != NULL){
		if (strcmp(getNomeEsame(nCorrente->pte), nomeMateria) == 0){
			return nCorrente->pte;
		}
		nCorrente = nCorrente->next;
	}
	return NULL;
}

void stampaPrenotati(ListaEsami ptl){
	if (ptl == NULL) return;
	struct nodo_esame *nCorrente = ptl->head;
	while (nCorrente != NULL){
		if (getVotoEsame(nCorrente->pte) == -1){
			stampaEsame(nCorrente->pte);
		}
		nCorrente = nCorrente->next;
	}
}

void stampaSuperati(ListaEsami ptl){
	if (ptl == NULL) return;
	struct nodo_esame *nCorrente = ptl->head;
	while (nCorrente != NULL){
		if (getVotoEsame(nCorrente->pte) >= 18){
			stampaEsame(nCorrente->pte);
		}
		nCorrente = nCorrente->next;
	}
}

float calcoloMediaAritmetica(ListaEsami ptl){
	if (ptl == NULL) return 0.0f;
	int somma = 0;
	int count = 0;
	struct nodo_esame *nCorrente = ptl->head;
	while (nCorrente != NULL){
		int voto = getVotoEsame(nCorrente->pte);
		if (voto >= 18){
			somma += voto;
			count++;
		}
		nCorrente = nCorrente->next;
	}
	return (count > 0) ? ((float)somma / count) : 0.0f;
}

float calcoloMediaPonderata(ListaEsami ptl){
	if (ptl == NULL) return 0.0f;
	int sommaPonderata = 0;
	int totCfu = 0;
	struct nodo_esame *nCorrente = ptl->head;
	while (nCorrente != NULL){
		int voto = getVotoEsame(nCorrente->pte);
		if (voto >= 18){
			int cfu = getCfuEsame(nCorrente->pte);
			sommaPonderata += voto * cfu;
			totCfu += cfu;
		}
		nCorrente = nCorrente->next;
	}
	return (totCfu > 0) ? ((float)sommaPonderata / totCfu) : 0.0f;
}

int calcoloTotaleCfu(ListaEsami ptl){
	if (ptl == NULL) return -1;
	int tot = 0;
	struct nodo_esame *nCorrente = ptl->head;
	while (nCorrente != NULL){
		int voto = getVotoEsame(nCorrente->pte);
		if (voto >= 18) tot += getCfuEsame(nCorrente->pte);
		nCorrente = nCorrente->next;
	}
	return tot;
}

Esame getPrimoEsame(ListaEsami lista){
	if (lista == NULL || lista->head == NULL) return NULL;
	return lista->head->pte;
}

Esame getEsameSuccessivo(ListaEsami lista, Esame pte){
	if (lista == NULL || pte == NULL) return NULL;
	struct nodo_esame *n = lista->head;
	while (n != NULL){
		if (n->pte == pte){
			if (n->next != NULL){
				return n->next->pte;
			} else{
 				return NULL;
			}
		}
		n = n->next;
	}
	return NULL;
}
