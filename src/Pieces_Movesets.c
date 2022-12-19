#include "Pieces_Movesets.h"

// Fonction permettant de remplir le tableau de mouvements de la tour.
void UpdateTowerMove(Piece *maPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]){

    int i, checkEncounter;

    checkEncounter = 0; // Booléen permettant d'analyser si une pièce a été rencontrée.
    // Boucle permettant d'analyser les mouvements possibles vers la droite (dans les limites de la grille)
    // Le compteur est init aux x et y de la pièce
    for(i = maPiece->x + 1; i < 8; i++){

        // Si on ne rencontre rien on continu d'ajouter 1 qui signifie un mouvement possible.
        if(checkEncounter == 0){
            if(gameField[maPiece->y][i].occupied == 0){
                maPiece->possibleMoves[maPiece->y][i] = 1;
            } 
            else{
                // Si on rencontre une pièce, on signifie qu'aucun mouvement est possible.
                checkEncounter = 1;

                // Si la pièce est adverse
                if(gameField[maPiece->y][i].piece->team != maPiece->team){

                    // Si c'est un Roi on initie un Echec au Roi.
                    if(gameField[maPiece->y][i].piece->type == 5){

                        *kingThreaten = 1;
                        threateningPiece[0] = maPiece->y;
                        threateningPiece[1] = maPiece->x;
                    }

                    // Sinon on signifie juste une capture
                    maPiece->possibleMoves[maPiece->y][i] = 2;
                }
                else{ // Si la pièce est alliée : on le signifie avec un 3.
                    maPiece->possibleMoves[maPiece->y][i] = 3;
                }
            }
        }
    }

    checkEncounter = 0;
    // Boucle permettant d'analyser les mouvements possibles vers la gauche
    for(i = maPiece->x - 1; i >= 0; i--){
        // Si on ne rencontre rien on continu d'ajouter 1 qui signifie un mouvement possible.
        if(checkEncounter == 0){
            if(gameField[maPiece->y][i].occupied == 0){
                maPiece->possibleMoves[maPiece->y][i] = 1;
            } 
            else{
                // Si on rencontre une pièce, on signifie qu'aucun mouvement est possible.
                checkEncounter = 1;

                // Si la pièce est adverse
                if(gameField[maPiece->y][i].piece->team != maPiece->team){

                    // Si c'est un Roi on initie un Echec au Roi.
                    if(gameField[maPiece->y][i].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                    }

                    // Sinon on signifie juste une capture
                    maPiece->possibleMoves[maPiece->y][i] = 2;
                }
                else{ // Si la pièce est alliée : on le signifie avec un 3.
                    maPiece->possibleMoves[maPiece->y][i] = 3;
                }
            }
        }
    }

    checkEncounter = 0;
    // Boucle permettant d'analyser les mouvements possibles vers le bas
    for(i = maPiece->y + 1; i < 8; i++){

        // Si on ne rencontre rien on continu d'ajouter 1 qui signifie un mouvement possible.
        if(checkEncounter == 0){
            if(gameField[i][maPiece->x].occupied == 0){
                maPiece->possibleMoves[i][maPiece->x] = 1;
            } 
            else{
                // Si on rencontre une pièce, on signifie qu'aucun mouvement est possible.
                checkEncounter = 1;

                // Si la pièce est adverse
                if(gameField[i][maPiece->x].piece->team != maPiece->team){

                    // Si c'est un Roi on initie un Echec au Roi.
                    if(gameField[i][maPiece->x].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }

                    // Sinon on signifie juste une capture
                    maPiece->possibleMoves[i][maPiece->x] = 2;
                }else{ // Si la pièce est alliée : on le signifie avec un 3.
                    maPiece->possibleMoves[i][maPiece->x] = 3;
                }
            }
        }
    }

    checkEncounter = 0;
    // Boucle permettant d'analyser les mouvements possibles vers le haut
    for(i = maPiece->y - 1; i >= 0; i--){

        if(checkEncounter == 0){
            if(gameField[i][maPiece->x].occupied == 0){
                maPiece->possibleMoves[i][maPiece->x] = 1;
            } 
            else{
                // Si on rencontre une pièce, on signifie qu'aucun mouvement est possible.
                checkEncounter = 1;

                // Si la pièce est adverse
                if(gameField[i][maPiece->x].piece->team != maPiece->team){

                     // Si c'est un Roi on initie un Echec au Roi.
                    if(gameField[i][maPiece->x].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }

                    // Sinon on signifie juste une capture
                    maPiece->possibleMoves[i][maPiece->x] = 2;
                }else{ // Si la pièce est alliée : on le signifie avec un 3.
                    maPiece->possibleMoves[i][maPiece->x] = 3;
                }
            }
        }
    }
}

