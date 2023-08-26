#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsGlobale.h"
#include <fstream>
#include "Library/clsString.h"
using namespace std;

class clsSaveInFile
{
	public:
	struct sGameInfo
	{
		string Name;
		int WinnTime;
	};
	static string ConvertGameInfoRecordToLine(sGameInfo Game, string Delim = "#//#")
	{
		string Line = "";
		Line += Game.Name + Delim;
		Line += to_string(Game.WinnTime) ;

		return Line;
	}

	static sGameInfo ConvertGameInfoLineToRecord(string Line, string Delim = "#//#")
	{
		sGameInfo Game;
		vector <string> vString = clsString::SplitString(Line, Delim);
		Game.Name = vString[0];
		Game.WinnTime = stoi(vString[1]);

		return Game;
	}
	static vector <sGameInfo> PutGameInfoFromFileToVector()
	{
		vector <sGameInfo> vString;
		fstream FILE;
		FILE.open(GameInfoFile, ios::in | ios::out);
		if (FILE.is_open())
		{
			string line;
			while (getline(FILE, line))
			{
				vString.push_back(ConvertGameInfoLineToRecord(line));
			}
			FILE.close();
		}
		return vString;
	}
	static bool FindPlayer(string name, sGameInfo& game)
	{
		vector <sGameInfo> vGame = PutGameInfoFromFileToVector();
		for (auto& i : vGame)
		{
			if (i.Name == name)
			{
				game = i;
				return true;
			}
			
		}
		return false;
	}
	static void _SaveInfoToFile(sGameInfo Game)
	{

		vector <sGameInfo> vGame = PutGameInfoFromFileToVector();
		bool find = false;
		for (auto& i : vGame)
		{
			if (i.Name == Game.Name)
			{
				i.WinnTime = Game.WinnTime;
				find = true;
			}
		}
		fstream FILE;
		FILE.open(GameInfoFile, ios::out);
		if (FILE.is_open())
		{
			
			for (auto& i : vGame)
			{
				FILE << ConvertGameInfoRecordToLine(i) << endl;
			}
			if (!find)
			{
				FILE << ConvertGameInfoRecordToLine(Game) << endl;
			}
			FILE.close();
		}

	}
};

