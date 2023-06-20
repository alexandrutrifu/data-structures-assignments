/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


int push(TStiva *vf, int x) {

	TStiva aux = alocCelula(x);
	if (!aux) {
		return 0;
	}

	aux->urm = *vf;
	*vf = aux;

	return 1;
}

int pop(TStiva *vf, int *x) {

	if ((*vf) == NULL) {
		return 0;
	}

	TStiva aux = *vf;
	*x = aux->info;
	*vf = aux->urm;

	free(aux);

	return 1;

}