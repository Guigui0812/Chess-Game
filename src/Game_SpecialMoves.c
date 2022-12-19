#include "Game_SpecialMoves.h"

// Vérifier si le Roi peut bouger, et si oui de combien de mouvement il dispose
int GetNbMovesKing(Piece Roi){

    int nbMoves = 0;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){

            // Si le roi capture ou se déplace, on incrémente
            if(Roi.possibleMoves[i][j] == 1 || Roi.possibleMoves[i][j] == 2){
                nbMoves++;
            }
        }
    }

    return nbMoves;
}

// Permet d'obtenir l'emplacement du Roi d'une équipe sur le plateau.
int GetKing(Piece **gamePieces, int *player){

    int kingCoord = 0;

    for(int j=0; j < 16; j++){

        if(gamePieces[*player][j].team == *player && gamePieces[*player][j].type == 5){
            kingCoord = j;
        }
    }

    return kingCoord;
}

// Fonction permettant de contrôler si le Roi peut bouger, si il y a un Echec au Roi ou un Echec et Mat
void CheckIfKingMove(Piece **gamePieces, int *player, int *EchecMat, Player *joueur, int *kingThreaten, int threateningPiece[2])
{

    /*
        Gestion des Echecs selon ces principes : 
            - Si le Roi ne peut plus se déplacer
            - Si le Roi ne peut pas capturer
            - Si aucune pièce alliée ne peut intercepter la trajectoire de la pièce menaçante
            - Si aucune pièce alliée ne peut capturer la pièce menaçante

            --> Si aucune de ces conditions n'est rempli : Echec et Mat
    */

    int Echec = 0;
    int interceptable = 0;
    int tmp = 0, checkKingMove = 0;
    int kingCoord = GetKing(gamePieces, player);
    int nbMovesKing = GetNbMovesKing(gamePieces[*player][kingCoord]);
    int xbis = 0, ybis = 0;

    // Si le Roi peut bouger
    if (nbMovesKing > 0)
    {
        // Identifiant de l'équipe adverse
        if (*player == 0)
        {
            tmp = 1;
        }

        // On boucle sur l'ensemble des movesets des pièces de l'équipe ennemi
        for (int i = 0; i < 16; i++)
        {
            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    // Vérification des possibilités d'esquive du Roi. 
                    if ((gamePieces[tmp][i].possibleMoves[y][x] == 1 || gamePieces[tmp][i].possibleMoves[y][x] == 3) && (gamePieces[*player][kingCoord].possibleMoves[y][x] == 1 || gamePieces[*player][kingCoord].possibleMoves[y][x] == 2) && gamePieces[tmp][i].captured == 0)
                    {
                        gamePieces[*player][kingCoord].possibleMoves[y][x] = 0;
                        checkKingMove++;
                    }

                    if(*kingThreaten != 0){

                        // Si Roi menacé, on récupère la pièce menaçante.
                        if (gamePieces[tmp][i].y == threateningPiece[0] && gamePieces[tmp][i].x == threateningPiece[1] && gamePieces[tmp][i].captured == 0)
                        {
                            // Comparaison des mouvements possibles de la pièce menaçante avec les pièces alliées du Roi
                            // Détection d'une interception
                            for(int j = 0; j < 16; j++){
                                
                                // On ici exclue le cas de la tour, du fou et de la Reine du fait de leur moveset spécifiques
                                // C'est traité à part
                                if (gamePieces[tmp][i].type != 1 && gamePieces[tmp][i].type != 3 && gamePieces[tmp][i].type != 4){

                                    // identification d'une interception
                                    if (gamePieces[tmp][i].possibleMoves[y][x] == 1 && gamePieces[*player][j].possibleMoves[y][x] == 1)
                                    {
                                        // On le signale avec le 1 dans "canProtect"
                                        // Si il peut intercepter : on identifie la case correspondante par un 6
                                        // On signifie avec "interceptable" que c'est un Echec au Roi qui peut être résolu
                                        gamePieces[*player][j].canProtect = 1;
                                        gamePieces[*player][j].possibleMoves[y][x] = 6;
                                        interceptable = 1;
                                    }
                                }

                                // Peut empêcher l'échec par une capture.
                                if(gamePieces[*player][j].possibleMoves[gamePieces[tmp][i].y][gamePieces[tmp][i].x] == 2){
                                    // Si il peut capturer : on identifie la case correspondante par un 7
                                    gamePieces[*player][j].canProtect = 1;
                                    gamePieces[*player][j].possibleMoves[gamePieces[tmp][i].y][gamePieces[tmp][i].x] = 7;
                                    interceptable = 1;
                                }
                            }
                        }
                    }
                }
            }

            // Gestion de la détection avec les mouvements spéciaux de la tour, du fou et de la reine.
            if(*kingThreaten != 0){

                // Récupération de la pièce menaçante.
                if (gamePieces[tmp][i].y == threateningPiece[0] && gamePieces[tmp][i].x == threateningPiece[1] && gamePieces[tmp][i].captured == 0)
                {
                    // Vérification du type.
                    if (gamePieces[tmp][i].type == 1 || gamePieces[tmp][i].type == 3 || gamePieces[tmp][i].type == 4)
                    {
                        // Initialisation avec les coordonnées de la pièce menaçante.
                        xbis = gamePieces[tmp][i].x;
                        ybis = gamePieces[tmp][i].y;

                        // Vérification de potentielles interception sur les cases entre la pièce et le Roi
                        // Pour chaque case du mouvement pièce -> Roi, on contrôle si un allié du Roi l'intercepte
                        while (xbis != gamePieces[*player][kingCoord].x && ybis != gamePieces[*player][kingCoord].y)
                        {
                            if (xbis < gamePieces[*player][kingCoord].x)
                            {
                                xbis++;
                            }
                            else if (xbis > gamePieces[*player][kingCoord].x)
                            {
                                xbis--;
                            }

                            if (ybis < gamePieces[*player][kingCoord].y)
                            {
                                ybis++;
                            }
                            else if (ybis > gamePieces[*player][kingCoord].y)
                            {
                                ybis--;
                            }

                            // Comparaison du mouvement avec toutes les pièces alliées
                            for (int j = 0; j < 16; j++)
                            {
                                // Si une pièce alliée coupe la trajectoire, on peut intercepter l'échec au roi
                                if (gamePieces[tmp][i].possibleMoves[ybis][xbis] == 1 && gamePieces[*player][j].possibleMoves[ybis][xbis] == 1)
                                {
                                    gamePieces[*player][j].possibleMoves[ybis][xbis] = 6;
                                    gamePieces[*player][j].canProtect = 1;
                                    interceptable = 1;
                                }
                            }
                        }
                    }
                }
            }
        }

        if(*kingThreaten != 0){
            
            // On contrôle si les conditions de l'échec est Mat sont remplies. 
            // Si oui, le contenu du pointeur EchecMat sera "1" : permet de finir la partie et d'en relancer une
            if (nbMovesKing == checkKingMove && interceptable == 0)
            {
                *EchecMat = 1;
            }

            // On signale l'échec et mat avec une message box personnalisée.
            if (*EchecMat == 1)
            {
                if(*player == 1){
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Blancs", "Les blancs sont échec et mat", NULL);

                }
                else{
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Noirs", "Les noirs sont échec et mat", NULL);
                }
            }
            else // Sinon on signale un échec au Roi, personnalisé également
            {
                if(*player == 1){
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Blancs", "Le Roi blanc est en échec, déplacez votre pièce.", NULL);
                }
                else{
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Noirs", "Le Roi noir est en échec, déplacez votre pièce.", NULL);
                }            
            }
        }
    }
}

