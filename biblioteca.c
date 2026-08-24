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
	char d;             // d vale d se disponibile, p se prestato

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
	if(libro->d == 'd')
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

	libro->d = 'd';
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
		char d;

		int massimo_id=0;

		while(fscanf(fp, "%d%*c%[^\t]%*c%[^\t]%*c%d%*c%d%*c%[^\t]%*c%c%*c", &id, titolo, autore, &pagine, &anno, genere, &d)>0) {

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
				nuovoNodo->libro.d=d;

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
			fprintf(fp, "%d\t%s\t%s\t%d\t%d\t%s\t%c\n", nodo->libro.id, nodo->libro.titolo, nodo->libro.autore, nodo->libro.pagine, nodo->libro.anno, nodo->libro.genere, nodo->libro.d);
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
		printf("0: Termina il programma\n\n");
		scanf("%d%*c", &risposta);

		if(risposta==1)
			stampaLista(head);
		else if(risposta==2)
			head=inserisciCoda(head, &prossimo_id);
		else if(risposta==3)
			head=cancellaLibro(head);
		else if(risposta==0) {
			printf("Finito!\n\n");
			salvataggio(head);
		}
		else
			printf("Selezione non valida!\n\n");

	}
}

