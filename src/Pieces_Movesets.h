#include <stdio.h>
#include "Game_CoreStructures.h"
#include "Pieces_Setup.h"

void UpdateTowerMove(Piece *maPiece, Case **gameField,int *kingThreaten, int threateningPiece[2]);
void CheckPrisePion(Piece *maPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]);
void UpdatePionMove(Piece *maPiece, Case **gameField, int *enPassant, int enPassantCoord[2], int *kingThreaten, int threateningPiece[2]);
void UpdateKnightMove(Piece *maPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]);
void UpdateFouMove(Piece *maPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]);
void UpdateKingMove(Piece *maPiece, Case **gameField);
void UpdateQueenMove(Piece *selectedPiece, Case **gameField, int *kingThreaten, int threateningPiece[2]);
void UpdatePieceMoveSet(Piece *selectedPiece, Case **gameField, int *enPassant, int enPassantCoord[2], int *kingThreaten, int threateningPiece[2]);
void UpdateAllPiecesMoveSets(Piece **gamePieces, Case **gameField, int *enPassant, int enPassantCoord[2], int *kingThreaten, int threateningPiece[2]);