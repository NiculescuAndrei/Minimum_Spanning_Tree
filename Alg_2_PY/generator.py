from random import randrange


#     Functie pentru a reprezenta graful sub forma unei matrici adiacente.

#     Valorile muchiilor sunt generate in mod aleatoriu de la 0 pana la 9999
#     prin intermediul functiei randrange din libraria random.

#     Prima data am initializat elementele matricei cu valoarea -1.

#     Deoarece nu exista muchii intre un nod si el insusi am pus
#     valoarea 0 atunci cand i = j.

#     Dupa aceea daca atat pe pozitia graf[i][j] cat si graf[j][i]
#     se afla valoarea -1, atunci se genereaza aleatoriu o valoare.

#     Daca pe una dintre cele 2 pozitii se afla o valoare, atunci
#     pe cealalta pozitie unde se afla valoarea -1 se va copia
#     acea valoare, deoarece graful este neorientat.
def initializare_matrice_adiacenta(numar_noduri, graf):
    for i in range(0, numar_noduri):
        for j in range(0, numar_noduri):
            graf[i][j] = -1
    for i in range(0, numar_noduri):
        for j in range(0, numar_noduri):
            if i == j:
                graf[i][j] = 0
            elif graf[i][j] == -1 and graf[j][i] == -1:
                graf[i][j] = randrange(0, 9999)
            else:
                graf[i][j] = graf[j][i]
            print(graf[i][j])
        print('')
