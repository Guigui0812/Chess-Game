#include "Game_MainFonctions.h"
#include "Game_SpecialMoves.h"
#include "Game_Drawing_Field.h"
#include "Pieces_Movesets.h"

// Opérations réalisées pour le mouvement seul
void MovementCase(Piece *maPiece, Case **gameField, int i, int j, int *moveOk){

    // Suppression du lien entre la case et sa pièce
    gameField[maPiece->y][maPiece->x].occupied = 0;
    gameField[maPiece->y][maPiece->x].piece = NULL;
    // Modification des coordonnée de la pièce déplacée sur la case cliquée
    maPiece->rectangle.x = gameField[i][j].rectangle.x;
    maPiece->rectangle.y = gameField[i][j].rectangle.y;
    maPiece->y = i;
    maPiece->x = j;
    // Création d'un lien entre la case et la pièce
    gameField[i][j].occupied = 1;
    gameField[i][j].piece = maPiece;
    *moveOk = 0;
}

// Opération réalisée pour la capture d'une pièce
void CaptureOperation(Piece *pieceOnCase, Player *joueur1, Player *joueur2){
    
    // Check de l'équipe pour que la pièce aille vers la bonne défausse
    if (pieceOnCase->team == 0){
        // Déplacement vers la défausse, booléen de capture activé et réinitialisation du moveset
        pieceOnCase->rectangle.x = joueur1->defaussePionPlace[joueur1->captured].x;
        pieceOnCase->rectangle.y = joueur1->defaussePionPlace[joueur1->captured].y;
        joueur1->captured = joueur1->captured + 1;
        pieceOnCase->captured = 1;
        InitialisePieceMovesetArr(pieceOnCase->possibleMoves);
    }
    else{
        // Déplacement vers la défausse, booléen de capture activé et réinitialisation du moveset
        pieceOnCase->rectangle.x = joueur2->defaussePionPlace[joueur2->captured].x;
        pieceOnCase->rectangle.y = joueur2->defaussePionPlace[joueur2->captured].y;
        joueur2->captured = joueur2->captured + 1;
        pieceOnCase->captured = 1;
        InitialisePieceMovesetArr(pieceOnCase->possibleMoves);
    }
}

void PerformRightRoque(Piece *maPiece, Case **gameField, int i, int j, int *moveOk){

    Piece *tmpPiece;

    // Si la pièce cliquée est bien à droite
    if(maPiece->x < gameField[i][j].piece->x){

            // Opérations pour permuter les pièces aux bonnes coordonnées
            // Modification des variables des structures

            // Suppression du lien entre le Roi et sa case
            gameField[maPiece->y][maPiece->x].occupied = 0;
            gameField[maPiece->y][maPiece->x].piece = NULL;

            // Déplacement du Roi sur sa nouvelle case
            maPiece->x = maPiece->x + 2;
            maPiece->rectangle.x = gameField[maPiece->y][maPiece->x].rectangle.x;
            maPiece->rectangle.y = gameField[maPiece->y][maPiece->x].rectangle.y;
            gameField[maPiece->y][maPiece->x].occupied = 1;
            gameField[maPiece->y][maPiece->x].piece = maPiece;

            // Déplacements de la tour + création d'un lien avec sa nouvelle case
            tmpPiece = gameField[i][j].piece;
            tmpPiece->rectangle.x = gameField[7][5].rectangle.x;
            tmpPiece->rectangle.y = gameField[7][5].rectangle.y; 
            gameField[i][j].occupied = 0;
            gameField[i][j].piece = NULL;
            gameField[tmpPiece->y][tmpPiece->x].occupied = 1;
            gameField[tmpPiece->y][tmpPiece->x].piece = tmpPiece;
            
            *moveOk = 0;
    }
}

