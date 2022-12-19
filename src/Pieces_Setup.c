#include "Pieces_Setup.h"

/****** Création et placement des pièces ******/

// Initialisation des tableaux de movesets des pièces à 0.
void InitialisePieceMovesetArr(int pieceMovesetArray[8][8]){

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pieceMovesetArray[i][j] = 0;
        }
    }
}

// Paramétrage des variables de chaque pièce. Ceci permet de les préparer pour la partie.
void SetPiecesTeamAndType(int *pieceType, Piece **gamePieces){

    int j = 15;
    Piece tmpPiece;

    // Deux compteurs i et j 
    // Cela permet de placer le bon type à la bonne pièce puisque les équipes sont symétriques

    // Boucle + initialisation des variables des deux équipes.
    for(int i = 0; i < 16; i++){
        gamePieces[0][i].team = 0;
        gamePieces[1][i].team = 1;
        gamePieces[0][i].doubleMove = 0;
        gamePieces[1][i].doubleMove = 0;
        gamePieces[0][i].captured = 0;
        gamePieces[1][i].captured = 0;
        gamePieces[0][i].canProtect = 0;
        gamePieces[1][i].canProtect = 0;

        // Deux compteurs i et j 
        // Cela permet de placer le bon type à la bonne pièce puisque les équipes sont symétriques
        gamePieces[0][i].type = pieceType[i];
        gamePieces[1][i].type = pieceType[j];

        InitialisePieceMovesetArr(gamePieces[0][i].possibleMoves);
        InitialisePieceMovesetArr(gamePieces[1][i].possibleMoves);
        j--;
    }

    // Inversion du Roi et de la Reine de l'équipe Noir pour qu'elles soient face à face.
    for(int i = 0; i < 16; i++){
        if(gamePieces[1][i].type == 4){
            tmpPiece = gamePieces[1][i-1];
            gamePieces[1][i-1] = gamePieces[1][i];
            gamePieces[1][i] = tmpPiece;
        }
    }
}

