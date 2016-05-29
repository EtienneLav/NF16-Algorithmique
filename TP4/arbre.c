#include "arbre.h"
#include <string.h>




ArbreBr *creer_abr(){
    // Fonction qui crée un ABR vide (renvoie NULL en cas d'échec)
    ArbreBr* new_arbre = malloc(sizeof (ArbreBr));
    if(new_arbre){

        new_arbre->racine = NULL;
        new_arbre->nb_mots_differents = 0;
        new_arbre->nb_mots_total = 0;
        return new_arbre;
    }
    else{
        perror("malloc");   //Commentaire de l'échec du malloc
        return NULL;
    }

}

NoeudABR* creer_noeud(){ // Fonction de creation d'un noeud
    // Fonction qui crée un noeud vide
    NoeudABR* new_noeud = malloc(sizeof (NoeudABR));

    if(new_noeud){

        char* name = malloc(20*sizeof(char));  //Allocation mémoire des caractères constituants la chaine
        new_noeud->mot=name;
        new_noeud->positions = creer_liste_positions();
        new_noeud->filsDroit=NULL;
        new_noeud->filsGauche=NULL;
        return new_noeud;
    }
    else{
         perror("malloc");   //Commentaire de l'échec du malloc
        return NULL;
    }
}

int ajouterMot(ArbreBr* a, char* mot, int ligne, int ordre, int numphrase){
    // Chercher si le mot est déjà présent dans l'arbre (fonciton existante)
    NoeudABR* noeud_temp = rechercher_noeud(a, mot);


    if (noeud_temp != NULL){
        // Si oui, il existe ajouter position (fonction existante)
        if(ajouter_position(noeud_temp->positions, ligne, ordre, numphrase))
        return 1;
    }

    else{
        // Sinon créer nouveau noeud grâce à la fonction creer_noeud et inrecrementer nomre de mots differents

        a->nb_mots_differents = a->nb_mots_differents+1;
        noeud_temp= creer_noeud();

        strcpy(noeud_temp->mot,mot);  // Lui attribue le mot actuellement traité

        ajouter_position(noeud_temp->positions, ligne, ordre, numphrase);
        noeud_temp->filsGauche=NULL;
        noeud_temp->filsDroit=NULL;


        //l'insérer dans l'arbre
        if (a->racine==NULL){  //en tant que racine de l'arbre
            a->racine=noeud_temp;
            return 1;
        }

        else{
            //insérer dans arbre en tant que noeud different de la racine
            NoeudABR* noeud_arbre = a->racine;
            NoeudABR* noeud_y = NULL;

            while(noeud_arbre!=NULL){
                noeud_y=noeud_arbre;
                if(stricmp(noeud_temp->mot,noeud_arbre->mot)<0){
                    noeud_arbre=noeud_arbre->filsGauche;
                }
                else{
                    noeud_arbre=noeud_arbre->filsDroit;
                }
            }


            if(noeud_y==NULL){
                a->racine=noeud_temp;
            }
            else{
                if(stricmp(noeud_temp->mot,noeud_y->mot)<0){
                    noeud_y->filsGauche=noeud_temp;
                }
                else{
                    noeud_y->filsDroit=noeud_temp;
                }
            }

            //noeud_temp->filsGauche
            //noeud_temp->filsDroit
            return 1;
        }

    }

}


