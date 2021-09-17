#   Functie pentru a gasi nodul cu cea mai mica valoare asociata si care nu a fost inca vizitat.

#   Pe masura ce parcurgem graful asociem nodurilor adiacente nodului curent valoarea muchiei
#   prin care sunt legate de nodul curent, pana cand nodurile devine vizitate in cele din urma.

#   In cazul in care, repepetand pasul de mai sus, se gaseste o muchie cu o valoare mai mica
#   decat cea care este deja atasata in nodul corespunzator,
#   iar nodul nu este inca vizitat, se va actualiza cu aceasta valoare.


def determinare_valoare_minima(numar_noduri, valori_noduri, noduri_vizitate):
    minim = 10000
    pozitie_minim = 0
    for i in range(0, numar_noduri):
        if valori_noduri[i] < minim and noduri_vizitate[i] == 0:
            minim = valori_noduri[i]
            pozitie_minim = i
    return pozitie_minim


#   Functie pentru a afisa muchiile arborelui minim de acoperire gasit si valorile acestora
#   cu ajutorul vectorului nod_parinte in care se afla nodul "parinte" al fiecarui nod vizitat
#   pentru a putea determina muchiile din care este compus arborele.

#   De asemenea, in aceasta functie, este calculata si suma acestor valori pentru a determina "costul" arborelui gasit.
def afisare_arbore_minim(numar_noduri, nod_parinte, graf, str2):
    e = open(str2, "w")
    cost_arbore_minim = 0
    e.write("Muchiile din care este alcatuit arborele minim de acoperire sunt:")
    # contorul i porneste de la 1 deoarece nodul 0 reprezinta radacina arborelui
    for i in range(1, numar_noduri):
        e.write('\n{}.muchia ( {} , {} ) = {}'.format(i, nod_parinte[i], i, graf[i][nod_parinte[i]]))
        cost_arbore_minim = cost_arbore_minim + graf[i][nod_parinte[i]]
    e.write("\nPrin urmare costul arborelui minim de acoperire gasit este: {}\n".format(cost_arbore_minim))


#   Functie pentru a construi arborele minim de acoperire a unui graf
#   reprezentat cu ajutorul unei matrici de adiacenta.

#   Construirea arborelui se bazeaza pe algoritmul de tip Greedy numit Prim.
def arbore_minim_de_acoperire_prim(numar_noduri, graf, str2):
    # Vector pentru a stoca "parintele" fiecarui nod vizitat
    # ce urmeaza a fi folosit in afisarea laturilor care formeaza arborele.
    nod_parinte = [0]*numar_noduri

#   Vector pentru a asocia nodurilor adiacente nodului curent
#   valorile muchiilor de care sunt legate
#   atata timp cat aceste noduri nu au fost inca vizitate.

#   Daca in urma repetarii acestui pas se gaseste o muchie
#   cu o valoare mai mica decat cea asociata deja nodului corespunzator,
#   aceasta noua valoare va fi asociata nodului daca acesta nu a fost deja vizitat.
    valori_noduri = [10000]*numar_noduri  # Initializam valorile in noduri cu numere cat mai mari

#   Vector pentru a tine cont de nodurile care au fost vizitate sau nu.
#   0 - va insemna nod nevizitat, iar 1 - nod vizitat.
#   Initial nici un nod nu este vizitat.
    noduri_vizitate = [0]*numar_noduri

#   Dand valoarea 0 primului nod asiguram faptul ca acesta va fi ales primul
#   din vectorul valori_noduri cu ajutorul functiei determinare_valoare_minima.
    valori_noduri[0] = 0

#   Din moment ce primul nod este de fapt radacina arborelui minim de acoperire
#   acesta nu are nici un nod "parinte".
    nod_parinte[0] = -1

    for i in range(0, numar_noduri):
        # Alegem de fiecare data nodul cu cea mai mica valoare asociata
        # din multimea de noduri care nu este deja inclusa in arbore.
        # Valorile vor fi actualizate mereu in vectorul valori_noduri.
        u = determinare_valoare_minima(numar_noduri, valori_noduri, noduri_vizitate)
        noduri_vizitate[u] = 1  # Odata ales nodul, acesta va fi marcat ca si vizitat in vectorul noduri_vizitate.

        # In urmatorul for se actualizeaza mereu valorile si parintii nodurilor adiacente
        # nodului selectat prin intermediul variabilei u de mai sus.

        # De asemenea, se iau in considerare doar acele noduri care nu au fost deja vizitate.
        for v in range(0, numar_noduri):
            # graf[u][v] va avea valoare nenula numai in cazul in care
            # exista o muchie intre u si v (nodurile sunt adiacente).

            # noduri_vizitate[v] va avea valoarea 0 numai daca
            # nodul v nu a fost inca vizitat.

            # Valoarea corespunzatoare nodului v va fi actualizata numai daca
            # valoarea muchiei este mai mica decat valoarea deja atribuita nodului.
            if graf[u][v] != 0 and noduri_vizitate[v] == 0 and graf[u][v] < valori_noduri[v]:
                nod_parinte[v] = u
                valori_noduri[v] = graf[u][v]

    # Prin intermediul functiei de afisare, output-ul programului va fi urmatorul:
    # - muchiile din care este compus arborele cu valorile corespunzatoare acestora.
    # - suma tuturor acestor valori pentru a indica "costul" arborelui minim de
    #   acoperire gasit prin intermediul algoritmului Prim.
    afisare_arbore_minim(numar_noduri, nod_parinte, graf, str2)
