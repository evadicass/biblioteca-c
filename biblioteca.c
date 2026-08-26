#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*****************************/
/********* STRUTTURE *********/
/*****************************/

typedef struct Libro {
	int id;
	char titolo[30];
	char autore[30];
	int pagine;
	int anno;
	char genere[30];
	char status;             // vale d se disponibile, p se prestato

} LIBRO;

typedef struct Nodo {
	LIBRO libro;
	struct Nodo *next;
} NODO;

/**************************************/
/*********** VISUALIZZAZIONE **********/
/**************************************/

void stampaLibro (LIBRO *libro) {
	printf("ID: %d\n", libro->id);
	printf("TITOLO: %s\n", libro->titolo);
	printf("AUTORE: %s\n", libro->autore);
	printf("Numero di pagine: %d\n", libro->pagine);
	printf("Anno di pubblicazione: %d\n", libro->anno);
	printf("Genere: %s\n", libro->genere);
	if(libro->status == 'd')
		printf("Disponibile!\n\n");
	else
		printf("Prestato!\n\n");
}

void stampaLista (NODO *head) {
	NODO *nodoCorrente = head;

	if(head==NULL)
		printf("Biblioteca vuota!\n\n");
	else {
		printf("Ecco la lista dei libri:\n\n");
		while(nodoCorrente != NULL) {
			stampaLibro(&(nodoCorrente->libro));
			nodoCorrente = nodoCorrente->next;
		}
	}
}

/**********************************************
 **************** INSERIMENTO *****************
 **********************************************/

void inserisciLibro(LIBRO *libro) {

	printf("Come si intitola il libro?  ");
	fgets(libro->titolo, 30, stdin);
	(libro->titolo)[strlen(libro->titolo)-1]='\0';

	printf("\nCome si chiama l'autore?  ");
	fgets(libro->autore, 30, stdin);
	(libro->autore)[strlen(libro->autore)-1]='\0';

	printf("\nQuante pagine ha?  ");
	scanf("%d%*c", &(libro->pagine));

	printf("\nQuando %c stato pubblicato?  ", 138);
	scanf("%d%*c", &(libro->anno));

	printf("\nChe genere tratta?  ");
	fgets(libro->genere, 30, stdin);
	(libro->genere)[strlen(libro->genere)-1]='\0';

	libro->status = 'd';
}

NODO *inserisciCoda (NODO *head, int *prossimo_id) {
	NODO *nuovoNodo = malloc(sizeof(NODO));

	if(nuovoNodo==NULL) {
		printf("Errore allocazione memoria!\n\n");
		return head;
	}

	inserisciLibro(&(nuovoNodo->libro));
	nuovoNodo->libro.id = *prossimo_id;
	(*prossimo_id)++;
	nuovoNodo->next = NULL;

	if(head==NULL)
		head=nuovoNodo;
	else {
		NODO *nodoCorrente = head;
		while(nodoCorrente->next != NULL)
			nodoCorrente = nodoCorrente->next;
		nodoCorrente->next = nuovoNodo;
	}

	printf("\nInserimento effettuato!\n\n");
	return head;
}

/**********************************************
 ************** CANCELLAZIONE *****************
 **********************************************/

NODO *cancellaLibro (NODO *head) {
	if(head==NULL) {
		printf("\nBiblioteca vuota: nessun libro da eliminare!\n\n");
		return head;
	}

	char libroDaCancellare[30];
	printf("Come si intitola il libro da eliminare?  ");
	fgets(libroDaCancellare, 30, stdin);
	libroDaCancellare[strlen(libroDaCancellare)-1]='\0';

	int eliminato = 0;

	/* il libro da eliminare è il primo */
	while(head != NULL && (strcmp(head->libro.titolo, libroDaCancellare)==0) && !eliminato) {
		NODO *temp = head;
		head = head->next;
		free(temp);
		eliminato=1;
		printf("\nCancellazione effettuata!\n\n");
	}

	/* il libro da eliminare è nel resto della lista */
	if(head != NULL) {
		NODO *nodoPrec = head;
		NODO *nodoCorr = head->next;

		while(nodoCorr != NULL && !eliminato) {
			if(strcmp(nodoCorr->libro.titolo, libroDaCancellare)==0) {
				nodoPrec->next = nodoCorr->next;
				free(nodoCorr);
				eliminato=1;
				printf("Cancellazione effettuata!\n\n");
			}
			else {
				nodoPrec = nodoCorr;
				nodoCorr = nodoCorr->next;
			}
		}
	}

	return head;
}

