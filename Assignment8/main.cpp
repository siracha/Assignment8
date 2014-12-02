/***************************************************************************************
Title:    	Assignment 8
Course:   	GAM1545 Game Development 1
Section:  	3
Author:   	Jade Thomas
Date:     	2014/12/01
Description:
In this final assignment you will create a simple “semi-real-time” maze game that displays and plays in the console window.
This assignment will make use of Vectors, lists, classes, overloading, advanced console commands and a secondary thread.
*****************************************************************************************/

#include <iostream>
#include"maze.h"
#include"functions.h"
#include<process.h>

using namespace std;

int main()
{ 
	int g_menuChoice = 0;
	unsigned int thread_id = 0;

	//g_isThreadRunning = true;// start the thread loop
	//_beginthreadex(NULL, 0, TimerThread, NULL, 0, &thread_id); // start thred = keeps running until we set g_isThreadTunning to false

	//HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	//if (hStdin == INVALID_HANDLE_VALUE)
	//{
	//	cerr << "getStdHandle for main failed" << endl;
	//	return 1;
	//}

	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hStdout, &info); 
	
	int userChoice = 0;

	do
	{
		userChoice = menu();// menu call

		switch (userChoice)
		{
		case 1:
			playGame(chooseMaze());
			break;
		case 2:
			helpAndOptions();
			break;
		case 3:
			showLeaderboard();
			break;
		default://quit
			cout << "Come back and play another time." << endl;
			break;
		}
	} while (userChoice != 4);

	system("pause");
	return 0;
}