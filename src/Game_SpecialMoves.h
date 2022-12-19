#include "Game_CoreStructures.h"
#include "Pieces_Setup.h"

int CheckEchecMate(Piece Roi);
int GetKing(Piece **gamePieces, int *player);
void CheckIfKingMove(Piece **gamePieces, int *player, int *EchecMat, Player *joueur, int *kingThreaten, int threateningPiece[2]);
void CheckPriseEnPassant(Piece *maPiece, Case **gameField, int enPassantCoord[2]);
void checkRoque(Piece *maPiece, Case **gameField, Piece **gamePieces, int *player, Player *joueur);
int CheckPromotion(Piece *maPiece);
void Promote(SDL_Renderer *renderer, Piece *maPiece, Case **gameField);
void Promotion(SDL_Renderer *renderer, Piece *maPiece, Case **gameField);