/**********************************************
 **************** RICERCA *********************
 **********************************************/

void cercaLibro (NODO *head) {
	NODO *nodoCorrente = head;
	int input = -1;
	int trovato = 0;

	if(head==NULL) {
		printf("\nBiblioteca vuota: nessun libro da cercare!\n\n");
		return;
	}

	while(input!=1 && input!=2 && input!=3 && input!=4 && input!=5 && input!=6) {
		printf("Come vuoi cercare?\nPremi (1) se per titolo\nPremi (2) se per autore\nPremi (3) se per ID\nPremi (4) se per anno\nPremi (5) se per genere\nPremi (6) se per disponibilit%c\n\n", 133);
		scanf("%d%*c", &input);
	}

	/* RICERCA PER TITOLO */
	if(input==1) {

		char titoloDaTrovare[30];
		printf("\nCome si intitola il libro da cercare?  ");
		fgets(titoloDaTrovare, 30, stdin);
		titoloDaTrovare[strlen(titoloDaTrovare)-1]='\0';

		while(nodoCorrente!=NULL && !trovato) {
			if(strcmp(nodoCorrente->libro.titolo, titoloDaTrovare)==0) {
				printf("\nLibro trovato!\n\n");
				stampaLibro(&(nodoCorrente->libro));
				trovato = 1;
			}
			else
				nodoCorrente = nodoCorrente->next;
		}

		if(trovato==0)
			printf("\nNessun libro con questo titolo trovato!\n\n");
	}

	/* RICERCA PER AUTORE */
	if(input==2) {

		char autoreDaTrovare[30];
		printf("\nDi quale autore cerchi il libro?  ");
		fgets(autoreDaTrovare, 30, stdin);
		autoreDaTrovare[strlen(autoreDaTrovare)-1]='\0';

		int quanti=0;

		while(nodoCorrente!=NULL) {
			if(strcmp(nodoCorrente->libro.autore, autoreDaTrovare)==0) {
				trovato = 1;
				quanti++;
			}

			nodoCorrente = nodoCorrente->next;
		}

		if(trovato==1) {
			if(quanti==1)
				printf("\n%c stato trovato un solo libro con questo autore:\n\n", 212);
			else
				printf("\nSono stati trovati in totale %d libri con questo autore:\n\n", quanti);

			NODO *nodoCorr = head;

			while(nodoCorr!=NULL) {
				if(strcmp(nodoCorr->libro.autore, autoreDaTrovare)==0)
					stampaLibro(&(nodoCorr->libro));

				nodoCorr = nodoCorr->next;
			}
		}
		else
			printf("\nNessun libro con questo autore trovato!\n\n");
	}

	/* RICERCA PER ID */
	if(input==3) {

		int idDaTrovare;
		printf("\nQual'%c l'ID di cui cerchi il libro?  ", 138);
		scanf("%d%*c", &idDaTrovare);

		while(nodoCorrente!=NULL && !trovato) {
			if(nodoCorrente->libro.id == idDaTrovare) {
				printf("\nEcco il libro con l'ID cercato:\n\n");
				stampaLibro(&(nodoCorrente->libro));
				trovato=1;
			}
			else
				nodoCorrente = nodoCorrente->next;
		}

		if(trovato==0)
			printf("\nNessun libro con questo ID trovato!\n\n");
	}

	/* RICERCA PER ANNO */
	if(input==4) {

		int annoDaTrovare;
		printf("\nDi quale anno cerchi il libro?  ");
		scanf("%d%*c", &annoDaTrovare);

		int quanti=0;

		while(nodoCorrente!=NULL) {
			if(nodoCorrente->libro.anno == annoDaTrovare) {
				trovato = 1;
				quanti++;
			}

			nodoCorrente = nodoCorrente->next;
		}

		if(trovato==1) {
			if(quanti==1)
				printf("\n%c stato trovato un solo libro di questo anno:\n\n", 212);
			else
				printf("\nSono stati trovati in totale %d libri di questo anno:\n\n", quanti);

			NODO *nodoCorr = head;

			while(nodoCorr!=NULL) {
				if(nodoCorr->libro.anno == annoDaTrovare)
					stampaLibro(&(nodoCorr->libro));

				nodoCorr = nodoCorr->next;
			}
		}
		else
			printf("\nNessun libro di questo anno trovato!\n\n");

	}

	/* RICERCA PER GENERE */
	if(input==5) {

		char genereDaTrovare[30];
		printf("\nDi quale genere cerchi il libro?  ");
		fgets(genereDaTrovare, 30, stdin);
		genereDaTrovare[strlen(genereDaTrovare)-1]='\0';

		int quanti=0;

		while(nodoCorrente!=NULL) {
			if(strcmp(nodoCorrente->libro.genere, genereDaTrovare)==0) {
				trovato = 1;
				quanti++;
			}

			nodoCorrente = nodoCorrente->next;
		}

		if(trovato==1) {
			if(quanti==1)
				printf("\n%c stato trovato un solo libro di questo genere:\n\n", 212);
			else
				printf("\nSono stati trovati in totale %d libri di questo genere:\n\n", quanti);

			NODO *nodoCorr = head;

			while(nodoCorr!=NULL) {
				if(strcmp(nodoCorr->libro.genere, genereDaTrovare)==0)
					stampaLibro(&(nodoCorr->libro));

				nodoCorr = nodoCorr->next;
			}
		}
		else
			printf("\nNessun libro di questo genere trovato!\n\n");
	}

	/* RICERCA PER DISPONIBILITA */
	if(input==6) {
		int quanti=0;

		while(nodoCorrente!=NULL) {
			if(nodoCorrente->libro.status == 'd') {
				trovato=1;
				quanti++;
			}

			nodoCorrente = nodoCorrente->next;
		}

		NODO *nodoCorr = head;

		if(trovato==1) {
			printf("\nLibri disponibili: %d\nEcco i titoli:\n\n", quanti);
			while(nodoCorr!=NULL) {
				if(nodoCorr->libro.status == 'd')
					printf("%s\n\n", nodoCorr->libro.titolo);

				nodoCorr = nodoCorr->next;
			}
		}
		else
			printf("\nNessun libro disponibile!\n\n");	
	}
}

