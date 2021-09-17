#include <stdio.h>
#include <stdlib.h>
#include "graf.c"
#include <time.h>
#define numar 20
int main()
{
    char str1[numar], str2[numar];
    for( int i = 1; i <= 10; i++ )
    {

    sprintf( str1,"test%d.in", i ); // scrie pe rand in sirul de caractere -str1- test1.in, test2.in etc pentru a putea fi accesat mai usor la citirea din fisier
    sprintf(str2,"test%d.out",i); // scrie pe rand in sirul de caractere -str2- test1.out, test2.out etc pentru a putea fi accesat mai usor la scrierea in fisier
    f=fopen(str1,"r"); // deschide fisierul test1.in, test2.in etc in modul "citire"
    e=fopen(str2,"w"); // deschide fisierul test1.out, test2.out etc in modul "scriere"
    fscanf(f,"%d",&numar_noduri); // citeste numarul de noduri din fisier

    clock_t start, end;//functia clock cronometreaza timpul de executie al functiei kruskal
    int graf[numar_noduri][numar_noduri];

    initializare_matrice_adiacenta( numar_noduri,graf );
    start = clock();
    kruskal ( numar_noduri, graf );
    end = clock();
    float timp;
    timp = ( end - start ) / CLOCKS_PER_SEC;//se imparte la clocks_per_sec, deoarece instructiunea clock masoara in ticuri
    fprintf( e,"Durata de executie:%.12f", timp );


    }

    return 0;
}