// Fpnction gérant la capture pour le pion
void CheckPrisePion(Piece *maPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]){

    // On vérifie qu'on est bien dans la grille de jeu et qu'on est dans la team blanche.
    if(maPiece->team == 0 && maPiece->y < 7){

        // Check pour en bas à droite.
        if(gameField[maPiece->y + 1][maPiece->x + 1].occupied == 1){

            // Check de la team.
            if(maPiece->team != gameField[maPiece->y + 1][maPiece->x + 1].piece->team){

                    // Même process que pour la tour, le fou ou le cavalier
                    // On identifie une capture
                    // Si c'est le Roi on initie un Echec au Roi.
                    maPiece->possibleMoves[maPiece->y + 1][maPiece->x + 1] = 2;

                    if(gameField[maPiece->y + 1][maPiece->x + 1].piece->type == 5){
                        *kingThreaten = 1;
                        threateningPiece[0] = maPiece->y;
                        threateningPiece[1] = maPiece->x;
                    }
            }
            else{ // Sinon c'est bien un pion allié.
                maPiece->possibleMoves[maPiece->y + 1][maPiece->x + 1] = 3;
            }
        }

        // Check en bas à gauche
        if(gameField[maPiece->y + 1][maPiece->x - 1].occupied == 1){

            // Check de la team.
            if(maPiece->team != gameField[maPiece->y + 1][maPiece->x - 1].piece->team){


                // Même process que pour la tour, le fou ou le cavalier
                // On identifie une capture
                // Si c'est le Roi on initie un Echec au Roi.
                maPiece->possibleMoves[maPiece->y + 1][maPiece->x - 1] = 2;

                    if(gameField[maPiece->y + 1][maPiece->x - 1].piece->type == 5){
                        *kingThreaten = 1;
                        threateningPiece[0] = maPiece->y;
                        threateningPiece[1] = maPiece->x;
                    }
            }
            else{// Sinon c'est bien un pion allié.
                maPiece->possibleMoves[maPiece->y + 1][maPiece->x - 1] = 3;
            }
        }
    }
    // Check qu'on ne sort pas de la grille et qu'on est en team Noir.
    else if(maPiece->team == 1 && maPiece->y > 0){

        // Check en haut à droite
        if(gameField[maPiece->y - 1][maPiece->x + 1].occupied == 1){
            // Check de la team.
            if(maPiece->team != gameField[maPiece->y - 1][maPiece->x + 1].piece->team){


                // Même process que pour la tour, le fou ou le cavalier
                // On identifie une capture
                // Si c'est le Roi on initie un Echec au Roi.
                maPiece->possibleMoves[maPiece->y - 1][maPiece->x + 1] = 2;

                    if(gameField[maPiece->y - 1][maPiece->x + 1].piece->type == 5){
                        *kingThreaten = 1;
                        threateningPiece[0] = maPiece->y;
                        threateningPiece[1] = maPiece->x;
                    }
            }
            else{ // Sinon c'est bien un pion allié.
                maPiece->possibleMoves[maPiece->y - 1][maPiece->x + 1] = 3;
            }
        }

        // Check en haut à gauche
        if(gameField[maPiece->y - 1][maPiece->x - 1].occupied == 1){
            if(maPiece->team != gameField[maPiece->y - 1][maPiece->x - 1].piece->team){

                // Même process que pour la tour, le fou ou le cavalier
                // On identifie une capture
                // Si c'est le Roi on initie un Echec au Roi.
                maPiece->possibleMoves[maPiece->y - 1][maPiece->x - 1] = 2;

                if(gameField[maPiece->y - 1][maPiece->x - 1].piece->type == 5){
                    *kingThreaten = 1;
                    threateningPiece[0] = maPiece->y;
                    threateningPiece[1] = maPiece->x;
                }
            }
            else{ // Sinon c'est bien un pion allié.
                maPiece->possibleMoves[maPiece->y - 1][maPiece->x - 1] = 3;
            }
        }
    }
}

