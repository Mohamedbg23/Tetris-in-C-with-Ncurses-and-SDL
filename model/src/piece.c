//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#include "piece.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

piece * creerPiece(couleur c, unsigned x,unsigned y,couleur *tab,piece *p){
    assert(tab);
    //allocations
    if(!p){
        p=(piece*)malloc(sizeof(piece));
        if(!p){
            perror("Erreur d'allocation de la piece\n");
            exit(EXIT_FAILURE);
        }
        p->coordonnees=calloc(8,sizeof(unsigned));
        if(! p->coordonnees){
            perror("Erreur d'allocation de la piece\n");
            exit(EXIT_FAILURE);
        }
        p->coordonneesOmbre=calloc(8,sizeof(unsigned));
        if(! p->coordonneesOmbre){
            perror("Erreur d'allocation de la piece\n");
            exit(EXIT_FAILURE);
        }
    }
    
    //creation des coordonnées de la piece, en fonction de sa couleur
    switch (c)
    {
    case I:
        p->coordonnees[0]=x;
        p->coordonnees[1]=y-1;

        p->coordonnees[2]=x;
        p->coordonnees[3]=y;

        p->coordonnees[4]=x;
        p->coordonnees[5]=y+1;

        p->coordonnees[6]=x;
        p->coordonnees[7]=y+2;
        break;

    case J:
        p->coordonnees[0]=x;
        p->coordonnees[1]=y;

        p->coordonnees[2]=x+1;
        p->coordonnees[3]=y;

        p->coordonnees[4]=x+1;
        p->coordonnees[5]=y+1;

        p->coordonnees[6]=x+1;
        p->coordonnees[7]=y+2;
        break;

    case L:
        p->coordonnees[0]=x;
        p->coordonnees[1]=y;

        p->coordonnees[2]=x+1;
        p->coordonnees[3]=y;

        p->coordonnees[4]=x+1;
        p->coordonnees[5]=y-1;

        p->coordonnees[6]=x+1;
        p->coordonnees[7]=y-2;
        break;

    case S:
        p->coordonnees[0]=x;
        p->coordonnees[1]=y-1;

        p->coordonnees[2]=x;
        p->coordonnees[3]=y;

        p->coordonnees[4]=x+1;
        p->coordonnees[5]=y;

        p->coordonnees[6]=x+1;
        p->coordonnees[7]=y+1;
        break;

    case Z:
        p->coordonnees[0]=x;
        p->coordonnees[1]=y+1;

        p->coordonnees[2]=x;
        p->coordonnees[3]=y;

        p->coordonnees[4]=x+1;
        p->coordonnees[5]=y;

        p->coordonnees[6]=x+1;
        p->coordonnees[7]=y-1;
        break;
    case O:
        p->coordonnees[0]=x;
        p->coordonnees[1]=y;

        p->coordonnees[2]=x;
        p->coordonnees[3]=y+1;

        p->coordonnees[4]=x+1;
        p->coordonnees[5]=y;

        p->coordonnees[6]=x+1;
        p->coordonnees[7]=y+1;
        break;
    case T:
        p->coordonnees[0]=x;
        p->coordonnees[1]=y;

        p->coordonnees[2]=x+1;
        p->coordonnees[3]=y;

        p->coordonnees[4]=x+1;
        p->coordonnees[5]=y+1;

        p->coordonnees[6]=x+1;
        p->coordonnees[7]=y-1;
        break;

    }
    
    p->k=1;
    p->c=c;
    ombrePiece(p,tab);
    return p;

}//creerPiece

int reinitPiece(piece *p,couleur c, unsigned x,unsigned y,couleur *tab){
    assert(p);
    p=creerPiece(c,x,y,tab,p);
    for(int i=0;i<8;i+=2){
        unsigned c=p->coordonnees[i];
        unsigned c2=p->coordonnees[i+1];
        if(tab[c*LARGEUR+c2]!= VIDE){
            return 0;//si la nouvelle piece est en collision avec une autre, la partie s'arrete
        }
    }
    dessinePiece(tab,p);
    return 1;
}

