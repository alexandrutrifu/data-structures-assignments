/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


void dezalocGraf(TGL **graf) {

	for (int i = 0; i < (*graf)->n; i++) {

		AArc lista = (*graf)->x[i];
		AArc aux;

		while (lista != NULL) {

			aux = lista;
			lista = lista->urm;
			free(aux);
		}
	}
	
	free((*graf)->adancimi);
	free((*graf)->x);
	free((*graf));
	*graf = NULL;
}

void dezalocCodif(char ***codificari, int n) {

	for (int i = 0; i < n; i++) {

		free((*codificari)[i]);
	}

	free((*codificari));
	*codificari = NULL;
}