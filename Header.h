
int** allocazione(int n);
void inizializzazione(int n, int **m);
void lettura(char* percorsoFile, int **m);
void FloydWarshall(int n, int **m);
void controllo(int* v, int i, int massimo);
void trovaMassimi(int n, int **m, int*v);
int trovaEccentricita(int*v, int value, int n);
void trovaCentro(int n, int e, int*v, char*percorsoFile);
void completaFile(int c, char* percorsoFile);
void stampa(int c, char* percorsoFile, int n);