void liberePiece(piece *p){
    if(p){
        if(p->coordonnees){
            free(p->coordonnees);
        }
        if(p->coordonneesOmbre){
            free(p->coordonneesOmbre);
        }
        free(p);
    }
}

int deplacePiece(piece *p,direction d, couleur *tab){
    assert(p);
    int ok=1;
    effacePiece(tab,p);//permet de ne pas détecter des collisions entre la piece et elle même
    switch(d){
        case BAS:
            for(int i=0;i<8;i+=2){//vérification des collisions
                if(*(p->coordonnees+i)+1>=HAUTEUR || *(tab+(*(p->coordonnees+i)+1)*LARGEUR+(*(p->coordonnees+i+1) ))!=VIDE){
                    ok=0;
                }
            }
            if(ok){//modification des coordonnées
                for(int i=0;i<8;i+=2){
                    *(p->coordonnees+i)+=1;
                }
            }
            
            break;
        case GAUCHE :
            for(int i=0;i<8;i+=2){//vérification des collisions
                if((int)*(p->coordonnees+i+1)-1 < 0 || *(tab+(*(p->coordonnees+i))*LARGEUR+(*(p->coordonnees+i+1)-1))!=VIDE){
                    ok=0;
                }
            }
            if(ok){//modification des coordonnées
                for(int i=1;i<8;i+=2){
                    *(p->coordonnees+i)-=1;
                }
            }
            break;
        case DROITE :
            for(int i=0;i<8;i+=2){//vérification des collisions
                if(*(p->coordonnees+i+1)+1>=LARGEUR || *(tab+(*(p->coordonnees+i))*LARGEUR+(*(p->coordonnees+i+1)+1))!=VIDE){
                    ok=0;
                }
            }
            if(ok){//modification des coordonnées
                for(int i=1;i<8;i+=2){
                    *(p->coordonnees+i)+=1;
                }
            }
            break;    
    }
    ombrePiece(p,tab);
    dessinePiece(tab,p);
    return ok;
}//deplacePiece

void teleportePieceBas(piece *p,couleur *tab){
    assert(p);
    for(int i=0;i<HAUTEUR;i++){
        deplacePiece(p,BAS,tab);
    }
}

void ombrePiece(piece *p,couleur *tab){
    assert(p);
    assert(tab);
    int ok=1;
    memcpy(p->coordonneesOmbre,p->coordonnees,8*sizeof(unsigned));
    while(ok){//déplacement de l'ombre vers le bas, tant qu'il n y pas de collision
        for(int i=0;i<8;i+=2){
            if(*(p->coordonneesOmbre+i)+1>=HAUTEUR || tab[(*(p->coordonneesOmbre+i)+1)*LARGEUR+*(p->coordonneesOmbre+i+1)]!=VIDE){
                ok=0;
            }
        }
        if(ok){
            for(int i=0;i<8;i+=2){
                *(p->coordonneesOmbre+i)+=1;
            }
        }
    }

}

int verifieCollision(piece *p,couleur *tab){
    assert(p && tab);
    int ok=1;
    for(int i=0;i<8;i+=2){
                if(*(p->coordonnees+i)>=HAUTEUR || (int)*(p->coordonnees+i)<0 ||*(p->coordonnees+i+1)>=LARGEUR ||(int)*(p->coordonnees+i+1)<0 ||*(tab+(*(p->coordonnees+i))*LARGEUR+(*(p->coordonnees+i+1) ))!=VIDE){
                    ok=0;
                }
            }
    return ok;
}