/**********************************************
 ************* RICERCA SPECIFICA **************
 **********************************************/

NODO *cercaPerID (NODO *head, int valore) {
	NODO *nodoCorrente = head;
	int trovato=0;

	while(nodoCorrente!=NULL && !trovato) {
		if(nodoCorrente->libro.id == valore)
			trovato=1;
		else
			nodoCorrente = nodoCorrente->next;
	}

	return nodoCorrente;
}

NODO *cercaPerTitolo (NODO *head, char *nome) {
	NODO *nodoCorrente = head;
	int trovato=0;

	while(nodoCorrente!=NULL && !trovato) {
		if(strcmp(nodoCorrente->libro.titolo, nome)==0)
			trovato=1;
		else
			nodoCorrente = nodoCorrente->next;
	}

	return nodoCorrente;
}

/**********************************************
 ************** MODIFICA **********************
 **********************************************/

void modificaLibro(NODO *head) {
	NODO *nodoDaModificare;

	int risposta = -1;
	while(risposta!=0 && risposta!=1) {
		printf("\nVuoi cercare il libro per ID (0) o per titolo (1)?  ");
		scanf("%d%*c", &risposta);
	}

	if(risposta==0) {
		int idDaModificare;
		printf("\n\nQual'%c l'ID del libro di cui vuoi modificare i dati?  ", 138);
		scanf("%d%*c", &idDaModificare);

		nodoDaModificare = cercaPerID(head, idDaModificare);
		if(nodoDaModificare==NULL) {
			printf("\nNessun libro con questo ID trovato!\n\n");
			return;
		}
	}
	else {
		char titoloDaModificare[30];
		printf("\n\nQual'%c il titolo del libro di cui vuoi modificare i dati?  ", 138);
		fgets(titoloDaModificare, 30, stdin);
		titoloDaModificare[strlen(titoloDaModificare)-1]='\0';

		nodoDaModificare = cercaPerTitolo(head, titoloDaModificare);
		if(nodoDaModificare==NULL) {
			printf("\nNessun libro con questo titolo trovato!\n\n");
			return;
		}
	}

	int input = -1;
	while(input!=1 && input!=2 && input!=3 && input!=4 && input!=5) {
		printf("\nQuali dati vuoi modificare?\nPremi (1) se il titolo\nPremi (2) se l'autore\nPremi (3) se il numero di pagine\nPremi (4) se l'anno\nPremi (5) se il genere\n");
		scanf("%d%*c", &input);
	}

	if(input==1) {
		char nuovoTitolo[30];
		printf("Qual'%c il nuovo titolo?  ", 138);
		fgets(nuovoTitolo, 30, stdin);
		nuovoTitolo[strlen(nuovoTitolo)-1]='\0';

		strcpy(nodoDaModificare->libro.titolo, nuovoTitolo);
		printf("Modifica effettuata!\n\n");
	}

	if(input==2) {
		char nuovoAutore[30];
		printf("Qual%c il nuovo autore?  ", 138);
		fgets(nuovoAutore, 30, stdin);
		nuovoAutore[strlen(nuovoAutore)-1]='\0';

		strcpy(nodoDaModificare->libro.autore, nuovoAutore);
		printf("Modifica effettuata!\n\n");
	}

	if(input==3) {
		int nuovePagine;
		printf("Qual'%c il nuovo numero di pagine?  ", 138);
		scanf("%d%*c", &nuovePagine);

		nodoDaModificare->libro.pagine = nuovePagine;
		printf("Modifica effettuata!\n\n");
	}

	if(input==4) {
		int nuovoAnno;
		printf("Qual'%c il nuovo anno di pubblicazione?  ", 138);
		scanf("%d%*c", &nuovoAnno);

		nodoDaModificare->libro.anno = nuovoAnno;
		printf("Modifica effettuata!\n\n");
	}

	if(input==5) {
		char nuovoGenere[30];
		printf("Qual%c il nuovo genere?  ", 138);
		fgets(nuovoGenere, 30, stdin);
		nuovoGenere[strlen(nuovoGenere)-1]='\0';

		strcpy(nodoDaModificare->libro.genere, nuovoGenere);
		printf("Modifica effettuata!\n\n");
	}
}