void PerformLeftRoque(Piece *maPiece, Case **gameField, int i, int j, int *moveOk){

    Piece *tmpPiece;

    // Si la pièce cliquée est bien à gauche
    if(maPiece->x > gameField[i][j].piece->x){

        // Opérations pour permuter les pièces aux bonnes coordonnées
        // Modification des variables des structures

        // Suppression du lien entre le Roi et sa case
        gameField[maPiece->y][maPiece->x].occupied = 0;
        gameField[maPiece->y][maPiece->x].piece = NULL;

        // Déplacement du Roi sur sa nouvelle case
        maPiece->x = maPiece->x - 2;
        maPiece->rectangle.x = gameField[maPiece->y][maPiece->x].rectangle.x;
        maPiece->rectangle.y = gameField[maPiece->y][maPiece->x].rectangle.y;
        gameField[maPiece->y][maPiece->x].occupied = 1;
        gameField[maPiece->y][maPiece->x].piece = maPiece;

        // Déplacements de la tour + création d'un lien avec sa nouvelle case
        gameField[i][j].piece->x = gameField[i][j].piece->x + 3;
        gameField[i][j].piece->rectangle.x = gameField[gameField[i][j].piece->y][gameField[i][j].piece->x].rectangle.x;
        gameField[i][j].piece->rectangle.y = gameField[gameField[i][j].piece->y][gameField[i][j].piece->x].rectangle.y;
        tmpPiece = gameField[i][j].piece;
        gameField[i][j].occupied = 0;
        gameField[i][j].piece = NULL;
        gameField[tmpPiece->y][tmpPiece->x].occupied = 1;
        gameField[tmpPiece->y][tmpPiece->x].piece = tmpPiece;

        *moveOk = 0;
    }
}

// Fonction permettant de déplacer la pièce sélectionnée et de réaliser les opérations induites par celui-ci
int MovePiece(Piece *maPiece, Case **gameField, int x, int y, Player *joueur1, Player *joueur2, int *enPassant, int enPassantCoord[2], int *kingThreaten){

    int moveOk;

    // Détection de la case cliquée en bouclant sur la grille
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

            if((x > gameField[i][j].rectangle.x && x < (gameField[i][j].rectangle.x + gameField[i][j].rectangle.w)) &&
                y > gameField[i][j].rectangle.y && y < (gameField[i][j].rectangle.y + gameField[i][j].rectangle.h)){

                /* En fonction du numéro présent dans le moveset de la pièce on réalise :
                /* - Un déplacement simple
                /* - Une capture
                /* - Une prise en passant
                /* - Un Roque
                /* - Réaliser une interception dans le cas d'un Echec au Roi
                */


                // En fonction du type de déplacement présent dans le moveset de la pièce ->
                // des procédures spécifiques sont appelées (déplacement, capture, Roque, prise en passant...)
                if(maPiece->possibleMoves[i][j] == 1){

                    // Si un double move a été effectué par un pion : on signale qu'il pourra plus avec "doubleMove" à 1
                    // On enregistre ensuite ses coordonnées pour faire une prise en passant.
                    if(maPiece->type == 6 && maPiece->doubleMove == 0 && gameField[i][j].occupied != 1){
                        maPiece->doubleMove = 1;
                        *enPassant = 1;
                        enPassantCoord[0] = i;
                        enPassantCoord[1] = j;
                    }    

                    MovementCase(maPiece, gameField, i, j, &moveOk);     
                }
                else if (maPiece->possibleMoves[i][j] == 2){

                    CaptureOperation(gameField[i][j].piece, joueur1, joueur2);
                    MovementCase(maPiece, gameField, i, j, &moveOk);
                }
                else if(maPiece->possibleMoves[i][j] == 4){

                    CaptureOperation(gameField[enPassantCoord[0]][enPassantCoord[1]].piece, joueur1, joueur2);
                    MovementCase(maPiece, gameField, i, j, &moveOk);
                    // On supprime le lien avec la case si il y a eu une capture
                    gameField[enPassantCoord[0]][enPassantCoord[1]].occupied = 0;
                    gameField[enPassantCoord[0]][enPassantCoord[1]].piece = NULL;
                }
                else if(maPiece->possibleMoves[i][j] == 5){
                    PerformRightRoque(maPiece, gameField, i, j, &moveOk);
                    PerformLeftRoque(maPiece, gameField, i, j, &moveOk);
                }
                else if (*kingThreaten == 1){

                    /* 
                       Cette condition permet de ne rendre possible que les mouvements permettant le sauvetage du Roi
                       s'il en existe. 
                    */ 

                    if(maPiece->possibleMoves[i][j] == 6){
                        MovementCase(maPiece, gameField, i, j, &moveOk);   
                    }
                    else if(maPiece->possibleMoves[i][j] == 7){
                        CaptureOperation(gameField[i][j].piece, joueur1, joueur2);
                        MovementCase(maPiece, gameField, i, j, &moveOk);
                    }
                }
                else{
                    moveOk = 1; 
                    // MoveOk à 1 signifie que la pièce a été déplacée et que le jeu peut continuer
                }
            }
        }
    }

    return moveOk;
}

