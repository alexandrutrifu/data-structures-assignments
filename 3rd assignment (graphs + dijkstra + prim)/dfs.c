/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


void dfs(TGL *graf, int *visited, int index, int IC) {

	visited[index] = IC; /* marcăm nodul ca vizitat */

	/* parcurgem lista de adiacență a nodului curent */
	AArc lista = graf->x[index];

	int dest; /* nodul-destinație */

	while (lista) { /* parcurgem lista de adiacență a nodului */

		dest = lista->d;
		
		if (!visited[dest]) { /* dacă nodul adiacent nu a fost vizitat,
								continuăm parcurgerea */

			dfs(graf, visited, dest, IC);
		
		}

		lista = lista->urm;
	}
}