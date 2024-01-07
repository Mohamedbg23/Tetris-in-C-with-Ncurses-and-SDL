//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#include "listeAttente.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

listeAttente * creerListeAttente(){
    //allocations
    listeAttente *l=malloc(sizeof(listeAttente));
    if(!l){
        perror("erreur allocation listeAttente\n");
        exit(EXIT_FAILURE);
    }
    l->liste=malloc(14*sizeof(couleur));
    if(!l->liste){
        perror("erreur allocation liste couleur\n");
        exit(EXIT_FAILURE);
    }
    //génération de la liste de couleurs
    l->indice=0;
    genererCouleurs(l);
    l->indice=7;
    genererCouleurs(l);
    return l;
}

void libereListeAttente(listeAttente *l){
    if(l){
        if(l->liste){
            free(l->liste);
        }
        free(l);
    }
}

void genererCouleurs(listeAttente *l){
    //creation d'un tableau contenant les 7 valeurs possibles pour une piece
    int *tab=malloc(7*sizeof(int));
    for(int i=0;i<7;i++){
        *(tab+i)=i+1;
    }
    //mélange du tableau
    int mem,j;
    for (int i=0;i<7-1;i++){
        j=i+rand()/(RAND_MAX/(7-i)+1);
        mem=*(tab+j);
        *(tab+j)=*(tab+i);
        *(tab+i)=mem;
    }
    //copie du tableau provisoire
    int dest=abs(l->indice);
    memcpy((l->liste+dest),tab,7*sizeof(int));
    free(tab);
}

couleur couleurSuivante(listeAttente *l){
    assert(l);
    couleur retour =*(l->liste+l->indice);
    l->indice+=1;
    if(l->indice==7){
        genererCouleurs(l);
    }
    if(l->indice>=14){
            l->indice=0;
            genererCouleurs(l);
    }
    
    
    return retour;
}

couleur getCouleurListe(listeAttente *l,int i){
    assert(l);
    couleur retour;
    if(l->indice+i>=14){
        retour=*(l->liste+14-l->indice+i);
    }
    else{
        retour =*(l->liste+l->indice+i);
    }
    return retour;
}