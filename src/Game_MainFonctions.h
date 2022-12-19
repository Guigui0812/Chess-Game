#include <stdio.h>

#include "Game_CoreStructures.h"
#include "Game_Consts.h"
#include "SDL_image.h"
#include "SDL.h"

#include "Game_Consts.h"
#include "Pieces_Setup.h"
#include "Game_CoreStructures.h"

// Opérations réalisées pour le mouvement seul.
void MovementCase(Piece *maPiece, Case **gameField, int i, int j, int *moveOk);
void CaptureOperation(Piece *pieceOnCase, Player *joueur1, Player *joueur2);
void PerformRightRoque(Piece *maPiece, Case **gameField, int i, int j, int *moveOk);
int MovePiece(Piece *maPiece, Case **gameField, int x, int y, Player *joueur1, Player *joueur2, int *enPassant, int enPassantCoord[2], int *kingThreaten);
void ColorisedPossibleCase(SDL_Renderer *renderer, Piece *maPiece, Case **gameField, int kingThreaten);
void ColorisedProtector(SDL_Renderer *renderer, Piece **gamePieces, Case **gameField, int player);
void HandleMouseClick(SDL_Renderer *renderer, int *ClicOnPion, Case **gameField, Piece **gamePieces, int *selectedPion, int *player, Player *joueur1, Player *joueur2, int *enPassant, int enPassantCoord[2], int *kingThreaten, int *EchecMate, int threateningPiece[2]);
void PlayerEvents(SDL_Renderer *renderer, SDL_bool *program_launched, int *player, int *ClicOnPion, Piece **gamePieces, Case **gameField, int *selectedPion, Player *joueur1, Player *joueur2, int *enPassant, int enPassantCoord[2], int *kingThreaten, int *EchecMate, int threateningPiece[2]);
void PiecesUpdateRender(SDL_Renderer *renderer, Piece **gamePieces);
void printTurnName(SDL_Renderer *renderer, TTF_Font *maPolice, int player);