#include <stdio.h>
#include <stdlib.h>

typedef struct Position T_Position;
struct Position
{
    int numeroLigne;
    int ordre;
    int numeroPhrase;
    struct Position* suivant;
};

typedef struct Noeud T_Noeud;
struct Noeud
{
    char* mot;
    int nbOccurences;
    T_Position* listePositions;
    struct Noeud* filsGauche;
    struct Noeud* filsDroit;
};

typedef struct Index T_Index;
struct Index
{
    T_Noeud* racine;
    int nbMotsDistincts;
    int nbMotsTotal;
};
int isBefore(T_Position* position, int ligne, int ordre) //Dit si ligne, ordre est avant position
{
    if(position==NULL)
    {
        return 1;
    }
    return (ligne < position->numeroLigne || ((ligne == position->numeroLigne ) && (ordre < position->ordre)));
}
T_Position *ajouterPosition(T_Position *listeP, int ligne, int ordre, int phrase)
{
    T_Position* new_position = malloc(sizeof(T_Position));
    new_position->numeroLigne = ligne;
    new_position->ordre = ordre;
    new_position->numeroPhrase = phrase;
    new_position->suivant = NULL;
    if (listeP == NULL)
    {
        //Definir comme l'avant
        return new_position;
    }
    else if (isBefore(listeP, ligne, ordre))
    {
        //l'inserer à l'avant
        new_position->suivant = listeP;
        return new_position;
    }
    else
    {

        T_Position* positionToCheck = listeP; //On commence à la racine de la liste chainée
        while(positionToCheck->suivant != NULL || !isBefore(positionToCheck->suivant, ligne, ordre))
        {
            positionToCheck = positionToCheck->suivant;
        }
        //positionToCheck est la position qui est juste avant celle où on doit inserer
        T_Position* tmpPosition = positionToCheck->suivant; //On sauvegarde le suivant de positionToCheck
        positionToCheck->suivant = new_position;
        new_position->suivant = tmpPosition;
        return listeP;
    }
}

int main()
{
    T_Position* racine = ajouterPosition(NULL, 11, 15, 1);

    racine = ajouterPosition(racine, 12, 15, 1);
    racine = ajouterPosition(racine, 12, 17, 1);

    racine = ajouterPosition(racine, 12, 5, 1);

    T_Position* positionToCheck = racine; //On commence à la racine de la liste chainée
    while(positionToCheck->suivant != NULL)
    {
        printf("%d | %d\n", positionToCheck->numeroLigne, positionToCheck->ordre);
        positionToCheck = positionToCheck->suivant;
    }
    return 0;
}
