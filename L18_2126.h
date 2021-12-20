#pragma once
#include "player.h"
#include "gamestate.h"
#include "connect4move.h"
#include "connect4board.h"
#include "connect4state.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include<iomanip>

using namespace std;

struct col_score
{
    int col;
    int score;
};

class L18_2126 : public Player
{
public:
    L18_2126(char Color = 'A');
    Connect4Move* SuggestMove(GameState* State);
    double EvaluateState(GameBoard* Board, char player);
    double EvaluateWindow(char arr[],int size, char Player);
    col_score minmax(GameState* Board, int depth, int alpha, int beta, bool isMax, char ai, char opponent);
};



void BlankLines1(int n) {
	for (int i = 0; i < n; i++)
		cout << "\n";
}

void ShowBoard(GameBoard* B)
{
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			cout << static_cast <Connect4Board*> (B)->State[i][j] << " ";
		}
		cout << endl;
	}
}

void ShowConnect41(GameState* C) {
	Connect4State* C4 = static_cast<Connect4State*> (C);
	string P1 = C4->GetPlayerName(0);
	string P2 = C4->GetPlayerName(1);

	cout << "\t\t" << P1 << "\t\t vs \t\t" << P2;
	BlankLines1(3);
	for (int i = 1; i < 8; i++) {
		if (i == 1)
			cout << setw(8) << i;
		else
			cout << setw(11) << i;
	}
	BlankLines1(3);

	for (int r = 0; r < 6; r++) {
		for (int c = 0; c < 7; c++) {
			if (c == 0)
				cout << setw(2) << "|";
			char PlayerCode = C4->getState(r, c);
			cout << setw(6) << PlayerCode << setw(5) << "|";
		}
		cout << endl;

		for (int b = 0; r < 5 && b < 2; b++) {
			for (int c = 0; r < 5 && c < 7; c++) {
				if (c == 0)
					cout << setw(2) << "|";
				cout << setw(6) << ' ' << setw(5) << "|";
			}
			cout << endl;
		}
	}
	for (int i = 0; i < 80; i++)
		cout << char(220);

	if (C4->GetTurningPlayer() == 1)
		cout << endl << "Turn of " << P2;
	else
		cout << endl << "Turn of " << P1;
	cout << endl << endl;
}

void strcpy(char*& arr, char*& arr2)
{
	if (arr2 != nullptr)
	{
		if (arr != nullptr)
		{
			delete[] arr;
			arr = nullptr;
			arr = new char[strlen(arr2) + 1];
		}
		else
		{
			arr = new char[strlen(arr2) + 1];
		}

		for (int i = 0; i < strlen(arr2) + 1; i++)
		{
			arr[i] = arr2[i];
		}
	}
}


char* getDiag_Left(char(*arr)[7], int row, int col, int window_size)
{
	char* window = new char[window_size];
	for (int i = 0; i < window_size; i++)
	{
		window[i] = arr[row - i][col - i];
	}
	return window;
}

char* getDiag_Right(char(*arr)[7], int row, int col, int window_size)
{
	char* window = new char[window_size];
	for (int i = 0; i < window_size; i++)
	{
		window[i] = arr[row - i][col + i];
	}
	return window;
}

char* getCol(char(*arr)[7], int col)
{
	char* buffer = new char[6];
	int a = 0;
	for (int i = 0; i < 6; i++)
	{
		buffer[a] = arr[i][col];
		a++;
	}

	return buffer;
}

char* getWindow(char arr[], int window_size, int initial_point)
{
	char* window = new char[window_size];
	int a = 0;
	for (int i = 0; i < window_size; i++)
	{
		window[a] = arr[initial_point + i];
		a++;
	}
	return window;
}
int count_player(char arr[], int size, char player)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == player)
		{
			count++;
		}
	}
	return count;
}

int count_opponent(char arr[], int size, char Player)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] != Player && arr[i] != '.')
		{
			count++;
		}
	}
	return count;
}

double L18_2126::EvaluateWindow(char arr[], int size, char Player)
{
	int score = 0;

	if (count_player(arr, size, Player) == 4)
	{
		score += 100;
	}

	else if (count_player(arr, size, Player) == 3 && count_player(arr, size, '.') == 1)
	{
		score += 5;
	}

	else if (count_player(arr, size, Player) == 2 && count_player(arr, size, '.') == 2)
	{
		score += 2;
	}

	if (count_opponent(arr, size, Player) == 3 && count_player(arr, size, '.') == 1)
	{
		score += -4;
	}

	return score;
}


L18_2126::L18_2126(char Color) :Player("AI_Player", Color) {
	// Just call the base constructor
}

int count_arr(char arr[], int size, char player)
{
	int count = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == player)
		{
			count++;
		}
	}
	return count;
}

void print_arr(char arr[], int size)
{
	for (int k = 0; k < 4; k++)
	{
		cout << arr[k] << " ";
	}
	cout << endl;
}


