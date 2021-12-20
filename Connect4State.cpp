#include "connect4state.h"
#include "connect4board.h"

bool Check_Winning_Move(GameState* Board, char player)
{
    GameBoard* temp = Board->GetBoard();

    //Check rows
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (static_cast <Connect4Board*> (temp)->State[j][i] == player &&
                static_cast <Connect4Board*> (temp)->State[j][i + 1] == player &&
                static_cast <Connect4Board*> (temp)->State[j][i + 2] == player &&
                static_cast <Connect4Board*> (temp)->State[j][i + 3] == player)
            {
                return true;
            }

        }
    }

    //Check Columns
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (static_cast <Connect4Board*> (temp)->State[j][i] == player &&
                static_cast <Connect4Board*> (temp)->State[j + 1][i] == player &&
                static_cast <Connect4Board*> (temp)->State[j + 2][i] == player &&
                static_cast <Connect4Board*> (temp)->State[j + 3][i] == player)
            {
                return true;
            }

        }
    }


    //Check For Right Diagonals
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (static_cast <Connect4Board*> (temp)->State[j][i] == player &&
                static_cast <Connect4Board*> (temp)->State[j + 1][i + 1] == player &&
                static_cast <Connect4Board*> (temp)->State[j + 2][i + 2] == player &&
                static_cast <Connect4Board*> (temp)->State[j + 3][i + 3] == player)
            {
                return true;
            }

        }
    }

    //Check For Left Diagonals
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (static_cast <Connect4Board*> (temp)->State[5 - i][j + 3] == player &&
                static_cast <Connect4Board*> (temp)->State[5 - i - 1][j + 3 - 1] == player &&
                static_cast <Connect4Board*> (temp)->State[5 - i - 2][j + 3 - 2] == player &&
                static_cast <Connect4Board*> (temp)->State[5 - i - 3][j + 3 - 3] == player)
            {
                return true;
            }

        }
    }
    return false;
}


bool Connect4State::NoMoreMoves() {
    for (int i = 0; i < 7; i++)
        if (MoveTo[i] > -1)
            return false;
    return true;
}

int Connect4State::CheckWinner(int r, int c) {
    /** Your Code Goes Here

    Function will check if the player that made a move at position
    (r, c) has won the game or not

    If game has been won then the players ID will be returned
    else -1 will be the return value
    */
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (State[j][i] == this->GetPlayerColor(TurningPlayer) &&
                State[j][i + 1] == this->GetPlayerColor(TurningPlayer) &&
                State[j][i + 2] == this->GetPlayerColor(TurningPlayer) &&
                State[j][i + 3] == this->GetPlayerColor(TurningPlayer))
            {
                return 1;
            }

        }
    }

    //Check Columns
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (State[j][i] == this->GetPlayerColor(TurningPlayer) &&
                State[j + 1][i] == this->GetPlayerColor(TurningPlayer) &&
                State[j + 2][i] == this->GetPlayerColor(TurningPlayer) &&
                State[j + 3][i] == this->GetPlayerColor(TurningPlayer))
            {
                return 1;
            }

        }
    }


    //Check For Right Diagonals
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (State[j][i] == this->GetPlayerColor(TurningPlayer) &&
                State[j + 1][i + 1] == this->GetPlayerColor(TurningPlayer) &&
                State[j + 2][i + 2] == this->GetPlayerColor(TurningPlayer) &&
                State[j + 3][i + 3] == this->GetPlayerColor(TurningPlayer))
            {
                return 1;
            }

        }
    }

    //Check For Left Diagonals
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (State[5 - i][j + 3] == this->GetPlayerColor(TurningPlayer) &&
                State[5 - i - 1][j + 3 - 1] == this->GetPlayerColor(TurningPlayer) &&
                State[5 - i - 2][j + 3 - 2] == this->GetPlayerColor(TurningPlayer) &&
                State[5 - i - 3][j + 3 - 3] == this->GetPlayerColor(TurningPlayer))
            {
                return 1;
            }

        }
    }
    if (NoMoreMoves())
        return -2; // Game Drawn
    return -1;
}

double Connect4State::Utility(unsigned int PlayerIndex) {
    // Your code goes here;
    int Winner = GamePlayers.Winner;
    if (Winner == -2)
        return 0;
    if (PlayerIndex == Winner)
        return 1;
    return -1;
    //            return 0;
}

void Connect4State::SetState(int r, int c, char ch) {
    State[r][c] = ch;
}

Connect4State::Connect4State(Connect4State& Connect4) {
    /**
    This copy constructor will be needed by the clone method
    */
    //no need to create copy of the static part of class

    this->TurningPlayer = Connect4.TurningPlayer;
    for (int c = 0; c < 7; c++) {
        this->MoveTo[c] = Connect4.MoveTo[c];
        for (int r = 0; r < 6; r++)
            this->State[r][c] = Connect4.State[r][c];
    }
    this->GamePlayers.Winner = Connect4.WhoWon();
}

char Connect4State::getState(int r, int c) {
    return State[r][c];
}

Connect4State::Connect4State() {
    /**
    Default constructor to initialize a new game;
    */
    this->GamePlayers.Winner = -1; // the value will be set to winning player ID or zero by the MakeMove function
    for (int c = 0; c < 7; c++) {
        MoveTo[c] = 5; // Largest empty row in each column
        for (int r = 0; r < 6; r++)
            State[r][c] = '.'; // Initially each cell has null char
    }
}

bool Connect4State::Winning(GameMove* Move) {
    
    if (Check_Winning_Move(this->Clone(), TurningPlayer))
    {
        return true;
    }
   /* else if (Check_Winning_Move(this->Clone(), SelectNextPlayer()))
    {
        return true;
    }*/
    return false;

}

bool Connect4State::Valid(GameMove* Move) {
    if (Move == nullptr)
        return false;
    Connect4Move* M = static_cast <Connect4Move*> (Move);
    int Column = M->GetMove();
    if (MoveTo[Column] < 0)
        return false;
    return true;
}


std::vector<GameMove*> Connect4State::GetPossibleMoves() {
    /**
        This function will use the reference to MoveList to
        return all possible moves by the current player in the current state.

        return value will be true if some moves are possible and false otherwise
    */
    std::vector<GameMove*> MoveList;
    MoveList.clear();
    for (int c = 0; c < 7; c++) {
        if (State[0][c] == '.') {
            Connect4Move* T = new Connect4Move(c);
            MoveList.push_back(T);
        }
    }
    return MoveList;
}

GameState* Connect4State::ApplyMove(GameMove* Move) {
    /**
        Apply the move on the current state and return a pointer to a
        copy of the new state.
    */
    Connect4Move* M = (static_cast <Connect4Move*> (Move));
    int c = M->GetMove();// Column;
    State[MoveTo[c]][c] = this->GamePlayers.GetPlayerColor(TurningPlayer);
    MoveTo[c]--;
    this->GamePlayers.Winner = CheckWinner(MoveTo[c] + 1, c);
    TurningPlayer = SelectNextPlayer();
    return Clone();
}

double Connect4State::EvaluateState(unsigned int PlayerIndex) {
    // Your code goes here

    return 0;
}

GameState* Connect4State::Clone() {
    return new Connect4State(*this);
}

GameBoard* Connect4State::GetBoard() {
    Connect4Board* Board = new Connect4Board(State);
    return Board;
}
