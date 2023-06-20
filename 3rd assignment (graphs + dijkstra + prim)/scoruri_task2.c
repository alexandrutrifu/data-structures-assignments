/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


void calcul_scoruri(TGL *graf) {

	for (int i = 0; i < graf->n; i++) {

		AArc lista = graf->x[i];

		while (lista) {

			lista->scor = (lista->c * 1.0) / graf->adancimi[lista->d];
			lista = lista->urm;
		}
	}
}