#include "tp3.h"
#include<string.h>


t_ludotheque * creer_ludotheque(){ //Cette fonction crée une ludotheque et affecte un espace mémoire

t_ludotheque* ludo_vide = malloc(sizeof (t_ludotheque));

  if (ludo_vide){
        ludo_vide->nb_jeu = 0;
        ludo_vide->debut = NULL;
        return ludo_vide;
  }
  else
    return NULL; //Retourne null si la ludotheque n'a pas été créée
}

t_jeu * creer_jeu(char * nom, enum genre_jeu genre, int nbJoueurMin, int nbJoueurMax, int duree){

//Cette fonction crée un nouveau jeu

    t_jeu * new_jeu = malloc(sizeof(t_jeu)); //Allocation de la mémoire
    if(new_jeu)
    {
        char* name = malloc(20* sizeof(char)); //Le nom étant un pointeur sur chaine de caractère une affectation ne suffit pas
        strcpy(name,nom);
        new_jeu->nom   = name;
        new_jeu->genre = genre;
        new_jeu->nbJoueurMin = nbJoueurMin;
        new_jeu->nbJoueurMax = nbJoueurMax;
        new_jeu->duree = duree;
        new_jeu->suivant=NULL;
        return new_jeu;
    }
    else
        return NULL;
}

int ajouter_jeu(t_ludotheque* ludo, t_jeu* j){

//Cette fonction ajoute un jeu dans la ludotheque précisée en argument

     if(!ludo){
        printf("Cette ludotheque n'existe pas\n");
        return 0;
        }
    t_jeu* jeu_temp = ludo->debut;
    if ((jeu_temp==NULL)||(strcmp((j->nom),(jeu_temp->nom))<0)){ //Si j inférieur à premier ou ludo vide
            j->suivant=ludo->debut;
            ludo->debut=j;
            ludo->nb_jeu++;
            return 1;
        }

        else{
            while ((jeu_temp->suivant)!=NULL && strcmp((j->nom),(jeu_temp->suivant->nom))>0){
                jeu_temp=jeu_temp->suivant;
            }
            j->suivant =jeu_temp->suivant;
            jeu_temp->suivant = j;
            ludo->nb_jeu++;
            return 1;
        }
}

void affiche_ludotheque(t_ludotheque * ludo) {

//Affichage de la ludotheque précisée en argument

    char esp = ' ';
    if(!ludo) {
        printf("\n\nCette ludotheque n'existe pas\n\n");
    }
    else{
        printf("--------------------------------------------------------------------------------");
        printf("%10c|Nom%10c|Type%10c|Nombre de Joueurs%10c|Duree (min)%1c", esp, esp, esp, esp, esp);
        printf("--------------------------------------------------------------------------------");
        printf("--------------------------------------------------------------------------------");


        t_jeu* jeu_temp = ludo->debut;
        while (jeu_temp!=NULL){
            char* type;
            switch(jeu_temp->genre){   //Switch pour expliciter la variable énumérée
                case 0: type ="PLATEAU"; break;
                case 1 : type="RPG"; break;
                case 2 : type= "COOPERATIF"; break;
                case 3 : type = "AMBIANCE"; break;
                case 4 : type = "HASARD"; break;
                default : type = "AUTRE"; break;
            }


            printf("%10c|%-13s|%-14s|%d-%-25d|%-10d\n",esp,jeu_temp->nom, type, jeu_temp->nbJoueurMin, jeu_temp->nbJoueurMax, jeu_temp->duree);
            jeu_temp=jeu_temp->suivant;
        }
        printf("--------------------------------------------------------------------------------");
        printf("Total : %d jeu[x]\n", ludo->nb_jeu);
        printf("--------------------------------------------------------------------------------\n\n");
    }
}

int retirer_jeu(t_ludotheque* ludo, char* nom) {

//cette fonction retire un jeu de la ludotheque précisée

    t_jeu* jeu_temp = ludo->debut;
    t_jeu* memoire=jeu_temp;
    t_jeu* supp;

    if ((!ludo)||(jeu_temp==NULL)){   //Si la ludotheque est inexistante ou vide
        printf("\nLa ludotheque n'existe pas ou est vide..\n");
        return 0;
    }
    else if ((jeu_temp->suivant)==NULL){
            //Un seul jeu
            ludo->debut=NULL;
            ludo->nb_jeu--;
            return 1;
    }
    else{
            if(strcmp(jeu_temp->nom,nom)==0){//Retrait du premier jeu
                    ludo->debut=jeu_temp->suivant;
                    ludo->nb_jeu--;
                    return 1;
            }
            while ((strcmp(jeu_temp->nom,nom)!=0) && ((jeu_temp->suivant)!=NULL)){  //Parcours de la liste chainée
                    memoire=jeu_temp;
                    jeu_temp=jeu_temp->suivant;
            }
            if((strcmp((jeu_temp->nom),nom))==0){
                    supp = memoire->suivant;
                    memoire->suivant=jeu_temp->suivant;
                    ludo->nb_jeu--;
                    free(supp);
                    return 1;

            }
            else{
                printf("Le jeu n'existe pas\n");
                return 0;
            }

    }
}

