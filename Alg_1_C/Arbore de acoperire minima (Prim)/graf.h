#ifndef GRAF_H_INCLUDED
#define GRAF_H_INCLUDED

int numar_noduri;
FILE *f,*e;

void initializare_matrice_adiacenta ( int numar_noduri,int graf[numar_noduri][numar_noduri] );
int determinare_valoare_minima ( int numar_noduri, int valori_noduri[], int noduri_vizitate[] );
void afisare_arbore_minim ( int numar_noduri, int nod_parinte[], int graf[numar_noduri][numar_noduri] );
void arbore_minim_de_acoperire_prim ( int numar_noduri, int graf[numar_noduri][numar_noduri] );

#endif // GRAF_H_INCLUDED


