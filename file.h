//
// Created by hugo on 06/11/2023.
//

#ifndef HUGO_LEO_TP6_FILE_H
#define HUGO_LEO_TP6_FILE_H

/* Structure de al file */
typedef struct FIFO {
    int* elements;
    int tete;
    int queue;
    int max;
} FIFO;

typedef struct Graphe Graphe;
extern int val_init;

FIFO* creer_file(int taille);
void enfile(FIFO* f, int valeur);
int defile(FIFO* f);
int file_vide(FIFO* f);
void BFS(Graphe* g, int sommet_init);

#endif //HUGO_LEO_TP6_FILE_H
