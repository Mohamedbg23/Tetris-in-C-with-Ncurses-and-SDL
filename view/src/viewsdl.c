//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "viewsdl.h"

#define H data->h
#define W data->w

viewer *initSdlViewer(){
    viewer *v=malloc(sizeof(viewer));
    if(!v){
        perror("initSDLviewer viewer\n");
        return NULL;
    }

    /* Initialise SDL */
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Could not initialise SDL: %s\n", SDL_GetError());
        return NULL;
    }
    if(TTF_Init()){
        fprintf(stderr,"Could not initialise TTF: \n");
    }
    dataSdlViewer *data = (dataSdlViewer *)malloc(sizeof(dataSdlViewer));
    if (!data) {
        perror("Problem when allocation the data structure.");
        return NULL;
    }
    

    SDL_CreateWindowAndRenderer(10, 10, SDL_INIT_VIDEO, &data->window,&data->renderer);
    if (!data->window) {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return NULL;
    }
    //obtention de la resolution de l'écran
    SDL_DisplayMode dm;
    if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return NULL;
    }
    data->h=dm.h/2.2;
    data->w=data->h;//la fenetre de jeu est carrée

    SDL_SetWindowSize(data->window,data->w*2,data->h*2);
    SDL_SetWindowPosition(data->window,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED);
    v->affiche=afficheSdl;
    v->data=data;
    v->destroy=destroySdlViewer;
    return v;
}

void afficheSdl(viewer *v,grille *g,int pause){
    dataSdlViewer *data = (dataSdlViewer *)v->data;
    
    SDL_SetRenderDrawColor(data->renderer,0,0,0,125);
    SDL_RenderClear(data->renderer);
    
    
    
    afficheGrilleSdl(v,g);
    afficheReserveSdl(v,g);
    afficheSuivanteSdl(v,g);
    afficheControles(v);
    afficheScoreSdl(v,g->score,(g->niveau/10)+1);
    if(pause){
        affichePause(v);
        afficheControlesComplet(v);
    }
    SDL_RenderPresent(data->renderer);
    
}

void afficheGrilleSdl(viewer *v, grille *g){
    assert(v && g);
    dataSdlViewer *data = (dataSdlViewer *)v->data;
    SDL_Texture *texture=SDL_CreateTexture( data->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, W, H*2 );  
    SDL_SetRenderTarget(data->renderer,texture);
    int ratioH=((H*2)/20);
    int ratioW=(W/10);
    
    //affichage de la grille case par case
    SDL_Rect rect={0,0,10,10};
    int *tabcouleur=malloc(4*sizeof(int));
    assert(tabcouleur);
    for(int i=0;i<20;i++){
        for(int j=0;j<10;j++){
            getTabCouleur(tabcouleur,g->tab[i*LARGEUR+j],g->pieceactive->c);
            SDL_SetRenderDrawColor(data->renderer,tabcouleur[0],tabcouleur[1],tabcouleur[2],tabcouleur[3]);
            rect=(SDL_Rect){j*ratioW,i*ratioH,ratioH,ratioH};
            
            if(g->tab[i*LARGEUR+j]==VIDE){//contour pour les cases vides
                SDL_SetRenderDrawColor(data->renderer,0,0,50,255);
            }
            else if(g->tab[i*LARGEUR+j]!=OMBRE){
                SDL_RenderFillRect(data->renderer,&rect);
                SDL_SetRenderDrawColor(data->renderer,0,0,0,255);
            }
            
            SDL_RenderDrawRect(data->renderer,&rect); 
        }
    }
    free(tabcouleur);
    //affichage de la grille dans un rectangle
    SDL_Rect rectangleGrille={0,0,W,H*2};
    SDL_SetRenderDrawColor(data->renderer,255,255,255,255);
    SDL_RenderDrawRect(data->renderer,&rectangleGrille);
    
    //affichage de la texture
    rectangleGrille=(SDL_Rect){W/2,0,W,H*2};
    SDL_SetRenderTarget(data->renderer,NULL);
    SDL_RenderCopy(data->renderer, texture, NULL, &rectangleGrille);
    SDL_DestroyTexture(texture);
}

