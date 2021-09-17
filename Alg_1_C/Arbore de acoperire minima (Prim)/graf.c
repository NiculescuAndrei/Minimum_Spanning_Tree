#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graf.h"
/*   Functie pentru a reprezenta graful sub forma unei matrici adiacente

     Valorile muchiilor sunt generate in mod aleatoriu de la 0 pana la 9999
     prin intermediul functiei rand() din libraria time.h

     Prima data am initializat elementele matricei cu valoarea -1.

     Deoarece nu exista muchii intre un nod si el insusi am pus
     valoarea 0 atunci cand i = j.

     Dupa aceea daca atat pe pozitia graf[i][j] cat si graf[j][i]
     se afla valoarea -1, atunci se genereaza aleatoriu o valoare.

     Daca pe una dintre cele 2 pozitii se afla o valoare, atunci
     pe cealalta pozitie unde se afla valoarea -1 se va copia
     acea valoare, deoarece graful este neorientat.
*/

void initializare_matrice_adiacenta ( int numar_noduri, int graf[numar_noduri][numar_noduri] )
{
    srand(time(NULL));

    for( int i = 0; i < numar_noduri; i++ )
        {
            for( int j = 0; j < numar_noduri; j++ )
            {
                graf[i][j] = -1;
            }
        }

    for( int i = 0; i < numar_noduri; i++ )
        {
            for( int j = 0; j < numar_noduri; j++ )
            {
                if( i == j )
                {
                    graf[i][j] = 0;
                }
                else if ( graf[i][j] == -1 && graf[j][i] == -1 )
                {
                    graf[i][j] = rand()%10000;
                }
                else
                {
                    graf[i][j] = graf[j][i];
                }
                printf("%d\t", graf[i][j]);
            }
            printf("\n");
        }
}

/* Functie pentru a gasi nodul cu cea mai mica valoare asociata si care nu a fost inca vizitat.
   Pe masura ce parcurgem graful asociem nodurilor adiacente nodului curent valoarea muchiei prin care sunt legate de nodul curent, pana cand nodurile devin vizitate in cele din urma.
   In cazul in care, repepetand pasul de mai sus, se gaseste o muchie cu o valoare mai mica decat cea care este deja atasata in nodul corespunzator,
   iar nodul nu este inca vizitat, se va actualiza cu aceasta valoare, iar daca muchia are o valoare mai mare nu se va face nici o schimbare.
*/
int determinare_valoare_minima ( int numar_noduri, int valori_noduri[], int noduri_vizitate[] )
{
    int minim = 10000;
    int pozitie_minim;

    for (int i = 0; i < numar_noduri; i++)
    {
        if( valori_noduri[i] < minim && noduri_vizitate[i] == 0)
        {
            minim = valori_noduri[i];
            pozitie_minim = i;
        }
    }
    return pozitie_minim;
}

/* Functie pentru a afisa muchiile arborelui minim de acoperire gasit si valorile acestora
   cu ajutorul vectorului nod_parinte[] in care se afla nodul "parinte" al fiecarui nod vizitat
   pentru a putea determina muchiile din care este compus arborele.
   De asemenea, in aceasta functie, este calculata si suma acestor valori pentru a determina "costul" arborelui construit.
*/
void afisare_arbore_minim ( int numar_noduri, int nod_parinte[], int graf[numar_noduri][numar_noduri] )
{
    int cost_arbore_minim = 0;
    fprintf( e, "\nMuchiile din care este alcatuit arborele minim de acoperire sunt:\n" );
    for( int i = 1; i < numar_noduri; i++) /* contorul i porneste de la 1 deoarece nodul 0 reprezinta radacina arborelui */
    {
        fprintf(e, "%d. muchia (%d,%d) = %d\n",i,nod_parinte[i],i,graf[i][nod_parinte[i]] );
        cost_arbore_minim += graf[i][nod_parinte[i]];
    }
    fprintf( e, "\nPrin urmare costul arborelui minim de acoperire gasit este: %d\n",cost_arbore_minim );
}

