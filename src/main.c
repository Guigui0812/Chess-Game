#include "Game_CoreStructures.h"
#include "Game_MainFonctions.h"
#include "Game_Drawing_Field.h"
#include "Pieces_Movesets.h"

/****** Fonction principale ******/

void Game(SDL_Renderer *renderer){

    // Déclaration des variables générales du jeu.
    Player joueur1, joueur2;
    int enPassantCoord[2];
    int enPassant;
    SDL_bool program_launched = SDL_TRUE;
    int player;
    int ClicOnPion;
    int selectedPion[2];
    int threateningPiece[2];
    int EchecMate;
    int kingThreaten;
    TTF_Font *maPolice = TTF_OpenFont("CaviarDreams.ttf", 20); 

    // Déclaration et allocation des tableaux.
    Case **gameField = malloc(8 * sizeof(Case*));

    for(int i = 0; i < 8; i++){
        gameField[i] = malloc(8 * sizeof(Case));
    }

    Piece **gamePieces = malloc(2 * sizeof(Piece*));

    for(int i = 0; i < 2; i++){
        gamePieces[i] = malloc(16 * sizeof(Piece));
    }

    // Boucle globale du jeu.
    do{
        // Initialisation des variables.
        player = 1;
        ClicOnPion = 0;
        EchecMate = 0;
        kingThreaten = 0;
        enPassant = 0;
        joueur1.captured = 0;
        joueur2.captured = 0;
        joueur1.kingMove = 0;
        joueur2.kingMove = 0;
        joueur1.towerMove = 0;
        joueur2.towerMove = 0;

        // Initialisation du plateau, de la défausse et des pièces.
        InitGameField(renderer, gameField, gamePieces);
        GeneratedefaussePionPlaceBlancs(renderer, &joueur1);
        GeneratedefaussePionPlaceNoirs(renderer, &joueur2);
        SDL_RenderPresent(renderer);
        // Première analyse des mouvements possibles pour chaque pièce.
        UpdateAllPiecesMoveSets(gamePieces, gameField, &enPassant, enPassantCoord, &kingThreaten, threateningPiece); 

        // Boucle de la partie. Ceci permet d'en recommencer une lorsque la première est terminée.
        while (EchecMate == 0 && program_launched)
        {  
            SDL_RenderClear(renderer);
            DrawDefausse(renderer, &joueur1, &joueur2);
            DrawGameField(renderer, gameField, gamePieces);
            //printTurnName(renderer, maPolice, player); Mis en commentaire car SDL_TTF crée une fuite de mémoire.
            if(ClicOnPion == 1) ColorisedPossibleCase(renderer, &gamePieces[selectedPion[0]][selectedPion[1]], gameField, kingThreaten);
            if(kingThreaten == 1) ColorisedProtector(renderer, gamePieces, gameField, player);
            PlayerEvents(renderer, &program_launched, &player, &ClicOnPion, gamePieces, gameField, selectedPion, &joueur1, &joueur2, &enPassant, enPassantCoord, &kingThreaten, &EchecMate, threateningPiece);
            PiecesUpdateRender(renderer, gamePieces);
            SDL_RenderPresent(renderer);
        }

        EchecMate = 0;

    } while(program_launched);

    
    TTF_CloseFont(maPolice);
}

// Main du programme.
int main(int argc, char** argv)
{
    // Initialisation des éléments SDL
    SDL_Renderer *renderer;
    SDL_Window *window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        SDL_Log("ERREUR INIT SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    TTF_Init();

    // Création de la fenêtre avec gestion d'erreurs.
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0){
        SDL_Log("ERREUR : Creation de la fenetre et du rendu echouee > %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Création de l'icone de la fenêtre
    SDL_Surface *tmpSurface = IMG_Load("./piecesTextures/Noirs/CavalierNoir.png");
    SDL_SetWindowIcon(window, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    SDL_SetWindowTitle(window, "Chess");

    // Appel de la fonction principale du jeu.
    Game(renderer);

    // Exit et destruction des éléments.
    IMG_Quit();
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}