void afficheReserveSdl(viewer *v, grille *g){
    assert(v && g);
    dataSdlViewer *data = (dataSdlViewer *)v->data;
    SDL_Texture *texture=SDL_CreateTexture( data->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, W/5, H/5);  
    SDL_SetRenderTarget(data->renderer,texture);
    int ratioH=((H/5)/4);
    int ratioW=(W/5)/4;

    SDL_Rect rect={0,0,10,10};
    int *tabcouleur=malloc(4*sizeof(int));
    int *tabcoordonnees=malloc(16*sizeof(int));
    assert(tabcoordonnees && tabcouleur);
    if(g->reserve!=VIDE){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                getTabCouleur(tabcouleur,g->reserve,g->pieceactive->c);
                getCoordonnees(tabcoordonnees,g->reserve);
                SDL_SetRenderDrawColor(data->renderer,tabcouleur[0],tabcouleur[1],tabcouleur[2],tabcouleur[3]);
                rect=(SDL_Rect){j*ratioW,i*ratioH,ratioH,ratioH};
                if(tabcoordonnees[i*4+j]){
                    SDL_RenderFillRect(data->renderer,&rect);
                    SDL_SetRenderDrawColor(data->renderer,0,0,0,255);
                    SDL_RenderDrawRect(data->renderer,&rect); 
                }
            }
        }
    }
    free(tabcouleur);
    free(tabcoordonnees);

    //affichage du contour
    SDL_Rect rectangleReserve={0,0,W/5,H/5};
    SDL_SetRenderDrawColor(data->renderer,255,255,255,255);
    SDL_RenderDrawRect(data->renderer,&rectangleReserve);

    //affichage de la texture
    rectangleReserve=(SDL_Rect){W/5,H/10,W/5,H/5};
    SDL_SetRenderTarget(data->renderer,NULL);
    SDL_RenderCopy(data->renderer, texture, NULL, &rectangleReserve);

    SDL_DestroyTexture(texture);
}

void afficheSuivanteSdl(viewer *v,grille *g){
    assert(v && g);
    dataSdlViewer *data = (dataSdlViewer *)v->data;
    SDL_Texture *texture=SDL_CreateTexture( data->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, W/5, 4*H/5);  
    SDL_SetRenderTarget(data->renderer,texture);
    int ratioH=((H/5)/4);
    int ratioW=(W/5)/4;

    SDL_Rect rect={0,0,10,10};
    int *tabcouleur=malloc(4*sizeof(int));
    int *tabcoordonnees=malloc(16*sizeof(int));
    assert(tabcoordonnees && tabcouleur);
    couleur c;
    for(int a=0;a<4;a++){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                c=getCouleurListe(g->liste,a);
                getTabCouleur(tabcouleur,c,g->pieceactive->c);
                getCoordonnees(tabcoordonnees,c);
                SDL_SetRenderDrawColor(data->renderer,tabcouleur[0],tabcouleur[1],tabcouleur[2],tabcouleur[3]);
                rect=(SDL_Rect){j*ratioW,i*ratioH+4*a*ratioH,ratioH,ratioH};
                if(tabcoordonnees[i*4+j]){
                    SDL_RenderFillRect(data->renderer,&rect);
                    SDL_SetRenderDrawColor(data->renderer,0,0,0,255);
                    SDL_RenderDrawRect(data->renderer,&rect); 
                }
            }
        }
        
    }
    free(tabcouleur);
    free(tabcoordonnees);

    //affichage du contour
    SDL_Rect rectangleSuiv={0,0,W/5,4*H/5};
    SDL_SetRenderDrawColor(data->renderer,255,255,255,255);
    SDL_RenderDrawRect(data->renderer,&rectangleSuiv);

    //affichage de la texture
    rectangleSuiv=(SDL_Rect){8*W/5,H/5,W/5,4*H/5};
    SDL_SetRenderTarget(data->renderer,NULL);
    SDL_RenderCopy(data->renderer, texture, NULL, &rectangleSuiv);

    SDL_DestroyTexture(texture);
}