// Permet d'afficher les cases où la pièce peut se déplacer, ou réaliser une capture.
void ColorisedPossibleCase(SDL_Renderer *renderer, Piece *maPiece, Case **gameField, int kingThreaten){

    // Parcours de la grille.
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

            // Pour chaque case, si celle-ci correspond à un identifiant dans le moveset de la pièce, on la colorise selon son numéro.
            
            // Cas usuel sans menace pour le Roi.
            if(kingThreaten == 0){
  
                // Pour chaque cas : 
                // - Définition de la transparence
                // - Définition d'une couleur
                // - Remplissage du rectangle "possibleMove" présent dans la structure Case.
                
                if(maPiece->possibleMoves[i][j] == 1){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 59, 213, 49, 150);
                    SDL_RenderFillRect(renderer, &gameField[i][j].rectPossibleMove);
                }
                else if (maPiece->possibleMoves[i][j] == 2){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 173, 40, 11, 150);
                    SDL_RenderFillRect(renderer, &gameField[i][j].rectPossibleMove);
                }
                else if (maPiece->possibleMoves[i][j] == 4){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 241, 200, 14, 150);
                    SDL_RenderFillRect(renderer, &gameField[i][j].rectPossibleMove);
                }
                else if (maPiece->possibleMoves[i][j] == 5){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 54, 225, 252, 150);
                    SDL_RenderFillRect(renderer, &gameField[i][j].rectPossibleMove);
                }
            }
            else if(kingThreaten == 1){ // Case où le Roi est menacé.
                if(maPiece->possibleMoves[i][j] == 6){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 59, 213, 49, 150);
                    SDL_RenderFillRect(renderer, &gameField[i][j].rectPossibleMove);
                }
                else if (maPiece->possibleMoves[i][j] == 7){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 173, 40, 11, 150);
                    SDL_RenderFillRect(renderer, &gameField[i][j].rectPossibleMove);
                }
                else if(maPiece->possibleMoves[i][j] == 1 && maPiece->type == 5){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 59, 213, 49, 150);
                    SDL_RenderFillRect(renderer, &gameField[i][j].rectPossibleMove);
                }
                else if(maPiece->possibleMoves[i][j] == 2 && maPiece->type == 5){
                    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(renderer, 173, 40, 11, 150);
                    SDL_RenderFillRect(renderer, &gameField[i][j].rectPossibleMove);
                }
            }
        }
    }
}

// Permet la colorisation des pièces pouvant protéger le Roi si il est menacé.
void ColorisedProtector(SDL_Renderer *renderer, Piece **gamePieces, Case **gameField, int player){

    for(int i = 0; i < 16; i++){

        if(gamePieces[player][i].canProtect == 1){
            
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            SDL_SetRenderDrawColor(renderer, 241, 200, 14, 150);
            SDL_RenderFillRect(renderer, &gameField[gamePieces[player][i].y][gamePieces[player][i].x].rectPossibleMove);
        }
    }
}

