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
		printf("File vuoto!\n\n");
	else {
		printf("Ecco la lista:\n\n");
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

	char libroDaCancellare[30];
	printf("Come si intitola il libro da eliminare?  ");
	fgets(libroDaCancellare, 30, stdin);
	libroDaCancellare[strlen(libroDaCancellare)-1]='\0';

	int eliminato = 0;

	if(head==NULL)
		printf("\nLista vuota: nessun libro da eliminare!\n\n");
	else {
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
	}

	return head;
}

/**********************************************
 ***************** RICERCA ********************
 **********************************************/

void esisteLibro (NODO *head) {
	NODO *nodoCorrente = head;
	int trovato = 0;
	int input = -1;

	while(input!=1 && input!=2 && input!=3 && input!=4 && input!=5) {
		printf("Come vuoi cercare?\nPremi (1) se per titolo\nPremi (2) se per autore\nPremi (3) se per ID\nPremi (4) se per anno\nPremi (5) se per genere\n");
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
				nodoCorrente = nodoCorrente->next;
			}
			else
				nodoCorrente = nodoCorrente->next;
		}

		if(trovato==1) {
			if(quanti==1)
				printf("\n%c stato trovato un solo libro con questo autore:\n\n", 212);
			else
				printf("\nSono stati trovati in totale %d libri con questo autore:\n\n", quanti);

			NODO *nodoCorr = head;

			while(nodoCorr!=NULL) {
				if(strcmp(nodoCorr->libro.autore, autoreDaTrovare)==0) {
					stampaLibro(&(nodoCorr->libro));
					nodoCorr = nodoCorr->next;
				}
				else
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
				nodoCorrente = nodoCorrente->next;
			}
			else
				nodoCorrente = nodoCorrente->next;
		}

		if(trovato==1) {
			if(quanti==1)
				printf("\n%c stato trovato un solo libro di questo anno:\n\n", 212);
			else
				printf("\nSono stati trovati in totale %d libri di questo anno:\n\n", quanti);

			NODO *nodoCorr = head;

			while(nodoCorr!=NULL) {
				if(nodoCorr->libro.anno == annoDaTrovare) {
					stampaLibro(&(nodoCorr->libro));
					nodoCorr = nodoCorr->next;
				}
				else
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
				nodoCorrente = nodoCorrente->next;
			}
			else
				nodoCorrente = nodoCorrente->next;
		}

		if(trovato==1) {
			if(quanti==1)
				printf("\n%c stato trovato un solo libro di questo genere:\n\n", 212);
			else
				printf("\nSono stati trovati in totale %d libri di questo genere:\n\n", quanti);

			NODO *nodoCorr = head;

			while(nodoCorr!=NULL) {
				if(strcmp(nodoCorr->libro.genere, genereDaTrovare)==0) {
					stampaLibro(&(nodoCorr->libro));
					nodoCorr = nodoCorr->next;
				}
				else
					nodoCorr = nodoCorr->next;
			}
		}
		else
			printf("\nNessun libro di questo genere trovato!\n\n");
	}
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

		while(fscanf(fp, "%d%*c%[^\t]%*c%[^\t]%*c%d%*c%d%*c%[^\t]%*c%c%*c", &id, titolo, autore, &pagine, &anno, genere, &status)>0) {

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
	scanf("%d", &input);
	
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
		printf("0: Termina il programma\n\n");
		scanf("%d%*c", &risposta);

		if(risposta==1)
			stampaLista(head);
		else if(risposta==2)
			head=inserisciCoda(head, &prossimo_id);
		else if(risposta==3)
			head=cancellaLibro(head);
		else if(risposta==4)
			esisteLibro(head);
		else if(risposta==0) {
			printf("Finito!\n\n");
			salvataggio(head);
		}
		else
			printf("Selezione non valida!\n\n");

	}
}