/**********************************************
 *************** PRESTITO *********************
 **********************************************/

void prestaLibro (NODO *head) {
	NODO *nodoDaPrestare;

	int risposta = -1;
	while(risposta!=0 && risposta!=1) {
		printf("\nVuoi cercare il libro per ID (0) o per titolo (1)?  ");
		scanf("%d%*c", &risposta);
	}

	if(risposta==0) {
		int idDaPrestare;
		printf("\n\nQual'%c l'ID del libro che desidera?  ", 138);
		scanf("%d%*c", &idDaPrestare);

		nodoDaPrestare = cercaPerID(head, idDaPrestare);
		if(nodoDaPrestare==NULL) {
			printf("\nNessun libro con questo ID trovato!\n\n");
			return;
		}
	}
	else {
		char titolodaPrestare[30];
		printf("\n\nQual'%c il titolo del libro che desidera?  ", 138);
		fgets(titolodaPrestare, 30, stdin);
		titolodaPrestare[strlen(titolodaPrestare)-1]='\0';

		nodoDaPrestare = cercaPerTitolo(head, titolodaPrestare);
		if(nodoDaPrestare==NULL) {
			printf("\nNessun libro con questo titolo trovato!\n\n");
			return;
		}
	}

	if(nodoDaPrestare->libro.status == 'd') {
		printf("\nIl libro %c disponibile!\n", 138);
		nodoDaPrestare->libro.status = 'p';
		printf("Prestito effettuato!\n\n");
	}
	else
		printf("\nIl libro non %c disponibile!\n\n", 138);
}

