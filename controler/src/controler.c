//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <time.h>

#include "../../model/src/listeAttente.h"
#include "../../model/src/grille.h"
#include "../../model/src/piece.h"
#include "../../view/src/viewer.h"
#include "../../view/src/viewsdl.h"
#include "../../view/src/viewtxt.h"
#include "controler.h"




void jeuSDL() {
    
    grille *g=creerGrille();
    viewer *v=makeViewer("sdl");
    char c='a';
    time_t minuteur=clock(),nouveau;
    int refresh=1; //indique que le jeu doit être réaffiché
    SDL_Event event;
    int fin=0,fin2;
    int pause=0;
    time_t collision;//permet de deplacer la piece d'une case après la collision avec le bas
    while(!fin){//boucle principale
        fin2=0;
        nouveau=clock();
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                fin =1;
                break;
            }
            
            if (event.type != SDL_KEYDOWN) continue;
            switch (event.key.keysym.sym) {
                case SDLK_DOWN:
                    if(!pause && deplacePiece(g->pieceactive,BAS,g->tab)){
                        minuteur=nouveau;
                        refresh=1;  
                    }
                    break;
                case SDLK_UP:
                    if(!pause){
                        rotationPiece(g->pieceactive,DROITE,g->tab);
                        refresh=1;
                    }
                    break;
                case SDLK_LEFT:
                    if(!pause && deplacePiece(g->pieceactive,GAUCHE,g->tab)){
                        refresh=1;
                    }
                    break;
                case SDLK_RIGHT:
                    if(!pause && deplacePiece(g->pieceactive,DROITE,g->tab)){
                        refresh=1;
                    }
                    break;
                case SDLK_c:
                    if(!pause){
                        reserve(g);
                        refresh=1;
                        minuteur=nouveau;
                    }
                    break;
                case SDLK_z:
                    if(!pause){
                        rotationPiece(g->pieceactive,GAUCHE,g->tab);
                        refresh=1;
                    }
                    break;
                case SDLK_SPACE:
                    if(!pause){
                        teleportePieceBas(g->pieceactive,g->tab);
                        refresh=1;
                        fin2=1; //pas le droit au dernier deplacement si espace est utilisé
                    }
                    break;
                case SDLK_ESCAPE:
                    fin=1;
                    break;
                case SDLK_p:
                    pause=pause==0?1:0;
                    break;

                default:
                    break;
            }
        }
        if((nouveau-minuteur)*1000/CLOCKS_PER_SEC > 1300-(g->niveau*10)){
            if(!pause){
                deplacePiece(g->pieceactive,BAS,g->tab);
            }
            
            minuteur=nouveau;
            refresh=1;
        }
        if(refresh){
            if(!pause && detecteCollision(g)){
                collision=clock();
                refresh=0;
                v->affiche(v,g,pause);
                
                while((clock()-collision)*1000/CLOCKS_PER_SEC < 1300-(g->niveau*10) && !fin2){//permet de deplacer la piece d'une case max après collision avec le bas
                    while(SDL_PollEvent(&event)){
                        if(event.type == SDL_QUIT){
                            fin=1;
                            fin2=1;
                            break;
                        }
        
                        if (event.type != SDL_KEYDOWN) continue;    
                        switch (event.key.keysym.sym) {
                            case SDLK_LEFT:
                                if(deplacePiece(g->pieceactive,GAUCHE,g->tab)){
                                    refresh=1;
                                }
                                fin2=1;
                                break;
                            case SDLK_RIGHT:
                                if(deplacePiece(g->pieceactive,DROITE,g->tab)){
                                    refresh=1;
                                }
                                fin2=1;
                                break;
                            case SDLK_DOWN:
                                fin2=1;
                                break;
                            default:
                                break;
                        }
                        if(refresh){
                            v->affiche(v,g,pause);
                        }
                    }
                }
                
                if(!reinitPiece(g->pieceactive,couleurSuivante(g->liste),0,5,g->tab)){
                    fin=1;
                    continue;
                }
                detecteLigne(g);
                minuteur=clock();
            }
            
            v->affiche(v,g,pause);
            
        }
    }
    printf("PARTIE TERMINEE. SCORE : %d. NIVEAU : %d\n",g->score,(g->niveau/10)+1);
    v->destroy(v);
    libereGrille(g);
    return;
}

void jeuTXT(){
    grille *g=creerGrille();
    viewer *v = initTextViewer();
    printw("Press ESCAPE to exit");
    
    display(((dataTextViewer *)v->data),g);
    int refresh=1;
    int fin=0,fin2;
    time_t minuteur=clock(),nouveau;
    time_t collision;//permet de deplacer la piece d'une case après la collision avec le bas
    int ch;
    while ( !fin) {
        nouveau=clock();

        if ((ch = getch()) != ERR){
        if (ch == 27) {
            fin = 1;
            break;
        }
        

        switch (ch) {
        case KEY_LEFT:
        if(deplacePiece(g->pieceactive,GAUCHE,g->tab)){
            refresh=1;  
            }
            break;
        case KEY_RIGHT:
        if(deplacePiece(g->pieceactive,DROITE,g->tab)){
            refresh=1;  
            }
            break;
        case KEY_UP:
            rotationPiece(g->pieceactive,DROITE,g->tab);
            refresh=1;  
            break;
        case KEY_DOWN:
        if(deplacePiece(g->pieceactive,BAS,g->tab)){
            minuteur=nouveau;
            refresh=1;  
        }
            break;
        case 'c':
            reserve(g);
            refresh=1;
            minuteur=nouveau;
            break;
        case 'z':
            rotationPiece(g->pieceactive,GAUCHE,g->tab);
            refresh=1;
            break;
        case ' ':
            teleportePieceBas(g->pieceactive,g->tab);
            refresh=1;
        break;
        }}
        if((nouveau-minuteur)*1000/CLOCKS_PER_SEC > 1500-(g->niveau*10)){
                deplacePiece(g->pieceactive,BAS,g->tab);
                minuteur=nouveau;
                refresh=1;
        }

        if(refresh){
                if(detecteCollision(g)){
                    collision=clock();
                    refresh=0;

                    while((clock()-collision)*1000/CLOCKS_PER_SEC < 1300-(g->niveau*10) && !fin2){//permet de deplacer la piece d'une case max après collision avec le bas
                        if ((ch = getch()) != ERR){
                            if(ch == 27){
                                fin=1;
                                fin2=1;
                                break;
                            }
            
                            switch (ch) {
                                case KEY_LEFT:
                                    if(deplacePiece(g->pieceactive,GAUCHE,g->tab)){
                                        refresh=1;
                                    }
                                    fin2=1;
                                    break;
                                case KEY_RIGHT:
                                    if(deplacePiece(g->pieceactive,DROITE,g->tab)){
                                        refresh=1;
                                    }
                                    fin2=1;
                                    break;
                                case KEY_DOWN:
                                    fin2=1;
                                    break;
                                default:
                                    break;
                            }
    
                        }
                    }
                    
                    if(!reinitPiece(g->pieceactive,couleurSuivante(g->liste),0,5,g->tab)){
                        fin=1;
                        continue;
                    }
                    detecteLigne(g);
                    minuteur=clock();
                }
                            
            }
        
        display(((dataTextViewer *)v->data),g);
    }
  // play
    stopTextPlayer(v);
    v->destroy;
}