int charger_fichier(ArbreBr *arbre){

    FILE* fichier = NULL;
    int nb_mots=0;
    int ordre=1;
    int num_phrase=1;

    fichier = fopen("fichier_test.txt", "r"); // Toujours changer le nom du fichier text en fichier_test.txt pour le lire
     if (fichier != NULL)
        {

            char* mot=malloc(20*sizeof(char));
            char buff[1000];
            int i=0 ;
            int longueur_chaine;
            int compteur_mot = 0;
            int compteur_ligne=0;
            int tableau_mot[1000];
            int max_ligne;
            int numero_mot = 1;
            int numero_ligne = 1;
            int test_phrase=0;

            while (fgets(buff, 1000, fichier)!=NULL){ //Premier parcourt du fichier pour récupérer nombre de ligne et mots par ligne
                compteur_ligne++;                      // Boucle while qui est effectuée à chaque ligne récupérée par fgets
                longueur_chaine = strlen(buff);

                for (i=0; i<longueur_chaine; i++){

                    if (buff[i]== ' '){
                        compteur_mot++;
                    }
                }

                compteur_mot++;
                tableau_mot[compteur_ligne]= compteur_mot;  //Tableau stockant : en indice le numero de la ligne et le contenu de la case est le nombre de mots de la ligne
                printf("\nLa ligne numero : %d contient %d mots\n", compteur_ligne, tableau_mot[compteur_ligne]);
                compteur_mot = 0;
                max_ligne = compteur_ligne;

            }
            rewind(fichier);  // On revient au début et on analyse mot par mot le fichier désormais

            while(fscanf(fichier, "%s",mot)==1){ // Analyse mot par mot du fichier

                longueur_chaine = strlen (mot);  // Récupère la longueur du mot

                if (mot[longueur_chaine - 1]=='.'){ // Vérifie si ce mot n'est pas le dernier du phrase. Dans ce cas il contient le "." à la fin, donc on enlève ce point et on sait qu'on passe ensuite à la phrase suivant

                    mot[longueur_chaine - 1]= mot[longueur_chaine];
                    test_phrase = 1;
                    }

                if (numero_mot<=tableau_mot[numero_ligne]){ // Test si on est toujours à la ligne actuelle ou pas (grâce au premier parcourt et au tableau renté)

                    if(ajouterMot(arbre, mot, numero_ligne, ordre, num_phrase)==1){
                        numero_mot++;
                        nb_mots++;
                        arbre->nb_mots_total= arbre->nb_mots_total+1;
                        }
                    if (test_phrase)
                        num_phrase++;
                    ordre++;
                }


                else{ // Si non, on a sauté à la ligne suivant
                    numero_mot=1;
                    ordre = 1;
                    numero_ligne++;
                    if(ajouterMot(arbre, mot, numero_ligne, ordre, num_phrase)==1){
                        nb_mots++;
                        arbre->nb_mots_total= arbre->nb_mots_total+1;
                        numero_mot++;
                    }
                    ordre++;
                }
            test_phrase=0;
            }

        fclose(fichier);
        }
        else
        {
            printf("Impossible d'ouvrir le fichier fichier_test.txt");
        }

    return nb_mots;
}




NoeudABR *rechercher_noeud(ArbreBr *arbre, char *mot){
    // Fonction de service pour rechercher un noeud de l'arbre par le mot qu'il contient

    NoeudABR * noeud_temp= arbre->racine;

    while((noeud_temp!=NULL)&&(stricmp(mot, noeud_temp->mot)!=0)){   //Parcourt l'arbre selon l'ordre alphabétique
        if(stricmp(mot, noeud_temp->mot)<0){                          // des mots des noeuds recontrés
            noeud_temp=noeud_temp->filsGauche;
        }
        else{
            noeud_temp=noeud_temp->filsDroit;
        }

    }
    return noeud_temp;
}


void afficher_mot (NoeudABR* noeud){
    //Fonction de service pour afficher un noeud et non un arbre

    NoeudABR * mot_temp= noeud;
    if(mot_temp!=NULL){
        afficher_mot(mot_temp->filsGauche);
        printf("%s\n", mot_temp->mot);
        afficher_mot(mot_temp->filsDroit);
    }

}
void afficher_arbre(ArbreBr* arbre){
    // Fonction qui affiche les mots classés par ordre alphabétique
    // Par parcours infixe grâce à l'appel de afficher_mot

    NoeudABR * mot_temp= arbre->racine;
    afficher_mot(mot_temp);

}

