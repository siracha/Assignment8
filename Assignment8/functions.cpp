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
void playGame()
{
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

	//load and display maze
	if (theMaze.loadMaze("maze.txt"))
		theMaze.showMaze();
	else
		cerr << "load maze failed!" << endl;

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