/**********************************************
 *************** RESTITUZIONE *****************
 **********************************************/

void restituisciLibro (NODO *head) {
	NODO *nodoDaRestituire;

	int risposta = -1;
	while(risposta!=0 && risposta!=1) {
		printf("\nVuoi cercare il libro per ID (0) o per titolo (1)?  ");
		scanf("%d%*c", &risposta);
	}


	if(risposta==0) {
		int idDaRestituire;
		printf("\n\nQual'%c l'ID del libro che desidera?  ", 138);
		scanf("%d%*c", &idDaRestituire);

		nodoDaRestituire = cercaPerID(head, idDaRestituire);
		if(nodoDaRestituire==NULL) {
			printf("\nNessun libro con questo ID trovato!\n\n");
			return;
		}
	}
	else {
		char titolodaRestituire[30];
		printf("\n\nQual'%c il titolo del libro che desidera?  ", 138);
		fgets(titolodaRestituire, 30, stdin);
		titolodaRestituire[strlen(titolodaRestituire)-1]='\0';

		nodoDaRestituire = cercaPerTitolo(head, titolodaRestituire);
		if(nodoDaRestituire==NULL) {
			printf("\nNessun libro con questo titolo trovato!\n\n");
			return;
		}
	}

	if(nodoDaRestituire->libro.status == 'p') {
		nodoDaRestituire->libro.status = 'd';
		printf("\nRestituzione effettuata!\n\n");
	}
	else 
		printf("\nIl libro con questo ID %c gi%c presente!\n\n", 138, 133);
}

/**********************************************
 *************** STATISTICHE ******************
 **********************************************/

void statistiche(NODO *head) {

	if(head==NULL) {
		printf("\nBiblioteca vuota!\n\n");
		return;
	}

	int quantiLibri=0;
	int quantiDisponibili=0;
	int quantiPrestati=0;
	int sommaPagine=0;
	int sommaAnni=0;

	NODO *nodoCorrente = head;
	
	NODO *libroPiuVecchio = head;
	NODO *libroPiuRecente = head;

	while(nodoCorrente!=NULL) {
		quantiLibri++;

		if(nodoCorrente->libro.status == 'd')
			quantiDisponibili++;
		else
			quantiPrestati++;

		sommaPagine += nodoCorrente->libro.pagine;
		sommaAnni += nodoCorrente->libro.anno;

		if(nodoCorrente->libro.anno < libroPiuVecchio->libro.anno)
			libroPiuVecchio = nodoCorrente;

		if(nodoCorrente->libro.anno > libroPiuRecente->libro.anno)
			libroPiuRecente = nodoCorrente;

		nodoCorrente = nodoCorrente->next;
	}

	printf("\nSTATISTICHE:\n\n");

	printf("LIBRI TOTALI: %d\n", quantiLibri);
	printf("DISPONIBILI: %d\n", quantiDisponibili);
	printf("PRESTATI: %d\n", quantiPrestati);
	double percentuale = ((double)quantiPrestati/quantiLibri)*100.0;
	printf("PERCENTUALE LIBRI PRESTATI: %.2f%%\n\n", percentuale);

	printf("MEDIA DELLE PAGINE: %d\n", sommaPagine/quantiLibri);
	printf("ANNO MEDIO: %d\n\n", sommaAnni/quantiLibri);

	printf("LIBRO PI%c VECCHIO: %s, %d\n", 235, libroPiuVecchio->libro.titolo, libroPiuVecchio->libro.anno);
	printf("LIBRO PI%c RECENTE: %s, %d\n", 235, libroPiuRecente->libro.titolo, libroPiuRecente->libro.anno);
}