void affichePause(viewer *v){
    assert(v);
    dataSdlViewer *data = (dataSdlViewer *)v->data;
    //police d'ecriture
    TTF_Font* police = TTF_OpenFont("ressources/Tetris.ttf", 36*((float)data->h/500));//adaptation de la taille de police à la résolution
    if(!police){
        printf("erreur police\n");
    }
    SDL_Color White = {255, 255, 255};
    char buffer[1024];
    snprintf(buffer,sizeof(buffer),"PAUSE");
    SDL_Surface* surfaceMessage =TTF_RenderText_Solid_Wrapped(police, buffer, White,W/2);
    
    //creation de la texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(data->renderer, surfaceMessage);
    SDL_SetRenderTarget(data->renderer,texture);

    //creation et affichage du rectangle
    SDL_Rect rectangle={0,0,surfaceMessage->w,surfaceMessage->h};
    SDL_SetRenderTarget(data->renderer,NULL);
    SDL_RenderCopy(data->renderer, texture, NULL, &rectangle);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(police);
}

void afficheControlesComplet(viewer *v){
    assert(v);
    dataSdlViewer *data = (dataSdlViewer *)v->data;
    //police d'ecriture
    TTF_Font* police = TTF_OpenFont("ressources/Tetris.ttf", 30*((float)data->h/500));//adaptation de la taille de police à la résolution
    if(!police){
        printf("erreur police\n");
    }
    SDL_Color White = {255, 255, 255};
    char buffer[1024];
    snprintf(buffer,sizeof(buffer),"FLECHE GAUCHE : deplace la piece vers la gauche\n\nFLECHE DROITE : deplace la piece vers la droite\n\nFLECHE BAS : deplace la piece vers le bas\n\nFLECHE HAUT : pivote la piece dans le sens trigonometrique\n\nC : met la piece en reserve et utilise la piece deja en reserve si il y en a une\n\nZ : pivote la piece dans le sens anti-trigonometrique\n\nESPACE : deplace la piece instantanement tout en bas\n\nP : active/desactive la pause\n\nECHAP : met fin a la partie et quitte le jeu");
    SDL_Surface* surfaceMessage =TTF_RenderText_Solid_Wrapped(police, buffer, White,W);
    
    //creation de la texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(data->renderer, surfaceMessage);
    SDL_SetRenderTarget(data->renderer,texture);

    //creation et affichage du rectangle
    SDL_Rect rectangle={W/2,H/10,surfaceMessage->w,surfaceMessage->h};
    SDL_SetRenderTarget(data->renderer,NULL);
    SDL_SetRenderDrawColor(data->renderer,0,0,0,255);
    SDL_RenderFillRect(data->renderer,&rectangle);
    SDL_SetRenderDrawColor(data->renderer,255,255,255,255);
    SDL_RenderDrawRect(data->renderer,&rectangle);
    SDL_RenderCopy(data->renderer, texture, NULL, &rectangle);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(police);
}

void afficheControles(viewer *v){
    assert(v);
    dataSdlViewer *data = (dataSdlViewer *)v->data;
    //police d'ecriture
    TTF_Font* police = TTF_OpenFont("ressources/Tetris.ttf", 30*((float)data->h/500));//adaptation de la taille de police à la résolution
    if(!police){
        printf("erreur police\n");
    }
    SDL_Color White = {255, 255, 255};
    char buffer[1024];
    snprintf(buffer,sizeof(buffer),"P : met en pause et affiche les controles");
    SDL_Surface* surfaceMessage =TTF_RenderText_Solid_Wrapped(police, buffer, White,W/2);
    
    //creation de la texture
    SDL_Texture *texture = SDL_CreateTextureFromSurface(data->renderer, surfaceMessage);
    SDL_SetRenderTarget(data->renderer,texture);

    //creation et affichage du rectangle
    SDL_Rect rectangle={0,H+H/2,surfaceMessage->w,surfaceMessage->h};
    SDL_SetRenderTarget(data->renderer,NULL);
    SDL_RenderCopy(data->renderer, texture, NULL, &rectangle);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(police);
}

