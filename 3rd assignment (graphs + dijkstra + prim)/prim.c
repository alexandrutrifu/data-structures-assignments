/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


int nod_tranzitie_minima(TGL *graf, int *tranzitii, int *visited) {

	int Min = INT_MAX;
	int index_Min = 0;

	for (int i = 0; i < graf->n; i++) {

		if (visited[i] == 0 && tranzitii[i] < Min) {
			Min = tranzitii[i];
			index_Min = i;
		}

	}

	return index_Min;

}

int prim(TGL *graf, int start, int nr_noduri) {

	int cost_total = 0;

	/* vector noduri parcurse */
	int *drum = (int *) malloc(graf->n * sizeof(int));
	if (!drum) { 
		return 0;
	}

	/* vector de vizitati */
	int *visited = (int *) calloc(graf->n, sizeof(int));
	if (!visited) {
		return 0;
	}

	/* vector de costuri asociate nodurilor adiacente */
	int *tranzitii = (int *) malloc(graf->n * sizeof(int));
	if (!tranzitii) {
		return 0;
	}

	for (int i = 0; i < graf->n; i++) {
		tranzitii[i] = INT_MAX;
	}
	tranzitii[start] = 0;

	int noduri_parcurse = 0;

	/* parcurgem componenta conexă */
	while (noduri_parcurse < nr_noduri) {

		int u = nod_tranzitie_minima(graf, tranzitii, visited);
		
		cost_total += tranzitii[u];

		drum[noduri_parcurse] = u;
		noduri_parcurse++;

		visited[u] = 1;

		/* parcurgem vectorul de noduri incluse în drum, actualizând
		tranzițiile dinspre acestea către nodurile adiacente */
		for (int i = 0; i < noduri_parcurse; i++) {

			AArc lista = graf->x[drum[i]];

			while (lista) {

				/* dacă nodul adiacent nu a fost încă vizitat, verificăm
				dacă trebuie actualizat costul tranziției de la nodul curent la acesta */
				if (visited[lista->d] == 0 && lista->c < tranzitii[lista->d]) {
					tranzitii[lista->d] = lista->c;
				}

				lista = lista->urm;

			}
		}
	}

	/* dezalocări */
	free(visited);
	free(drum);
	free(tranzitii);

	return cost_total;



}