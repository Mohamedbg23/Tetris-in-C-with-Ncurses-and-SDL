//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#include "grille.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

grille * creerGrille(){
    //allocations
    grille *g=malloc(sizeof(grille));
    if(!g){
        perror("erreur allocation grille\n");
        exit(EXIT_FAILURE);
    }
    g->liste=creerListeAttente();
    g->tab=malloc(HAUTEUR*LARGEUR*sizeof(couleur));
    if(!g->tab){
        perror("erreur allocation tableau couleur\n");
        exit(EXIT_FAILURE);
    }

    //initialisation du tableau représetant le jeu à VIDE
    for(int i=0;i<HAUTEUR;i++){
        for(int j=0;j<LARGEUR;j++){
            *(g->tab+i*LARGEUR+j)=VIDE;
        }
    }
    g->reserve=VIDE;
    g->pieceactive=creerPiece(couleurSuivante(g->liste),0,LARGEUR/2,g->tab,g->pieceactive);
    dessinePiece(g->tab,g->pieceactive);
    g->score=0;
    g->niveau=1;
    g->lignes=0;
    g->reserveUtilisee=0;

    return g;
}

void libereGrille(grille *g){
    if(g){
        if(g->tab){
            free(g->tab);
        }
        if(g->pieceactive){
            liberePiece(g->pieceactive);
        }
        if(g->liste){
            libereListeAttente(g->liste);
        }
        free(g);
    }

}

int detecteCollision(grille *g){
    assert(g && g->tab && g->pieceactive->coordonnees);
    unsigned *c=g->pieceactive->coordonnees;
    couleur *tab=g->tab;
    effacePiece(g->tab,g->pieceactive);//permet de ne pas détecter une collision entre la pièce active et elle même
    for(int i=0;i<8;i+=2){
        if(*(c+i)+1>=HAUTEUR || *(tab+(*(c+i)+1)*LARGEUR+(*(c+i+1) ))!=VIDE){
            dessinePiece(g->tab,g->pieceactive);
             g->reserveUtilisee=0;
            return 1;
        }
    }
    dessinePiece(g->tab,g->pieceactive);
    return 0;
}

void detecteLigne(grille *g){
    effacePiece(g->tab,g->pieceactive);
    assert(g && g->tab);
    int totalLigne=0;
    int cpt;
    for(int i=0;i<HAUTEUR;i++){
        cpt=0;
        for(int j=0;j<LARGEUR;j++){
           if(*(g->tab+i*LARGEUR+j)!=VIDE){
                cpt++;
           }
        }
        if(cpt==LARGEUR){
            totalLigne++;
            supprimeLigne(g,i);
        }
    }
    dessinePiece(g->tab,g->pieceactive);
    switch(totalLigne){
        case 1:
            g->score+=800*((g->niveau/10)+1);
            break;
        case 2:
            g->score+=1200*((g->niveau/10)+1);
            break;
        case 3:
            g->score+=1800*((g->niveau/10)+1);
            break;
        case 4:
            g->score+=2000*((g->niveau/10)+1);
            break;
    }
    if(g->niveau<100){
        g->niveau+=totalLigne;
    }
    
}

void supprimeLigne(grille *g, unsigned x){
    assert(g && g->tab);
    if(x>HAUTEUR){
        perror("supprimeLigne : ligne non valide\n");
        exit(EXIT_FAILURE);
    }

    //suppression de la ligne
    for(int i=0;i<LARGEUR;i++){
        *(g->tab+x*LARGEUR+i)=VIDE;
    }
    
    //décalage des lignes supérieures vers le bas
    for(int i=x;i>0;i--){
        for(int j=0;j<LARGEUR;j++){
            *(g->tab+i*LARGEUR+j)=*(g->tab+(i-1)*LARGEUR+j);
        }
    }
    ombrePiece(g->pieceactive,g->tab);
}

void reserve(grille *g){
    if(! g->reserveUtilisee){
        effacePiece(g->tab,g->pieceactive);
        if(g->reserve==VIDE){
            g->reserve=g->pieceactive->c;
            reinitPiece(g->pieceactive,couleurSuivante(g->liste),0,LARGEUR/2,g->tab);
        }
        else{
            couleur mem=g->pieceactive->c;
            reinitPiece(g->pieceactive,g->reserve,0,LARGEUR/2,g->tab);
            g->reserve=mem;
        }
        g->reserveUtilisee=1;
    }
}

void afficheGrille(grille *g){
    printf("Grille :\n");
    for(int i=0;i<HAUTEUR;i++){
        for(int j=0;j<LARGEUR;j++){
            if(g->tab[i*LARGEUR+j]==VIDE){
                printf("| |");
            }
            else{
                printf("|%d|",g->tab[i*LARGEUR+j]);
            }
            
        }
        printf("\n");
    }
    printf("reserve : %d\n",g->reserve);
    printf("score : %d\n",g->score);
}