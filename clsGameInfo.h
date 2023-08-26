#pragma once
#include "clsScreen.h"
#include "clsSaveInFile.h"
#include <fstream>
#include "clsGlobale.h"
#include <vector>
#include <iomanip>
class clsGameInfo : protected clsScreen , protected  clsSaveInFile
{


    static void _PrintUserRecordLine(sGameInfo User)
    {

        cout << setw(8) << left << "" << "| " << setw(12) << left << User.Name;
        cout << "| " << setw(12) << left << User.WinnTime;

    }
public:
	static void ShowGameInfoScreen()
	{
		DrawTheHeader("Game Info Screen");
		vector <sGameInfo> Info = PutGameInfoFromFileToVector();

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(12) << "Player Name";
        cout << "| " << left << setw(25) << "Winning Time";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        if (Info.size() == 0)
            cout << "\t\t\t\tNo Users Available In the System!";
        else
        {
            for (auto& i : Info)
            {
                _PrintUserRecordLine(i);
                cout << endl;
            }
        }
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "______________________________________________\n" << endl;

        cout << "\n\n Do You Want To Restart This Score  ? y/n ? ";
        char Answer;
        cin >> Answer;
        if (towlower(Answer) == 'y')
        {
            fstream FILE;
            FILE.open(GameInfoFile, ios::out);
            FILE.close();
            cout << "\nDone";
        }
	}
	
};

