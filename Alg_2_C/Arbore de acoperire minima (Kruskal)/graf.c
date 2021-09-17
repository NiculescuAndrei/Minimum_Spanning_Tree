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
     pe cealalta pozitie unde se afla -1 se va copia
     acea valoare, deoarece graful este neorientat.
*/
void initializare_matrice_adiacenta (int numar_noduri, int graf[numar_noduri][numar_noduri] )
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


/*  Scopul acestei functii este de a evita formarea ciclurilor.

    De fiecare data cand se alege o muchie se verifica care este
    nodul parinte al fiecarui nod din care este formata muchia.

    Daca cele 2 noduri nu au fost atasate la arborele minim
    de acoperire ( valoarea lor din nod_parinte[] este -1)
    atunci muchia se ataseaza la arbore, iar primul nod
    devine parintele celui de-al doilea ( nod_parinte[v] = u )
    unde u si v reprezinta nodurile care delimiteaza muchia.

    Daca muchia selectata are un nod atasat la arborele minim
    de acoperire, iar celalalt nod nu este inclus in acesta
    ( nod_parinte[] este -1 ), atunci acesta va fi adaugat la arbore.

    Daca muchia selectata are ambele noduri in arbore, atunci
    se verifica daca nu cumva adaugarea acestei muchii va fomra un ciclu.
    Pentru fiecare nod se traverseaza din "parinte in parinte" pana se ajunge
    la ultimul nod parinte (radacina). Daca pentru ambele noduri aceasta radacina
    coincide, atunci muchia este inlaturata deoarece ar forma un ciclu.
*/
 int gaseste_parinte ( int numar_noduri, int nod, int nod_parinte[numar_noduri] )
 {
     while ( nod_parinte[nod] != -1 )
     {
         nod = nod_parinte[nod];
     }
     return nod;
 }


/* Functie prin care se reunesc 2 noduri pentru a face parte din acelasi arbore
   minim de acoperire.

   Cu ajutorul functiei de mai sus ( gaseste_parinte ) cele doua noduri se reunesc
   prin urmare a constatarii faptului ca fiecare dintre ele au o radacina a arborelui
   diferita ( daca functia de mai sus ar returna aceeasi valoare pentru ambele noduri
   ar insemna faptul ca se va forma un ciclu, iar reuniunea nu va avea loc)
*/
 int reuniune_noduri ( int numar_noduri, int u, int v, int nod_parinte[numar_noduri] )
 {
     if ( u != v)  /* u si v reprezinta cele doua noduri care au fost analizate
                      ( nodurile care delimiteaza muchia )
                   */
     {
         nod_parinte[v] = u;  /* primul nod devine parintele celui de-al doilea */
         return 1;
     }
     return 0;
 }

  void kruskal ( int numar_noduri, int graf[numar_noduri][numar_noduri] )
  {
      int numar_muchii_arbore = 1, cost_arbore_minim = 0; /* -prima variabila indica numarul de muchii din arbore
                                                              si este folosita pentru a opri cautarea atunci cand arborele
                                                              va avea numar_noduri - 1 muchii.
                                                             -a doua calculeaza, la final, costul minim al arborelui gasit prin
                                                              adunarea valorilor asociate muchiilor din care este format.
                                                          */
      int a, b, u, v, minim; /* variabila minim este folosita pentru a stoca valoarea minima
                                din matricea de adiacenta.
                             */
      int nod_parinte[numar_noduri]; /* vector pentru a tine cont de parintele fiecarui nod
                                        din arborele minim de acoperire format
                                     */

      for (int i = 0; i < numar_noduri; i++)
      {
          nod_parinte[i] = -1; /* Initializam valorile din vectorul nod_parinte[] cu -1,
                                  ceea ce inseamna ca toate nodurile sunt libere ( nu au nici un parinte )
                               */
      }

      for ( int i = 0; i < numar_noduri; i++)
      {
          for ( int j = 0; j < numar_noduri; j++)
          {
              if ( graf[i][j] == 0)
              {
                  graf[i][j] = 10000;  /* Acolo unde nu exista legaturi dam o valoare cat mai mare
                                          pentru a elimina elementul din cautarea valorii minime.
                                       */
              }
          }
      }

      fprintf (e,"\nMuchiile din care este alcatuit arborele minim de acoperire sunt:\n");

      while ( numar_muchii_arbore < numar_noduri ) /* Arborele minim de acoperire are intotdeauna
                                                      numar_noduri - 1 muchii
                                                   */
      {
          minim = 10000;
          for ( int i = 0; i < numar_noduri; i++)
          {
              for ( int j = 0; j < numar_noduri; j++)
              {
                  if ( graf[i][j] < minim )
                  {
                      minim = graf[i][j]; /* dupa parcurgerea integrala a matricei in variabila
                                             minim se va afla muchia cu valoarea minima din graf
                                          */
                      a = u = i;
                      b = v = j; /* Salvam de doua ori numarul nodurilor care delimiteaza muchia deoare:
                                    - Prima data aceste valori se vor folosi in functia gaseste_parinte
                                      in urma careia valorile se vor pierde.
                                    - A doua oara se folosesc la final, in cazul in care nodurile vor fi reunite
                                      in arborele minim de acoperire, pentru a indica numarul nodurilor care
                                      alcatuiesc muchia.
                                 */
                  }

              }
          }

          u = gaseste_parinte( numar_noduri, u, nod_parinte );
          v = gaseste_parinte( numar_noduri, v, nod_parinte );

        /*In cazul in care cele doua noduri sunt compatibile, muchia delimitata
          de aceste noduri va fi adaugata la arbore.

          De asemenea, numarul de muchii din arbore va creste cu o unitate, iar
          la "costul" arborelui se va adauga valoarea muchiei adaugate.
        */
          if ( reuniune_noduri( numar_noduri, u, v, nod_parinte ) != 0 )
          {
              fprintf(e,"%d. muchia (%d,%d) = %d\n", numar_muchii_arbore, a, b, minim);
              numar_muchii_arbore++;
              cost_arbore_minim += minim;
          }

          graf[a][b] = graf[b][a] = 10000; /* Chiar daca muchia a fost adaugata sau nu la arbore, dupa ce
                                              aceasta a fost testata i se atribuie o valoare cat mai mare
                                              pentru a nu fi inclusa din nou in cautarea urmatoare a valorii minime.
                                          */
      }

      fprintf(e,"\nPrin urmare costul arborelui minim de acoperire gasit este: %d\n",cost_arbore_minim);
  }
