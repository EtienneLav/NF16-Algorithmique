#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "tp3.h"

int main()
{
    int choix, fin=0;
    int chx1 = 0, chx2= 0;
    int a=0;
    int m=0;
    int choiix=0;
    int i=0, k=0;
    int z=0;
    char nom_ret[50];
    char name[20];

    t_ludotheque* tab_ludo[10]; //tableau de pointeurs sur les ludotheques
        for (a=0;a<10;a++)
            tab_ludo[a]=NULL;

    t_jeu* tab_jeux[20]; //tableau des jeux
        for (a=0;a<20;a++)
            tab_jeux[a]=NULL;

    t_ludotheque* l;
    t_ludotheque* ludo1;
    t_ludotheque* ludo2;
    t_ludotheque* ludo_fus;
    int genre, min, max, duree;

    printf("_________________________________________________________\n");
    printf("|                                                        |\n");
    printf("|              .:Gestion de ludotheques:.                |\n");
    printf("|________________________________________________________|\n\n\n");

    while (fin==0){
        printf("===============MENU===============\n\n");
        printf("1. Creer une ludotheque\n");
        printf("2. Liste des ludotheques existantes\n");
        printf("3. Afficher une ludotheque\n");
        printf("4. Ajouter un jeu\n");
        printf("5. Rechercher un jeu\n");
        printf("6. Retirer un jeu\n");
        printf("7. Creer, afficher, fusionner et afficher 2 ludotheques .. puis les supprimer..\n");
        printf("8. Fusionner 2 ludotheques au choix\n");
        printf("9. Vider une ludotheque\n");
        printf("10. Vider les ludotheques\n");
        printf("11. Quitter\n\n\n");
        printf("Saisissez votre choix: ");
        scanf("%d",&choix);
        printf("\n");



    switch(choix){

        case 1 : // Creation d'une ludotheque

                i = 0;

                l = creer_ludotheque();

                if(l==NULL)
                    printf("Erreur : Ludotheque non creee\n");

                else{

                    i = premiere_case_vide(tab_ludo); // Recupere l'indice de la premier case vide du tableau de ludotheque
                    tab_ludo[i]=l;
                    printf("Vous venez de creer la ludotheque numero %d\n",i);
                    printf("Celle-ci est vide pour le moment...\n\n\n");
                    }


            break;


        case 2 :  // Affichage les ludotheques existantes

                k = nombre_ludotheque (tab_ludo); // Nous récupérons dans k le nombre de ludotheque disponibles

                if (k==0)
                    printf("\nAucune ludotheque dans la BDD... Veuillez d'abord en creer une (choix 1)\n");

                else {
                    z = liste_ludotheque(tab_ludo); // Nous affichons les ludotheques existantes. z sert simplement à un affichage coherent et a accorder le verbe exister s'il n'y a qu'une ludotheque ou plusieurs à afficher

                    if (z==1)
                        printf(" existe\n");
                    else
                        printf(" existent\n\n");
                }
            break;


        case 3 :   // Affiche une ludotheque au choix

                choiix=0;

                k = nombre_ludotheque (tab_ludo); // Nous récupérons dans k le nombre de ludotheque disponibles

                if (k==0)
                    printf("\nAucune ludotheque dans la BDD... Veuillez d'abord en creer une (choix 1)\n");

                else {
                    printf("\nVeuillez faire votre choix parmi les ludotheques suivantes: ");
                    liste_ludotheque(tab_ludo);

                    printf("\t");
                    scanf("%d",&choiix);

                    printf("\n");

                    if (tab_ludo[choiix]==NULL) // Test si le choix de l'utilisateur est valide
                         printf("\nChoix non valide ...\n");
                    else
                        affiche_ludotheque(tab_ludo[choiix]);
                    }
            break;

        case 4 : //Ajouter un jeu dans une ludotheque
                choiix = 0;
                z = 0;
                k = nombre_ludotheque (tab_ludo); // Nous récupérons dans k le nombre de ludotheque disponibles

                if (k==0) //On test s'il existe des ludotheques dans la BDD
                    printf("\nAucune ludotheque dans la BDD... Veuillez d'abord en creer une (choix 1)\n");

                else {

                    printf("\nSaisissez le nom du jeu :  ");
                    scanf("%s",name);
                    printf("\nSaisissez le genre\n(0:PLATEAU ou 1:RPG ou 2:COOPERATIF ou 3:AMBIANCE ou 4:HASARD) :  ");
                    scanf("%d",&genre);
                    printf("\nSaisissez le nombre de joueur min : ");
                    scanf("%d",&min);
                    printf("\nSaisissez le nombre de joueur max : ");
                    scanf("%d",&max);
                    printf("\nSaisissez la duree moyenne du jeu :  ");
                    scanf("%d",&duree);


                    z= indice_jeu(tab_jeux); // z récupère l'indice qu'occupera le jeu dans la table des jeux

                    tab_jeux[z] = creer_jeu(name,genre, min, max, duree);

                    printf("\nDans quelle ludotheque voulez-vous l'ajouter?  ");
                    liste_ludotheque(tab_ludo); // on affiche les ludotheque disponibles


                    printf("\t");
                    scanf("%d",&choiix);

                    if (tab_ludo[choiix]== NULL) // On test si le choix de ludotheque dans laquelle ajouter le jeu est valide
                        printf("\nChoix non valide ...\n");

                    else

                            if(ajouter_jeu(tab_ludo[choiix], tab_jeux[z])==0) // On test si l'ajout du jeu s'est bien passe..
                                printf("\nAjout non reussi...\n\n");
                }
            break;

        case 5 :  // Recherche jeu dans une ludotheque

                k = nombre_ludotheque (tab_ludo); // Nous récupérons dans k le nombre de ludotheque disponibles
                choiix = 0;

                if (k==0)
                    printf("\nAucune ludotheque dans la BDD... Veuillez d'abord en creer une (choix 1)\n");

                else {


                    printf("Dans quelle ludotheque voulez-vous faire votre recherche?  ");
                    liste_ludotheque(tab_ludo);  // On affiche la liste des ludotheque disponible

                    printf("\t");
                    scanf("%d",&choiix);

                    if (tab_ludo[choiix] == NULL)  // On test si le numero entre correspond à une ludotheque existante et proposee ci dessus
                        printf("\nChoix non valide ...\n");

                    else {

                            if (tab_ludo[choiix]->debut == NULL)  // On test si la ludotheque est vide .. Si c'est le cas aucune recherche possible
                                printf("\nLa ludotheque est vide .. Recherche impossible ..\n\n");

                            else{
                                printf("\nEntrez les criteres du jeu demande: (-1 si non connu)\n\n");
                                printf("Entrez le genre du jeu\n(0:PLATEAU ou 1:RPG ou 2:COOPERATIF ou 3:AMBIANCE ou 4:HASARD) : ");
                                scanf("%d",&genre);
                                printf("\nEntrez le nombre de joueurs : ");
                                scanf("%d",&min);
                                printf("\nEntrer la duree voulue : ");
                                scanf("%d", &duree);
                                printf("\n\n");


                                l = requete_jeu(tab_ludo[choiix],genre, min, duree); // Envoie la requete pour rechercher un jeu (renvoye dans une ludotheque
                                affiche_ludotheque(l);  // Affiche la ludotheqe des résultats de la requete
                                supprimer_ludotheque(l); // Supprime cette ludotheque des resultats de la requete
                                }
                            }
                        }

                break;


        case 6 : // Retirer un jeu au choix

                i = 0;
                m = 0;

                k = nombre_ludotheque (tab_ludo); // Nous récupérons dans k le nombre de ludotheque disponibles

                if (k==0)
                    printf("\nAucune ludotheque dans la BDD... Veuillez d'abord en creer une (choix 1)\n");

                else {
                    liste_ludotheque(tab_ludo); // Nous affichons les ludotheques disponibles

                    if (z==1)
                        printf(" existe\n");
                    else
                        printf(" existent\n\n");


                    printf("Veuillez faire votre choix parmi les existantes ci-dessus : \t");
                    scanf("%d", &choiix);

                    if (tab_ludo[choiix] ==NULL)  // On test si le choix est valide ou pas
                        printf("\nChoix non valide ...");

                    else {

                            if (tab_ludo[choiix]->debut == NULL)  // On test aussi si la ludotheque choisie est vide
                                printf("\nLa ludotheque est vide ... Recherche impossible\n");

                            else  // Si elle n'est pas vide et que le choix est valide ...
                                {

                                    printf("\nEntre le nom du jeu a retirer ...Attention au MAJ/MIN : \t");
                                    scanf("%s", nom_ret);
                                    if (retirer_jeu(tab_ludo[choiix], nom_ret))   // Test si le jeu a bien ete retire..
                                        printf("\nLe jeu %s a ete retirer de la ludotheque %d\n\n", nom_ret, choiix);

                                }
                        }
                    }
            break;

        case 7 : // Fusion de deux ludotheques pre-entrées

                i=0;
                l = creer_ludotheque();
                if(l==NULL)
                    printf("Ludotheque non creee\n");
                else{
                    while (tab_ludo[i]!=NULL){
                        i++;
                    }
                    tab_ludo[i]=l;
                }
                l = creer_ludotheque();
                if(l==NULL)
                    printf("Ludotheque non creee\n");
                else{
                    tab_ludo[i+1]=l;
                }
                printf("Les ludotheques numeros %d et %d viennent d'etre creees\n\n\n",i+1, i+2);

                ajouter_jeu(tab_ludo[i], creer_jeu("Time's up", AMBIANCE, 4, 8, 35));
                ajouter_jeu(tab_ludo[i], creer_jeu("Endor   ", RPG, 3, 8, 90));

                ajouter_jeu(tab_ludo[i+1], creer_jeu("Monopoly", PLATEAU, 3, 8, 120));
                ajouter_jeu(tab_ludo[i+1], creer_jeu("Puissance4", PLATEAU, 2, 2, 10));
                ajouter_jeu(tab_ludo[i+1], creer_jeu("Manille", COOPERATIF, 4, 8, 26));
                ajouter_jeu(tab_ludo[i+1], creer_jeu("Des   ", HASARD, 2, 10, 2));

                printf("Ludotheque %d : \n",i+1);
                affiche_ludotheque(tab_ludo[i]);
                printf("Ludotheque %d : \n",i+2);
                affiche_ludotheque(tab_ludo[i+1]);

                l=fusion(tab_ludo[i], tab_ludo[i+1]);
                printf("\n\nLudotheque fusionnee : \n");
                affiche_ludotheque(l);


                supprimer_ludotheque(tab_ludo[i]);
                tab_ludo[i]=NULL;
                supprimer_ludotheque(tab_ludo[i+1]);
                tab_ludo[i+1]=NULL;
                supprimer_ludotheque(l);
            break;

        case 8 : // Fusion de deux lodotheques au choix
                i = 0;

                k = nombre_ludotheque (tab_ludo); // Nous récupérons dans k le nombre de ludotheque disponibles

                if (k==0)
                    printf("\nAucune ludotheque dans la BDD... Veuillez d'abord en creer au moins une (choix 1)\n");

                else {
                    printf("\nQUelles ludotheques voulez vous fusionner ? ");
                    liste_ludotheque(tab_ludo);


                    printf("\t");
                    scanf("%d", &chx1);
                    printf("");
                    scanf("%d", &chx2);

                    ludo_fus= fusion_deux_ludo(tab_ludo[chx1], tab_ludo[chx2]);
                    i = premiere_case_vide(tab_ludo);
                    tab_ludo[i]=ludo_fus;

                    printf("\nLa ludotheque creee porte le numero : %d\n\n", i);

                }
            break;

        case 9 : // Vider une ludothèque

                k = nombre_ludotheque (tab_ludo); // Nous récupérons dans k le nombre de ludotheque existantes

                if (k==0)
                    printf("\nAucune ludotheque dans la BDD... Veuillez d'abord en creer une (choix 1)\n");

                else {
                    printf("Quelle ludotheque voulez vous vider ? \t");
                    liste_ludotheque(tab_ludo); // Nous affichons la liste des ludotheques existantes


                    printf("\t");
                    scanf("%d", &choiix);

                    if (tab_ludo[choiix] != NULL) {      // Test sur le choiix entre par l'utilisateur
                        supprimer_ludotheque(tab_ludo[choiix]);  // Supprime la ludotheque choisie
                        tab_ludo[choiix]= NULL;
                        printf("\nLa ludotheque numero : %d a ete videe\n", choiix);
                        }
                    else
                        printf("\nChoix non valide ...\n");
                }

            break;

        case 10 : // Vider toutes les ludothèques

                z = nombre_ludotheque(tab_ludo); // On récupere le nombre de ludotheques existantes

                if (z) {
                    for (i=0; i<10; i++){  // On parcourt tout le tableau des ludothèques

                        if(tab_ludo[i]!=NULL){

                            supprimer_ludotheque(tab_ludo[i]);    // on libère la mémoire prise par les ludotheques et leurs jeux
                            tab_ludo[i]= NULL;                     // on re-initialise la case du tableau de ludotheque en question à NULL
                            printf("\nLa ludotheque numero : %d a ete videe..\n", i);
                        }

                    }
                }

                else
                    printf("\nAucune ludotheque a supprimer ...\n");

            break;


        case 11 : // fermeture du programme

                for (i=0; i<10; i++){  // On parcourt tout le tableau des ludotheque

                    if(tab_ludo[i]!=NULL){

                    supprimer_ludotheque(tab_ludo[i]);    // on libère toute la mémoire prise par les ludotheques et leurs jeux
                    tab_ludo[i]= NULL;
                    printf("\nLa ludotheque numero : %d a ete videe..\n", i);
                    }

                }
                printf("\n\n");
                printf("\t...\nFermeture du programme de listes chainees\n\t...\n");
                printf("\n----------------------------------\n");
                printf("\tClemence lefebvre \n\t\t&\n\tEtienne Laviolette\n\tNovembre 2014, UTC\n");
                printf("----------------------------------\n");

                fin=1;

            break;


        default: printf("Choix non valide, veuillez recommencer ! \n\n");

            break;

        }
    }

    return 0;
}
