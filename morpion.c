/**
 * \file morpion.c
 * \author Romain Rodrigues
 * \brief Morpion
 * \version 2.0
 * \date 21 avril 2022
 * 
 * Ce programme permet de réaliser une ou des partie(s) de morpion
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define MAX_PRENOM 10
#define HAUTEUR 3
#define LARGEUR 3
#define LARG_TAB 11

typedef char MORPION[HAUTEUR][LARGEUR];

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

void affichage(MORPION tab){
    int compt1;
    int compt2;
    int trace;

    for(compt1=0; compt1<HAUTEUR; compt1++){
        for(compt2=0; compt2<LARGEUR; compt2++){
            printf(" %c ", tab[compt1][compt2]);
            if (compt2!=2){
                printf("|");
            }
        }
        printf("\n");
        if(compt1!=2){
            for(trace=0; trace<LARG_TAB; trace++){
                printf("-");
            }
            printf("\n");
        }
    }
    printf("\n");
}

void action(MORPION tab, int tour){
    int ligne;
    int colonne;
    printf("Entrez le numéro de la ligne :");
    scanf("%d", &ligne);
    printf("Entrez le numéro de la colonne :");
    scanf("%d", &colonne);
    printf("\n");
    while(tab[ligne-1][colonne-1]!=' '){
        printf("Erreur cette case est déjà remplie.\n");
        printf("Entrez le numéro de la ligne :");
        scanf("%d", &ligne);
        printf("Entrez le numéro de la colonne :");
        scanf("%d", &colonne);
        printf("\n");
    }
    if(tour==1){
        tab[ligne-1][colonne-1]='X';
    }
    else{
        tab[ligne-1][colonne-1]='O';
    }
    printf("\n");
}

bool win(MORPION tab){
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

    while((compt1<HAUTEUR)&&!(fin)){
        trouve1=0;
        trouve2=0;
        trouve3=0;
        trouve4=0;
        compt2=0;
        while(compt2<(LARGEUR-1)){
            if((tab[compt1][compt2]==tab[compt1][compt2+1])&&(tab[compt1][compt2]!=' ')){
                trouve1++;
            }
            if((tab[compt2][compt1]==tab[compt2+1][compt1])&&(tab[compt2][compt1]!=' ')){
                trouve2++;
            }
            if((tab[compt2][compt2]==tab[compt2+1][compt2+1])&&(tab[compt2][compt2]!=' ')){
                trouve3++;
            }
            if((tab[compt2][HAUTEUR-(compt2+1)]==tab[compt2+1][HAUTEUR-(compt2+2)])&&(tab[compt2][HAUTEUR-(compt2+1)]!=' ')){
                trouve4++;
            }
            compt2++;
        }
        if((trouve1==2)||(trouve2==2)||(trouve3==2)||(trouve4==2)){
            fin=true;
        }
        compt1++;
    }
    return fin;
}

bool resultat(MORPION tab){
    int compt1;
    int compt2;
    int nbCases;
    bool termine;
    termine=false;
    nbCases=0;
    for(compt1=0; compt1<HAUTEUR; compt1++){
        for(compt2=0; compt2<LARGEUR; compt2++){
            if(tab[compt1][compt2]!=' '){
                nbCases++;
            }
        }
    }
    if(nbCases==9){
        termine=true;
    }
    return termine;
}

int main(){
    char joueur1[50];
    char joueur2[50];
    char jouer[10];
    int tour;
    int compt1;
    int compt2;
    bool termine;
    bool gagne;
    int nbTours;
    MORPION tableau;
    strcpy(jouer, "oui");

    system("clear");
    prenom(joueur1, joueur2);

    while(strcmp(jouer, "non")!=0){
        termine=false;
        gagne=false;
        nbTours=0;
        for(compt1=0; compt1<HAUTEUR; compt1++){
            for(compt2=0; compt2<LARGEUR; compt2++){
                tableau[compt1][compt2]=' ';
            }
        }

        while(!(termine)&&!(gagne)){
            
            tour=1;
            while((tour<3)&&!(termine)&&!(gagne)){
                system("clear");
                if(tour==1){
                    printf("Au tour de %s\n\n", joueur1);
                }
                else{
                    printf("Au tour de %s\n\n", joueur2);
                }
                affichage(tableau);
                sleep(2);
                action(tableau, tour);
                termine=resultat(tableau);
                gagne=win(tableau);
                nbTours++;
                if((termine)||(gagne)){
                    system("clear");
                    affichage(tableau);
                    if((tour==1)&&(gagne)){
                        printf("Le vainqueur est %s\n\n", joueur1);
                    }
                    else if((tour==2)&&(gagne)){
                        printf("Le vainqueur est %s\n\n", joueur2);
                    }
                    else{
                        printf("Egalité, pas de vainqueur\n\n");
                    }
                    printf("Voulez-vous rejouer (oui ou non) : ");
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