// Identification d'une prise en passant dans la grille de moveset du Pion avec le chiffre "4"
void CheckPriseEnPassant(Piece *maPiece, Case **gameField, int enPassantCoord[2]){

    if(((enPassantCoord[1] == maPiece->x + 1) || (enPassantCoord[1] == maPiece->x - 1)) && (enPassantCoord[0] == maPiece->y)){
        if(maPiece->team == 0){
            maPiece->possibleMoves[enPassantCoord[0] + 1][enPassantCoord[1]] = 4;
        }         
        else {
            maPiece->possibleMoves[enPassantCoord[0] - 1][enPassantCoord[1]] = 4;  
        }
    }
}

// Fonction permettant de vérifier la possibilité d'effectuer un Roque
void checkRoque(Piece *maPiece, Case **gameField, Piece **gamePieces, int *player, Player *joueur){

    int checkObstacle = 0, towerFound = 0, i = maPiece->x + 1, roquePossible = 0, tmpPlay;

    // On vérifie que la tour et le roi de l'équipe concerné n'a pas bougé.
    if(joueur->kingMove == 0 && joueur->towerMove == 0){

        if (*player == 1)
        {
            tmpPlay = 0;
        }
        else
        {
            tmpPlay = 1;
        }

        // Si la pièce sélectionnée est bien le Roi
        if (maPiece->type == 5)
        {
            // Vérification de l'absence d'obstacles entre le Roi et la tour vers la droite
            // On boucle tant qu'aucun obstacle n'a été trouvé, ou jusqu'à trouver la tour
            while (checkObstacle == 0 && towerFound == 0)
            {
                // Si il y a un obstacle on le signale avec "CheckObstacle" à 1
                if (gameField[maPiece->y][i].occupied == 1)
                {
                    // Si ce n'est pas la tour on signale un obstacle
                    if(gameField[maPiece->y][i].piece->type != 1){
                        checkObstacle = 1;
                    }
                    else // Si c'est la tour, on signale qu'on l'a trouvé avec "towerFound"
                    {
                        maPiece->possibleMoves[maPiece->y][i] = 5;
                        towerFound = 1;
                    } 
                }
                else if (gameField[maPiece->y][i].occupied == 0)
                {
                    for (int j = 0; j < 16; j++)
                    {
                        if (gamePieces[tmpPlay][j].possibleMoves[maPiece->y][i] == 1)
                        {
                            checkObstacle = 1;
                        }    
                    }
                }

                i++;
            }

            checkObstacle = 0;
            towerFound = 0; 
            i = maPiece->x - 1;

            // Même procédure qu'auparavant vers la gauche
            while (checkObstacle == 0 && towerFound == 0)
            {
                if (gameField[maPiece->y][i].occupied == 1)
                {
                    if(gameField[maPiece->y][i].piece->type != 1){
                        checkObstacle = 1;
                    }
                    else
                    {
                        maPiece->possibleMoves[maPiece->y][i] = 5;
                        towerFound = 1;
                    } 
                }
                else if (gameField[maPiece->y][i].occupied == 0)
                {
                    for (int j = 0; j < 16; j++)
                    {
                        if (gamePieces[tmpPlay][j].possibleMoves[maPiece->y][i] == 1)
                        {
                            checkObstacle = 1;
                        }    
                    }
                }
                i--;
            }
        }
    }
}

