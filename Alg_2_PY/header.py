#     Scopul acestei functii este de a evita formarea ciclurilor.

#     De fiecare data cand se alege o muchie se verifica care este
#     nodul parinte al fiecarui nod din care este formata muchia.

#     Daca cele 2 noduri nu au fost atasate la arborele minim
#     de acoperire ( valoarea lor din nod_parinte[] este -1)
#     atunci muchia se ataseaza la arbore, iar primul nod
#     devine parintele celui de-al doilea ( nod_parinte[v] = u )
#     unde u si v reprezinta nodurile care delimiteaza muchia.

#     Daca muchia selectata are un nod atasat la arborele minim
#     de acoperire, iar celalalt nod nu este inclus in acesta
#     ( nod_parinte[] este -1 ), atunci acesta va fi adaugat la arbore.

#     Daca muchia selectata are ambele noduri in arbore, atunci
#     se verifica daca nu cumva adaugarea acestei muchii va fomra un ciclu.
#     Pentru fiecare nod se traverseaza din "parinte in parinte" pana se ajunge
#     la ultimul nod parinte (radacina). Daca pentru ambele noduri aceasta radacina
#     coincide, atunci muchia este inlaturata deoarece ar forma un ciclu.


def gaseste_parinte(nod, nod_parinte):
    while nod_parinte[nod] != -1:
        nod = nod_parinte[nod]
    return nod


#     Functie prin care se reunesc 2 noduri pentru a face parte
#     din acelasi arbore minim de acoperire.

#     Cu ajutorul functiei de mai sus ( gaseste_parinte ) cele doua noduri se reunesc
#     prin urmare a constatarii faptului ca fiecare dintre ele au o radacina a arborelui
#     diferita ( daca functia de mai sus ar returna aceeasi valoare pentru ambele noduri
#     ar insemna faptul ca se va forma un ciclu, iar reuniunea nu va avea loc)
def reuniune_noduri(u, v, nod_parinte):
    # u si v reprezinta cele doua noduri care au fost analizate
    # (nodurile care delimiteaza muchia)
    if u != v:
        # primul nod devine parintele celui de-al doilea
        nod_parinte[v] = u
        return 1
    return 0


def kruskal(numar_noduri, graf, str2):
    e = open(str2, "w")
    # prima variabila indica numarul de muchii din arbore
    # si este folosita pentru a opri cautarea atunci cand arborele
    # va avea numar_noduri - 1 muchii.
    numar_muchii_arbore = 1

    # a doua variabila calculeaza, la final, "costul" minim al arborelui gasit
    # prin adunarea valorilor asociate muchiilor din care este format.
    cost_arbore_minim = 0

    # variabile folosite mai tarziu in salvarea nodurilor care delimiteaza muchiile
    a = b = u = v = 0

    # Vector pentru a tine cont de parintele fiecarui nod
    # din arborele minim de acoperire format.
    # Initializam valorile din acest vector cu -1,
    # ceea ce inseamna ca toate nodurile sunt "libere" ( nu au nici un parinte )
    nod_parinte = [-1]*numar_noduri

    for i in range(0, numar_noduri):
        for j in range(0, numar_noduri):
            if graf[i][j] == 0:
                # Acolo unde nu exista legaturi dam o valoare cat mai mare
                # pentru a elimina elementul din cautarea valorii minime.
                graf[i][j] = 10000

    e.write("Muchiile din care este alcatuit arborele minim de acoperire sunt:")
    # Arborele minim de acoperire are intotdeauna numar_noduri - 1 muchii
    while numar_muchii_arbore < numar_noduri:
        # Variabila minim este folosita pentru a stoca
        # valoarea minima din matricea de adiacenta.
        # Initial ii dam o valoare cat mai mare
        # care nu se gaseste in matrice.
        minim = 10000
        for i in range(0, numar_noduri):
            for j in range(0, numar_noduri):
                if graf[i][j] < minim:
                    # Dupa parcurgerea integrala a matricei, in variabila minim
                    # se va afla muchia cu valoarea minima din graf.
                    minim = graf[i][j]

                    # Salvam de doua ori numarul fiecarui nod care delimiteaza muchia deoarece:
                    # - Prima data aceste valori se vor folosi in functia gaseste_parinte
                    #   in urma careia valorile se vor pierde ( numarul nodurilor ).
                    # - A doua oara se folosesc la final, in cazul in care nodurile vor fi reunite
                    #   in arborele minim de acoperire, pentru a indica nodurile care alcatuiesc muchia.
                    a = u = i
                    b = v = j

        u = gaseste_parinte(u, nod_parinte)
        v = gaseste_parinte(v, nod_parinte)

        # In cazul in care cele doua noduri sunt compatibile, muchia delimitata
        # de aceste noduri va fi adaugata la arbore.

        # De asemenea, numarul de muchii din arbore va creste cu o unitate, iar
        # la "costul" arborelui se va adauga valoarea muchiei adaugate.
        if reuniune_noduri(u, v, nod_parinte) != 0:
            e.write('\n{}.muchia  ( {} , {} ) = {}'.format(numar_muchii_arbore, a, b, minim))
            numar_muchii_arbore = numar_muchii_arbore + 1
            cost_arbore_minim = cost_arbore_minim + minim

        # Chiar daca muchia a fost adaugata sau nu la arbore, dupa ce
        # aceasta a fost testata, i se atribuie o valoare cat mai mare
        # pentru a nu fi inclusa din nou in cautarea urmatoare a valorii minime.
        graf[a][b] = graf[b][a] = 10000

    e.write("\nPrin urmare costul arborelui minim de acoperire gasit este: {}\n".format(cost_arbore_minim))