// Génération des textures pour chaque pièce + placement sur la case correspondante.
void GeneratePieceTexture(Case *gameCase, Piece *gamePiece, SDL_Renderer *renderer, char *texturePath){

    // Chargement de la texture dans une surface.
    SDL_Surface *tmpSurface = IMG_Load(texturePath);
    tmpSurface->h = CASE_SIZE;
    tmpSurface->w = CASE_SIZE;

    // Création de la texture et placement dans la case où elle doit être placée.
    gamePiece->pieceTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
    gamePiece->rectangle.x = gameCase->rectangle.x;
    gamePiece->rectangle.y = gameCase->rectangle.y;
    gamePiece->rectangle.w = gameCase->rectangle.w;
    gamePiece->rectangle.h = gameCase->rectangle.h;

    // Libération de la surface pour la mémoire.
    SDL_FreeSurface(tmpSurface);

    if (gamePiece->pieceTexture == NULL)
    {
        SDL_DestroyRenderer(renderer);
        SDL_Log("ERREUR : Echec création texture Paddle > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Application de la structure pour l'afficher sur le rendu.
    if(SDL_QueryTexture(gamePiece->pieceTexture, NULL, NULL, &(gamePiece->rectangle.w), &(gamePiece->rectangle.h)) != 0){
        
        SDL_DestroyRenderer(renderer);
        SDL_Log("ERREUR : chargement piece > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

// Procédure permettant de lier la bonne texture avec les bonne pièce
// En fonction de l'équipe et du type.
void CreateChessPiece(int pieceTeam, int pieceType, Case *gameCase, Piece *gamePiece, SDL_Renderer *renderer){

    char *texturePath = NULL;

    if(pieceTeam == 0){

        switch (pieceType)
        {
        case 1:
            texturePath = "./piecesTextures/noirs/TourNoir.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        case 2:
            texturePath = "./piecesTextures/noirs/CavalierNoir.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        case 3:
            texturePath = "./piecesTextures/noirs/FouNoir.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        case 4:
            texturePath = "./piecesTextures/noirs/ReineNoir.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        case 5:
            texturePath = "./piecesTextures/noirs/RoiNoir.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;
        
        case 6:
            texturePath = "./piecesTextures/noirs/PionNoir.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        default:
            break;
        }

    }
    else if(pieceTeam == 1){

        switch (pieceType)
        {
        case 1:
            texturePath = "./piecesTextures/blancs/TourBlanc.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        case 2:
            texturePath = "./piecesTextures/blancs/CavalierBlanc.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        case 3:
            texturePath = "./piecesTextures/blancs/FouBlanc.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        case 4:
            texturePath = "./piecesTextures/blancs/ReineBlanc.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        case 5:
            texturePath = "./piecesTextures/blancs/RoiBlanc.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;
        
        case 6:
            texturePath = "./piecesTextures/blancs/PionBlanc.png";
            GeneratePieceTexture(gameCase, gamePiece, renderer, texturePath);
            break;

        default:
            break;
        }
    }
}

// Fonction permettant l'initialisation et le placement des pièces pour le début de partie.
void FirstPiecesPlacement(Piece **gamePieces, Case **gameField, SDL_Renderer *renderer){
    
    int piecesCpt = 0; // Compteur d'équipe 
    int teamSetup[16] = {1,2,3,4,5,3,2,1,6,6,6,6,6,6,6,6};

    /* Les types sont symbolisés par ces numéros : 
        - 1 : tour
        - 2 : Cavalier
        - 3 : Fou
        - 4 : Reine
        - 5 : Roi
        - 6 : Pion
    */

    // Appel de la fonction pour intialiser les variables des pièces.
    SetPiecesTeamAndType(teamSetup, gamePieces);

    // Parcours du plateau pour placer chaque pièce au bon endroit (noirs en haut et blanc en bas)
    for(int i = 0; i < 8; i++){

        if(i == 5){
            piecesCpt = 0;
        }

        for (int j = 0; j < 8; j++){

            gameField[i][j].occupied = 0;

            // Placement des noirs
            if(i < 2){
                
                // Ajout des coordonnées de la pièce dans la structure
                gamePieces[0][piecesCpt].y = i;
                gamePieces[0][piecesCpt].x = j;
                gameField[i][j].occupied = 1; // Signification de l'occupation de la case
                gameField[i][j].piece = &gamePieces[0][piecesCpt];
                CreateChessPiece(gamePieces[0][piecesCpt].team, gamePieces[0][piecesCpt].type, &gameField[i][j], &gamePieces[0][piecesCpt], renderer);
                SDL_RenderCopy(renderer, gamePieces[0][piecesCpt].pieceTexture, NULL, &(gamePieces[0][piecesCpt].rectangle));
                piecesCpt++;
            }   
            // Placement des blancs
            else if (i > 5){

                // Ajout des coordonnées de la pièce dans la structure
                gamePieces[1][piecesCpt].y = i;
                gamePieces[1][piecesCpt].x = j;
                gameField[i][j].occupied = 1; // Signification de l'occupation de la case
                gameField[i][j].piece = &gamePieces[1][piecesCpt];
                CreateChessPiece(gamePieces[1][piecesCpt].team, gamePieces[1][piecesCpt].type, &gameField[i][j], &gamePieces[1][piecesCpt], renderer);                               
                SDL_RenderCopy(renderer, gamePieces[1][piecesCpt].pieceTexture, NULL, &(gamePieces[1][piecesCpt].rectangle));
                piecesCpt++;
            }    
        }
    }
}

// Permet de rafraîchir l'affichage des textures pièces à chaque itération
// Procédure très importante puisque cela permet de la faire apparaître sur sa nouvelle case après déplacement
void PiecesUpdateRender(SDL_Renderer *renderer, Piece **gamePieces){

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 16; j++){
            SDL_RenderCopy(renderer, gamePieces[i][j].pieceTexture, NULL, &(gamePieces[i][j].rectangle));
        }
    }
}