void afficheScoreSdl(viewer *v, int score, int niveau){
    assert(v);
    dataSdlViewer *data = (dataSdlViewer *)v->data; 
    
    //police d'ecriture
    TTF_Font* police = TTF_OpenFont("ressources/Tetris.ttf", 36*((float)data->h/500));//adaptation de la taille de police à la résolution
    if(!police){
        printf("erreur police\n");
    }
    SDL_Color White = {255, 255, 255};
    char buffer[1024];
    snprintf(buffer,sizeof(buffer),"SCORE : %d \nNIVEAU : %d",score,niveau);
    SDL_Surface* surfaceMessage =TTF_RenderText_Solid_Wrapped(police, buffer, White,W/2); 

    SDL_Texture *texture = SDL_CreateTextureFromSurface(data->renderer, surfaceMessage);
    SDL_SetRenderTarget(data->renderer,texture);
    
    SDL_Rect rectangle={0,H,surfaceMessage->w,surfaceMessage->h};
    SDL_SetRenderDrawColor(data->renderer,255,255,255,255);
    SDL_RenderDrawRect(data->renderer,&rectangle);
    
    SDL_SetRenderTarget(data->renderer,NULL);
    SDL_RenderCopy(data->renderer, texture, NULL, &rectangle);

    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(police);
}

void getTabCouleur(int *tabcouleur,couleur c,couleur pieceactive){
    assert(tabcouleur);
    switch (c)
    {
    case VIDE:
        tabcouleur[0]=0;
        tabcouleur[1]=0;
        tabcouleur[2]=0;
        tabcouleur[3]=255;
        break;
    case I: //BLEU CLAIR
        tabcouleur[0]=1;
        tabcouleur[1]=237;
        tabcouleur[2]=250;
        tabcouleur[3]=255;
        break;
    case J: //BLEU
        tabcouleur[0]=0;
        tabcouleur[1]=119;
        tabcouleur[2]=211;
        tabcouleur[3]=255;
        break;
    case L: //ORANGE
        tabcouleur[0]=255;
        tabcouleur[1]=145;
        tabcouleur[2]=12;
        tabcouleur[3]=255;
        break;
    case Z: //ROUGE
        tabcouleur[0]=234;
        tabcouleur[1]=20;
        tabcouleur[2]=28;
        tabcouleur[3]=255;
        break;
    case S://VERT
        tabcouleur[0]=83;
        tabcouleur[1]=218;
        tabcouleur[2]=63;
        tabcouleur[3]=255;
        break;
    case O: //JAUNE
        tabcouleur[0]=254;
        tabcouleur[1]=251;
        tabcouleur[2]=52;
        tabcouleur[3]=255;
        break;
    case T: //VIOLET
        tabcouleur[0]=221;
        tabcouleur[1]=10;
        tabcouleur[2]=178;
        tabcouleur[3]=255;
        break;
    case OMBRE:
        getTabCouleur(tabcouleur,pieceactive,pieceactive); //l'ombre doit etre de la même couleur que la piece active
        break;
    default:
        break;
    }

}

