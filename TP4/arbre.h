#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"
#include "outils.h"


struct noeudABR {
    char* mot;
    ListePosition* positions;
    struct noeudABR* filsGauche;
    struct noeudABR* filsDroit;
};
typedef struct noeudABR NoeudABR;

struct arbreBR {
    NoeudABR* racine;
    int nb_mots_differents;
    int nb_mots_total;
};
typedef struct arbreBR ArbreBr;




ArbreBr *creer_abr();
int ajouterMot(ArbreBr* a, char* mot, int ligne, int ordre, int numphrase);
int charger_fichier(ArbreBr *arbre);
NoeudABR *rechercher_noeud(ArbreBr *arbre, char *mot);
void afficher_arbre(ArbreBr* arbre);
void afficher_mot (NoeudABR* noeud);
void effacer_arbre(NoeudABR* racine);
NoeudABR* ABR_Minimum (NoeudABR* racine);
NoeudABR* Pere(ArbreBr* arb, NoeudABR* n);
NoeudABR* Successeur(ArbreBr* arb, NoeudABR* n);
int* ProfondeurArbre(NoeudABR* racine, int prof, int* profMax);
int equilibre (ArbreBr* arb);

#endif