///////////////////////////////////////////////////////////////////////////
//CASE 7
void effacer_arbre(NoeudABR* racine){ // Parcourt l'arbre binaire en postfixe pour efface chaque noeud

    ListePosition* list_pos;
    Position *pos_temp;
    Position *memoire;
    int noeud_efface = 0;
    int i =1;


 	if (racine != NULL) // Arbre non vide
        {
            effacer_arbre(racine->filsGauche); // Parcourt
            effacer_arbre(racine->filsDroit); // Postfixe

            printf("Pour le mot : \"%s\", on a ", racine->mot);
            // Liberer d'abord les positions de chaque mot s'ils sont apparus a plusieurs endroits
            pos_temp =((racine->positions)->debut);
            list_pos = racine->positions;
            printf("%d occurence\n", list_pos->nb_elements);
            if (list_pos->nb_elements != 1) { // Condition pour savoir si le mot existe plusieurs fois dans s'il faut vider une liste

                while (pos_temp != NULL){
                    memoire = pos_temp;
                    pos_temp=pos_temp->suivant;   //Liberer les positions de la liste de position s'il y a
                    free(memoire);
                    printf("Free l'occurrence numero : %d\n", i); //Informe de l'occurence supprimee
                    i++;
                    }
            printf("Liste des positions de ce mot a ete videe\n");
            }
            free(list_pos->debut); //Liberer le premier element de a liste de position qui existe toujours
            free(list_pos); // Liberation du pointeur de liste de position
            printf("Liberation du pointeur de liste des positions effectuee\n");


            free(racine->mot); //Liberer le mot de chaque noeud
            printf("Liberation du mot effectue\n");
            free(racine);   //Liberer le noeud actuel (noeud cle)
            printf("Liberation du noeud\n\n");
            racine = NULL;  //Remise à NULL du noeud actuel apres liberation
            noeud_efface++;

        }

}
/////////////////////////////////////////////////////////////////////////////////////////////
//CASE 4

NoeudABR* ABR_Minimum (NoeudABR* x){ // Revoie le noeud de cle minimum d'un arbre


    while(x->filsGauche!=NULL){
        x = x->filsGauche;
    }

    return x;
}

NoeudABR* Pere (ArbreBr* arb, NoeudABR* n){ // Renvoie le pere d'un noeud
    NoeudABR * noeud_temp= arb->racine;
    NoeudABR * noeud_pere=NULL;
      while((noeud_temp!=NULL)&&(stricmp(n->mot, noeud_temp->mot)!=0)){
          noeud_pere=noeud_temp;
            if(stricmp(n->mot, noeud_temp->mot)<0){
                noeud_temp=noeud_temp->filsGauche;
            }
            else{
                noeud_temp=noeud_temp->filsDroit;
            }

        }
        return noeud_pere;
}

NoeudABR* Successeur(ArbreBr* arb, NoeudABR* n){ //Renvoie le successeur d'un noeud
    if (n->filsDroit!=NULL){
        n=ABR_Minimum(n->filsDroit);
        return n;
    }
    else{
        NoeudABR* noeud2=Pere(arb, n);
        while((noeud2!=NULL)&&(noeud2->filsDroit!=NULL)&&(stricmp(noeud2->filsDroit->mot,n->mot)==0)){
            n=noeud2;
            noeud2=Pere(arb, noeud2);
        }

        return noeud2;
    }
}
///////////////////////////////////////////////////////////////////////////////////////////
//CASE 3

int* ProfondeurArbre (NoeudABR* racine, int prof, int* profMax){ //Calcul la pronfondeur de l'arbre

    if (racine!=NULL){
    prof++;
    ProfondeurArbre(racine->filsGauche,prof, profMax);
    if(prof>*profMax){
        *profMax=prof;
    }
    ProfondeurArbre(racine->filsDroit,prof, profMax);
    if(prof>*profMax){
        *profMax=prof;
    }
    prof--;
    }
    return profMax;

}

int equilibre (ArbreBr* arb){  //Renvoie l'equilibre de l'arbre
//hauteur gauche
    int* profGauche=malloc(sizeof(int));
    *profGauche=0;
    profGauche= ProfondeurArbre( arb->racine->filsGauche, 0, profGauche);

//hauteur droit
    int* profDroit=malloc(sizeof(int));
    *profDroit=0;
    profDroit= ProfondeurArbre ( arb->racine->filsDroit, 0, profDroit);
//egal?

    if(*profGauche==*profDroit){
        free(profGauche);
        free(profDroit);
        return 1;
    }
    else{
        free(profGauche);
        free(profDroit);
        return 0;
        }
}
