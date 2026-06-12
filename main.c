#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"


void pulisci_buffer(){
	char ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

void leggi_stringa(char *dest, int dim, const char *msg){
	printf("%s", msg);
	fgets(dest, dim, stdin);
	dest[strcspn(dest, "\n")] = '\0';
}

int menu_principale(){
	int scelta;
	printf("\n___Benvenuto in GestUni___\n");
	printf("1. Registrazione\n");
	printf("2. Login\n");
	printf("3. Visualizza studenti iscritti\n");
	printf("4. Esci\n");
	printf("Scelta: ");
	scanf("%d", &scelta);
	return scelta;
}

void registra_studente(ListaStudenti lista){
	char nome[50], cognome[50], username[50], password[50];

	pulisci_buffer();
	leggi_stringa(nome, sizeof(nome), "Inserisci nome: ");
	leggi_stringa(cognome, sizeof(cognome), "Inserisci cognome: ");
	leggi_stringa(username, sizeof(username), "Inserisci username: ");
	leggi_stringa(password, sizeof(password), "Inserisci password: ");

	Studente pts = creaStudente(nome, cognome, username, password);
	if (pts != NULL){
		int esito = inserisciStudente(lista, pts);
		if (esito == 0){
			printf("Registrazione completata. Matricola: %d\n", getMatricola(pts));
		} else if (esito == -1){
			printf("Impossibile registrarsi: username gia' presente, riprovare con un altro.\n");
			liberaStudente(pts);
		} else{
			printf("Errore: Registrazione fallita.\n");
			liberaStudente(pts);
		}
	} else{
		printf("Errore: Creazione studente fallita\n");
        }
}

void login_studente(ListaStudenti lista){
	char username[50], password[50];

	pulisci_buffer();
	leggi_stringa(username, sizeof(username), "Username: ");
	leggi_stringa(password, sizeof(password), "Password: ");

	Studente pts = cercaPerUsername(lista, username);
	if (pts != NULL && strcmp(getPassword(pts), password) == 0){
		printf("Login effettuato con successo!\n");
		menuStudente(pts);
	} else{
		printf("Credenziali errate.\n");
	}
}

void visualizza_studenti(ListaStudenti lista){
	printf("\n=== Studenti iscritti ===\n");
	stampaTuttiStudenti(lista);
}

void menuStudente(Studente pts){
	int scelta;
	do{
		printf("\n=== Menu Studente ===\n");
		printf("1. Gestione esami\n");
		printf("2. Visualizza libretto\n");
		printf("3. Cruscotto\n");
		printf("4. Logout\n");
		printf("Scelta: ");
		scanf("%d", &scelta);
		pulisci_buffer();

		switch (scelta){
			case 1:
				menuGestioneEsami(pts);
				break;
			case 2:
				printf("\n=== Libretto ===\n");
				stampaSuperati(getSuperati(pts));
				break;
			case 3:{
				printf("\n=== Cruscotto ===\n");
				int cfuTot = calcoloTotaleCfu(getSuperati(pts));
				float mediaArit = calcoloMediaAritmetica(getSuperati(pts));
				float mediaPond = calcoloMediaPonderata(getSuperati(pts));
				printf("CFU Totali: %d/180\n", cfuTot);
				printf("Media aritmetica: %.2f\n", mediaArit);
				printf("Media ponderata: %.2f\n", mediaPond);
				break;
			}
			case 4:
				printf("Logout eseguito.\n");
				break;
			default:
				printf("Scelta non valida.\n");
		}
	} while (scelta != 4);
}

void menuGestioneEsami(Studente pts){
	int scelta;
	do{
		printf("\n=== Gestione Esami ===\n");
		printf("1. Prenota esame\n");
		printf("2. Visualizza/modifica esami prenotati\n");
		printf("3. Annulla prenotazione\n");
		printf("4. Inserisci voto esame sostenuto\n");
		printf("5. Torna al menu principale\n");
		printf("Scelta: ");
		scanf("%d", &scelta);
		pulisci_buffer();

		switch (scelta){
			case 1:{
				char nome[50];
				int cfu;
				leggi_stringa(nome, sizeof(nome), "Nome materia: ");
				printf("CFU: ");
				scanf("%d", &cfu);
				pulisci_buffer();
				Esame pte = creaEsame(nome, cfu);
				if (pte != NULL){
					if (cercaEsamePerNome(getSuperati(pts), nome) != NULL){
						printf("Impossibile prenotare: esame già superato.\n");
						liberaEsame(pte);
					} else if (cercaEsamePerNome(getPrenotati(pts), nome) != NULL) {
						printf("Impossibile prenotare: esame già prenotato.\n");
						liberaEsame(pte);
					} else{
						int esito = inserisciEsameInOrdine(getPrenotati(pts), pte);
						if (esito == 0){
							printf("Esame %s prenotato con successo!\n", nome);
						} else{
							printf("Errore: prenotazione fallita.\n");
							liberaEsame(pte);
						}
					}
				} else {
					printf("Errore: creazione esame fallita.\n");
				}
				break;
			}
			case 2:{
				printf("\n=== Esami Prenotati ===\n");
				stampaPrenotati(getPrenotati(pts));
				char nome[50];
				leggi_stringa(nome, sizeof(nome), "Vuoi modificare un esame? Inserisci nome materia (oppure 'no'): ");
				if (strcmp(nome, "no") != 0){
					Esame pte = cercaEsamePerNome(getPrenotati(pts), nome);
					if (pte != NULL){
						int nuovaScelta;
						printf("1. Modifica nome\n2. Modifica CFU\nScelta: ");
						scanf("%d", &nuovaScelta);
						pulisci_buffer();
						if (nuovaScelta == 1){
							char nuovoNome[50];
							leggi_stringa(nuovoNome, sizeof(nuovoNome), "Nuovo nome: ");
							modificaNomeMateria(pte, nuovoNome);
						} else if (nuovaScelta == 2){
							int nuovoCfu;
							printf("Nuovo CFU: ");
							scanf("%d", &nuovoCfu);
							pulisci_buffer();
							modificaCfuEsame(pte, nuovoCfu);
						}
					} else{
						printf("Esame non trovato.\n");
					}
				}
				break;
			}
			case 3:{
				char nome[50];
				leggi_stringa(nome, sizeof(nome), "Inserisci nome esame da annullare: ");
				nome[strcspn(nome, "\n")] = '\0';
				Esame pte = cercaEsamePerNome(getPrenotati(pts), nome);
				if (pte != NULL && rimuoviEsame(getPrenotati(pts), nome) == 0){
					liberaEsame(pte);
					printf("Prenotazione annullata.\n");
				} else{
					printf("Esame non trovato.\n");
				}
				break;
			}
			case 4:{
				char nome[50];
				leggi_stringa(nome, sizeof(nome), "Inserisci nome esame da sostenere: ");
				Esame pte = cercaEsamePerNome(getPrenotati(pts), nome);
				if (pte != NULL){
					int voto;
					printf("Inserisci voto (0-30, 31 per 30L): ");
					scanf("%d", &voto);
					pulisci_buffer();
					if (voto > 0 && voto <18){
						rimuoviEsame(getPrenotati(pts), nome);
						printf("Esame %s: bocciato.\n", nome);
					} else if (voto < 0 || voto > 31){
						printf("Voto inserito non valido. Riprovare!\n");
					} else{
						inserisciVotoEsame(pte, voto);
						rimuoviEsame(getPrenotati(pts), nome);
						aggiungiEsameSuperato(pts, pte);
						printf("Esame %s superato con voto %d.\n", nome, voto);
					}
				} else{
					printf("Esame non trovato nei prenotati.\n");
				}
				break;
			}
			case 5:
				printf("Ritorno al menu principale...\n");
				break;
			default:
				printf("Scelta non valida.\n");
		}
	} while (scelta != 5);
}

int main(){
	ListaStudenti lista = creaListaStudenti();
	if (lista == NULL){
		printf("Errore creazione lista studenti.\n");
		return 1;
	}
	int scelta;
	do{
		scelta = menu_principale();

		switch (scelta){
			case 1:
				registra_studente(lista);
				break;
			case 2:
				login_studente(lista);
				break;
			case 3:
				visualizza_studenti(lista);
				break;
			case 4:
			printf("Uscita dal programma...\n");
			break;
			default:
			printf("Scelta non valida.\n");
		}

	} while (scelta != 4);

	liberaListaStudenti(lista);
	return 0;
}
