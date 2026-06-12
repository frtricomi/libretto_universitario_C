# libretto universitario in C 
Questo progetto consiste in un sistema di gestione di un libretto universitario simulato, sviluppato in linguaggio C. Il focus principale del progetto è l'utilizzo e l'implementazione di strutture dati astratte (Abstract Data Types - ADT o moduli).

Gestione Studenti: Implementazione dell'ADT 'studente' e della relativa lista dinamica per la gestione dei dati anagrafici.
Gestione Esami: Implementazione dell'ADT 'esame' e 'lista_esami' per tracciare i nomi della materia, voti e i crediti (CFU) acquisiti.

inoltre il codice è fortemente suddiviso tra interfacce (file '.h') e implementazioni (file '.c') per garantire semplici modifiche.

Il progetto è strutturato nei seguenti moduli:
-'studente': Gestisce le informazioni del singolo studente.
-'esame': Gestisce i dettagli del singolo esame superato.
-'lista_studenti' e 'lista_esami': Gestiscono le collezioni dinamiche dei dati sotto il cofano.

Nonostante siano previste funzioni di registrazione utente e login NON è implementata alcuna logica di salvataggio o caricamento da file. Il progetto è anche previsto di un cruscotto in cui vengono calcolati dati del tipo medie e cfu totali conseguiti ognuno personale per ogni singolo studente

Il progetto include uno script di compilazione automatica. Per avviarlo su sistemi Unix/macOS:
1. Apri il terminale nella cartella del progetto.
2. Dai i permessi di esecuzione allo script (se necessario):
   chmod +x make.sh
   ./make.sh

   o in alternativa
   bash make.sh

   dopo di che runnare ./main

   
