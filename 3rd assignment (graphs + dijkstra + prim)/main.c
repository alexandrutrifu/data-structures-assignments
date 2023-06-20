/* TRIFU-URZICĂ Alexandru - 315CB */
#include "header.h"


int main(int argc, char *argv[]) {

	FILE *input = fopen("tema3.in", "r");


	if (strcmp(argv[1], "1") == 0) { /* CERINȚA 1 */
		
		FILE *output = fopen("tema3.out", "w");
		
		/* citirea datelor de intrare */
		int n, m;
		TGL *graf;
		char **codificari;

		citire_task1(input, &n, &m, &codificari, &graf);

		/* aflarea componentelor conexe ale grafului neorientat */
		int IC = 1; /* incremenent / nr. componente conexe */

		int *visited = comp_conexe(graf, &IC); /* funcția va returna vectorul nodurilor vizitate 
												și, prin efect lateral, numărul componentelor conexe*/
		if (!visited) {
			return 0;
		}
		
		fprintf(output, "%d\n", IC); /* afișăm numărul de componente conexe */

		fclose(output);

		calcul_costuri(graf, visited, IC);

		/* dezalocări, închidere fișiere */
		free(visited);
		dezalocGraf(&graf);
		dezalocCodif(&codificari, n);

	} else { /* CERINȚA 2 */

		int n, m;
		TGL *graf;
		int comoara;

		char **codificari = citire_task2(input, &n, &m, &graf, &comoara);
		if (!codificari) {
			return 0;
		}

		calcul_scoruri(graf);

		/* verificăm dacă există un drum de la corabie la insulă */
		int *drum = (int *) malloc(graf->n * sizeof(int));
		if (!drum) {
			return 0;
		}

		float *scoruri_minime = dijkstra(graf, 1, drum);
		if (!scoruri_minime) {
			return 0;
		}

		if (scoruri_minime[0] == INT_MAX) {
			
			FILE *output = fopen("tema3.out", "w");

			fprintf(output, "Echipajul nu poate ajunge la insula\n");

			fclose(output);

		} else {
			
			free(scoruri_minime);
			
			/* verificăm dacă există un drum de la insulă la corabie */
			scoruri_minime = dijkstra(graf, 0, drum);
			if (!scoruri_minime) {
				return 0;
			}

			if (scoruri_minime[1] == INT_MAX) {
				
				FILE *output = fopen("tema3.out", "w");

				fprintf(output, "Echipajul nu poate transporta comoara inapoi la corabie\n");

				fclose(output);

			} else {

				float scor_drum_intoarcere = scoruri_minime[1];

				/* găsim drumul optim de la insulă la corabie */
				drum_intoarcere(graf, scor_drum_intoarcere, codificari, comoara);
			}
		}

		/* dezalocări */
		free(drum);
		free(scoruri_minime);
		dezalocCodif(&codificari, graf->n);
		dezalocGraf(&graf);
	}

	fclose(input);

	return 0;
}