double L18_2126::EvaluateState(GameBoard* Board, char player)
{
	//ShowBoard(Board);
	//ShowConnect41(State);
	double score = 0;
	//GameState* temp = State->Clone();
	/*This gives priority to the Middle column as it gives probability of winning*/
	char center_arr[6];
	int a = 0;
	for (int i = 5; i > -1; i--)
	{
		center_arr[a] = static_cast <Connect4Board*> (Board)->State[i][3];
		a++;
	}

	int center_count = 0;
	center_count = count_arr(center_arr, 6, player);
	//center_count = EvaluateWindow(center_arr, 6, player);
	score += static_cast <double> (center_count) * 3;



	//Check for Horizontal Score
	char* buffer;
	char* window;
	for (int i = 0; i < 6; i++)
	{
		buffer = new char[7];
		buffer = getWindow(static_cast <Connect4Board*> (Board)->State[i], 7, 0);

		for (int j = 0; j < 4; j++)
		{
			window = getWindow(buffer, 4, j);
			score += EvaluateWindow(window, 4, player);
		}

	}
	delete[] buffer;
	delete[] window;
	buffer = nullptr;
	window = nullptr;

	//Check for Vertical Score
	for (int i = 0; i < 7; i++)
	{
		buffer = getCol(static_cast <Connect4Board*> (Board)->State, i);
		for (int j = 0; j < 3; j++)
		{
			window = getWindow(buffer, 4, j);
			//print_arr(window, 4);
			score += EvaluateWindow(window, 4, player);
		}
	}
	buffer = nullptr;
	window = nullptr;

	//Check For Diagonal Right
	for (int i = 0; i < 6 - 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			window = getDiag_Right(static_cast <Connect4Board*> (Board)->State, 5 - i, j, 4);
			score += EvaluateWindow(window, 4, player);
		}
	}
	buffer = nullptr;
	window = nullptr;


	//Check For Diagonal Left
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			window = getDiag_Left(static_cast <Connect4Board*> (Board)->State, 5 - i, j + 3, 4);
			score += EvaluateWindow(window, 4, player);
		}
	}

	return score;

}

bool Winning_Move(GameState* Board, char player)
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

bool if_terminal(GameState* Board)
{
	char player = Board->GetPlayerColor(Board->GetTurningPlayer());
	char opponent = Board->GetPlayerColor(static_cast <GameState*> (Board)->SelectNextPlayer());
	return (Winning_Move(Board, player)) || (Winning_Move(Board, opponent)) || (Board->GetPossibleMoves().size() == 0);
}

int get_next_row(GameState* State, int col)
{
	GameBoard* temp = State->GetBoard();
	for (int i = 0; i < 6; i++)
	{
		if (static_cast<Connect4Board*>(temp)->State[i][col] == '.')
		{
			return i;
		}

	}
}



col_score L18_2126::minmax(GameState* Board, int depth, int alpha, int beta, bool isMax, char ai, char opponent)
{
	//ShowConnect41(Board);
	std::vector <GameMove*> valid = Board->GetPossibleMoves();
	bool is_terminal = if_terminal(Board);
	if (depth == 0 || is_terminal)
	{
		if (is_terminal)
		{
			if (Winning_Move(Board, ai))
			{
				col_score AI_win;
				AI_win.score = 10000000000;
				return AI_win;
			}
			else if (Winning_Move(Board, opponent))
			{
				col_score opp;
				opp.score = -10000000000;
				return opp;
			}
			else
			{
				col_score tie;
				tie.col = -1;
				tie.score = 0;
				return tie;

			}
		}
		else
		{
			col_score meh;
			char curr_player = Board->GetPlayerColor(Board->GetTurningPlayer());
			meh.score = EvaluateState(Board->GetBoard(), curr_player);
			return meh;
		}
	}

	if (isMax)
	{
		int value = INT_MIN;
		int column = 0;
		//GameState* clone;
		std::vector<GameMove*> baka = Board->GetPossibleMoves();
		for (int i = 0; i < 7; i++)
		{
			int row = get_next_row(Board, i);
			GameState* clone = Board->Clone();
			GameMove* temp_move = new Connect4Move(i);
			//column = static_cast<Connect4Move*>(baka[0])->GetMove();
			if (clone->Valid(temp_move))
			{
				clone = static_cast <Connect4State*> (clone)->ApplyMove(temp_move);
				col_score new_score;
				new_score = minmax(clone, depth - 1, alpha, beta, false, ai, opponent);
				if (new_score.score > value)
				{
					value = new_score.score;
					column = i;
				}
				alpha = std::max(alpha, value);
				if (alpha >= beta)
				{
					break;
				}
			}
		}
		col_score max;
		//column = static_cast<Connect4Move*>(baka[0])->GetMove();
		max.col = column;
		max.score = value;
		return max;
	}
	else
	{
		int value2 = INT_MAX;
		int column2 = 0;
		std::vector<GameMove*> baka = Board->GetPossibleMoves();
		for (int i = 0; i < 7; i++)
		{
			int row = get_next_row(Board, i);
			GameState* clone = Board->Clone();
			GameMove* temp_move = new Connect4Move(i);
			//column2 = static_cast<Connect4Move*>(baka[0])->GetMove();
			if (clone->Valid(temp_move))
			{
				clone = static_cast <Connect4State*> (clone)->ApplyMove(temp_move);
				col_score new_score2;
				new_score2 = minmax(clone, depth - 1, alpha, beta, true, ai, opponent);
				if (new_score2.score < value2)
				{
					value2 = new_score2.score;
					column2 = i;
				}
				beta = std::min(beta, value2);
				if (alpha >= beta)
				{
					break;
				}
			}
		}
		col_score min;
		min.col = column2;
		min.score = value2;
		return min;
	}
}

Connect4Move* L18_2126::SuggestMove(GameState* State)
{
	char player = State->GetPlayerColor(State->GetTurningPlayer());
	char opp = State->GetPlayerColor(State->SelectNextPlayer());
	Connect4Move* Move = new Connect4Move();
	col_score bestmove;
	bestmove = minmax(State, 4, INT_MIN, INT_MAX, true, player, opp);
	Move->SetMove(bestmove.col);

	return Move;
}