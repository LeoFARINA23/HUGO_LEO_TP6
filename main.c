#include "Graphe.h"
#include "file.h"
int val_init = 0;
void afficher_successeurs(pSommet * sommet, int num)
{
    printf(" sommet %d :\n", num + val_init);
    pArc arc = sommet[num]->arc;

    while(arc != NULL)
    {
        printf("%d ", arc->sommet + val_init);
        arc = arc->arc_suivant;
    }
}

pSommet* CreerArete(pSommet* sommet, int s1, int s2)

{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp=sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            temp->sommet=s2;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
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

Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FIFO * ifs = fopen(nomFichier, "r");
    int taille, orientation, ordre, s1, s2;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }

    fscanf(ifs, "%d", &ordre);
    fscanf(ifs, "%d", &taille);
    fscanf(ifs, "%d", &orientation);

    if (orientation == 1) // Si le graphe est orienté, on a met l'val_init à 2
    {
        val_init = 2;
    }

    graphe = CreerGraphe(ordre);
    graphe->orientation = orientation;
    graphe->ordre = ordre;

    for (int i = 0; i < taille; ++i)
    {
        fscanf(ifs, "%d%d", &s1, &s2);

        s1 -= val_init;
        s2 -= val_init;

        graphe->pSommet = CreerArete(graphe->pSommet, s1, s2);
        if (!orientation)
            graphe->pSommet = CreerArete(graphe->pSommet, s2, s1);
    }

    return graphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("\ngraphe ");

    if(graphe->orientation)
        printf("oriente = 1\n");
    else
        printf("non oriente = 0\n");

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
    int sommetinit;

    printf("entrer le nom du fichier du labyrinthe:");
    gets(nom_fichier);

    g = lire_graphe(nom_fichier);
    printf("numero du sommet initial : ");
    scanf("%d", &sommetinit);


    graphe_afficher(g);
    printf("\nBFS :\n");
    BFS(g, sommetinit);
    return 0;
}