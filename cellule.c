//
// Created by hugo on 05/10/2023.
//
#include "file.h"
#include "Graphe.h"

// Fonction pour créer une nouvelle file vide
FIFO* creer_file(int taille) {
    // creation file
    FIFO* f = (FIFO*)malloc(sizeof(FIFO));
    f->elements = (int*)malloc(taille * sizeof(int));
    f->tete = -1;
    f->queue = -1;
    f->max = taille;

    return f;
}

// Fonction pour ajouter une valeur à la fin de la file
void enfile(FIFO* f, int valeur) {
    // Vérifier si la file est pleine
    if (f->queue == f->max - 1) {
        return;
    } else {
        // Si la file est vide, initialiser la tête à 0
        if (f->tete == -1) {
            f->tete = 0;
        }

        // Ajouter la valeur à la position de la queue et déplacer la queue vers l'arrière
        f->queue += 1;
        f->elements[f->queue] = valeur;
    }
}

// Fonction pour retirer et retourner la valeur de l'avant de la file
int defile(FIFO* f) {
    int element;
    // Vérifier si la file est vide
    if (file_vide(f)) {
        return -1;
    } else {
        // Obtenir la valeur de a tete de la file
        element = f->elements[f->tete];

        // Déplacer la tête vers l'arrière
        f->tete += 1;

        // Si la tête dépasse la queue, réinitialiser la file à vide
        if (f->tete > f->queue) {
            f->tete = f->queue = -1;
        }

        return element;
    }
}

// Fonction pour vérifier si la file est vide
int file_vide(FIFO* f) {
    // Si la queue est à -1, la file est vide
    if (f->queue == -1) {
        return 1;
    }
    return 0;
}


void BFS(Graphe* g, int sommet_init) { //déclaration de la fonction BFS
    int taille = g->ordre;
    sommet_init -= val_init; // récupération de l'ordre du graphe
    int decouvert[taille];
    int pred[taille]; // Prédécesseurs de chaque sommet

    for (int i = 0; i < taille; i++) {
        decouvert[i] = 0;  // Aucun sommet n'est visité
        pred[i] = -1;  // Prédécesseur de chaque sommet est initialisé à -1 pour être sur de commencer à 0
    }

    FIFO *f = creer_file(taille); //création d'une file

    enfile(f, sommet_init);
    decouvert[sommet_init] = 1;
    /*Si un sommet voisin n'a pas été découvert, il est ajouté à la file, marqué comme découvert,
    et son prédécesseur est mis à jour : */
    while (!file_vide(f)) {
        int valeur_actuelle = defile(f);
        pArc arc = g->pSommet[valeur_actuelle]->arc;

        while (arc) {
            if (!decouvert[arc->sommet]) {
                enfile(f, arc->sommet);
                decouvert[arc->sommet] = 1;
                pred[arc->sommet] = valeur_actuelle;
            }
            arc = arc->arc_suivant;
        }
    }
    printf("%d\n", sommet_init + (g->orientation ? 2 : 0)); //on affiche les resultats du graphe tous en précisant si c'est un graphe orienté ou pas orienté

    for (int i = 0; i < taille; i++) {
        if (i != sommet_init && decouvert[i]) { // boucle pour remonter la chaine de tous les prédecesseurs du sommet_init jusqu-au sommet actuel
            printf("%d", i + (g->orientation ? 2 : 0));
            int j = i;
            while (pred[j] != -1) {
                printf(" <- %d", pred[j] + (g->orientation ? 2 : 0));
                j = pred[j];
            }
            printf("\n");
        }
    }

}

