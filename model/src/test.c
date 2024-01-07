//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
/**
 * @brief fichier de test pour le modele. permet de jouer au coup par coup dans le terminal.
*/
#include <stdio.h>
#include <stdlib.h>
#include "grille.h"
#include "piece.h"
#include <time.h>
int main(){
    srand(time(NULL));
    //printf("demat bed\n");
    grille *g=creerGrille();
    couleur *tab=malloc(200*sizeof(couleur));
    piece *p=creerPiece(L,0,5,tab,p);
    liberePiece(p);
    free(tab);
    //g->pieceactive=creerPiece(T,0,5,g->tab,g->pieceactive);
    //dessinePiece(g->tab,g->pieceactive);

    afficheGrille(g);
   /* afficheGrille(g);
    effacePiece(g->tab,g->pieceactive);
    rotationGauche(g->pieceactive);
    rotationGauche(g->pieceactive);
    rotationGauche(g->pieceactive);
    rotationGauche(g->pieceactive);
    deplacePiece(g->pieceactive,GAUCHE,g->tab);
    printf("\n");
    deplacePiece(g->pieceactive,GAUCHE,g->tab);
    printf("\n");
    deplacePiece(g->pieceactive,GAUCHE,g->tab);
    printf("\n");
    deplacePiece(g->pieceactive,GAUCHE,g->tab);
    printf("\n");
    deplacePiece(g->pieceactive,GAUCHE,g->tab);
    dessinePiece(g->tab,g->pieceactive);
    afficheGrille(g);
    */




    int a=0;
    int var=0;
    while(1){
        if(detecteCollision(g)){
            
            if(!reinitPiece(g->pieceactive,couleurSuivante(g->liste),0,5,g->tab)){
                printf("PARTIE TERMINEE. SCORE : %d\n",g->score);
                return 0;
            }
            detecteLigne(g);
            afficheGrille(g);
        }
        
        afficheGrille(g);
        printf("Option 0 pour quiter 1 pour faire la rotation 2 pour changer la pieece\n 4 : GAUCHE\t5: BAS\t6: DROITE\t8 : teleporte BAS\n");
        scanf("%d",&a);
        switch (a)
        {
        case 0:
            exit(EXIT_SUCCESS);
            break;
        case 1:
            rotationPiece(g->pieceactive,GAUCHE,g->tab);
            afficheGrille(g);
            break;
        case 2:
            printf("Les pieces: I=1,J,L,Z,S,O,T\n");
            scanf("%d",&var);
            effacePiece(g->tab,g->pieceactive);
            reinitPiece(g->pieceactive,var,0,5,g->tab);
            dessinePiece(g->tab,g->pieceactive);
            afficheGrille(g);
            break;
        case 4:
            deplacePiece(g->pieceactive,GAUCHE,g->tab);
            afficheGrille(g);
            break;
        case 5:
            deplacePiece(g->pieceactive,BAS,g->tab);
            afficheGrille(g);
            break;
        case 6:
            deplacePiece(g->pieceactive,DROITE,g->tab);
            afficheGrille(g);
            break;
        case 8:
            teleportePieceBas(g->pieceactive,g->tab);
            afficheGrille(g);
            break;
        case 9:
            reserve(g);
            afficheGrille(g);
            break;
        default:
            break;
        }
        
    }




    libereGrille(g);
}