// Procédure permettant la gestion des clics que l'utilisateur (sélection de la pièce et de la case)
void HandleMouseClick(SDL_Renderer *renderer, int *ClicOnPion, Case **gameField, Piece **gamePieces, int *selectedPion, int *player, Player *joueur1, Player *joueur2, int *enPassant, int enPassantCoord[2], int *kingThreaten, int *EchecMate, int threateningPiece[2]){

    int x, y, kingCoord;
    SDL_GetMouseState(&x, &y);

    // Pas de pion sélectionné à cet instant.
    if(*ClicOnPion == 0){

            // Boucler pour récupérer la pièce correspondant aux coordonnées du clic.
            for(int i=0; i < 2; i++){

                for(int j=0; j < 16; j++){

                    // Check des coordonnées
                    if (x > gamePieces[i][j].rectangle.x && x < (gamePieces[i][j].rectangle.x + gamePieces[i][j].rectangle.w))
                    {
                        if (y > gamePieces[i][j].rectangle.y && y < (gamePieces[i][j].rectangle.y + gamePieces[i][j].rectangle.h))
                        {
                            // Check de l'équipe
                            if (gamePieces[i][j].team == *player)
                            {
                                // Cas d'un tour ordinaire sans menace.
                                if(*kingThreaten == 0){

                                    selectedPion[0] = i;
                                    selectedPion[1] = j;

                                    if (*enPassant == 1) // Verif de la prise en passant
                                    {
                                        CheckPriseEnPassant(&gamePieces[selectedPion[0]][selectedPion[1]], gameField, enPassantCoord);
                                        *enPassant = 0;
                                    }

                                    if (*player == 1) // Verif des possibilités de Roque.
                                    {
                                        checkRoque(&gamePieces[selectedPion[0]][selectedPion[1]], gameField, gamePieces, player, joueur2);
                                    }
                                    else
                                    {
                                        checkRoque(&gamePieces[selectedPion[0]][selectedPion[1]], gameField, gamePieces, player, joueur1);
                                    }

                                    *ClicOnPion = 1;
                                }                               
                                else{ // Cas où le Roi est menacé

                                    // Condition obligeant la sélection du Roi ou d'une pièce pouvant le protéger
                                    if(gamePieces[i][j].canProtect == 1 || gamePieces[i][j].type == 5){
                                    
                                    selectedPion[0] = i;
                                    selectedPion[1] = j;

                                    if (*enPassant == 1)
                                    {
                                        CheckPriseEnPassant(&gamePieces[selectedPion[0]][selectedPion[1]], gameField, enPassantCoord);
                                        *enPassant = 0;
                                    }

                                    if (*player == 1)
                                    {
                                        checkRoque(&gamePieces[selectedPion[0]][selectedPion[1]], gameField, gamePieces, player, joueur2);
                                    }
                                    else
                                    {
                                        checkRoque(&gamePieces[selectedPion[0]][selectedPion[1]], gameField, gamePieces, player, joueur1);
                                    }

                                    *ClicOnPion = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        } 
    else if (*ClicOnPion == 1){ // Cas où la pièce a été sélectionnée

        // Une fois la pièce déplacée, on réalise les opérations pour actualiser les variables du jeu.
        if(MovePiece(&gamePieces[selectedPion[0]][selectedPion[1]], gameField, x, y, joueur1, joueur2, enPassant, enPassantCoord, kingThreaten) == 0){
            
            // Si le Roi était menacé, on remet les variables à 0
            if(*kingThreaten == 1){

                for(int i = 0; i < 16; i++){
                    gamePieces[*player][i].canProtect = 0;
                }
                
                *kingThreaten = 0;
                threateningPiece[0] = 0;
                threateningPiece[1] = 0;
            }

            // Si une pièce doit être promue, on réalise la promotion.
            Promotion(renderer, &gamePieces[selectedPion[0]][selectedPion[1]], gameField);

            if(*player != 1){

                // Si le Roi a été déplacé on indique qu'il a été déplacé (Roque plus accessible)
                if(gamePieces[selectedPion[0]][selectedPion[1]].type == 5){
                    joueur1->kingMove++;
                }

                // Changement du joueur
                *player = 1;

                // Actualisation des movesets
                UpdateAllPiecesMoveSets(gamePieces, gameField, enPassant, enPassantCoord, kingThreaten, threateningPiece);  
                // Vérification d'un potentiel Echec au Roi ou Echec et Mat
                CheckIfKingMove(gamePieces, player, EchecMate, joueur2, kingThreaten, threateningPiece); 
            }                                 
            else{
                
                // Si le Roi a été déplacé on indique qu'il a été déplacé (Roque plus accessible)
                if(gamePieces[selectedPion[0]][selectedPion[1]].type == 5){
                    joueur2->kingMove++;
                }

                // Changement du joueur
                *player = 0;

                // Actualisation des movesets
                UpdateAllPiecesMoveSets(gamePieces, gameField, enPassant, enPassantCoord, kingThreaten, threateningPiece);
                // Vérification d'un potentiel Echec au Roi ou Echec et Mat
                CheckIfKingMove(gamePieces, player, EchecMate, joueur1, kingThreaten, threateningPiece); 
            }                      
        }

        *ClicOnPion = 0;
    }
}

void PlayerEvents(SDL_Renderer *renderer, SDL_bool *program_launched, int *player, int *ClicOnPion, Piece **gamePieces, Case **gameField, int *selectedPion, Player *joueur1, Player *joueur2, int *enPassant, int enPassantCoord[2], int *kingThreaten, int *EchecMate, int threateningPiece[2]){

    SDL_Event Event;

    // Vérification des événements : clique sur la fenêtre ou clique sur la croix de sortie
    while(SDL_PollEvent(&Event))
    {
        switch(Event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                HandleMouseClick(renderer, ClicOnPion, gameField, gamePieces, selectedPion, player, joueur1, joueur2, enPassant, enPassantCoord, kingThreaten, EchecMate, threateningPiece);
                break;

            case SDL_QUIT:
                *program_launched = SDL_FALSE;
                break;

            default:
                break;
        }
    }
}

// Fonction permettant d'afficher "Tour des Blancs" ou "Tour des Noirs"
void printTurnName(SDL_Renderer *renderer, TTF_Font *maPolice, int player){
    
    // Variables permettant le placement du texte.
    SDL_Rect positionTexte;
    SDL_Rect fondTexte;
    SDL_Surface *textSurface;
    positionTexte.x = 450;
    positionTexte.y = WINDOW_HEIGHT - 30;
    positionTexte.h = 20;
    positionTexte.w = 160;
    SDL_Color noir = {0, 0, 0}; 

    // Placement d'un fond coloré pour le texte.
    SDL_SetRenderDrawColor(renderer, 214, 201, 195, SDL_ALPHA_OPAQUE);
    fondTexte.x = 0;
    fondTexte.y = WINDOW_HEIGHT - 40;
    fondTexte.h = WINDOW_HEIGHT;
    fondTexte.w = WINDOW_WIDTH;

    SDL_RenderFillRect(renderer, &fondTexte);

    // Contenu du texte personnalisé en fonction de l'équipe
    if(player != 0){
        textSurface = TTF_RenderText_Blended(maPolice, "Tour des blancs.", noir);
    }
    else{
        textSurface = TTF_RenderText_Blended(maPolice, "Tour des noirs.", noir);
    }
    // Génération de la texture du texte et application sur le renderer de la fenêtre
    SDL_Texture *text = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_QueryTexture(text, NULL, NULL, &positionTexte.w, &positionTexte.h);
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(renderer, text, NULL, &positionTexte);
}