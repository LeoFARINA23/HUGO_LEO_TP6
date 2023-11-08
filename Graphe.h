//
// Created by hugo on 06/11/2023.
//

#ifndef HUGO_LEO_TP6_GRAPHE_H
#define HUGO_LEO_TP6_GRAPHE_H

#include <stdio.h>
#include <stdlib.h>


struct Arc {
    int sommet;        // Destination de l'arc
    int capacite;      // Capacité de l'arc
    struct Arc* arc_suivant; // Pointeur vers l'arc suivant
};


/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    int valeur;
    char* nom;
};

/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int ordre;
    pSommet* pSommet;
} Graphe;



// créer le graphe
Graphe* CreerGraphe(int ordre);


Graphe * lire_graphe(char * nomFichier);

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2, int capacite);

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num);
/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe);

#endif //HUGO_LEO_TP6_GRAPHE_H
