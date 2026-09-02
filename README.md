# Biblioteca in C

Progetto personale sviluppato per esercitarmi con il linguaggio C, le liste concatenate e la gestione dei file.

## Descrizione

Il programma si occupa di gestire una biblioteca, permettendo di inserire ed eliminare libri caratterizzati dal numero ID inserito automaticamente, il titolo, il nome dell'autore, il numero di pagine, l'anno di pubblicazione, il genere e lo status.

## Funzionalità attuali

Il programma permette di:

- Visualizzazione tutti i libri presenti nella biblioteca
- Inserire nuovi libri
- Assegnare automaticamente ID univoci
- Cancellare un libro tramite il titolo
- Cercare libri tramite:
	- Titolo
	- Autore
	- ID
	- Anno di Pubblicazione
	- Genere
	- Disponibilità
- Modificare i dati di un libro tramite ID o titolo
- Effettuare il prestito di un libro tramite ID o titolo
- Registrare la restituzione di un libro tramite ID o titolo
- Analizzare statistiche sui vari dati della biblioteca
- Salvare i dati della biblioteca su file
- Caricare automaticamente i dati da file all'avvio del programma

## Strutture e concetti utilizzati

- Struct
- Liste concatenate
- Puntatori
- Allocazione dinamica della memoria
- Gestione dei file

## Come compilare ed eseguire il codice

Per far funzionare questo progetto hai bisogno di un compilatore C (come GCC o Clang) installato nel tuo sistema.

**1. Compilazione**
Apri il terminale, spostati nella cartella in cui hai salvato il progetto e compila il file `biblioteca.c` eseguendo:

```bash
gcc -o biblioteca biblioteca.c
```

**2. Esecuzione**
Una volta terminata la compilazione senza errori, avvia il programma dal terminale:

* **Su Mac/Linux:** `./biblioteca`
* **Su Windows:** `biblioteca.exe`
