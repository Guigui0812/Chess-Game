#include "Game_Drawing_Field.h"

/****** Génération des défausses des pions ******/
// Ceci permet de faire apparaître les pions captures à gauche ou à droite en fonction des équipes

// Fonction permettant de créer des cases capables d'accueillir les pions capturés.
void GeneratedefaussePionPlaceBlancs(SDL_Renderer *renderer, Player *joueur1){

    int x = 10;
    int y = 0;

    for(int i = 0; i < 16; i++){

        if (i == 8){
            y = 0;
            x = 10 + CASE_SIZE;
        }

        joueur1->defaussePionPlace[i].x = x;
        joueur1->defaussePionPlace[i].y = y;  
        y = y + CASE_SIZE;      
    }
}

// Fonction permettant de créer des cases capables d'accueillir les pions capturés.
void GeneratedefaussePionPlaceNoirs(SDL_Renderer *renderer, Player *joueur2){

    int x = WINDOW_WIDTH - (30 + CASE_SIZE * 2);
    int y = 0;

    for(int i = 0; i < 16; i++){

        if (i == 8){
            y = 0;
            x = x + 10 + CASE_SIZE;
        }

        joueur2->defaussePionPlace[i].x = x;
        joueur2->defaussePionPlace[i].y = y;  
        y = y + CASE_SIZE;      
    }
}

// Procédure permettant de dessiner la défausse à l'écran (les parties grises)
void DrawDefausse(SDL_Renderer *renderer, Player *joueur1, Player *joueur2){

    SDL_Rect defausseFond;
    defausseFond.x = 0;
    defausseFond.y = 0;
    defausseFond.h = WINDOW_HEIGHT;
    defausseFond.w = WINDOW_WIDTH;

    SDL_SetRenderDrawColor(renderer, 121, 130, 137, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &defausseFond);
}

/****** Génération du plateau de jeu ******/
// Le plateau de jeu n'est pas une texture mais un ensemble de rectangles générés par le jeu lui-même.
// Le plateau est donc un ensemble de structures de type "Case"

// Procédure permettant de changer de couleur : permet d'intervertir entre blanc et noir pour le plateau.
void ChangeDrawColor(SDL_Renderer *renderer, int colorState){

    if(colorState == 0){
        if(SDL_SetRenderDrawColor(renderer, 246, 241, 238, SDL_ALPHA_OPAQUE) != 0){
            SDL_Log("ERREUR : Modification couleur du rendu echouee > %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    } 

    else {

        if(SDL_SetRenderDrawColor(renderer, 138, 135, 133, SDL_ALPHA_OPAQUE) != 0){
            SDL_Log("ERREUR : Modification couleur du rendu echouee > %s\n", SDL_GetError());
            exit(EXIT_FAILURE);
        }
    }
}

// Procédure permettant de dessiner les cases du plateau 
void *DrawCase(Case *maCase, SDL_Renderer *renderer, int x, int y){

    // Initialisation de la case passée en paramètres pour la placée au bon endroit sur le plateau.
    maCase->rectangle.x = x;
    maCase->rectangle.y = y;
    maCase->rectangle.w = CASE_SIZE;
    maCase->rectangle.h = CASE_SIZE;

    // Application de ces valeurs à un autre rectangle
    // Celui-ci est utilisé pour afficher les possibilités de déplacement des pièces au cours de la partie
    // C'est ceci qui permet donc une mise en surbrillance
    maCase->rectPossibleMove.x = x;
    maCase->rectPossibleMove.y = y;
    maCase->rectPossibleMove.w = CASE_SIZE;
    maCase->rectPossibleMove.h = CASE_SIZE;

    SDL_RenderFillRect(renderer, &maCase->rectangle);
}

// Procédure globale permettant de dessiner le plateau de jeu
void DrawGameField(SDL_Renderer *renderer, Case **gameField, Piece **gamePieces){

    int i = 0;
    // Variables permettant de placer la case aux bonnes coordonnées (coordonnées en pixels)
    int x = 200;
    int y = 0;
    int colorState = 0;

    // Boucle permettant de faire un 8 x 8 cases (--> pour les 64 cases du plateau de jeu)
    for (i = 0; i < 8; i++){  

        for(int j = 0; j < 8; j++){

            if(j != 0){

                // Intervertion de la couleur pour avoir l'effet 1/2
                if(colorState == 0){
                    colorState = 1;
                } 
                else {
                    colorState = 0;
                }
            }

            // Appel des fonctions pour dessiner la case au bon endroit avec la bonne couleur.
            ChangeDrawColor(renderer, colorState);
            DrawCase(&gameField[i][j], renderer, x, y);     


            // Maj des coordonnées en pixels.
            x = x + CASE_SIZE;
        }

        // Maj des coordonnées en pixels.
        y = y + CASE_SIZE;
        x = 200;
    }
}

// Procédure d'appel de l'initialisation
void InitGameField(SDL_Renderer *renderer, Case **gameField, Piece **gamePieces){

    DrawGameField(renderer, gameField, gamePieces);
    FirstPiecesPlacement(gamePieces, gameField, renderer);
}