#include "Game_CoreStructures.h"

void InitialisePieceMovesetArr(int pieceMovesetArray[8][8]);
void SetPiecesTeamAndType(int *pieceType, Piece **gamePieces);
void GeneratePieceTexture(Case *gameCase, Piece *gamePiece, SDL_Renderer *renderer, char *texturePath);
void CreateChessPiece(int pieceTeam, int pieceType, Case *gameCase, Piece *gamePiece, SDL_Renderer *renderer);
void FirstPiecesPlacement(Piece **gamePieces, Case **gameField, SDL_Renderer *renderer);
void PiecesUpdateRender(SDL_Renderer *renderer, Piece **gamePieces);