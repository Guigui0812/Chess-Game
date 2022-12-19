#ifndef GAME_STRUCTURES
#define GAME_STRUCTURES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_ttf.h"
#include "Game_Consts.h"

/* 
Choix d'implémenter des structures motivé par :
    - Une meilleure maintenabilité du code avec de nombreuses variables concentrées ici
    - Une plus grande flexibilité pour élaborer les différentes fonctionnalités.
    - Un rapprochement avec une structure orientée objet : meilleure implémentation
*/

// Structure embarquant les variables essentiels au déroulement de la partie des joueurs.
typedef struct Player {
    SDL_Rect defaussePionPlace[16]; // Cases qui permettent de placer les pièces capturées
    int captured, kingMove, towerMove, nbMoveOfKing;
} Player;

// Structure embarquant les variables essentiels à chaque pièce.
typedef struct Piece {
    SDL_Texture *pieceTexture; // Texture de la pièce
    SDL_Rect rectangle; // Rectangle symbolisant l'emplacement de la pièce sur l'échéquier.
    int type, team, doubleMove, x, y, captured, canProtect;
    int possibleMoves[8][8]; // Matrice essentielle contenant les déplacements possibles de la pièce.
    // 1 : déplacement / 2 : capture / 3 : alliée... 
} Piece;

// Structure embarquant les variables essentiels à chaque case.
// Le plateau est un ensemble de cases
typedef struct Case {
    SDL_Rect rectangle; // emplacement de la case dans la fenêtre
    SDL_Rect rectPossibleMove; // Rectangle supplémentaire pour illustrer les déplacements des pièces
    int occupied; // entier booléen d'occupation
    Piece *piece; // Pointeur permettant d'établir un lien entre une case et une pièce
} Case;

#endif