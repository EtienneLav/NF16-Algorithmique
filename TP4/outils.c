
#include "outils.h"
#include "arbre.h"




//scénario

void menu (){
    int fin=0;
    int choix;
    ArbreBr* arb;

    char chemin[30]="fichier_test.txt";
    NoeudABR* noeud1 = malloc(sizeof(NoeudABR));
    NoeudABR* noeud2 = malloc(sizeof(NoeudABR));

    int* profMax=malloc(sizeof(int));

    char* mot = malloc(15*sizeof(char));
    Position * pos;
    char* mot2 = malloc(15*sizeof(char));
    Position* pos_mot1;
    Position* pos_mot2;
    int trouve=0, phrase=0;


    int arbre_cree=0; // Ne pas proposer d'autre choix tant que l'utilisateur n'a pas créé d'arbre

    printf("_________________________________________________________\n");
    printf("|                                                        |\n");
    printf("|              .: Indexation par arbre binaire :.        |\n");
    printf("|________________________________________________________|\n\n\n");


    while (fin==0){
        printf("Que souhaitez-vous faire?\n");
        printf("1. Creer un arbre\n2. Charger un fichier dans l'arbre\n3. Afficher les caracteristiques de l'arbre\n4. Afficher tous les mots par ordre alphabetique\n5. Rechercher un mot\n6. Afficher les phrases contenant deux mots\n7. Quitter\n");
        scanf("%d", &choix);

        switch (choix){
            case 1:
                //création d'un arbre
                arb = creer_abr();
                printf("Vous venez de creer l'arbre \"arb\" \n");
                arbre_cree = 1;

            break;

            case 2:
                //chargement d'un fichier

                if (arbre_cree){
                    printf("Indiquez le chemin du fichier à charger:\n");

                    int nb_mots = charger_fichier(arb);
                    printf("Nombre de mots lus : %d\n", nb_mots);
                    printf("charge\n");
                }
                else {
                    printf("Veuillez d'abord creer l'arbre de traitement..\n\n");
                }

            break;

            case 3:
                //Affiche caractéristiques de l'arbre

                if (arbre_cree){
                    printf("\nnombre de noeuds: ");
                    printf("%d\n", arb->nb_mots_differents);
                    printf("profondeur : ");
                    *profMax=0;
                    profMax=ProfondeurArbre (arb->racine, 0, profMax);
                    printf("%d\n", (*profMax)-1);

                    //equilibré?
                    if(equilibre(arb)==1)
                        printf("L'arbre est equilibre\n");
                    else
                        printf("L'arbre n'est pas equilibre\n");
                    printf("\n\n");
                }
                else {
                    printf("Veuillez d'abord creer l'arbre de traitement..\n\n");
                }

                break;

            case 4:
                //affichage de tous les mots distincts par ordre alphabétique

                //affichage minimum
                if (arbre_cree){
                   noeud1 = ABR_Minimum(arb->racine);

                    printf("\n\n%s\n",noeud1->mot);
                    //boucle affichage successeurs
                    while (Successeur(arb, noeud1)!=NULL){
                            noeud1=Successeur(arb,noeud1);
                        printf("%s\n",noeud1->mot);
                    }

                    printf("\n\n");
                }
                else {
                    printf("Veuillez d'abord creer l'arbre de traitement..\n\n");
                }

                break;

            case 5:

                //recherche d'un mot
                if (arbre_cree){
                    printf("Entrez le mot recherche : ");
                    scanf("%s",mot);
                    noeud1= rechercher_noeud(arb, mot);
                    if (noeud1==NULL)
                        printf("\n Desole ce mot n'existe pas dans l'arbre\n");
                    else{
                        printf("\nCe mot est present %d fois\n",noeud1->positions->nb_elements);
                        pos=noeud1->positions->debut;
                        while (pos!=NULL){
                            printf("\nnumero de ligne : %d \nordre dans la ligne : %d \nnuero de phrase : %d\n\n\n",pos->numero_ligne, pos->ordre, pos->numero_phrase );
                            pos=pos->suivant;
                        }
                    }
                }
                else {
                    printf("Veuillez d'abord creer l'arbre de traitement..\n\n");
                }

                break;

            case 6:
                //Affichage des phrases contenant deux mots

                if (arbre_cree){

                    trouve=0; //variable permettant si une phrase a été trouvée
                    printf("Entrez le 1er mot : ");
                    scanf("%s", mot);
                    printf("Entrez le 2eme mot : ");
                    scanf("%s", mot2);

                    //on recherche les noeuds demandés
                    noeud1=rechercher_noeud(arb,mot);
                    noeud2=rechercher_noeud(arb, mot2);

                    //s'il existe on récupere leurs positions
                    if ((noeud1!=NULL)&&(noeud2!=NULL)){
                        pos_mot1 = noeud1->positions->debut;
                        pos_mot2 = noeud2->positions->debut;

                        //on teste pour chaque position si elles sont égales
                        while (pos_mot1!=NULL){
                            while (pos_mot2!=NULL){
                                    if(pos_mot1->numero_phrase==pos_mot2->numero_phrase){

                                            if(phrase!=pos_mot2->numero_phrase){ //test si la phrase a déjà été écrite
                                                printf("La phrase %d comporte les deux mots demandes\n\n",pos_mot1->numero_phrase); //affichage du numéro de la phrase
                                                recuperer_phrase (chemin, pos_mot2->numero_phrase); // affichage de la phrase
                                                phrase=pos_mot2->numero_phrase; //on stocke le numéro de la dernière phrase affichée
                                            }
                                    trouve=1;
                                    }
                                pos_mot2=pos_mot2->suivant; //on passe à la position suivante du mot 2
                            }
                            pos_mot1=pos_mot1->suivant; //on passe à la position suivante du mot 1
                            pos_mot2 = noeud2->positions->debut; //on replace le pointeur au début de la liste des positions du mot2
                        }
                        if(trouve==0) //si on n'a trouvé aucune phrase
                            printf("Dsl, aucune phrase ne comporte ces 2 mots\n\n");
                    }
                    else //si un ou les deux mots n'existe pas
                        printf("Dsl, un des deux mots n'existe pas\n\n");
                }
                else {//si l'arbre n'existe pas
                    printf("Veuillez d'abord creer l'arbre de traitement..\n\n");
                }
                printf("\n");
                break;

             case 7:
                //Quitter

                fin=1;

                if (arbre_cree && (arb->racine != NULL)){


                    effacer_arbre(arb->racine);
                    printf("Les %d noeuds ont ete vides...\n", arb->nb_mots_total);
                    free(arb);
                    printf("L'arbre de traitement a ete libere\n\n");
                }

                else {

                        if (arbre_cree && arb->racine==NULL){
                            printf("L'arbre soumis est vide, nous liberons simplement son pointeur\n\n");
                            free(arb);
                            arb = NULL;
                        }

                        else {
                            printf("Aucun arbre n'a ete cree.. Aucune liberation\n\n");

                        }
                }

                printf("\t...\nFermeture du programme d'indexation\n\t...\n");
                printf("\n----------------------------------\n");
                printf("\tClemence lefebvre \n\t\t&\n\tEtienne Laviolette\n\tJanvier 2015, UTC\n");
                printf("----------------------------------\n");
                break;
        }

    }

    free(noeud1);
    free(noeud2);
    free(profMax);
    free(mot);
}
void recuperer_phrase (char *filename, int num_phrase){
    int num=1;
    char c;
    FILE* fichier= fopen(filename, "r");

     if (fichier != NULL)
        {
        while((num!=num_phrase)&&(c!=EOF)){ //tant qu'on n'est pas devant la phrase recherchée ni à la fin du fichier
            c = fgetc(fichier);     //on recupere un caractère

            if(c=='.'){             //on teste si point
                num++;              //si oui on est devant nouvelle phrase donc on incrémente num
            }
        }
        //on est maintenant devant la phrase à afficher
            do{                         //on affiche les caractères jusqu'à rencontrer le point
                c=fgetc(fichier);
                printf("%c", c);
            }while(c!='.');

            printf("\n");

         fclose(fichier);           //on ferme le fichier
        }
        else
        {
            printf("Impossible d'ouvrir le fichier fichier_test.txt");
        }
}