/* Functie pentru a construi arborele minim de acoperire a unui graf
   reprezentat cu ajutorul unei matrici de adiacenta.
   Construirea arborelui se bazeaza pe algoritmul de tip Greedy numit Prim.
*/
void arbore_minim_de_acoperire_prim ( int numar_noduri, int graf[numar_noduri][numar_noduri] )
{
    int nod_parinte[numar_noduri]; /* Vector pentru a stoca "parintele" fiecarui nod vizitat
                                      ce urmeaza a fi folosit in afisarea laturilor care formeaza arborele.
                                   */

    int valori_noduri[numar_noduri]; /* Vector pentru a asocia nodurilor adiacente nodului curent
                                        valorile muchiilor de care sunt legate
                                        atata timp cat aceste noduri nu au fost inca vizitate.
                                        Daca in urma repetarii acestui pas se gaseste o muchie
                                        cu o valoare mai mica decat cea asociata deja nodului corespunzator,
                                        aceasta noua valoare va fi asociata nodului daca acesta nu a fost deja vizitat.
                                     */
    int noduri_vizitate[numar_noduri]; /* Vector pentru a tine cont de nodurile care au fost vizitate sau nu.
                                          0 - va insemna nod nevizitat, iar 1 - nod vizitat.
                                       */

    for ( int i = 0; i < numar_noduri ; i++)
    {
        valori_noduri[i] = 10000; /* Initializam valorile din noduri cu numere cat mai mari.*/
        noduri_vizitate[i] = 0;   /* Asociem fiecarei pozitii a vectorului valoarea 0
                                     pentru a marca faptul ca nici un nod nu este inca vizitat.
                                  */
    }

    valori_noduri[0] = 0;   /* Dand valoarea 0 primului nod asiguram faptul ca acesta va fi ales primul
                               din vectorul valori_noduri[] cu ajutorul functiei determinare_valoare_minima.
                            */
    nod_parinte[0] = -1;  /* Din moment ce primul nod este de fapt radacina arborelui minim de acoperire
                             acesta nu are nici un nod "parinte".
                          */

    /* Arborele va avea numar_noduri (variabila citita de la tastatura de utilizator) de noduri
       si din acest motiv structura for va rula de numar_noduri de ori.
    */
    for( int iterator = 0; iterator < numar_noduri; iterator++)
    {
        /* Alegem de fiecare data nodul cu cea mai mica valoare asociata
           din multimea de noduri care nu este deja inclusa in arbore.
           Valorile vor fi actualizate mereu in vectorul valori_noduri[].
        */
        int u = determinare_valoare_minima(numar_noduri,valori_noduri,noduri_vizitate);

        noduri_vizitate[u] = 1; /* Odata ales nodul, acesta va fi marcat ca si vizitat in vectorul noduri_vizitate[].*/

        /* In urmatorul for se actualizeaza mereu
           valorile si parintii nodurilor adiacente
           nodului selectat prin intermediul
           variabilei u de mai sus. De asemenea,
           se iau in considerare doar acele noduri
           care nu au fost deja vizitate.
        */
        for( int v = 0; v < numar_noduri; v++)
        {
            /* graf[u][v] va avea valoare nenula numai in cazul in care
               exista o muchie intre u si v (nodurile sunt adiacente).

               noduri_vizitate[v] va avea valoarea 0 numai daca
               nodul v nu a fost inca vizitat

               valoarea corespunzatoare nodului v va fi actualizata
               numai daca valoarea muchiei este mai mica decat
               valoarea deja atribuita nodului.
            */
            if( graf[u][v] != 0 && noduri_vizitate[v] == 0 && graf[u][v] < valori_noduri[v])
            {
                nod_parinte[v] = u;
                valori_noduri[v] = graf[u][v];
            }
        }
    }
    /* Prin intermediul functiei de afisare output-ul programului va fi urmatorul:
       - muchiile din care este compus arborele cu valorile corespunzatoare acestora
       - suma tuturor acestor valori pentru a indica "costul" arborelui minim de
         acoperire gasit prin intermediul algoritmului Prim.
    */
    afisare_arbore_minim( numar_noduri, nod_parinte, graf );
}
