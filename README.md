# Biblioteca in C

Progetto personale sviluppato per esercitarmi con il linguaggio C, le liste concatenate e la gestione dei file.

## Descrizione

Il programma si occupa di gestire una biblioteca, permettendo di inserire ed eliminare libri caratterizzati dal numero ID inserito automaticamente, il titolo, il nome dell'autore, il numero di pagine, l'anno di pubblicazione, il genere e lo status.

## Funzionalità attuali

- Visualizzazione dei libri
- Inserimento di libri
- Eliminazione di libri
- Assegnazione automatica di ID univoci
- Salvataggio dei dati su file
- Caricamento dei dati da file

## Strutture e concetti utilizzati

- Struct
- Liste concatenate
- Puntatori
- Allocazione dinamica della memoria
- Gestione dei file

## Sviluppi futuri

- Ricerca di libri
- Gestione dei prestiti
- Statistiche

## Come compilare ed eseguire il codice

Per far funzionare questo progetto hai bisogno di un compilatore C (come GCC o Clang) installato nel tuo sistema.

**1. Compilazione**
Apri il terminale, spostati nella cartella in cui hai salvato il progetto e compila il file `biblioteca.c` eseguendo:

```bash
gcc -o biblioteca.c biblioteca
```

**2. Esecuzione**
Una volta terminata la compilazione senza errori, avvia il programma dal terminale:

* **Su Mac/Linux:** `./biblioteca`
* **Su Windows:** `biblioteca.exe`