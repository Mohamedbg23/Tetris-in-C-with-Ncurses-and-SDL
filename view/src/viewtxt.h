//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#pragma once

#include <ncurses.h>

#include "../../model/src/listeAttente.h"
#include "../../model/src/grille.h"
#include "../../model/src/piece.h"

typedef struct viewer viewer;

typedef struct {
  WINDOW *win;
  WINDOW *secwin;
  int startx, starty, width, height;
} dataTextViewer;

/**
 * @brief Create and initialize a text viewer.
 *
 * @return is a pointer (we have to free) on a text viewer.
 */
viewer *initTextViewer();

/**
 * @brief Joue au taquin en mode console.
 *
 * @param v est le viewer.
 * @param e est le moteur du jeu.
 */
void playTextViewer(viewer *v,grille *g);

/**
 * @brief Stop the viewer engine.
 *
 */
void stopTextPlayer(viewer *v);

/**
 * @brief Affiche le tableau dans la console.
 *
 * @param e est le moteur de jeu.
 * @param data est la structure permettant de récupéer les data.
 */
void display( dataTextViewer *data,grille *g);

/**
 * @brief Detruit le viewer.
 *
 * @param v est le viewer qu'on souhaite libérer.
 */
void destroyTextViewer(viewer *v);