// Fonction gérant les déplacements généraux du pion.
void UpdatePionMove(Piece *maPiece, Case **gameField, int *enPassant, int enPassantCoord[2], int *kingThreaten, int threateningPiece[2]){

    // Gestion de la capture.
    CheckPrisePion(maPiece, gameField, kingThreaten, threateningPiece);

    // Cas où le pion peut faire son double move (au début)
    if(maPiece->doubleMove == 0){

        // Cas du déplacement des noirs (donc vers le bas)
        if(maPiece->team == 0){

            // Check des deux cases vers le haut.
            for(int i = maPiece->y + 1; i < maPiece->y + 3; i++){

                // Si la case est pas occupée on y place un déplacement (valeur 1)
                if(gameField[i][maPiece->x].occupied == 0){
                    maPiece->possibleMoves[i][maPiece->x] = 1;
                } 
            }
        } 
        else { // Cas du déplacement des blancs vers le haut

            // Check des deux cases vers le haut.
            for(int i = maPiece->y - 1; i > maPiece->y - 3; i--){

                // Si la case est pas occupée on y place un déplacement
                if(gameField[i][maPiece->x].occupied == 0){
                    maPiece->possibleMoves[i][maPiece->x] = 1;
                } 
            }
        }
    }
    else {

        // Cas des noirs
        if(maPiece->team == 0){
            
            // Check de la case en dessous
            if(maPiece->y + 1 < 8){
                // Si la case est pas occupée on y place un déplacement
                if(gameField[maPiece->y + 1][maPiece->x].occupied == 0){
                    maPiece->possibleMoves[maPiece->y + 1][maPiece->x] = 1;
                }
            }
        } 
        else {

            // Check de la case au dessus
            if(maPiece->y - 1 >= 0){
                // Si la case est pas occupée on y place un déplacement
                if(gameField[maPiece->y - 1][maPiece->x].occupied == 0){
                    maPiece->possibleMoves[maPiece->y - 1][maPiece->x] = 1;
                }
            }
        }
    }
}

