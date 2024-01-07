//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#pragma once
#include "piece.h"
#include "listeAttente.h"
#define HAUTEUR 20
#define LARGEUR 10

/**
 * @brief represente la grille de jeu, le score et le niveau
*/
typedef struct grille{
    couleur *tab;
    piece * pieceactive;
    couleur reserve;
    listeAttente *liste;
    int score;
    int niveau;//niveau de difficulté. s'incrémente avec le score
    int lignes;
    int reserveUtilisee;//booleen pour savoir si le joueur a fait appel à la réserve ou non
}grille;

/**
 * @brief cree la grille
 * @return grille *
*/
grille * creerGrille();

/**
 * @brief libere la memoire allouée pour la grille
 * @param grille *g
 * @return void
*/
void libereGrille(grille *g);

/**
 * @brief detecte les collisions entre la piece active et le reste.
 * @param grille * g
 * @return int
*/
int detecteCollision(grille *g);

/**
 * @brief detecte si une ligne est complete. met a jour la grille grace à supprimeLigne. met à jour le score.
 * @param grille *g
 * @return void
*/
void detecteLigne(grille *g);

/**
 * @brief supprime une ligne complétée et abaisse le reste des pieces
 * @param grille *g
 * @param unsigned x
 * @return void
*/
void supprimeLigne(grille *, unsigned x);

/**
 * @brief met en reserve la piece active et recupere la piece de la réserve s'il y a. 
 * @param grille *g
 * @return void
*/
void reserve(grille *g);

/**
 * @brief fonction de debug pour afficher la grille dans le terminal
 * @param grille *g
 * @return void
*/
void afficheGrille(grille *g);
