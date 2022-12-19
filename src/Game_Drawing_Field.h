#include "Game_CoreStructures.h"
#include "Pieces_Setup.h"

void GeneratedefaussePionPlaceBlancs(SDL_Renderer *renderer, Player *joueur1);
void GeneratedefaussePionPlaceNoirs(SDL_Renderer *renderer, Player *joueur2);
void DrawDefausse(SDL_Renderer *renderer, Player *joueur1, Player *joueur2);
void ChangeDrawColor(SDL_Renderer *renderer, int colorState);
void *DrawCase(Case *maCase, SDL_Renderer *renderer, int x, int y);
void DrawGameField(SDL_Renderer *renderer, Case **gameField, Piece **gamePieces);
void InitGameField(SDL_Renderer *renderer, Case **gameField, Piece **gamePieces);