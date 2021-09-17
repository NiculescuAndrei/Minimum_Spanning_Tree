from numpy import *
from header import *
from generator import *
import time

for i in range(1, 11):
    # scrie pe rand in sirul de caractere -str1- date1.in, date2.in etc
    # pentru a putea fi accesat mai usor la citirea din fisier
    str1 = "date{}in.txt".format(i)
    # scrie pe rand in sirul de caractere -str1- date1.out, date2.out etc
    # pentru a putea fi accesat mai usor la scrierea in fisier
    str2 = "date{}out.txt".format(i)

    f = open(str1, "r")  # deschide fisierul test1.in, test2.in etc in modul "citire"
    e = open(str2, "a")  # deschide fisierul test1.out, test2.out etc astfel incat sa se poata adauga la finalul lui.

    numar_noduri = f.readline()  # citeste numarul de noduri din fisier
    numar_noduri = int(numar_noduri)  # converteste din string in int

    # functia arange initializeaza un vector de numar_noduri*numar_noduri elemente
    # in care primul element este 0, pasul este 1, iar ultimul element este
    # (numar_noduri*numar_noduri)-1. Aceste valori vor fi modificate mai tarziu
    # in generatorul aleatoriu de date de intrare.
    # functia reshape transforma acest vector intr-o matrice cu numar_noduri linii si coloane.
    # ambele functii se afla in libraria numpy.
    graf = arange(numar_noduri*numar_noduri).reshape((numar_noduri, numar_noduri))

    initializare_matrice_adiacenta(numar_noduri, graf)

    start = time.time()
    kruskal(numar_noduri, graf, str2)
    finish = time.time()
    e.write('Timpul de executie: {}'.format(finish-start))