// Gestion des mouvements du cavalier
// Les boucles sont plus exigeantes que les autres car les mouvements de cette pièces sont très spécifiques.
void UpdateKnightMove(Piece *maPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]){

    int i;

    // Boucle pour identifier les mouvements du cavalier vers le bas
    for(i = maPiece->y + 1; i < maPiece->y + 3; i++){

        // Vérification des limites de la grille.
        if(i < 8 && i >= 0){

            // Si on est dans une case correspondant aux possibilités du cavalier (ici 2 cases bas et 1 gauche)
            if(maPiece->x - 1 >= 0 && i == maPiece->y + 2){

                // Si non occupée : on signifie qu'on peut s'y déplacer.
                if(gameField[i][maPiece->x - 1].occupied == 0){
                    maPiece->possibleMoves[i][maPiece->x - 1] = 1;
                } 
                else{ // Si elle est occupée
                    // Si Pion adverse
                    if(gameField[i][maPiece->x - 1].piece->team != maPiece->team){

                        // Signification d'une capture possible
                        maPiece->possibleMoves[i][maPiece->x - 1] = 2;

                        // Si la pièce adverse est le Roi, on passe l'int identifiant la menance à 1
                        // Ceci permet d'initier le processus d'Echec au Roi
                        if(gameField[i][maPiece->x - 1].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }

                    }
                    else { // Si la pièce est alliée on passe à 3
                        maPiece->possibleMoves[i][maPiece->x - 1] = 3;
                    }
                }
            } // Cases correspondant à 2 sauts vers le bas et 1 pas à droite
            if(maPiece->x + 1 < 8 && i == maPiece->y + 2){

                // Si non occupée : on signifie qu'on peut s'y déplacer.
                if(gameField[i][maPiece->x + 1].occupied == 0){
                    maPiece->possibleMoves[i][maPiece->x + 1] = 1;
                } 
                else{ // Si elle est occupée
                    // Si Pion adverse
                    if(gameField[i][maPiece->x + 1].piece->team != maPiece->team){

                        // Signification d'une capture possible
                        maPiece->possibleMoves[i][maPiece->x + 1] = 2;

                        // Si la pièce adverse est le Roi, on passe l'int identifiant la menance à 1
                        // Ceci permet d'initier le processus d'Echec au Roi
                        if(gameField[i][maPiece->x + 1].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }
                    }                    
                    else { // Si la pièce est alliée on passe à 3
                        maPiece->possibleMoves[i][maPiece->x + 1] = 3;
                    }
                }
            }
        }
    }

    // Boucle pour identifier les mouvements du cavalier vers le haut
    for(i = maPiece->y - 1; i > maPiece->y - 3; i--){

        // Vérification des limites de la grille.
        if(i < 8 && i >= 0){
        
            // Cases correspondant à 2 sauts vers le haut et 1 pas à gauche
            if(maPiece->x - 1 >= 0 && i == maPiece->y - 2){

                // Si non occupée : on signifie qu'on peut s'y déplacer.
                if(gameField[i][maPiece->x - 1].occupied == 0){
                    maPiece->possibleMoves[i][maPiece->x - 1] = 1;
                } 
                else{ // Si elle est occupée
                    // Si Pion adverse
                    if(gameField[i][maPiece->x - 1].piece->team != maPiece->team){
                        // Signification d'une capture possible
                        maPiece->possibleMoves[i][maPiece->x - 1] = 2;

                        // Si la pièce adverse est le Roi, on passe l'int identifiant la menance à 1
                        // Ceci permet d'initier le processus d'Echec au Roi
                        if(gameField[i][maPiece->x - 1].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }
                    }                   
                    else { // Si la pièce est alliée on passe à 3
                        maPiece->possibleMoves[i][maPiece->x - 1] = 3;
                    }
                }
            }   
            // Cases correspondant à 2 sauts vers le haut et 1 pas à droite
            if(maPiece->x + 1 < 8 && i == maPiece->y - 2){

                // Si non occupée : on signifie qu'on peut s'y déplacer.
                if(gameField[i][maPiece->x + 1].occupied == 0){
                    maPiece->possibleMoves[i][maPiece->x + 1] = 1;
                } 
                else{ // Si elle est occupée
                    // Si Pion adverse
                    if(gameField[i][maPiece->x + 1].piece->team != maPiece->team){
                        // Signification d'une capture possible
                        maPiece->possibleMoves[i][maPiece->x + 1] = 2;

                        // Si la pièce adverse est le Roi, on passe l'int identifiant la menance à 1
                        // Ceci permet d'initier le processus d'Echec au Roi
                        if(gameField[i][maPiece->x + 1].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }
                    }                    
                    else { // Si la pièce est alliée on passe à 3
                        maPiece->possibleMoves[i][maPiece->x + 1] = 3;
                    }
                }
            }
        }
    }

    // Boucle pour identifier les mouvements du cavalier vers la droite
    for(i = maPiece->x + 1; i < maPiece->x + 3; i++){

        if(i < 8 && i >= 0){

            // Cases correspondant à 1 saut vers le haut et 2 pas à droite
            if(maPiece->y - 1 >= 0 && i == maPiece->x + 2){

                // Si non occupée : on signifie qu'on peut s'y déplacer.
                if(gameField[maPiece->y - 1][i].occupied == 0){
                   
                    maPiece->possibleMoves[maPiece->y - 1][i] = 1;
                } 
                else{ // Si elle est occupée    
                    // Si Pion adverse
                    if(gameField[maPiece->y - 1][i].piece->team != maPiece->team){
                         // Signification d'une capture possible
                        maPiece->possibleMoves[maPiece->y - 1][i] = 2;

                        // Si la pièce adverse est le Roi, on passe l'int identifiant la menance à 1
                        // Ceci permet d'initier le processus d'Echec au Roi
                        if(gameField[maPiece->y - 1][i].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }
                    }
                    else { // Si la pièce est alliée on passe à 3
                        maPiece->possibleMoves[maPiece->y - 1][i] = 3;
                    }
                }
            }   
            // Cases correspondant à 1 saut vers le bas et 2 pas à droite            
            if(maPiece->y + 1 < 8 && i == maPiece->x + 2){

                // Si non occupée : on signifie qu'on peut s'y déplacer.
                if(gameField[maPiece->y + 1][i].occupied == 0){
                    
                    maPiece->possibleMoves[maPiece->y + 1][i] = 1;
                } 
                else{ // Si elle est occupée
                    // Si Pion adverse 
                    if(gameField[maPiece->y + 1][i].piece->team != maPiece->team){

                        // Signification d'une capture possible
                        maPiece->possibleMoves[maPiece->y + 1][i] = 2;

                        // Si la pièce adverse est le Roi, on passe l'int identifiant la menance à 1
                        // Ceci permet d'initier le processus d'Echec au Roi
                        if(gameField[maPiece->y + 1][i].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }
                    }                    
                    else { // Si la pièce est alliée on passe à 3
                        maPiece->possibleMoves[maPiece->y + 1][i] = 3;
                    }
                }
            }
        }
    }

    // Boucle pour identifier les mouvements du cavalier vers la gauche
    for(i = maPiece->x - 1; i > maPiece->x - 3; i--){

        if(i < 8 && i >= 0){

            // Cases correspondant à 1 saut vers le haut et 2 pas à gauche
            if (maPiece->y - 1 >= 0 && i == maPiece->x - 2)
            {

                // Si non occupée : on signifie qu'on peut s'y déplacer.
                if (gameField[maPiece->y - 1][i].occupied == 0)
                {
                    maPiece->possibleMoves[maPiece->y - 1][i] = 1;
                }
                else // Si elle est occupée
                {
                    // Si Pion adverse 
                    if (gameField[maPiece->y - 1][i].piece->team != maPiece->team)
                    {
                        // Signification d'une capture possible
                        maPiece->possibleMoves[maPiece->y - 1][i] = 2;

                        // Si la pièce adverse est le Roi, on passe l'int identifiant la menance à 1
                        // Ceci permet d'initier le processus d'Echec au Roi
                        if(gameField[maPiece->y - 1][i].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }
                    }
                    else { // Si la pièce est alliée on passe à 3
                        maPiece->possibleMoves[maPiece->y - 1][i] = 3;
                    }
                }
            }
            // Cases correspondant à 1 saut vers le bas et 2 pas à gauche
            if (maPiece->y + 1 < 8 && i == maPiece->x - 2)
            {
                // Si non occupée : on signifie qu'on peut s'y déplacer.
                if (gameField[maPiece->y + 1][i].occupied == 0)
                {
                    maPiece->possibleMoves[maPiece->y + 1][i] = 1;
                }
                else // Si elle est occupée
                {
                    // Si Pion adverse 
                    if (gameField[maPiece->y + 1][i].piece->team != maPiece->team)
                    {
                        // Signification d'une capture possible                        
                        maPiece->possibleMoves[maPiece->y + 1][i] = 2;

                        // Si la pièce adverse est le Roi, on passe l'int identifiant la menance à 1
                        // Ceci permet d'initier le processus d'Echec au Roi
                        if(gameField[maPiece->y + 1][i].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }
                    }
                    else { // Si la pièce est alliée on passe à 3
                        maPiece->possibleMoves[maPiece->y + 1][i] = 3;
                    }
                }
            }
        }
    }
}