void rotationPiece(piece *p, direction d,couleur *tab){
    assert(p && tab);

    effacePiece(tab,p);
    switch (d)
    {
    case GAUCHE:
        rotationGauche(p,tab);
        break;
    
    case DROITE:
        rotationGauche(p,tab);
        rotationGauche(p,tab);
        rotationGauche(p,tab);
        break;
    }
    ombrePiece(p,tab);

    dessinePiece(tab,p);
}

void rotationGauche(piece *p,couleur *tab){
    assert(p && tab);
    unsigned *mem=malloc(8*sizeof(unsigned));//mémorisation des anciennes coordonnées de la piece
    memcpy(mem,p->coordonnees,8*sizeof(unsigned));
    int memk=p->k;
    switch (p->c)//modifcation des coordonnées de la pièce au cas par cas
    {
        case I:    
            switch (p->k)
                {
                case 1:
                    p->coordonnees[0]=p->coordonnees[4];
                    p->coordonnees[1]=p->coordonnees[5];

                    p->coordonnees[2]=p->coordonnees[0]+1;
                    p->coordonnees[3]=p->coordonnees[1];                    

                    p->coordonnees[4]=p->coordonnees[0]+2;
                    p->coordonnees[5]=p->coordonnees[1];

                    p->coordonnees[6]=p->coordonnees[0]+3;
                    p->coordonnees[7]=p->coordonnees[1];
                    p->k++;
                break;
                case 2:

                    p->coordonnees[0]=p->coordonnees[4];
                    p->coordonnees[1]=p->coordonnees[5]-2;

                    p->coordonnees[2]=p->coordonnees[4];
                    p->coordonnees[3]=p->coordonnees[5]-1;

                    p->coordonnees[4];
                    p->coordonnees[5];

                    p->coordonnees[6]=p->coordonnees[4];
                    p->coordonnees[7]=p->coordonnees[5]+1;
                    p->k++;
                break;
                case 3:
                    p->coordonnees[4]=p->coordonnees[2];
                    p->coordonnees[5]=p->coordonnees[3];

                    p->coordonnees[0]=p->coordonnees[4]-2;
                    p->coordonnees[1]=p->coordonnees[5];

                    

                    p->coordonnees[2]=p->coordonnees[4]-1;
                    p->coordonnees[3]=p->coordonnees[5];

                    p->coordonnees[6]=p->coordonnees[4]+1;
                    p->coordonnees[7]=p->coordonnees[5];
                    p->k++;
                break;
                case 4:

                    p->coordonnees[0];
                    p->coordonnees[1]=p->coordonnees[1]-1;

                    p->coordonnees[2]=p->coordonnees[0];
                    p->coordonnees[3]=p->coordonnees[1]+1;

                    p->coordonnees[4]=p->coordonnees[0];
                    p->coordonnees[5]=p->coordonnees[1]+2;

                    p->coordonnees[6]=p->coordonnees[0];
                    p->coordonnees[7]=p->coordonnees[1]+3;
                    p->k=1;
                break;

                }
            break;
    
    case J:
        switch (p->k)
        {
        case 1:
            p->coordonnees[0]=p->coordonnees[4]-1;
            p->coordonnees[1]=p->coordonnees[5]+1;

            p->coordonnees[2]=p->coordonnees[4]-1;
            p->coordonnees[3]=p->coordonnees[5];

            p->coordonnees[4];
            p->coordonnees[5];

            p->coordonnees[6]=p->coordonnees[4]+1;
            p->coordonnees[7]=p->coordonnees[5];
            p->k++;
        break;
        case 2:

            p->coordonnees[2]=p->coordonnees[4];
            p->coordonnees[3]=p->coordonnees[5];

            p->coordonnees[0]=p->coordonnees[2];
            p->coordonnees[1]=p->coordonnees[3]-1;

            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3]+1;

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3]+1;
            p->k++;
        break;
        case 3:
            p->coordonnees[0]=p->coordonnees[2]-1;
            p->coordonnees[1]=p->coordonnees[3];

            

            p->coordonnees[2];
            p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2]+1;
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3]-1;
            p->k++;
        break;
        case 4:

            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[0]=p->coordonnees[4]-1;
            p->coordonnees[1]=p->coordonnees[5]-1;

            p->coordonnees[2]=p->coordonnees[4];
            p->coordonnees[3]=p->coordonnees[5]-1;

            p->coordonnees[6]=p->coordonnees[4];
            p->coordonnees[7]=p->coordonnees[5]+1;
            p->k=1;
        break;

        }
        break;

    case L:
        switch (p->k)
        {
        case 1:
            p->coordonnees[2]=p->coordonnees[4];
            p->coordonnees[3]=p->coordonnees[5];

            p->coordonnees[0]=p->coordonnees[2]-1;
            p->coordonnees[1]=p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2]+1;
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3]+1;
            p->k++;
        break;
        case 2:

            p->coordonnees[2];
            p->coordonnees[3];

            p->coordonnees[0]=p->coordonnees[2];
            p->coordonnees[1]=p->coordonnees[3]+1;

            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3]-1;

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3]-1;
            p->k++;
        break;
        case 3:
            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[0]=p->coordonnees[4]-1;
            p->coordonnees[1]=p->coordonnees[5]-1;

            p->coordonnees[2]=p->coordonnees[4]-1;
            p->coordonnees[3]=p->coordonnees[5];



            p->coordonnees[6]=p->coordonnees[4]+1;
            p->coordonnees[7]=p->coordonnees[5];
            p->k++;
        break;
        case 4:
            p->coordonnees[0]=p->coordonnees[4]-1;
            p->coordonnees[1]=p->coordonnees[5]+1;

            p->coordonnees[2]=p->coordonnees[4];
            p->coordonnees[3]=p->coordonnees[5]+1;

            p->coordonnees[4];
            p->coordonnees[5];

            p->coordonnees[6]=p->coordonnees[4];
            p->coordonnees[7]=p->coordonnees[5]-1;
            p->k=1;
        break;

        }
        break;

    case S:
        switch (p->k)
        {
        case 1:
            p->coordonnees[0]=p->coordonnees[4]-1;
            p->coordonnees[1]=p->coordonnees[5]+1;

            p->coordonnees[2]=p->coordonnees[4];
            p->coordonnees[3]=p->coordonnees[5]+1;

            p->coordonnees[4];
            p->coordonnees[5];

            p->coordonnees[6]=p->coordonnees[4]+1;
            p->coordonnees[7]=p->coordonnees[5];
            p->k++;
        break;
        case 2:

            p->coordonnees[2]=p->coordonnees[4];
            p->coordonnees[3]=p->coordonnees[5];

            p->coordonnees[0]=p->coordonnees[2];
            p->coordonnees[1]=p->coordonnees[3]-1;

            p->coordonnees[4]=p->coordonnees[2]+1;
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3]+1;
            p->k++;
        break;
        case 3:
            p->coordonnees[0]=p->coordonnees[2]-1;
            p->coordonnees[1]=p->coordonnees[3];

            p->coordonnees[2];
            p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3]-1;

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3]-1;
            p->k++;
        break;
        case 4:
            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[0]=p->coordonnees[4]-1;
            p->coordonnees[1]=p->coordonnees[5]-1;

            p->coordonnees[2]=p->coordonnees[4]-1;
            p->coordonnees[3]=p->coordonnees[5];

            p->coordonnees[6]=p->coordonnees[4];
            p->coordonnees[7]=p->coordonnees[5]+1;
            p->k=1;
        break;

        }
        break;

    case Z:
        switch (p->k)
        {
        case 1:
           

            p->coordonnees[2]=p->coordonnees[4];
            p->coordonnees[3]=p->coordonnees[5];

            p->coordonnees[0]=p->coordonnees[2]-1;
            p->coordonnees[1]=p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3]+1;

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3]+1;
            p->k++;
        break;
        case 2:
            p->coordonnees[0]=p->coordonnees[2];
            p->coordonnees[1]=p->coordonnees[3]+1;

            p->coordonnees[2];
            p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2]+1;
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3]-1;
            p->k++;
        break;
        case 3:
            p->coordonnees[0]=p->coordonnees[2]-1;
            p->coordonnees[1]=p->coordonnees[3];

            p->coordonnees[2]=p->coordonnees[2];
            p->coordonnees[3]=p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3]+1;

            p->coordonnees[6]=p->coordonnees[4]+1;
            p->coordonnees[7]=p->coordonnees[5];
            p->k++;
        break;
        case 4:
            p->coordonnees[0]=p->coordonnees[4]-1;
            p->coordonnees[1]=p->coordonnees[5];

            p->coordonnees[2]=p->coordonnees[4]-1;
            p->coordonnees[3]=p->coordonnees[5]-1;

            p->coordonnees[4];
            p->coordonnees[5]--;

            p->coordonnees[6]=p->coordonnees[4];
            p->coordonnees[7]=p->coordonnees[5]-1;
            p->k=1;
        break;

        }
        break;
    case O:
        
        break;
    case T:
        switch (p->k)
        {
        case 1:
            p->coordonnees[0]=p->coordonnees[2]-1;
            p->coordonnees[1]=p->coordonnees[3];

            p->coordonnees[2];
            p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2]+1;
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[6]=p->coordonnees[2];
            p->coordonnees[7]=p->coordonnees[3]+1;
            p->k++;
        break;
        case 2:
            p->coordonnees[0]=p->coordonnees[2];
            p->coordonnees[1]=p->coordonnees[3]+1;

            p->coordonnees[2];
            p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2]+1;
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[6]=p->coordonnees[2];
            p->coordonnees[7]=p->coordonnees[3]-1;
            p->k++;
        break;
        case 3:
            p->coordonnees[0]=p->coordonnees[2]-1;
            p->coordonnees[1]=p->coordonnees[3];

            p->coordonnees[2];
            p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2];
            p->coordonnees[5]=p->coordonnees[3]-1;

            p->coordonnees[6]=p->coordonnees[2]+1;
            p->coordonnees[7]=p->coordonnees[3];
            p->k++;
        break;
        case 4:
            p->coordonnees[0]=p->coordonnees[2];
            p->coordonnees[1]=p->coordonnees[3]+1;

            p->coordonnees[2];
            p->coordonnees[3];

            p->coordonnees[4]=p->coordonnees[2]-1;
            p->coordonnees[5]=p->coordonnees[3];

            p->coordonnees[6]=p->coordonnees[2];
            p->coordonnees[7]=p->coordonnees[3]-1;
            p->k=1;
        break;

        }
        break;
        
    

    }
    if(!verifieCollision(p,tab)){
        memcpy(p->coordonnees,mem,8*sizeof(unsigned));
        p->k=memk;
    }
    free(mem);
}//rotationGauche

void dessinePiece(couleur *tab, piece *p){
    assert(p && tab);
    unsigned *c=p->coordonneesOmbre;
    for(int i=0;i<8;i+=2){
        tab[*(c+i)*LARGEUR+*(c+i+1)]=OMBRE;
    }
    c=p->coordonnees;
    for(int i=0;i<8;i+=2){
        tab[*(c+i)*LARGEUR+*(c+i+1)]=p->c;
    }
    
}

void effacePiece(couleur *tab,piece *p){
    assert(p && tab);
    unsigned *c=p->coordonnees;
    for(int i=0;i<8;i+=2){
        tab[*(c+i)*LARGEUR+*(c+i+1)]=VIDE;
    }
    c=p->coordonneesOmbre;
    for(int i=0;i<8;i+=2){
        tab[*(c+i)*LARGEUR+*(c+i+1)]=VIDE;
    }
}