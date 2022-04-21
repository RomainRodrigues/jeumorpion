/**
 * \file morpion.c
 * \author Romain Rodrigues
 * \brief Morpion
 * \version 1.0
 * \date 30 décembre 2021
 * 
 * Ce programme permet de réaliser une ou plusieurs partie(s) de morpion
 */


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define MAX_PRENOM 10 //nombre max de caractère pour un prénom
#define HAUTEUR 3     //nombre de lignes
#define LARGEUR 3     //nombre de colonnes
#define LARG_TAB 11   //largeur de la grille du morpion

typedef char MORPION[HAUTEUR][LARGEUR];  //type morpion : tableau deux dimenssions

void prenom(char prenom1[50], char prenom2[50]){  //procédure qui s'occupe de l'attribution des prénoms
    printf("Entrez le premier prénom :");
    scanf("%s", prenom1);
    while (strlen(prenom1)>MAX_PRENOM){     //boucle qui verifie la longueur du premier prénom (changement si trop long)
        printf("Le prénom est trop long, entrez un prénom plus court.\n");
        printf("Modifié le premier prénom :");
        scanf("%s", prenom1);
    }
    printf("Entrez le deuxième prénom :");
    scanf("%s", prenom2);
    while (strlen(prenom2)>MAX_PRENOM){     //boucle qui verifie la longueur du deuxième prénom (changement si trop long)
        printf("Le prénom est trop long, entrez un prénom plus court.\n");
        printf("Modifié le deuxième prénom :");
        scanf("%s", prenom2);
    }
    while ((strcmp(prenom1, prenom2)==0)){      //boucle qui vérifie que les prénom ne sont pas identique (changement si identique)
        printf("Erreur les deux prénoms sont identique, joueur 2 modifié votre prénom :");
        scanf("%s", prenom2);
        while (strlen(prenom2)>MAX_PRENOM){
            printf("Le prénom est trop long, entrez un prénom plus court.\n");
            printf("Modifié le deuxième prénom :");
            scanf("%s", prenom2);
        }
    }
    printf("\n");
}

void affichage(MORPION tab){    //procédure qui permet d'afficher le morpion
    int compt1;
    int compt2;
    int trace;

    for(compt1=0; compt1<HAUTEUR; compt1++){    //boucle pour chaques lignes 
        for(compt2=0; compt2<LARGEUR; compt2++){    //boucle pour les 3 colonnes d'une ligne 
            printf(" %c ", tab[compt1][compt2]);
            if (compt2!=2){     //condition pour ne pas mettre de batton en fin de ligne
                printf("|");
            }
        }
        printf("\n");
        if(compt1!=2){      //condition pour ne pas tracer de ligne en dessous de la grille de jeu
            for(trace=0; trace<LARG_TAB; trace++){      //boucle qui trace une ligne 
                printf("-");
            }
            printf("\n");
        }
    }
    printf("\n");
}

void action(MORPION tab, int tour){     //procédure qui permet à un jouer de jouer
    int ligne;
    int colonne;
    printf("Entrez le numéro de la ligne :");
    scanf("%d", &ligne);
    printf("Entrez le numéro de la colonne :");
    scanf("%d", &colonne);
    printf("\n");
    while(tab[ligne-1][colonne-1]!=' '){    //boucle qui vérifie que la case choisie est bien vide et demande une autres si ce n'est pas le cas
        printf("Erreur cette case est déjà remplie.\n");
        printf("Entrez le numéro de la ligne :");
        scanf("%d", &ligne);
        printf("Entrez le numéro de la colonne :");
        scanf("%d", &colonne);
        printf("\n");
    }
    if(tour==1){
        tab[ligne-1][colonne-1]='X';    //met un X sur la case si c'est le premier joueur
    }
    else{
        tab[ligne-1][colonne-1]='O';    //met un O sur la case si c'est le deuxième joueur
    }
    printf("\n");
}