void getCoordonnees(int * tabcoordonnees,couleur c){
    assert(tabcoordonnees);
    switch (c)
    {
    case I: //BLEU CLAIR
        tabcoordonnees[0]=0;
        tabcoordonnees[1]=0;
        tabcoordonnees[2]=0;
        tabcoordonnees[3]=0;

        tabcoordonnees[4]=1;
        tabcoordonnees[5]=1;
        tabcoordonnees[6]=1;
        tabcoordonnees[7]=1;

        tabcoordonnees[8]=0;
        tabcoordonnees[9]=0;
        tabcoordonnees[10]=0;
        tabcoordonnees[11]=0;

        tabcoordonnees[12]=0;
        tabcoordonnees[13]=0;
        tabcoordonnees[14]=0;
        tabcoordonnees[15]=0;
        break;
    case J: //BLEU
        tabcoordonnees[0]=0;
        tabcoordonnees[1]=0;
        tabcoordonnees[2]=0;
        tabcoordonnees[3]=0;

        tabcoordonnees[4]=1;
        tabcoordonnees[5]=1;
        tabcoordonnees[6]=1;
        tabcoordonnees[7]=0;

        tabcoordonnees[8]=0;
        tabcoordonnees[9]=0;
        tabcoordonnees[10]=1;
        tabcoordonnees[11]=0;

        tabcoordonnees[12]=0;
        tabcoordonnees[13]=0;
        tabcoordonnees[14]=0;
        tabcoordonnees[15]=0;
        break;
    case L: //ORANGE
        tabcoordonnees[0]=0;
        tabcoordonnees[1]=0;
        tabcoordonnees[2]=0;
        tabcoordonnees[3]=0;

        tabcoordonnees[4]=1;
        tabcoordonnees[5]=1;
        tabcoordonnees[6]=1;
        tabcoordonnees[7]=0;

        tabcoordonnees[8]=1;
        tabcoordonnees[9]=0;
        tabcoordonnees[10]=0;
        tabcoordonnees[11]=0;

        tabcoordonnees[12]=0;
        tabcoordonnees[13]=0;
        tabcoordonnees[14]=0;
        tabcoordonnees[15]=0;
        break;
    case Z: //ROUGE
        tabcoordonnees[0]=0;
        tabcoordonnees[1]=0;
        tabcoordonnees[2]=0;
        tabcoordonnees[3]=0;

        tabcoordonnees[4]=0;
        tabcoordonnees[5]=1;
        tabcoordonnees[6]=1;
        tabcoordonnees[7]=0;

        tabcoordonnees[8]=1;
        tabcoordonnees[9]=1;
        tabcoordonnees[10]=0;
        tabcoordonnees[11]=0;

        tabcoordonnees[12]=0;
        tabcoordonnees[13]=0;
        tabcoordonnees[14]=0;
        tabcoordonnees[15]=0;
        break;
    case S://VERT
        tabcoordonnees[0]=0;
        tabcoordonnees[1]=0;
        tabcoordonnees[2]=0;
        tabcoordonnees[3]=0;

        tabcoordonnees[4]=1;
        tabcoordonnees[5]=1;
        tabcoordonnees[6]=0;
        tabcoordonnees[7]=0;

        tabcoordonnees[8]=0;
        tabcoordonnees[9]=1;
        tabcoordonnees[10]=1;
        tabcoordonnees[11]=0;

        tabcoordonnees[12]=0;
        tabcoordonnees[13]=0;
        tabcoordonnees[14]=0;
        tabcoordonnees[15]=0;
        break;
    case O: //JAUNE
        tabcoordonnees[0]=0;
        tabcoordonnees[1]=0;
        tabcoordonnees[2]=0;
        tabcoordonnees[3]=0;

        tabcoordonnees[4]=0;
        tabcoordonnees[5]=1;
        tabcoordonnees[6]=1;
        tabcoordonnees[7]=0;

        tabcoordonnees[8]=0;
        tabcoordonnees[9]=1;
        tabcoordonnees[10]=1;
        tabcoordonnees[11]=0;

        tabcoordonnees[12]=0;
        tabcoordonnees[13]=0;
        tabcoordonnees[14]=0;
        tabcoordonnees[15]=0;
        break;
    case T: //VIOLET
        tabcoordonnees[0]=0;
        tabcoordonnees[1]=0;
        tabcoordonnees[2]=0;
        tabcoordonnees[3]=0;

        tabcoordonnees[4]=1;
        tabcoordonnees[5]=1;
        tabcoordonnees[6]=1;
        tabcoordonnees[7]=0;

        tabcoordonnees[8]=0;
        tabcoordonnees[9]=1;
        tabcoordonnees[10]=0;
        tabcoordonnees[11]=0;

        tabcoordonnees[12]=0;
        tabcoordonnees[13]=0;
        tabcoordonnees[14]=0;
        tabcoordonnees[15]=0;
        break;
    default:
        break;
    }
}

void destroySdlViewer(viewer *v) {
    if(v){
        dataSdlViewer *data = (dataSdlViewer *)v->data;
        SDL_DestroyRenderer(data->renderer);
        SDL_DestroyWindow(data->window);

        free(data);
        free(v);

        TTF_Quit();
        SDL_Quit();
    }
}  // destroySdlViewer