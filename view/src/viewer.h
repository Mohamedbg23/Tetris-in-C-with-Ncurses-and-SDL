//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#pragma once
#include "../../model/src/listeAttente.h"
#include "../../model/src/grille.h"
#include "../../model/src/piece.h"

typedef struct viewer {
  void (*affiche)(struct viewer *,grille *,int pause);
  void *data;
  void(*destroy)(struct viewer *);
} viewer;

/**
 * @brief Construit un viewer et le retourne.
 * @param char * viewer
 * @return un pointeur sur un viewer.
 */
viewer *makeViewer(char *v);