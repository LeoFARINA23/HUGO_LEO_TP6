#include "Graphe.h"
#include "file.h"
void afficher_successeurs(pSommet* sommet, int num) {
    printf("Sommet %d:\n", num);
    pArc arc = sommet[num]->arc;

    while (arc != NULL) {
        printf("Vers sommet %d avec capacite %d\n", arc->sommet, arc->capacite);
        arc = arc->arc_suivant;
    }
}


pSommet* CreerArete(pSommet* sommet, int s1, int s2, int capacite) {
    // Allouer la mémoire pour le nouvel arc
    pArc Newarc = (pArc)malloc(sizeof(struct Arc));
    if (Newarc == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'arc.\n");
        exit(EXIT_FAILURE);
    }
    Newarc->sommet = s2;
    Newarc->capacite = capacite;  // Ajout de la capacité à la structure de l'arc
    Newarc->arc_suivant = NULL;

    // Si le sommet s1 n'a pas d'arc, lui ajouter directement le nouvel arc
    if (sommet[s1]->arc == NULL) {
        sommet[s1]->arc = Newarc;
    } else {
        // Sinon, parcourir la liste des arcs de s1 et ajouter le nouvel arc à la fin
        pArc temp = sommet[s1]->arc;
        while (temp->arc_suivant != NULL) {
            temp = temp->arc_suivant;
        }
        temp->arc_suivant = Newarc;
    }

    return sommet;
}


// créer le graphe
Graphe* CreerGraphe(int ordre)
{
    Graphe * Newgraphe = (Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre * sizeof(pSommet));

    for(int i = 0; i < ordre; i++)
    {
        Newgraphe->pSommet[i] = (pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur = i;
        Newgraphe->pSommet[i]->arc = NULL;
    }
    return Newgraphe;
}

Graphe* lire_graphe(char* nomFichier) {
    FILE *file = fopen(nomFichier, "r");
    if (!file) {
        printf("Erreur de lecture du fichier\n");
        exit(-1);
    }

    int ordre;
    fscanf(file, "%d", &ordre);

    // Lire et ignorer les noms des sommets pour le moment
    char temp[256];
    for (int i = 0; i < ordre; ++i) {
        fscanf(file, "%s", temp);
    }

    Graphe* graphe = CreerGraphe(ordre);

    int capacite;
    for (int i = 0; i < ordre; ++i) {
        for (int j = 0; j < ordre; ++j) {
            fscanf(file, "%d", &capacite);
            if (capacite > 0) {
                // Ajouter une arête seulement si la capacité est supérieure à zéro
                graphe->pSommet = CreerArete(graphe->pSommet, i, j, capacite);
            }
        }
    }

    fclose(file);
    return graphe;
}


/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("\ngraphe ");

    printf("\nordre = %d\n",graphe->ordre);

    printf("\nlistes d'adjacence :\n\n");

    for (int i=0; i<graphe->ordre; i++)
    {
        afficher_successeurs(graphe->pSommet, i);
        printf("\n");
    }

}

int main() {
    Graphe *g;

    char nom_fichier[50];

    printf("entrer le nom du fichier du labyrinthe:");
    gets(nom_fichier);

    g = lire_graphe(nom_fichier);



    graphe_afficher(g);

    return 0;
}