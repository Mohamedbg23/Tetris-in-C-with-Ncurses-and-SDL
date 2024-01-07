//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#pragma once
#define HAUTEUR 20
#define LARGEUR 10
/**
 * @brief decris les différentes couleurs/formes de pieces possible.
*/
typedef enum couleur { VIDE=0,I=1,J,L,Z,S,O,T,OMBRE}couleur;

/**
 * @brief decris les directions de deplacement pour les pieces
*/
typedef enum direction { BAS=1,GAUCHE,DROITE}direction;

/**
 * @brief represente une piece du jeu Tetris.
 * Est défini par une couleur, et les coordonnées des 4 points;
*/
typedef struct piece{
    couleur c;
    unsigned *coordonnees;
    unsigned *coordonneesOmbre;
    unsigned k;

}piece;

/**
 * @brief cree une piece a partir de sa couleur et de ses coordonnées centrales
 * @param couleur c
 * @param unsigned x
 * @param unsigned y
 * @param couleur *tab
 * @param piece *p
 * @return piece *
*/
piece * creerPiece(couleur c, unsigned x,unsigned y,couleur *tab,piece *p);

/**
 * @brief reinitialise la piece avec une nouvelle couleur et coordonnées
 * @param piece *p
 * @param couleur c
 * @param unsigned x
 * @param unsigned y
 * @param couleur *tab
 * @return int
*/
int reinitPiece(piece *p,couleur c, unsigned x,unsigned y,couleur *tab);

/**
 * @brief libere la memoire allouée pour la piece
 * @param piece * p
 * @return void
*/
void liberePiece(piece *p);

/**
 * @brief fait deplacer la piece dans la direction voulue
 * @param piece* p
 * @param direction d
 * @param couleur *tab
 * @return int
*/
int deplacePiece(piece *p,direction d,couleur *tab);

/**
 * @brief teleporte la piece aux cordonnées passées
 * @param piece*  p
 * @param couleur *tab
*/
void teleportePieceBas(piece *p,couleur *tab);

/**
 * @brief calcule les coordonnées de l'ombre de la piece
 * @param piece *p
 * @param couleur *tab
 * @return void 
*/
void ombrePiece(piece *p,couleur *tab);

/**
 * @brief verifie si la piece est en collision avec une autre piece de la grille
 * @param piece *p
 * @param couleur *tab
 * @return 1 si il n'y a pas de collision
*/
int verifieCollision(piece *p,couleur *tab);

/**
 * @brief effectue la rotation d'une piece
 * @param piece *p
 * @param direction d
 * @param couleur *tab
 * @return void
*/
void rotationPiece(piece *p, direction d,couleur *tab);

/**
 * @brief pivote la piece vers la gauche
 * @param piece *p
 * @param couleur *tab
 * @return void
*/
void rotationGauche(piece *p,couleur *tab);

/**
 *@brief met a jour la grille grace aux coordonnees de la piece 
 *@param couleur *tab
 *@param piece *p
 *@return void
*/
void dessinePiece(couleur *tab, piece *p);

/**
 * @brief met les cases occupees par la piece active à VIDE
 * @param couleur *tab
 * @param piece *p
 * @return void
*/
void effacePiece(couleur *tab, piece *p);
