build:
	gcc -std=c99 -g -o tema3 main.c citire_task1.c citire_task2.c alocari.c dezalocari.c comp_conexe.c \
	operatii_stiva.c dfs.c prim.c calcul_costuri.c scoruri_task2.c dijkstra.c drum_intoarcere.c

run:
	./tema3

clean:
	rm tema3

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./tema3 2