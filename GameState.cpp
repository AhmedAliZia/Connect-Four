#include "gamestate.h"
#include <iostream>
using namespace std;

//Players GamePlayers;

std::string GameState::GetPlayerName(int PlayerIndex) {
    return GamePlayers.GetPlayerName(PlayerIndex);
}
char GameState::GetPlayerColor(int PlayerIndex) {
    return GamePlayers.GetPlayerColor(PlayerIndex);
}

int GameState::AddPlayer(Player* P) {
    return GamePlayers.AddPlayer(P);
}

double GameState::Utility(unsigned int PlayerIndex) {

    if (this->GamePlayers.Winner == -2)
        return 0;

    if (this->GamePlayers.Winner == PlayerIndex)
        return 1;

    return -1;
}

unsigned int GameState::GetTurningPlayer() {
    return TurningPlayer;
}

int GameState::WhoWon() {
    return this->GamePlayers.Winner;
}

GameState::GameState() {
    this->TurningPlayer = 0;  //index of player making the move
}

bool GameState::GameOver() {
    return (this->GamePlayers.Winner != -1);
}


bool GameState::MakeMove() {
    GameMove* Move = nullptr;
    Move = GamePlayers.PlayerList[TurningPlayer]->SuggestMove(Clone());
    int NextTurn = SelectNextPlayer();
    if (!Valid(Move)) {
        TurningPlayer = NextTurn;
        return false;
    }
   /* if (Winning(Move))
    {
        GamePlayers.Winner = -1;
        cout << GamePlayers.PlayerList[TurningPlayer]->PlayerName << " Has Won the Game!!!!!!!!" << endl;
    }*/
    ApplyMove(Move);
    //            TurningPlayer = NextTurn;
    return true;
};

unsigned int GameState::SelectNextPlayer() {
    return (TurningPlayer + 1) % this->GamePlayers.TotalPlayers;
}

double GameState::EvaluateState(unsigned int PlayerIndex) {
    return 0;
}
