#pragma once
#include <vector>
#include <fstream>
#include <iostream>
#include "Library/clsString.h"
#include "Library/clsInputValidation.h"
#include "Library/clsUtil.h"
#include "clsGlobale.h"
#include "clsScreen.h"
#include "clsSaveInFile.h"
using namespace std;
static char Player1;
static char Player2;
vector<vector<char>> vBoard2(3, vector<char>(3, ' '));
class clsTwoUserGameScreen :  protected clsSaveInFile , protected clsScreen
{

	struct stCoordinates
	{
		int Row;
		int Colum;

	};

	static char _ReadTheChoice()
	{
		cout << "Please Enter Your Choice X[1] or O[0] ? : ";
		short Choice = clsInputValidate::ReadNumberBetween<short>(0, 1);
		return (Choice == 1) ? 'X' : 'O';
	}

	static 	stCoordinates ReadUserTurn(string user)
	{
		stCoordinates Coord;
		cout << "\n\nPlease Enter Your Choice in Board 3X3 [0-2] "<<"("<<user<<") : ? ";
		Coord.Row = clsInputValidate::ReadNumberBetween<short>(0, 2);
		Coord.Colum = clsInputValidate::ReadNumberBetween<short>(0, 2);
		while (!isValid(Coord))
		{
			cout << "Invalid/Coordinate Try Another ,,,";
			cout << "\n\nPlease Enter Your Choice in Board 3X3 [0-2] ? : ";
			Coord.Row = clsInputValidate::ReadNumberBetween<short>(0, 2);
			Coord.Colum = clsInputValidate::ReadNumberBetween<short>(0, 2);
		}
		return Coord;
	}

	static bool isValid(stCoordinates Coord)
	{
		return (vBoard2[Coord.Row][Coord.Colum] != 'X' && vBoard2[Coord.Row][Coord.Colum] != 'O');
	}

	static 	void ADDToBoard(stCoordinates Coord, char Player)
	{

		vBoard2[Coord.Row][Coord.Colum] = Player;

	}
	static void _PrintBoard()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (vBoard2[i][j] == 'X' || vBoard2[i][j] == 'O')
					cout << vBoard2[i][j];
				else
				{
					cout << " ";
				}
			}
			cout << endl;
		}
	}

	static 	bool _CheckWin(char Computer)
	{

		if (vBoard2[0][0] == Computer && vBoard2[1][1] == Computer && vBoard2[2][2] == Computer)
			return true;
		if (vBoard2[2][0] == Computer && vBoard2[1][1] == Computer && vBoard2[0][2] == Computer)
			return true;
		for (short i = 0; i < 3; i++)
		{
			if (vBoard2[i][0] == Computer && vBoard2[i][1] == Computer && vBoard2[i][2] == Computer)
				return true;
			if (vBoard2[0][i] == Computer && vBoard2[1][i] == Computer && vBoard2[2][i] == Computer)
				return true;
		}
		return false;
	}

	static 	char _Player2Choice()
	{
		return (Player1 == 'X') ? 'O' : 'X';
	}

	static void _RestartTheGame(sGameInfo game)
	{
		_SaveInfoToFile(game);
		while (!vBoard2.empty())
		{
			vBoard2.pop_back();
		}
		vBoard2.resize(3, std::vector<char>(3, 0));
	}

public:


	static void showGameScreen()
	{

		int Counter = 0;
		sGameInfo CurrentGame;
		DrawTheHeader("GAME START");
		char Answer;
		do
		{
			Player1 = _ReadTheChoice();
			Player2 = _Player2Choice();
			do
			{
				ADDToBoard(ReadUserTurn("Player1"), Player1);
				_PrintBoard();
				Counter++;
				if (Counter == 9 || _CheckWin(Player1))
				{
					cout << "\n\n";
					_PrintBoard();
					break;

				}
				ADDToBoard(ReadUserTurn("Player2"), Player2);
				Counter++;
				_PrintBoard();
			} while (!_CheckWin(Player1) && !_CheckWin(Player2) && Counter != 9);

			Counter = 0;
			if (!_CheckWin(Player1) && !_CheckWin(Player2))
			{
				cout << "it's Draw ,,,";
			}
			else
			{
				if (_CheckWin(Player1))
				{
					cout << "User1 Win ,,, ";
					if (!FindPlayer("Player1", CurrentGame))
					{
						CurrentGame.Name = "Player1";
						CurrentGame.WinnTime = 1;
					}
					else
						CurrentGame.WinnTime++;

				}
				else
				{
					cout << "User2  Win ,,,";
					if (!FindPlayer("Player2", CurrentGame))
					{
						CurrentGame.Name = "Player2";
						CurrentGame.WinnTime = 1;
					}
					else
					CurrentGame.WinnTime++;
				}
			}
			cout << "\n\nDo You Want To Play Again ? y/n ";
			cin >> Answer;
			_RestartTheGame(CurrentGame);
		} while (towlower(Answer) == 'y');

	}


};

