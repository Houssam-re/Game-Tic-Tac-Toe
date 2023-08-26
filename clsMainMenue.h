#pragma once
#include <iostream>
#include <iomanip>
#include "Library/clsInputValidation.h"
#include "clsScreen.h"
#include "clsTwoUserGameScreen.h"
#include "clsComputerVsUserGameScreen.h"
#include "clsGameInfo.h"
using namespace std;
class clsMainMenu : protected clsScreen
{

    enum enTic_Tac_Toe { eGameVsComputer = 1, eTwoUser = 2, eGameInfo = 3, eShutDown = 4 };
    static  int ReadTheChoice()
    {
        cout << "Enter Your Choice Between [1--4] :  ";
        return clsInputValidate::ReadNumberBetween(1, 4, "Please Enter Number In Range,,,");
    }
    static  void _GoBackToMainMeneu()
    {
        cout << "\n\nPress Any Key To Go Back ...\n\n";
        system("pause>0");
        ShowMainMenuGame();
    }
    static  void ShowCompurterVsUserScreen()
    {
        clsComputerVsUserGameScreen::showGameScreen();
    }
    static   void ShowTwoUserGameScreen()
    {
        clsTwoUserGameScreen::showGameScreen();
    }
    static void ShowGameInfoScreen()
    {
        clsGameInfo::ShowGameInfoScreen();
    }
    static   void _PerformChoice(enTic_Tac_Toe Choice)
    {
        switch (Choice)
        {
        case clsMainMenu::eGameVsComputer:
            system("cls");
            ShowCompurterVsUserScreen();
            _GoBackToMainMeneu();
            break;
        case clsMainMenu::eTwoUser:
            system("cls");
            ShowTwoUserGameScreen();
            _GoBackToMainMeneu();
            break;
        case clsMainMenu::eGameInfo:
            system("cls");
            ShowGameInfoScreen();
            _GoBackToMainMeneu();
            break;
        case clsMainMenu::eShutDown:
            break;
        default:
            break;
        }
    }
public:
    static void ShowMainMenuGame()
    {
        system("cls");
        DrawTheHeader(" Tic Tac Toe  Game ");
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Play vs Computer.\n";
        cout << setw(37) << left << "" << "\t[2] Two User Game.\n";
        cout << setw(37) << left << "" << "\t[3] Game Info.\n";
        cout << setw(37) << left << "" << "\t[4] ShutDown.\n";
        cout << setw(37) << left << "" << "===========================================\n";
        _PerformChoice((enTic_Tac_Toe)ReadTheChoice());
    }
};


