#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Header.h"

int main(int args, char *argv[]) {

	int** matrice;
	int nodi = 0;
	int eccentricita;
	int value = INT_MAX;

	FILE *f = fopen(argv[1], "r");
	fscanf(f, "%d", &nodi);
	int* vettore = (int*)malloc(nodi * sizeof(int));
	matrice = allocazione(nodi);
	/*inizializzazione(nodi, matrice);*/
	lettura(argv[1], matrice);
	FloydWarshall(nodi, matrice);
	trovaMassimi(nodi, matrice, vettore);
	eccentricita = trovaEccentricita(vettore, value, nodi);
	trovaCentro(nodi, eccentricita, vettore, argv[2]);
	system("pause");
	return 0;
}

//funzione che alloca memoria per la matrice
int** allocazione(int n) {
	int **m = (int **)malloc(n * sizeof(int*));
	int i = 0;
	while (i<n)
	{
		m[i] = (int *)malloc(n * sizeof(int));
		i++;
	}
	//funzione per settare la matrice a int_max
	//nessun arco inserito
	inizializzazione(n, m);
	return m;
}

void inizializzazione(int n, int **m) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			m[i][j] = INT_MAX;
		}
	}
}

//funzione che legge il file dato in input con il grafo
//e riempe la matrice
void lettura(char* percorsoFile, int **m) {
	FILE *f = fopen(percorsoFile, "r");
	int n, a, r, c, peso, i;

	fscanf(f, "%d", &n);
	fscanf(f, "%d", &a);

	for (i = 0; i < a; i++) {
		fscanf(f, "%d", &r);
		fscanf(f, "%d", &c);
		fscanf(f, "%d", &peso);
		//controllo per prendere il peso minore
		if (m[r - 1][c - 1] > peso)
			m[r - 1][c - 1] = peso;

	}
	fclose(f);

}

//implementazione dell'algoritmo di floydWarshall 
// aggiunto il controllo per escludere le coppie di nodi non collegate
void FloydWarshall(int n, int **m) {
	int q;
	int j;
	int w;
	for (q = 0; q < n; q++)
	{
		for (j = 0; j < n; j++)
		{
			for (w = 0; w <n; w++)
			{
				const int distancejw = m[j][w];
				const int distancejq = m[j][q];
				const int distanceqw = m[q][w];
				if (distancejq != INT_MAX && distanceqw != INT_MAX && distancejw > distancejq + distanceqw) {
					m[j][w] = distancejq + distanceqw;
				}
			}
		}
	}
}
void controllo(int* v, int i, int massimo) {
	//verifico se il nodo in questione non ha archi uscenti
	if (massimo == -1)
	{
		v[i] = INT_MAX;
	}
	else
	{
		v[i] = massimo;
	}

}
//funzione che trova i massimi
//per ogni nodi trova la sua distanza massima considerando gli archi
// tra lui e tutti gli altri
void trovaMassimi(int n, int **m, int*v) {
	int i;
	int k = 0;
	int massimo = -1;

	while (k < n) {
		for (i = 0; i < n; i++) {
			if (m[k][i] != INT_MAX && m[k][i] > massimo) {
				massimo = m[k][i];
			}
		}
		controllo(v, k, massimo);
		massimo = -1;
		k++;
	}

}

int trovaEccentricita(int*v, int value, int n) {
	int i = 0;
	for (i = 0; i < n; i++)
	{
		if (v[i] > value)
		{

		}
		else
		{
			value = v[i];
		}
	}

	return value;
}
void trovaCentro(int n, int e, int*v, char* percorsoFile) {
	int i = 0;
	int primoNodo = 0;
	while (i<n)
	{
		if (v[i] == e)
		{
			primoNodo++;
			stampa(i + 1, percorsoFile, primoNodo);

		}
		i++;
	}
}

void stampa(int c, char* percorsoFile, int n) {
	if (n == 1) {
		FILE *w = fopen(percorsoFile, "w");
		if (w != NULL) {
			fprintf(w, "%d", c);
		}
	}
	else {
		completaFile( c, percorsoFile);
	}

}

void completaFile(int c, char* percorsoFile){
	FILE *w = fopen(percorsoFile, "a");
	fprintf(w, ", %d", c);
}