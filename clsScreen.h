#pragma once
#include <iostream>
#include <string>
using namespace std;
class clsScreen
{
public :
	static void DrawTheHeader(string Titile)
	{
		cout << "\t\t\t\t_________________________________________________________\n\n";
		cout << "\t\t\t\t\t\t  " << Titile << "\n\n";
		cout << "\t\t\t\t_________________________________________________________\n\n";
	}

};

