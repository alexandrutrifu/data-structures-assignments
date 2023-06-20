/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


AArc alocArc(int destinatie, int cost) {

	AArc muchie = (AArc) malloc(sizeof(TCelArc));
	if (!muchie) {
		return NULL;
	}

	muchie->d = destinatie;
	muchie->c = cost;
	muchie->urm = NULL;

	return muchie;
}

TGL *alocGraf(int n) {

	TGL *graf = (TGL *) malloc(sizeof(TGL));
	if (!graf) {
		return NULL;
	}

	graf->x = (AArc *) calloc(n, sizeof(AArc));
	if (!graf->x) {

		free(graf);
		return NULL;
	}

	graf->adancimi = (int *) calloc(n, sizeof(int));
	if (!graf->adancimi) {
		return NULL;
	}

	graf->n = n;
}

TStiva alocCelula(int x) {

	TStiva aux = (TStiva) malloc(sizeof(TCelulaStiva));
	if (!aux) {
		return NULL;
	}

	aux->info = x;
	aux->urm = NULL;

	return aux;
}