// Gestion des mouvements du Fou : les principes généraux sont les mêmes que pour la tour.
// La seule différence réside dans les déplacements diagonales sur la grille
void UpdateFouMove(Piece *maPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]){

    int i, j, checkEncounter;

    checkEncounter = 0;
    // Double compteur pour gérer les déplacements du fou
    // Ces compteurs sont init à partir des coordonnées de la pièce.
    j = maPiece->x + 1;

    // Boucler jusqu'aux limites de la grille pour identifier les mouv possibles.
    for(i = maPiece->y + 1; i < 8; i++){

        if(j < 8){
            if(checkEncounter == 0){
                if(gameField[i][j].occupied == 0){
                    maPiece->possibleMoves[i][j] = 1;
                } 
                else{
                    checkEncounter = 1;

                    if(gameField[i][j].piece->team != maPiece->team){

                        if(gameField[i][j].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }

                        maPiece->possibleMoves[i][j] = 2;

                    }else{
                        maPiece->possibleMoves[i][j] = 3;
                    }
                }
            }

            j++;
        }
    }

    checkEncounter = 0;
    j = maPiece->x - 1;

    // Boucler jusqu'aux limites de la grille pour identifier les mouv possibles.
    for(i = maPiece->y - 1; i >= 0; i--){

        if(j >= 0){
            if(checkEncounter == 0){
                if(gameField[i][j].occupied == 0){
                    maPiece->possibleMoves[i][j] = 1;
                } 
                else{
                    checkEncounter = 1;

                    if(gameField[i][j].piece->team != maPiece->team){
                        maPiece->possibleMoves[i][j] = 2;

                        if(gameField[i][j].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }
                    }else{
                        maPiece->possibleMoves[i][j] = 3;
                    }
                }
            }

            j--;
        }
    }

    checkEncounter = 0;
    j = maPiece->x + 1;
    // Boucler jusqu'aux limites de la grille pour identifier les mouv possibles.
    for(i = maPiece->y - 1; i >= 0; i--){

        if(j < 8){
            if(checkEncounter == 0){
                if(gameField[i][j].occupied == 0){
                    maPiece->possibleMoves[i][j] = 1;
                } 
                else{
                    checkEncounter = 1;

                    if(gameField[i][j].piece->team != maPiece->team){
                        maPiece->possibleMoves[i][j] = 2;
                        
                        if(gameField[i][j].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }

                    }else{
                        maPiece->possibleMoves[i][j] = 3;
                    }
                }
            }

            j++;
        }
    }

    checkEncounter = 0;
    j = maPiece->x - 1;
    // Boucler jusqu'aux limites de la grille pour identifier les mouv possibles.
    for(i = maPiece->y + 1; i < 8; i++){

        if(j >= 0){
            if(checkEncounter == 0){
                if(gameField[i][j].occupied == 0){
                    maPiece->possibleMoves[i][j] = 1;
                } 
                else{
                    checkEncounter = 1;

                    if(gameField[i][j].piece->team != maPiece->team){
                        maPiece->possibleMoves[i][j] = 2;

                        if(gameField[i][j].piece->type == 5){
                            *kingThreaten = 1;
                            threateningPiece[0] = maPiece->y;
                            threateningPiece[1] = maPiece->x;
                        }

                    }else{
                        maPiece->possibleMoves[i][j] = 3;
                    }
                }
            }

            j--;
        }       
    }
}

