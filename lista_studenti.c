#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista_studenti.h"
#include "studente.h"

struct nodo_studente{
	Studente pts;
	struct nodo_studente *next;
};

struct lista_studenti{
	struct nodo_studente *head;
};

ListaStudenti creaListaStudenti(){
	ListaStudenti lista = (ListaStudenti) malloc(sizeof(struct lista_studenti));
	if (lista == NULL) return NULL;
	lista->head = NULL;
	return lista;
}

void liberaListaStudenti(ListaStudenti lista){
	if (lista == NULL) return;
	struct nodo_studente *nCorrente = lista->head;
	while (nCorrente != NULL){
		struct nodo_studente *nTemporaneo = nCorrente;
		nCorrente = nCorrente->next;
		liberaStudente(nTemporaneo->pts);
		free(nTemporaneo);
	}
	free(lista);
}

int inserisciStudente(ListaStudenti lista, Studente pts){
	if (lista == NULL || pts == NULL) return 1;
	struct nodo_studente *nuovo = (struct nodo_studente*) malloc(sizeof(struct nodo_studente));
	if (nuovo == NULL) return 1;
	nuovo->pts = pts;
	nuovo->next = NULL;

	if (lista->head != NULL && strcmp(getUsername(lista->head->pts), getUsername(pts)) == 0){
		free(nuovo);
		return -1;
        }
	if (lista->head == NULL || strcmp(getUsername(lista->head->pts), getUsername(pts)) > 0){
		nuovo->next = lista->head;
		lista->head = nuovo;
		return 0;
	}
	struct nodo_studente *nCorrente = lista->head;
	while (nCorrente->next != NULL && strcmp(getUsername(nCorrente->next->pts), getUsername(pts)) < 0){
		nCorrente = nCorrente->next;
	}
	if (nCorrente->next != NULL && strcmp(getUsername(nCorrente->next->pts), getUsername(pts)) == 0){
		free(nuovo);
		return -1;
	}
	nuovo->next = nCorrente->next;
	nCorrente->next = nuovo;
	return 0;
}

Studente cercaPerUsername(ListaStudenti lista, const char *username){
	if (lista == NULL || username == NULL) return NULL;
	struct nodo_studente *nCorrente = lista->head;
	while (nCorrente != NULL){
		if (strcmp(getUsername(nCorrente->pts), username) == 0){
			return nCorrente->pts;
		}
		nCorrente = nCorrente->next;
	}
	return NULL;
}

void stampaTuttiStudenti(ListaStudenti lista){
	if (lista == NULL) return;
	struct nodo_studente *nCorrente = lista->head;
	while (nCorrente != NULL){
		stampaStudente(nCorrente->pts);
		printf("--------------------------\n");
		nCorrente = nCorrente->next;
	}
}