void supprimer_ludotheque(t_ludotheque * ludo){

//Supprime une ludotheque et libère la mémoire

    if (!ludo)
        printf("cette ludotheque n'existe pas...\n");
    else{
        t_jeu* jeu_temp = ludo->debut;
        t_jeu* memoire;

            while(jeu_temp!=NULL){
                memoire=jeu_temp;
                jeu_temp=jeu_temp->suivant;
                free(memoire);   //Libération de la mémoire de chaque jeu
            }
    }
    free(ludo);
}


t_ludotheque * fusion(t_ludotheque * ludo1, t_ludotheque * ludo2) {

    t_ludotheque* ludo_fusion = creer_ludotheque();
    t_jeu* jeu_temp;// = ludo1->debut;
    t_jeu* jeu_suiv;


    //Si ludo1 vide ou inconnue
    if((!ludo1)||((ludo1->debut)==NULL)){
        printf("ludo1 vide ou inconnue\n");
        return ludo2;
    }

    //si ludo2 vide ou inconnue
    else if((!ludo2)||((ludo2->debut)==NULL)){
        printf("ludo2 inconnue ou vide\n");
        return ludo1;
    }

//On ajoute tous les jeux de ludo1 puis ceux de ludo2
//La fonction ajouter trie les jeux par ordre lexicographique

    else {
            jeu_temp=ludo1->debut;
        while (jeu_temp!=NULL){
            jeu_suiv=jeu_temp->suivant;
            ajouter_jeu(ludo_fusion, jeu_temp);
            jeu_temp = jeu_suiv;
        }

        jeu_temp=ludo2->debut;
        while (jeu_temp!=NULL){
            jeu_suiv=jeu_temp->suivant;
            ajouter_jeu(ludo_fusion, jeu_temp);
            jeu_temp = jeu_suiv;
        }

        return ludo_fusion;
    }

}


t_ludotheque * requete_jeu(t_ludotheque * ludo, enum genre_jeu genre, int nbJoueurs, int duree) {


    if ((!ludo)||((ludo->debut)==NULL)){
        printf("La ludotheque est inconnue ou vide\n");
        return NULL;
    }
    else {
        t_jeu* jeu_iterateur = ludo->debut;
        t_jeu* jeu_suiv;

         //On copie ludo la ludothèque des jeux possibles

        t_ludotheque* jeux_possibles;
        jeux_possibles=copier_ludo(ludo);

//Pour chaque critère on retire les jeux qui ne correspondent pas



        jeu_iterateur = jeux_possibles->debut;
        while(jeu_iterateur!=NULL){ //parcours de la ludotheque
                jeu_suiv=jeu_iterateur->suivant;
            if((genre!=-1)&&(jeu_iterateur->genre!=genre)) {
                //Suppression si genre different
                retirer_jeu(jeux_possibles, jeu_iterateur->nom);
            }

            else if((nbJoueurs!=-1)&&(!((jeu_iterateur->nbJoueurMin<= nbJoueurs)&&(jeu_iterateur->nbJoueurMax>=nbJoueurs)))){
                //Suppression si nb joueurs different
                retirer_jeu(jeux_possibles, jeu_iterateur->nom);
            }
            else if (duree!=-1){
                //Calcul de l'intervalle de duree
                float ecart=0;
                ecart=((10.0*(jeu_iterateur->duree))/100);
                //Retrait jeu si pas dans intervalle de duree
                if(!((((jeu_iterateur->duree)-ecart)<=duree)&&((jeu_iterateur->duree)+ecart)>=duree)){
                    retirer_jeu(jeux_possibles, jeu_iterateur->nom);
                }
            }

            jeu_iterateur=jeu_suiv;
        }

        return jeux_possibles;
    }
}


