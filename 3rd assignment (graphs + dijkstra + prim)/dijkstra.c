/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


int next_nod(TGL *graf, int *visited, float *costuri) {

	float Min = INT_MAX;
	int index_min = -1;

	for (int i = 0; i < graf->n; i++) {

		if (visited[i] == 0 && Min > costuri[i]) {

			Min = costuri[i];
			index_min = i;
		}
	}

	return index_min;
}

float *dijkstra(TGL *graf, int start, int *drum) {

	/* vector costuri (scoruri) */
	float *costuri = (float *) malloc(graf->n * sizeof(float));
	if (!costuri) {
		return NULL;
	}

	for (int i = 0; i < graf->n; i++) {
		costuri[i] = INT_MAX;
	}

	/* vector noduri vizitate */
	int *visited = (int *) calloc(graf->n, sizeof(int));
	if (!visited) {
		return NULL;
	}

	int index = start, nr = 0;
	costuri[index] = 0;

	while (1) {

		visited[index] = 1;
		drum[nr] = index;
		nr++;

		AArc lista = graf->x[index];

		while (lista) {

			if (costuri[lista->d] > lista->scor + costuri[index]) {
				
				costuri[lista->d] = lista->scor + costuri[index];
			}

			lista = lista->urm;
		}

		index = next_nod(graf, visited, costuri);

		if (index == -1)
			break;
	}

	/* dezalocări */
	free(visited);

	return costuri;
}