// Vérification de la possibilité d'une promotion de pion
int CheckPromotion(Piece *maPiece){

    int canBePromote = 0;

    // Pour les noirs on vérifie qu'un pion est arrivé en bas
    if(maPiece->y == 7 && maPiece ->team == 0 && maPiece->type == 6){
        canBePromote = 1;
    } // Pour les blancs on vérifie qu'un pion est arrivé en haut
    else if (maPiece->y == 0 && maPiece ->team == 1 && maPiece->type == 6){
        canBePromote = 1;
    }

    return canBePromote;
}

// Procédure permettant d'effectuer la promotion d'un pion
void Promote(SDL_Renderer *renderer, Piece *maPiece, Case **gameField){
    
    int choice = 0;
    SDL_Event promoEvent;

    // Message de la promotion
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Promotion", "Vous devez promouvoir cette pièce :\n- Cliquez sur A pour une tour\n- CLiquez sur Z pour un cavalier\n- Cliquez sur E pour un fou\n- Cliquez sur R pour une reine", NULL);
   
    do{ // tant que l'utilisateur n'a pas fait un choix correspondant au message

        SDL_WaitEvent(&promoEvent);
        
        // Gestion de la promotion au clavier
        switch(promoEvent.type)
        {
            case SDL_KEYDOWN:   
                switch(promoEvent.key.keysym.sym)
                {
                    case SDLK_a:
                        choice = 1;
                        break;

                    case SDLK_z:
                        choice = 2;
                        break;

                    case SDLK_e:
                        choice = 3;
                        break;

                    case SDLK_r:
                        choice = 4;
                        break;

                    default:
                        break;
                }
                break;
        }
    }while((choice == 0 || choice > 5));

    if(choice > 0 && choice < 5){
        maPiece->pieceTexture = NULL;
        maPiece->type = choice;
        // Recréation de la pièce sous sa nouvelle forme
        CreateChessPiece(maPiece->team, choice, &gameField[maPiece->y][maPiece->x], maPiece, renderer);
    }
}

// Si on détecte une promotion, cette procédure appelle la fonction de promotion
void Promotion(SDL_Renderer *renderer, Piece *maPiece, Case **gameField){

    if(CheckPromotion(maPiece) == 1){
        Promote(renderer, maPiece, gameField);
    }
}