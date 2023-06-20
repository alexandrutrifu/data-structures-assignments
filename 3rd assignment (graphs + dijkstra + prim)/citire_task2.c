/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


char **citire_task2(FILE *input, int *n, int *m, TGL **graf, int *comoara) {

	/* citire N, M */
	fscanf(input, "%d %d", n, m);

	/* alocare graf */
	*graf = alocGraf(*n);

	/* codificările nodurilor (care nu sunt insula/corabie) */
	char **codificari = (char **) calloc((*n), sizeof(char *));
	if (!codificari) {
		return NULL;
	}

	int nr_codif = 2;

	/* citirea listelor de adiacență */
	for (int i = 0; i < (*m); i++) {

		/* alocarea numelor obiectivelor */
		char *plecare = (char *) malloc(MAX_LEN * sizeof(char));
		if (!plecare) {
			return NULL;
		}

		char *destinatie = (char *) malloc(MAX_LEN * sizeof(char));
		if (!destinatie) {
			return NULL;
		}

		int cost;
		int index_plecare = -1, index_destinatie = -1;

		/* citirea datelor */
		fscanf(input, "%s %s %d", plecare, destinatie, &cost);

		/* indexarea nodurilor (insula va avea indexul 0, iar corabia, 1)*/

		/* codificăm nodul plecare */
		if (strcmp(plecare, "Insula") == 0) {
			
			index_plecare = 0;
			free(plecare);
		
		} else {

			if (strcmp(plecare, "Corabie") == 0) {
				
				index_plecare = 1;
				free(plecare);

			} else {
				
				for (int j = 2; j < nr_codif; j++) {

					if (strcmp(codificari[j], plecare) == 0) {
						index_plecare = j;
						break;
					}
				}

				if (index_plecare < 0) {

					codificari[nr_codif] = plecare;
					index_plecare = nr_codif;
					nr_codif++;
				
				} else {

					free(plecare);
				}
			}
		}

		/* codificăm nodul destinație */
		if (strcmp(destinatie, "Insula") == 0) {
			
			index_destinatie = 0;
			free(destinatie);
		
		} else {

			if (strcmp(destinatie, "Corabie") == 0) {
				
				index_destinatie = 1;
				free(destinatie);

			} else {

				for (int j = 2; j < nr_codif; j++) {

					if (strcmp(codificari[j], destinatie) == 0) {
						index_destinatie = j;
						break;
					}
				}

				if (index_destinatie < 0) {

					codificari[nr_codif] = destinatie;
					index_destinatie = nr_codif;
					nr_codif++;

				} else {

					free(destinatie);
				}
			}
		}

		/* actualizarea muchiilor din listele de adiacență
		(construim muchia plecare->destinatie avand costul specificat) */
		AArc *lista = &((*graf)->x[index_plecare]);
		
		AArc muchie = alocArc(index_destinatie, cost); /* alocarea muchiei */
		if (!muchie) {
			return NULL;
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

	/* citirea adâncimilor */
	for (int i = 0; i < (*n); i++) {

		char *nod = (char *) calloc(MAX_LEN, sizeof(char));
		if (!nod) {
			return NULL;
		}

		int adancime = 0;

		fscanf(input, "%s %d", nod, &adancime);

		if (strcmp(nod, "Insula") == 0) {
			
			(*graf)->adancimi[0] = adancime;
			
			free(nod);
			
			continue;

		}

		if (strcmp(nod, "Corabie") == 0) {

			(*graf)->adancimi[1] = adancime;

			free(nod);

			continue;
		}
				
		int index = -1;

		/* aflăm indexul nodului (codificat) */
		for (int j = 2; j < nr_codif; j++) {
			
			if (strcmp(codificari[j], nod) == 0) {

				index = j;
				break;
			}
		}

		(*graf)->adancimi[index] = adancime;

		free(nod);
	}
	
	/* greutatea comorii */
	fscanf(input, "%d", comoara);

	return codificari;
}