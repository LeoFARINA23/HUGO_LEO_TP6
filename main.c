#include "Graphe.h"
#include "file.h"
void afficher_successeurs(pSommet* sommet, int num) {
    printf("Sommet %s:\n", sommet[num]->nom);
    pArc arc = sommet[num]->arc;

    while (arc != NULL) {
        printf("Vers sommet %s avec capacite %d\n", sommet[arc->sommet]->nom, arc->capacite);
        arc = arc->arc_suivant;
    }
}


pSommet* CreerArete(pSommet* sommet, int s1, int s2, int capacite) {
    // Allouer la mémoire pour le nouvel arc
    pArc Newarc = (pArc)malloc(sizeof(struct Arc));

    Newarc->sommet = s2;
    Newarc->capacite = capacite;
    Newarc->arc_suivant = NULL;
    if (sommet[s1]->arc == NULL) {
        sommet[s1]->arc = Newarc;
    } else {

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

    Graphe* graphe = CreerGraphe(ordre);

    graphe->ordre = ordre;


    // Lire les noms des sommets
    for (int i = 0; i < ordre; ++i) {
        graphe->pSommet[i]->nom = (char*)malloc(sizeof(char));

        fscanf(file, "%s", graphe->pSommet[i]->nom);

    }
    int capacite;
    for (int i = 0; i < ordre; ++i) {
        for (int j = 0; j < ordre; ++j) {
            fscanf(file, "%d", &capacite);
            if (capacite > 0) {

                graphe->pSommet = CreerArete(graphe->pSommet, i, j, capacite);
            }
        }
    }

    fclose(file);
    return graphe;
}


/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe){

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