// Gestion des mouvements du Roi
void UpdateKingMove(Piece *maPiece, Case **gameField){
    
    // Tableau permettant de raccourcir le code en synthétisant l'ensemble des coordonnées à contrôler
    int checkXAxis[8] = {0,1,-1, 0, 1, -1, 1, -1};
    int checkYAxis[8] = {-1,-1,-1, 1, 1, 1, 0, 0};

    // Boucle dans les limites du tableau (8 cases autour du Roi à contrôler)
    for(int i = 0; i < 8; i++){

        // On s'assure d'être dans les limites de la grille.
        if((maPiece->y + checkYAxis[i] < 8 && maPiece->y + checkYAxis[i] >= 0) && ((maPiece->x + checkXAxis[i] < 8 && maPiece->x + checkXAxis[i] >= 0))){

            // Si la case n'est pas occupée le roi peut s'y déplacer.
            if(gameField[maPiece->y + checkYAxis[i]][maPiece->x + checkXAxis[i]].occupied == 0){
                maPiece->possibleMoves[maPiece->y + checkYAxis[i]][maPiece->x + checkXAxis[i]] = 1;
            } 
            else{
                // Si la case est occupée 
                // Si la pièce est un adversaire : le Roi peut la capturer.
                if(gameField[maPiece->y + checkYAxis[i]][maPiece->x + checkXAxis[i]].piece->team != maPiece->team){
                    maPiece->possibleMoves[maPiece->y + checkYAxis[i]][maPiece->x + checkXAxis[i]] = 2;
                }
                // Si la pièce est un allié : on l'identifie avec un 3
                else{
                    maPiece->possibleMoves[maPiece->y + checkYAxis[i]][maPiece->x + checkXAxis[i]] = 3;
                }
            }
        }
    }
}

