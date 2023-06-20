/* TRIFU-URZICĂ Alexandru - 315CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define MAX_LEN 30


/* implementarea grafului */
typedef struct celarc {
	int d;           /* destinație arc */
	int c;            /* cost arc */
	float scor;
	struct celarc *urm; /* adresa următorului nod adiacent */
} TCelArc, *AArc;

typedef struct {
	int n;     /* număr noduri */
	int *adancimi; /* adâncimile asociate nodurilor (task2) */
	AArc* x;    /* vector adrese liste arce */
} TGL;

/* implementarea stivei */
typedef struct celula {
	
	int info;
	struct celula *urm;

} TCelulaStiva, *TStiva;


/* funcții alocare */
AArc alocArc(int destinatie, int cost);
TGL *alocGraf(int n);
TStiva alocCelula(int x);

/* funcții citire */
void citire_task1(FILE *input, int *n, int *m, char ***codificari, TGL **graf);
char **citire_task2(FILE *input, int *n, int *m, TGL **graf, int *comoara);

/* funcții stivă */
int push(TStiva *vf, int x);
int pop(TStiva *vf, int *x);

/* funcții de prelucrare a grafului TASK 1 */
void dfs(TGL *graf, int *visited, int index, int IC);
int *comp_conexe(TGL *graf, int *IC);
int nod_tranzitie_minima(TGL *graf, int *tranzitii, int *visited);
int prim(TGL *graf, int start, int nr_noduri);

/* funcții de calcul și sortare costuri TASK 1 */
int comp(const void *a, const void *b);
void sortare_costuri(int *costuri_componente, int nr_componente);
void calcul_costuri(TGL *graf, int *visited, int nr_componente);

/* funcții TASK 2*/
void calcul_scoruri(TGL *graf);
int next_nod(TGL *graf, int *visited, float *costuri);
float *dijkstra(TGL *graf, int start, int *drum);
int dfs_intoarcere(TGL *graf, TStiva *stiva, int *visited, int index, \
					float scor_dorit, float scor_acumulat);
int *drum_intoarcere(TGL *graf, float scor_drum_intoarcere, char **codificari, int comoara);
int cost_intoarcere(TGL *graf, TStiva stiva);
int adancime_minima(TGL *graf, TStiva stiva);

/* dezalocări */
void dezalocGraf(TGL **graf);
void dezalocCodif(char ***codificari, int n);