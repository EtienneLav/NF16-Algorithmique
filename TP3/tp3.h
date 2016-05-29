#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


enum genre_jeu
{
    PLATEAU, RPG, COOPERATIF, AMBIANCE, HASARD
};
typedef enum genre_jeu genre_jeu;


struct jeu
{
    char* nom;
    genre_jeu genre;
    int nbJoueurMin;
    int nbJoueurMax;
    int duree;
    struct jeu* suivant;
};
typedef struct jeu t_jeu;

struct ludotheque
{
    int nb_jeu;
    t_jeu * debut;
};
typedef struct ludotheque t_ludotheque;

t_ludotheque * creer_ludotheque();
t_jeu * creer_jeu(char * nom, enum genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree);
int ajouter_jeu(t_ludotheque* ludo, t_jeu* j);
void affiche_ludotheque(t_ludotheque * ludo) ;
int retirer_jeu(t_ludotheque* ludo, char* nom) ;
void supprimer_ludotheque(t_ludotheque * ludo);
t_ludotheque * requete_jeu(t_ludotheque * ludo, enum genre_jeu genre, int nbJoueurs, int duree) ;
t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2) ;
t_ludotheque* fusion_deux_ludo(t_ludotheque * ludo1, t_ludotheque * ludo2) ;
t_ludotheque * copier_ludo (t_ludotheque * ludo);
int liste_ludotheque(t_ludotheque* tab_ludo[10]);
int nombre_ludotheque (t_ludotheque* tab_ludo[10]);
int indice_jeu (t_jeu * tab_jeu[20]);
int premiere_case_vide (t_ludotheque* tab_ludo[10]);

#endif // TP3_H_INCLUDED


