# Tema 3 - SDA

> <mark> *Notă*: În cazul ambelor cerințe, procesarea datelor de intrare a implicat codificarea, respectiv indexarea nodurilor-destinații transmise ca *string-uri*. </mark>

> Astfel, cele două funcții cu rol de citire a input-ului (`citire_task1`, `citire_task2`, implementate în fișierele-sursă cu aceleași nume) folosesc un vector de <mark> codificări </mark> prin care se verifică, la fiecare linie citită din fișier, dacă indecșii nodurilor specificate au fost, sau nu, atribuiți. Acești indecși vor fi folosiți, mai apoi, în modelarea grafurilor (ne)orientate necesare pentru rezolvarea cerințelor.

## Cerința 1:
---
Pentru citirea datelor de intrare s-a folosit funcția `citire_task1()`<sup>[1]</sup>, aceasta având rolul de a codifica destinațiile de pe hartă și de a construi listele de adiacență ale nodurilor asociate diferitelor locații. În acest sens, funcția alocă inițial un graf neorientat, apoi parcurge, pentru fiecare set de date, lista de adiacență a nodului-plecare, respectiv pe cea a nodului destinație, completându-le cu muchiile (și costurile) specifice. 

Odată construit graful, putem determina <mark>componentele conexe</mark> ale acestuia prin apelul funcției `comp_conexe()`<sup>[2]</sup>. Fiecare componentă conexă este determinată printr-o parcurgere de tip DFS<sup>[3]</sup> a grafului, fiind marcată cu un index propriu în vectorul `visited[]` (e.g. după prima parcurgere a unui graf cu trei componente conexe, nodurile celei dintâi componente vor fi marcate cu 1; funcția găsește primul nod marcat cu 0 în vector și parcurge din nou graful, pornind de la acesta ș.a.m.d.).

Funcția `comp_conexe()` returnează vectorul nodurilor vizitate, în urma etichetării acestora conform componentei căreia îi aparțin. Prin efect lateral, în contorul `IC` se va reține numărul de componente conexe ale grafului.


În continuare, funcția `calcul_costuri()`<sup>[4]</sup> servește la găsirea drumului de cost minim asociat fiecărei componente conexe. Pentru aceasta, se parcurge vectorul `visited` și se reține nodul "de început" al componentei, alături de numărul total de vârfuri ale acesteia. Informațiile sunt pasate ca argumente funcției `prim()`<sup>[5]</sup>, care aplică <mark>Algoritmul Prim</mark> asupra componentei și întoarce costul aferent arborelui minim de acoperire al acesteia.

Costurile precizate mai sus sunt stocate în vectorul `costuri_componente[]`. Odată completat, acesta este sortat (*vezi `sortare_costuri()`*<sup>[6]</sup>) și returnat programului principal spre afișare.

## Cerința 2:
---

Pentru citirea datelor de intrare s-a folosit funcția `citire_task2()`<sup>[7]</sup> (se procedează analog citirii de la punctul [1], citindu-se, adițional, adâncimile asociate nodurilor codificate și greutatea comorii; de această dată se lucrează cu un graf orientat, prin urmare trebuie completate doar listele de adiacență ale nodurilor-plecare).

Funcția `calcul_scoruri()`<sup>[8]</sup> asociază fiecărei muchii a grafului un scor, conform precizărilor din enunț.

În continuare, existența drumurilor de la corabie la insulă, respectiv de la insulă la corabie se verifică folosind <mark>Algoritmul Dijkstra</mark> (*vezi `dijkstra()`*<sup>[9]</sup>):

- primul apel al funcției returnează un vector de scoruri asociat drumurilor optime de la corabie (nodul 1) la celelalte noduri; pentru a trece la pasul următor, se verifică scorul drumului de la corabie la insulă (nodul 0), condiționat la o valoare finită.

- cel de-al doilea apel returnează un vector de scoruri asociat drumurilor optime de la insulă (nodul 0) la celelalte noduri; analog, se verifică scorul drumului de la insulă la corabie.

Dacă ambele condiții sunt îndeplinite, programul apelează funcția `drum_intoarcere()`<sup>[10]</sup>. Aceasta funcționează pe baza unei parcurgeri DFS în sens invers, pornind de la nodul Insula, până la nodul Corabie (*vezi `dfs_intoarcere()`*<sup>[11]</sup>).

### <mark><code style="color: white">dfs_intoarcere()</code></mark>: 
Funcția primește următorii parametri:

- un pointer la graful orientat
- un pointer la stiva ce va fi completată cu nodurile prin care trece drumul optim de la Insulă la Corabie
- un vector de noduri vizitate
- indexul nodului curent (a cărui lista de adiacență este verificată)
- scorul de recunoaștere al drumului optim ce trebuie identificat
- scorul acumulat de-a lungul parcurgerii

Parcurgerea în sens invers pornește de la nodul Corabie (de index 1). La fiecare apel recursiv al funcției, se verifică listele de adicență ale tuturor nodurilor din graf (cu excepția nodului Corabie), căutându-se acelea legate printr-o muchie de nodul curent. Fiecare nod corespunzător este adăugat în stivă, incrementându-se scorul acumulat de-a lungul căutării.

Astfel, parcurgerea continuă până la găsirea nodului Insulă (de la care trebuie să înceapă drumul dorit) - odată găsit, se verifică dacă scorul acumulat corespunde cu scorul drumului optim. În caz afirmativ, funcția returnează 1 și întoarce, prin efect lateral, stiva completată cu nodurile aferente parcurgerii. Altfel, funcția se întoarce la pasul anterior, eliminând nodurile care nu convin din stivă și reluând căutarea.

La ieșirea din `dfs_intoarcere()`, avem la îndemână lista cu nodurile prin care trebuie să trecem pentru a ne întoarce de la Insulă la Corabie. În urma afișării acestora (prin eliminarea succesivă din stivă), folosim funcțiile `cost_intoarcere()`, respectiv `adancime_minima()` (implementate în același fișier-sursă) pentru a calcula ultimele rezultate cerute.

---

### <mark>*Definirea structurilor și antete de funcții:*</mark>
- *vezi `header.h`*


### <mark>*Alocările și dezalocările structurilor folosite:*</mark>
 - *vezi `alocari.c` și `dezalocări.c`*

### <mark>*Implementările funcțiilor folosite:*:</mark>

<sup>[1]</sup> Sursă - fișierul `citire_task1.c`\
<sup>[2]</sup> Sursă - fișierul `comp_conexe.c`\
<sup>[3]</sup> Sursă - fișierul `dfs.c`\
<sup>[4]</sup> Sursă - fișierul `calcul_costuri.c`\
<sup>[5]</sup> Sursă - fișierul `prim.c`\
<sup>[6]</sup> Sursă - fișierul `calcul_costuri.c`\
<sup>[7]</sup> Sursă - fișierul `citire_task2.c`\
<sup>[8]</sup> Sursă - fișierul `scoruri_task2.c`\
<sup>[9]</sup> Sursă - fișierul `dijkstra.c`\
<sup>[10]</sup> Sursă - fișierul `drum_intoarcere.c`\
<sup>[11]</sup> Sursă - fișierul `drum_intoarcere.c`



