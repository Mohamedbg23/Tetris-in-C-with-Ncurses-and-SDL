//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../../model/src/listeAttente.h"
#include "../../model/src/grille.h"
#include "../../model/src/piece.h"
#include "viewer.h"

typedef struct {
  SDL_Window *window;
  SDL_Renderer *renderer;
  int h;
  int w;
} dataSdlViewer;


/***
 * @brief cree un viewer pour sdl
 * @return viewer *
*/
viewer *initSdlViewer();

/**
 * @brief affiche la fenetre de jeu
 * @param viewer *v
 * @param grille *g
 * @param int pause
 * @return rien
*/
void afficheSdl(viewer *v,grille *g,int pause);

/**
 * @brief affiche la grille
 * @param viewer *v
 * @param grille *g
 * @return rien
*/
void afficheGrilleSdl(viewer *v,grille *g);

/**
 * @brief affiche la réserve
 * @param viewer *v
 * @param grille *g
 * @return rien
*/
void afficheReserveSdl(viewer *v,grille *g);

/**
 * @brief affiche le score
 * @param viewer *v
 * @param grille *g
 * @return rien
*/
void afficheScoreSdl(viewer *v, int score, int niveau);

/**
 * @brief affiche les prochaines pieces
 * @param viewer *v
 * @param grille *g
 * @return rien
*/
void afficheSuivanteSdl(viewer *v,grille *g);

/**
 * @brief affiche le texte "PAUSE"
 * @param viewer *v
 * @return rien
*/
void affichePause(viewer *v);

/**
 * @brief affiche les controles complets du jeu
 * @param view *v
 * @return rien
*/
void afficheControlesComplet(viewer *v);

/**
 * @brief affiche les une indication que P met en pause
 * @param view *v
 * @return rien
*/
void afficheControles(viewer *v);

/**
 * @brief retourne un tableau avec les valeurs RGBA de la couleur
 * @param int * tabcouleur
 * @param couleur c
 * @param couleur piece active
 * @return rien
*/
void getTabCouleur(int *tabcouleur,couleur c,couleur pieceactive);

/**
 * @brief retourne un tableau de 16 cases correspondat aux coordoonees necessaire pour dessiner une piece
 * @param int *tabcoordonnees
 * @param couleur c
*/
void getCoordonnees(int *tabCoordonnees,couleur c);

/**
 * @brief détruit le viewersdl
 * @param viewer *v
 * @return rien
*/
void destroySdlViewer(viewer *v);