bool win(MORPION tab){      //fonction qui retourne vrai si trois cases identiques sont alignées
    int compt1;
    int compt2;
    int trouve1;
    int trouve2;
    int trouve3;
    int trouve4;
    bool fin;
    compt1=0;
    compt2=0;
    fin=false;

    while((compt1<HAUTEUR)&&!(fin)){     //boucle pour les lignes
        trouve1=0;  
        trouve2=0;
        trouve3=0;
        trouve4=0;
        compt2=0;
        while(compt2<(LARGEUR-1)){      //boucle pour les colonnes
            if((tab[compt1][compt2]==tab[compt1][compt2+1])&&(tab[compt1][compt2]!=' ')){   //vérifie sur les lignes
                trouve1++;     //+1 si deux cases coller identiques
            }
            if((tab[compt2][compt1]==tab[compt2+1][compt1])&&(tab[compt2][compt1]!=' ')){   //vérifie sur les colonnes
                trouve2++;      //+1 si deux cases coller identiques
            }
            if((tab[compt2][compt2]==tab[compt2+1][compt2+1])&&(tab[compt2][compt2]!=' ')){     //vérifie la diagonale qui part de en haut a gauche
                trouve3++;      //+1 si deux cases coller identiques
            }
            if((tab[compt2][HAUTEUR-(compt2+1)]==tab[compt2+1][HAUTEUR-(compt2+2)])&&(tab[compt2][HAUTEUR-(compt2+1)]!=' ')){   //vérifie la diagonale qui part de en haut a droite
                trouve4++;      //+1 si deux cases coller identiques
            }
            compt2++;
        }
        if((trouve1==2)||(trouve2==2)||(trouve3==2)||(trouve4==2)){     //si alignement de trois cases on passe a vrai
            fin=true;
        }
        compt1++;
    }
    return fin;
}

bool resultat(MORPION tab){     //fonction qui retourne vrai si toutes la grille est remplie 
    int compt1;
    int compt2;
    int nbCases;
    bool termine;
    termine=false;
    nbCases=0;
    for(compt1=0; compt1<HAUTEUR; compt1++){    //double boucle qui incrémente un entier si une cases n'est pas vide
        for(compt2=0; compt2<LARGEUR; compt2++){
            if(tab[compt1][compt2]!=' '){
                nbCases++;
            }
        }
    }
    if(nbCases==9){     //si toutes les cases sont remplie on passe a vrai
        termine=true;
    }
    return termine;
}

int main(){
    char joueur1[50];   //joueur 1
    char joueur2[50];   //joueur 2
    char jouer[10];     //mot pour rejouer ou non
    int tour;   //variables pour savoir quel joieur joue
    int compt1;
    int compt2;
    bool termine;   //bool pour le tableau remplie 
    bool gagne;     //bool pour un cas de victoires
    MORPION tableau;
    strcpy(jouer, "oui");

    system("clear");    //clear le terminal 
    prenom(joueur1, joueur2);   //initialisation du nom des jouers

    while(strcmp(jouer, "non")!=0){     //boucle qui tourne tant que les joueurs veulent rejoués
        termine=false;
        gagne=false;
        for(compt1=0; compt1<HAUTEUR; compt1++){       //double boucle qui initialise le tableau avec des cases vide
            for(compt2=0; compt2<LARGEUR; compt2++){
                tableau[compt1][compt2]=' ';
            }
        }

        while(!(termine)&&!(gagne)){    //on continue tant qu'il n'y a pas de victoires ou tant que la grille n'est pas pleine
            
            tour=1;
            while((tour<3)&&!(termine)&&!(gagne)){  //boucle pour que les joueurs joue l'un après l'autres
                system("clear");    //clear le terminal
                if(tour==1){    // si tour = 1 alors c'est le joueur 1 qui joue 
                    printf("Au tour de %s\n\n", joueur1);
                }
                else{   //sinon c'est le joueur 2
                    printf("Au tour de %s\n\n", joueur2);
                }
                affichage(tableau);     //affichage de la grille de jeu
                sleep(2);   //on stop le programme pendant deux secondes pour laisser le temps d'observer
                action(tableau, tour);      //le joueur joue
                termine=resultat(tableau);  //termine vaut vrai si la grille est pleine 
                gagne=win(tableau);     //gagne vaut vrai si le joueur a gagné la partie 
                if((termine)||(gagne)){     //si le joueur a gagné ou la grille est pleine 
                    system("clear");    //clear le terminal
                    affichage(tableau);     //affichage de la grille de jeu
                    if((tour==1)&&(gagne)){
                        printf("Le vainqueur est %s\n\n", joueur1); //cas ou le joueur 1 gagne 
                    }
                    else if((tour==2)&&(gagne)){
                        printf("Le vainqueur est %s\n\n", joueur2); //cas ou le joueur 2 gagne
                    }
                    else{
                        printf("Egalité, pas de vainqueur\n\n");    // cas d'égalité
                    }
                    printf("Voulez-vous rejouer (oui ou non) : ");  //on demande si ils veulent rejoué 
                    scanf("%s", jouer);
                    while((strcmp(jouer, "non")!=0)&&(strcmp(jouer, "oui")!=0)){
                        printf("Erreur veuillez répondre par oui ou non : ");
                        scanf("%s", jouer);
                    }
                }
                tour++;
            }
        }
    }
    return EXIT_SUCCESS;
}