//Tangi LE HENAFF et Mohamed BOUGHARIOU - 2023-2024
#pragma once
#include "piece.h"

/**
 * @brief modelise la liste des pieces suivantes
*/
typedef struct listeAttente{
    couleur *liste;
    int indice;
}listeAttente;

/**
 * @brief cree une liste d'attente de piece
 * @return listeAttente *
*/
listeAttente * creerListeAttente();

/**
 * @brief libere la memoire pour la liste d'attente
 * @param listeAttente * l
 * @return void
*/
void libereListeAttente(listeAttente *l);

/**
 * @brief genere une sequence de 7 couleurs dans un ordre aleatoire et met a jour la liste.
 * @param listeAttente *l
 * @return void
*/
void genererCouleurs(listeAttente *l);

/**
 * @brief retourne la couleur de la piece suivante et incremente l'indice.
 * @param listeAttente * l
 * @return couleur
*/
couleur couleurSuivante(listeAttente *l);

/**
 * @brief retourne la couleur suivante si i =0, decale de i sinon
 * @param listeAttente *l
 * @param int i
 * @return couleur
*/
couleur getCouleurListe(listeAttente *l,int i);