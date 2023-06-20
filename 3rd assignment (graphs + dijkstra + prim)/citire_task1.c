/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


void citire_task1(FILE *input, int *n, int *m, char ***codificari, TGL **graf) {

	/* citire N, M */
	fscanf(input, "%d %d", n, m);

	/* alocare vector codificări */
	*codificari = (char **) malloc((*n) * sizeof(char *));
	if (!(*codificari)) {
		return;
	}

	int nr_codif = 0;

	/* alocare graf */
	*graf = alocGraf(*n);

	/* citirea listei de adiacență */
	for (int i = 0; i < (*m); i++) {

		/* alocarea numelor obiectivelor */
		char *plecare = (char *) malloc(MAX_LEN * sizeof(char));
		if (!plecare) {
			return;
		}

		char *destinatie = (char *) malloc(MAX_LEN * sizeof(char));
		if (!destinatie) {
			return;
		}

		int cost;
		int index_plecare = -1, index_destinatie = -1;

		fscanf(input, "%s %s %d", plecare, destinatie, &cost);

		/* verificăm dacă numele obiectivelor au fost codificate */
		for (int j = 0; j < nr_codif; j++) {

			/* dacă nodul este deja înregistrat, adăugăm muchia în lista de adiacență */
			if (strcmp((*codificari)[j], plecare) == 0) {
				
				index_plecare = j;

			}
			if (strcmp((*codificari)[j], destinatie) == 0) {

				index_destinatie = j;

			}

		}

		if (index_plecare < 0) { /* nodul 1 nu a fost codificat */
			
			(*codificari)[nr_codif] = plecare;
			index_plecare = nr_codif;
			nr_codif++;
		
		} else {
			free(plecare); /* dacă nodul este deja codificat, nu mai e necesară 
							zona de memorie alocată suplimentar*/
		}

		if (index_destinatie < 0) { /* nodul 2 nu a fost codificat */

			(*codificari)[nr_codif] = destinatie;
			index_destinatie = nr_codif;
			nr_codif++;

		} else {
			free(destinatie);
		}

		/* actualizarea muchiilor din listele de adiacență
		(construim muchia plecare->destinatie avand costul specificat) */
		AArc *lista = &((*graf)->x[index_plecare]);
		
		AArc muchie = alocArc(index_destinatie, cost); /* alocarea muchiei */
		if (!muchie) {
			return;
		}

		if ((*lista) == NULL) { /* dacă lista de adiacență a nodului *plecare* este goală*/
			
			*lista = muchie;
		
		} else { /* adăugăm muchia la finalul listei */

			AArc aux = (*lista);

			while (aux->urm != NULL) { /* parcurgem lista până la ultimul element */
				aux = aux->urm;
			}

			aux->urm = muchie;

		}

		/* marcăm muchia destinație->plecare */
		lista = &((*graf)->x[index_destinatie]);

		muchie = alocArc(index_plecare, cost); /* alocarea muchiei */
		if (!muchie) {
			return;
		}

		if ((*lista) == NULL) { /* dacă lista de adiacență a nodului *plecare* este goală*/
			
			*lista = muchie;
		
		} else { /* adăugăm muchia la finalul listei */
			
			AArc aux = (*lista);

			while (aux->urm != NULL) { /* parcurgem lista până la ultimul element */
				aux = aux->urm;
			}

			aux->urm = muchie;

		}
	}
}