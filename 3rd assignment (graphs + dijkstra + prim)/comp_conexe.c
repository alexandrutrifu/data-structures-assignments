/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


int *comp_conexe(TGL *graf, int *IC) {

	/* alocarea vectorului caracteristic */
	int *visited = (int *) calloc(graf->n, sizeof(int));
	if (!visited) {
		return NULL;
	}

	int index = 0;

	while (1) { /* cât timp vectorul visited[] nu este complet */

		dfs(graf, visited, index, *IC);

		int ok = 1;

		for (int i = 0; i < graf->n; i++) {

			if (!visited[i]) { /* dacă s-a găsit un element nul */
				
				ok = 0;
				index = i; /* salvăm nodul de unde vom reîncepe parcurge*/
				(*IC)++; /* marcăm trecerea la o nouă componentă conexă */
				
				break;
			}
		}

		if (ok) /* ieșim din while dacă vectorul este complet */
			break;
	}

	return visited;
	

}