t_ludotheque* fusion_deux_ludo(t_ludotheque * ludo1, t_ludotheque * ludo2){

        int i;
        t_ludotheque * new_ludo;
        t_ludotheque * new_ludo2;
        int test;


        t_jeu* jeu_temp;// = ludo1->debut;
        t_jeu* jeu_suiv;


    //Si ludo1 vide ou inconnue
    if((!ludo1)||((ludo1->debut)==NULL)){
        printf("\nLa premiere ludo est vide ou inconnue ... ");
        printf("\nLa fusion renvoie donc la seconde ludotheque entiere\n");
        new_ludo=copier_ludo(ludo2);
        return new_ludo;
    }

    //Si ludo2 vide ou inconnue
    else if((!ludo2)||((ludo2->debut)==NULL)){
        printf("\nLa seconde ludo est vide ou  inconnue ...\n");
        printf("\nLa fusion renvoie donc la premiere ludotheque entiere\n");
        new_ludo=copier_ludo(ludo1);
        return new_ludo;
    }

//On ajoute tous les jeux de ludo1 puis ceux de ludo2
//La fonction ajouter trie les jeux

    else {
            new_ludo=copier_ludo(ludo1);
            new_ludo2=copier_ludo(ludo2);
            jeu_temp=new_ludo2->debut;

        while (jeu_temp!=NULL){
            jeu_suiv=jeu_temp->suivant;
            ajouter_jeu(new_ludo, jeu_temp);
            jeu_temp = jeu_suiv;
        }


        //Gestion des doublons
        jeu_temp= new_ludo->debut;

        while ((jeu_temp->suivant)!=NULL){


            if ((strcmp(jeu_temp->nom, (jeu_temp->suivant)->nom)== 0) && (jeu_temp->duree == (jeu_temp->suivant)->duree) && (jeu_temp->genre == (jeu_temp->suivant)->genre) && (jeu_temp->nbJoueurMax == (jeu_temp->suivant)->nbJoueurMax) && (jeu_temp->nbJoueurMin == (jeu_temp->suivant)->nbJoueurMin))  {


                    if ((jeu_temp->suivant)->suivant==NULL)
                        jeu_temp->suivant = NULL;

                    else
                    {
                        if ((jeu_temp->suivant)->suivant==NULL)
                            jeu_temp->suivant = NULL;
                        jeu_temp->suivant = (jeu_temp->suivant)->suivant;
                        jeu_temp= jeu_temp->suivant;
                    }

                }
            else
                jeu_temp= jeu_temp->suivant;

        }
        printf("\n\nVoici la ludotheque creee \n");

        affiche_ludotheque(new_ludo);

        return new_ludo;


    }

}


t_ludotheque * copier_ludo (t_ludotheque * ludo){

//Copie de la ludotheque en entier

        t_jeu* jeu_temp = ludo->debut;
        t_ludotheque* new_ludo = malloc(sizeof(t_ludotheque));
        t_jeu* new_jeu = malloc(sizeof(t_jeu));
        new_ludo->debut=new_jeu;
        new_ludo->nb_jeu=0;

        while( jeu_temp!=NULL){

            new_ludo->nb_jeu++;
            char* name=malloc(20*(sizeof(char)));
            strcpy(name,jeu_temp->nom);
            new_jeu->nom=name;
            new_jeu->genre=jeu_temp->genre;
            new_jeu->nbJoueurMin=jeu_temp->nbJoueurMin;
            new_jeu->nbJoueurMax=jeu_temp->nbJoueurMax;
            new_jeu->duree=jeu_temp->duree;
            t_jeu* jeu_suiv = malloc(sizeof(t_ludotheque));
            new_jeu->suivant=jeu_temp->suivant;
            new_jeu=malloc(sizeof(t_ludotheque));
            new_jeu=jeu_suiv;
            jeu_temp=jeu_temp->suivant;
    }

    return new_ludo;
}

int liste_ludotheque(t_ludotheque* tab_ludo[10]){


    // Cette fonction affiche les ludotheques disponibles et renvoie leur nombre

        int tab_temp[20];
        int i = 0;
        int m = 0;
        int k =0;

        for (i=0; i< 10; i++){

            if (tab_ludo[i] != NULL){
                tab_temp[k] = i;
                k++;
            }
        }

        if (!(k))
                ;

        else if (k==1)
            printf("|%d|",tab_temp[k-1]);

        else {
            for (m=0; m< k; m++)
                printf("|%d|",tab_temp[m]);

        }

        return k;
}

int nombre_ludotheque (t_ludotheque* tab_ludo[10]){ // Cette fonction retourne le nombre de ludotheque(s) existante(s)


        int i;
        int nbre= 0;

        for (i=0; i< 10; i++){
            if (tab_ludo[i] != NULL)
                    nbre++;
                }
        return nbre;
}

int indice_jeu (t_jeu* tab_jeux[20]){
        int i = 0;

            while (tab_jeux[i]!=NULL){
                i++;
            }
        return i;

}


 int premiere_case_vide (t_ludotheque* tab_ludo[10]){  //Cette fonction parcourt le tableau des ludothèques et retourne l'indice de la premiere case vide de ce tableau

        int i = 0;

        while (tab_ludo[i]!=NULL){
            i++;
        }
    return i;
 }
