#ifndef _MAZE_H
#define _MAZE_H

#include <iostream>
#include<vector>
#include<Windows.h>

enum MazeType
{
	MAZE_EMPTY,
	MAZE_WALL,
	MAZE_START,
	MAZE_KEY,
	MAZE_ERROR
};

class CMazeTile
{
	MazeType m_type;
	unsigned char m_colour;
	unsigned char m_symbol;
public:
	bool setTileFromCharacter(unsigned char);
	void showTile();
	bool setTile(MazeType);
	MazeType getType();
};

class CMaze
{
	int m_rows;
	int m_cols;
	std::vector < std::vector<CMazeTile>> m_theMaze ;
	COORD m_startPos;
public:
	std::vector < std::vector<CMazeTile> > getMaze(){ return m_theMaze; };
	bool loadMaze(std::string file);
	void showMaze();
	COORD getStartCoo();
	CMazeTile getTile(COORD p) { return m_theMaze[p.Y][ p.X]; };
	void setTileType(COORD pos, MazeType c);
};
#endif