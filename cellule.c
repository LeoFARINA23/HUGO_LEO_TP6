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


void BFS(Graphe* g, int sommet_init) {
    int taille = g->ordre;
    int decouvert[taille];
    int pred[taille]; // Prédécesseurs de chaque sommet

    // Initialisation des tableaux decouvert et pred
    for (int i = 0; i < taille; i++) {
        decouvert[i] = 0;  // Aucun sommet n'est visité
        pred[i] = -1;  // Prédécesseur de chaque sommet est initialisé à -1
    }

    // Création d'une file
    FIFO *f = creer_file(taille);

    // Enfiler le sommet initial et marquer comme découvert
    enfile(f, sommet_init);
    decouvert[sommet_init] = 1;

    // Boucle tant que la file n'est pas vide
    while (!file_vide(f)) {
        int sommet_courant = defile(f);
        pArc arc = g->pSommet[sommet_courant]->arc;

        // Parcourir tous les arcs du sommet courant
        while (arc) {
            if (!decouvert[arc->sommet]) {
                enfile(f, arc->sommet);
                decouvert[arc->sommet] = 1;
                pred[arc->sommet] = sommet_courant;
            }
            arc = arc->arc_suivant;
        }
    }

    // Affichage des chemins depuis sommet_init jusqu'aux autres sommets
    for (int i = 0; i < taille; i++) {
        if (i != sommet_init && decouvert[i]) {
            printf("Chemin jusqu'à %s: ", g->pSommet[i]->nom);
            int j = i;
            // Remontée de la chaîne des prédécesseurs
            while (pred[j] != -1) {
                printf("%s <- ", g->pSommet[j]->nom);
                j = pred[j];
            }
            printf("%s\n", g->pSommet[sommet_init]->nom);
        }
    }

    // Libération de la mémoire allouée à la file
    free(f->elements);
    free(f);
}

