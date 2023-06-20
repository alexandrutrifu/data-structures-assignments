/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"



int dfs_intoarcere(TGL *graf, TStiva *stiva, int *visited, int index, \
					float scor_dorit, float scor_acumulat) {
	
	visited[index] = 1;
	push(stiva, index);

	if (scor_acumulat > scor_dorit)
		return 0;

	for (int i = 0; i < graf->n; i++) {

		if (i == 1)
			continue;
		
		AArc lista = graf->x[i];

		while (lista) {

			if (lista->d == index) {

				if (i == 0) { /* dacă s-a găsit nodul Insulă*/

					char str[MAX_LEN] = "\0", str2[MAX_LEN] = "\0";

					sprintf(str, "%.3f", scor_dorit);
					sprintf(str2, "%.3f", scor_acumulat + lista->scor);

					if (atof(str) == atof(str2)) {
						push(stiva, 0);
						return 1;
					}

				} else {

					if (dfs_intoarcere(graf, stiva, visited, i, \
							scor_dorit, scor_acumulat + lista->scor))
						return 1;
				
					int aux;
					pop(stiva, &aux);
				}
			}

			lista = lista->urm;
		}

	}

	return 0;
} 

int cost_intoarcere(TGL *graf, TStiva stiva) {

	int cost = 0;

	while (stiva->urm != NULL) {

		int nod = stiva->info;

		AArc lista = graf->x[nod];

		while (lista->d != stiva->urm->info)
			lista = lista->urm;

		cost += lista->c;

		stiva = stiva->urm;
	}

	return cost;
}

int adancime_minima(TGL *graf, TStiva stiva) {

	int Min = INT_MAX;

	stiva = stiva->urm; /* nu luăm în considerare adâncimea asociată
						insulei sau corăbiei*/
	while (stiva->urm) {

		if (Min > graf->adancimi[stiva->info])
			Min = graf->adancimi[stiva->info];

		stiva = stiva->urm;
	}

	return Min;
}


int *drum_intoarcere(TGL *graf, float scor_drum_intoarcere, char **codificari, int comoara) {
	
	FILE *output = fopen("tema3.out", "w");

	int *visited = (int *) calloc(graf->n, sizeof(int));
	if (!visited) {
		return 0;
	}

	TStiva stiva = NULL;

	/* efectuăm o parcurgere în adâncime pornind de la Insula, 
	până la găsirea drumului de scor minim până la Corabie */	
	dfs_intoarcere(graf, &stiva, visited, 1, scor_drum_intoarcere, 0);

	int cost_drum_intoarcere = cost_intoarcere(graf, stiva);
	int adancime = adancime_minima(graf, stiva);

	while (stiva) {

		int nod;
		pop(&stiva, &nod);

		if (nod == 0) {
			fprintf(output, "Insula ");
			continue;
		}

		if (nod == 1) {
			fprintf(output, "Corabie\n");
			continue;
		}

		fprintf(output, "%s ", codificari[nod]);	
	}

	fprintf(output, "%d\n", cost_drum_intoarcere);
	fprintf(output, "%d\n", adancime);
	fprintf(output, "%d\n", comoara / adancime);

	free(visited);
	fclose(output);
}