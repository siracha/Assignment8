#ifndef _PLAYER_H
#define _PLAYER_H

#include<iostream>
#include<Windows.h>

class CPlayer
{
	unsigned char m_symbol;
	COORD m_pos;
	HANDLE m_hStdout;
	HANDLE m_hStdin;
public :
	CPlayer(unsigned char);
	void getPos(int &, int&);
	COORD getPos();
	void setPos(int, int);
	void setPos(COORD);
	void showPlayer();

	
};

#endif // !_PLAYER_H