/**********************************************
 **************** FILE ************************
 **********************************************/

NODO *acquisizione (NODO *head, int *prossimo_id) {
	FILE *fp = fopen("biblioteca.txt", "r");

	if(fp==NULL)
		printf("File vuoto!\n\n");
	else {

		int id;
		char titolo[30];
		char autore[30];
		int pagine;
		int anno;
		char genere[30];
		char status;

		int massimo_id=0;

		while(fscanf(fp, "%d%*c%[^\t]%*c%[^\t]%*c%d%*c%d%*c%[^\t]%*c%c%*c", &id, titolo, autore, &pagine, &anno, genere, &status)==7) {

				NODO *nuovoNodo = malloc(sizeof(NODO));
				if(nuovoNodo==NULL) {
					printf("Acquisizione non andata a buon fine!\n\n");
					return head;
				}

				nuovoNodo->libro.id=id;
				if(nuovoNodo->libro.id > massimo_id)
					massimo_id = nuovoNodo->libro.id;

				strcpy(nuovoNodo->libro.titolo, titolo);
				strcpy(nuovoNodo->libro.autore, autore);
				nuovoNodo->libro.pagine=pagine;
				nuovoNodo->libro.anno=anno;
				strcpy(nuovoNodo->libro.genere, genere);
				nuovoNodo->libro.status=status;

				nuovoNodo->next = NULL;

				/* inserimento in coda */
				if(head==NULL)
					head=nuovoNodo;
				else {
					NODO *nodoCorr = head;
					while(nodoCorr->next != NULL)
						nodoCorr = nodoCorr->next;
					nodoCorr->next = nuovoNodo;
				}
		}
		*prossimo_id = massimo_id+1;

		fclose(fp);
		printf("Acquisizione riuscita!\n\n");
	}

	return head;
}

void salvataggio (NODO *head) {
	NODO *nodo = head;
	FILE * fp = fopen("biblioteca.txt", "w");

	if(fp==NULL)
		printf("Errore salvataggio file!\n\n");
	else {
		while(nodo != NULL) {
			fprintf(fp, "%d\t%s\t%s\t%d\t%d\t%s\t%c\n", nodo->libro.id, nodo->libro.titolo, nodo->libro.autore, nodo->libro.pagine, nodo->libro.anno, nodo->libro.genere, nodo->libro.status);
			nodo = nodo->next; 
		}

		fclose(fp);
		printf("Salvataggio riuscito!\n\n");
	}
}


/**********************************************
 ************ FUNZIONE PRINCIPALE ************
 **********************************************/

int main() {
	NODO *head = NULL;
	int risposta = -1;
	int input = -1;

	int prossimo_id = 1;

	printf("Vuoi caricare la lista da un file (1) o digitarla te (0)?  ");
	scanf("%d%*c", &input);
	
	if(input==1)
		head=acquisizione(head, &prossimo_id);
	else
		printf("Lista vuota!\n\n");

	while(risposta != 0) {
		printf("Che operazione vuoi effettuare?\n");
		printf("1: Visualizzazione\n");
		printf("2: Inserimento\n");
		printf("3: Cancellazione\n");
		printf("4: Ricerca\n");
		printf("5: Modifica\n");
		printf("6: Prestito\n");
		printf("7: Restituzione\n");
		printf("8: Statistiche\n");
		printf("0: Termina il programma\n\n");
		scanf("%d%*c", &risposta);

		if(risposta==1)
			stampaLista(head);
		else if(risposta==2)
			head=inserisciCoda(head, &prossimo_id);
		else if(risposta==3)
			head=cancellaLibro(head);
		else if(risposta==4)
			cercaLibro(head);
		else if(risposta==5)
			modificaLibro(head);
		else if(risposta==6)
			prestaLibro(head);
		else if(risposta==7)
			restituisciLibro(head);
		else if(risposta==8)
			statistiche(head);
		else if(risposta==0) {
			printf("Finito!\n\n");
			salvataggio(head);
		}
		else
			printf("Selezione non valida!\n\n");

	}
}

