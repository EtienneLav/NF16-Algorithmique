#include "arbre.h"
#include "outils.h"
#include "liste.h"

ListePosition *creer_liste_positions(){
    // Fonction qui crée une liste de positions vide (renvoie NULL si echec)

    ListePosition* new_liste = malloc(sizeof (ListePosition));
    if(new_liste){

        new_liste->nb_elements=0;
        new_liste->debut=NULL;
        return new_liste;
    }
    else{
        perror("malloc");           //Renvoyer une signification de l'erreur
        return NULL;
    }
}


Position* creer_position(){
    // Fonction qui crée une liste de positions vide (renvoie NULL si echec)

    Position * new_position = (Position*) malloc(sizeof(Position));

    if(new_position){

        new_position->numero_ligne=0;
        new_position->ordre=0;
        new_position->numero_phrase=0;
        new_position->suivant=NULL;
        return new_position;
    }
    else {
        perror("malloc");  //Renvoyer une signification de l'erreur
        return NULL;

    }

}


int ajouter_position(ListePosition *listeP, int ligne, int ordre, int num_phrase) {
    // Fonction qui ajoute un élément dans une liste de positions en respectant l'ordre du mot dans le texte
    Position* new_pos;              // Créer la position

    new_pos = creer_position();
    new_pos->numero_ligne = ligne;
    new_pos->ordre = ordre;
    new_pos->numero_phrase = num_phrase;
    Position* pos_temp = listeP->debut;  // Variable temporairaire de type Position * pour parcourir la liste

    if(pos_temp==NULL){             // Si  la liste vide on insère en tête, cas idéal pour la complexité.
        listeP->debut=new_pos;
        new_pos->suivant=NULL;
        listeP->nb_elements++;
        return 1;
    }

    if((pos_temp->numero_ligne>ligne)&&(pos_temp->ordre>ordre)){   // Si inférieur à toutes les pos de la liste
        new_pos->suivant=listeP->debut;
        listeP->debut=new_pos;
        listeP->nb_elements++;
        return 1;
    }

    while ((pos_temp->suivant!=NULL)&&(pos_temp->numero_ligne<ligne)){ // Recherche de l'endroit où insérer précisemment
        pos_temp=pos_temp->suivant;
    }

    while ((pos_temp->suivant!=NULL)&&(pos_temp->ordre<ordre)){
        pos_temp=pos_temp->suivant;
    }
    new_pos->suivant = pos_temp->suivant;       // Insertion à sa place
    pos_temp->suivant=new_pos;
    listeP->nb_elements++;

    return 1;
}

