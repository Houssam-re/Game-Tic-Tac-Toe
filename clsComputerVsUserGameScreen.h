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
static char CurrentUser;
static char Computer;
vector<vector<char>> vBoard(3, vector<char>(3, ' '));
class clsComputerVsUserGameScreen : protected clsSaveInFile , protected clsScreen
{
	
	struct stCoordinates
	{
		int Row;
		int Colum;

	};


	static char _ReadTheChoice()
	{
		cout << "Please Enter Your Choice X[1] or O[0] ? : ";
		short Choice =  clsInputValidate::ReadNumberBetween<short>(0, 1);
		return (Choice == 1) ? 'X' : 'O';
	}
	
	static 	stCoordinates ReadUserTurn()
	{
		stCoordinates Coord;
		cout << "\n\nPlease Enter Your Choice in Board 3X3 [0-2] ? : ";
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
		return (vBoard[Coord.Row][Coord.Colum] != 'X' && vBoard[Coord.Row][Coord.Colum] != 'O');
	}

	static 	void ADDToBoard(stCoordinates Coord,char Player)
	{
		
		vBoard[Coord.Row][Coord.Colum] = Player;
	
	}

	static stCoordinates  ComputerTurn()
	{
		stCoordinates Coord;
		do
	{
			Coord.Row = clsUtil::RandomNumber(0, 2);
	  	    Coord.Colum = clsUtil::RandomNumber(0, 2);
		} while (!isValid(Coord));
		return Coord;
	}

	static void _PrintBoard()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (vBoard[i][j] == 'X' || vBoard[i][j] == 'O')
					cout << vBoard[i][j];
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
		
		if (vBoard[0][0] == Computer && vBoard[1][1] == Computer && vBoard[2][2] == Computer)
				return true;
		if (vBoard2[2][0] == Computer && vBoard2[1][1] == Computer && vBoard2[0][2] == Computer)
			return true;
		for (short i = 0; i < 3; i++)
		{
			if (vBoard[i][0] == Computer && vBoard[i][1] == Computer && vBoard[i][2] == Computer)
				return true;
			if (vBoard[0][i] == Computer && vBoard[1][i] == Computer && vBoard[2][i] == Computer)
				return true;
		}
		return false;
	}

	static 	char _Player2Choice()
	{
		return (CurrentUser == 'X') ? 'O' : 'X';
	}
	static void _RestartTheGame(sGameInfo game)
	{
		_SaveInfoToFile(game);
		while (!vBoard.empty())
		{
			vBoard.pop_back();
		}
		vBoard.resize(3, std::vector<char>(3, 0));
	}

public:
	

	static void showGameScreen()
	{

		int Counter = 0;
		sGameInfo Winner;
		DrawTheHeader("GAME START");
		char Answer;
		do
		{
			CurrentUser = _ReadTheChoice();
			Computer =    _Player2Choice();
			do
			{
				ADDToBoard(ReadUserTurn(), CurrentUser);
				Counter++;
				if (Counter == 9 || _CheckWin(CurrentUser))
				{
					_PrintBoard();
					break;

				}
				ADDToBoard(ComputerTurn(), Computer);
				Counter++;
				_PrintBoard();
			} while (!_CheckWin(CurrentUser) && !_CheckWin(Computer) && Counter != 9);
			Counter = 0;
			if (!_CheckWin(CurrentUser) && !_CheckWin(Computer))
			{
				cout << "it's Draw ,,,";
			}
			else
			{
				if (_CheckWin(CurrentUser))
				{
					cout << "User Win ,,, ";
					
					if (!FindPlayer("Player1", Winner))
					{
						Winner.Name = "Player1";
						Winner.WinnTime = 1;
					}
					else
						Winner.WinnTime++;
				}
				else
				{
					cout << "Computer  Win ,,,";
					if (!FindPlayer("Computer", Winner))
					{
						Winner.Name = "Player2";
						Winner.WinnTime = 1;
					}
					else
						Winner.WinnTime++;
				}
				
			}
			cout << "\n\nDo You Want To Play Again ? y/n ";
			cin >> Answer;
			_RestartTheGame(Winner);
		} while (towlower(Answer) == 'y');

	}
};

