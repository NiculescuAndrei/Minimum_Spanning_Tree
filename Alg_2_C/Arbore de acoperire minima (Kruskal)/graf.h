#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED

int numar_noduri;
FILE *f,*e;

void initializare_matrice_adiacenta ( int numar_noduri, int graf[numar_noduri][numar_noduri] );
int gaseste_parinte ( int numar_noduri, int nod, int nod_parinte[numar_noduri] );
int reuniune_noduri ( int numar_noduri, int u, int v, int nod_parinte[numar_noduri] );
void kruskal ( int numar_noduri, int graf[numar_noduri][numar_noduri] );

#endif // GRAF_H_INCLUDED
