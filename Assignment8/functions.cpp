#include"player.h"
#include"functions.h"
#include"maze.h"
#include<windows.h>
#include<iostream>

using namespace std;

unsigned char gameKeyEventProc(KEY_EVENT_RECORD ker)// returns what key was pressed
{
	if (ker.bKeyDown)
	{
		if (ker.wVirtualKeyCode == VK_LEFT)
		{
			return VK_LEFT;
		}
		if (ker.wVirtualKeyCode == VK_RIGHT)
		{
			return VK_RIGHT;
		}
		if (ker.wVirtualKeyCode == VK_DOWN)
		{
			return VK_DOWN;
		}
		if (ker.wVirtualKeyCode == VK_UP)
		{
			return VK_UP;
		}

	}
	return 0;
}
void playGame(int mazeNum)
{
	system("cls");
	INPUT_RECORD irInBuf[128];//buffer to read in input, windows type, 128 events wide
	DWORD cNumRead;//double word, windows specific type, used with read console input
	HANDLE  hStdin = GetStdHandle(STD_INPUT_HANDLE);// get handle for input device
	if (hStdin == INVALID_HANDLE_VALUE)//error check handle
	{
		cerr << "Error: GetStdHandle in" << endl;
		return;
	}

	HANDLE  hStdout = GetStdHandle(STD_OUTPUT_HANDLE);// get handle for output device
	if (hStdout == INVALID_HANDLE_VALUE)//error check handle
	{
		cerr << "Error: GetStdHandle out" << endl;
		return;
	}

	//init maze and player
	CMaze theMaze;
	CPlayer player(1);

	switch (mazeNum)
	{
	case 1:
		//load and display maze
		if (theMaze.loadMaze("maze.txt"))
			theMaze.showMaze();
		else
			cerr << "load maze failed!" << endl;
		break;
	case 2:
		//load and display maze
		if (theMaze.loadMaze("maze2.txt"))
			theMaze.showMaze();
		else
			cerr << "load maze failed!" << endl;
		break;
	case 3:
		//load and display maze
		if (theMaze.loadMaze("maze3.txt"))
			theMaze.showMaze();
		else
			cerr << "load maze failed!" << endl;
		break;
	case 4:
		//load and display maze
		if (theMaze.loadMaze("maze4.txt"))
			theMaze.showMaze();
		else
			cerr << "load maze failed!" << endl;
		break;
	default:
		cerr << "huh? maze choice switch" << endl;
	}

	//Set the player's start pos
	COORD pos;
	pos = theMaze.getStartCoo();

	player.setPos(pos);
	player.showPlayer();

	//Handle loop
	while (1)
	{
		//handle input
		if (!ReadConsoleInput(hStdin, irInBuf, 1, &cNumRead))//handle, buffer to read events, size of buffer,pointer  to write items read 
		{
			cerr << "Error: ReadConsleInput" << endl;
			return;
		}

		if (cNumRead > 0)
		{
			if (irInBuf[0].EventType == KEY_EVENT)
			{
				COORD coord = player.getPos();
				unsigned char key;

				key = gameKeyEventProc(irInBuf[0].Event.KeyEvent);

				if (key == VK_LEFT)
					coord.X--;
				else if (key == VK_UP)
					coord.Y--;
				else if (key == VK_DOWN)
					coord.Y++;
				else if (key == VK_RIGHT)
					coord.X++;

				if (coord.X < 0)
					coord.X = 0;
				if (coord.Y < 0)
					coord.Y = 0;
				
				//check for tile type
				//if (theMaze.getTile(coord) == )
				//get pos
				//erase current position
				SetConsoleCursorPosition(hStdout, player.getPos());
				cout << " ";
				//updated new pos
				player.setPos(coord);
				player.showPlayer();


			}
		}

		//update items/object in game
		//render your graphics
	}
}
int chooseMaze()
{
	cout << "which maze would you like to play? (mazes are numbered 1-4): ";
	int mazeChoice = 0;
	cin >> mazeChoice;
	if (mazeChoice > 4 || mazeChoice < 1)
	{
		cerr << "incorrect maze choice" << endl;
		return 0;
	}
	return mazeChoice;
}
void helpAndOptions()// how to play + controls
{
	system("cls");
	system("color 96");//lght b/y

	int userChoice = 0;
	do
	{
		cout << "1. How to Play\n2. Controls\n3. Back: ";
		cin >> userChoice;
		if (userChoice > 3 || userChoice < 1)
			cerr << "invalid choice!" << endl << endl;

		switch (userChoice)
		{
		case 1://how to play
			displayRules();
			break;
		case 2://controls
			displayControls();
			break;
		default://quit
			break;
		}
	} while (userChoice != 3);
}
void showLeaderboard()
{

}
int menu()
{
	system("cls");
	system("color 07");//b/w

	int userChoice = 0;

	cout << "1)Play game\n2)Help & Options\n3)Leaderboard\n4)Exit Game: ";
	cin >> userChoice;

	if (userChoice > 4 || userChoice < 1)
		cerr << "invalid choice!" << endl << endl;

	return userChoice;
}
void displayRules()
{
	cout << "The player uses the arrow keys to navigate to the end position"
		<< ", picking up any required items on the way" << endl;
}
void displayControls()
{
	cout << "The player uses the arrow keys to navigate." << endl;
}