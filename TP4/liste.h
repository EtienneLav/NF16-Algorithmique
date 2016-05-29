#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arbre.h"
#include "outils.h"

typedef struct position{
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct position *suivant;
}Position;



struct listePosition {
    Position* debut;
    int nb_elements;
};
typedef struct listePosition ListePosition;

ListePosition *creer_liste_positions();
Position* creer_position();
int ajouter_position(ListePosition *listeP, int ligne, int ordre, int num_phrase);

#endif
