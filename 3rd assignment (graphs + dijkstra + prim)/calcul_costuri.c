/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


int comp(const void *a, const void *b) {

	return (*(int *)a - *(int *)b);

}

void sortare_costuri(int *costuri_componente, int nr_componente) {

	qsort(costuri_componente, nr_componente, sizeof(int), comp);

}

void calcul_costuri(TGL *graf, int *visited, int nr_componente) {

	FILE *output = fopen("tema3.out", "a");

	/* alocăm vectorul de costuri asociate componentelor */
	int *costuri_componente = (int *) calloc(nr_componente, sizeof(int));
	if (!costuri_componente) {
		return;
	}

	/* aplicăm algoritmul Prim pentru fiecare componentă conexă */
	for (int i = 1; i <= nr_componente; i++) {
		
		int start = -1; /* primul nod din componenta conexă */
		int nr_noduri = 0; /* numărul nodurilor din componenta conexă */

		for (int j = 0; j < graf->n; j++) {

			if (visited[j] == i) { 

				if (start == -1) {
					start = j;
				}

				nr_noduri++;
			}
		}

		/* salvăm costul asociat componentei */
		costuri_componente[i - 1] = prim(graf, start, nr_noduri);
	}

	/* sortăm vectorul de costuri */
	sortare_costuri(costuri_componente, nr_componente);

	/* afișăm costurile calculate */
	for (int i = 0; i < nr_componente; i++) {
		fprintf(output, "%d\n", costuri_componente[i]);
	}

	free(costuri_componente);

	fclose(output);

}