// Gestion des mouvements de la Reine en liant Tour et Fou
void UpdateQueenMove(Piece *selectedPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]){
    UpdateFouMove(selectedPiece, gameField, kingThreaten, threateningPiece);
    UpdateTowerMove(selectedPiece, gameField, kingThreaten, threateningPiece);
}

// Fonction permettant de calculer le moveset de la pièce selon son type.
void UpdatePieceMoveSet(Piece *selectedPiece, Case **gameField, int *enPassant, int enPassantCoord[2], int *kingThreaten, int threateningPiece[2]){

    switch(selectedPiece->type)
    {
        case 1:
            UpdateTowerMove(selectedPiece, gameField, kingThreaten, threateningPiece);
            break;

        case 2:
            UpdateKnightMove(selectedPiece, gameField, kingThreaten, threateningPiece);
            break;

        case 3:
            UpdateFouMove(selectedPiece, gameField, kingThreaten, threateningPiece);
            break;

        case 4:
            UpdateQueenMove(selectedPiece, gameField, kingThreaten, threateningPiece);
            break;

        case 5:
            UpdateKingMove(selectedPiece, gameField);
            break;
        
        case 6:
            UpdatePionMove(selectedPiece, gameField, enPassant, enPassantCoord, kingThreaten, threateningPiece);
            break;

        default:
            break;
    }
}

// Boucle permettant la mise à jour de tous les moveset des pièces
void UpdateAllPiecesMoveSets(Piece **gamePieces, Case **gameField, int *enPassant, int enPassantCoord[2], int *kingThreaten, int threateningPiece[2]){

    for(int i=0; i < 2; i++){
        for(int j=0; j < 16; j++){
            if(gamePieces[i][j].captured == 0){
                InitialisePieceMovesetArr(gamePieces[i][j].possibleMoves);
                UpdatePieceMoveSet(&gamePieces[i][j], gameField, enPassant, enPassantCoord, kingThreaten, threateningPiece);   
            }
        }
    }
}