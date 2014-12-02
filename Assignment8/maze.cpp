#include<iostream>
#include"maze.h"
#include <fstream>
using namespace std;
#include <string>
#include<Windows.h>
#include"mycolours.h"

CMazeTile::CMazeTile()
{
	m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
}
bool CMazeTile::setTileFromCharacter(unsigned char c)
{
	bool result = true;
	switch (c)
	{
	case 'X':
		setTile(MAZE_WALL);
		break;
	case ' ':
		setTile(MAZE_EMPTY);
		break;
	case 'S':
		setTile(MAZE_START);
		break;
	case 'K':
		setTile(MAZE_KEY);
		break;
	case 'E':
		setTile(MAZE_EXIT);
		break;
	default:
		setTile(MAZE_ERROR);
		break;
	}
	return result;
}
bool CMazeTile::setTile(MazeType c)
{
	bool result = true;
	switch (c)
	{
	case MAZE_WALL:
		m_colour = setColour(LIGHT_CYAN, BLACK);
		m_symbol = (unsigned char)177;
		m_type = c;
		break;
	case MAZE_EMPTY:
		m_colour = setColour(LIGHT_CYAN, BLACK);
		m_symbol = ' ';
		m_type = c;
		break;
	case MAZE_START:
		m_colour = setColour(RED, BLACK);
		m_symbol = (unsigned char)16;
		m_type = c;
		break;
	case MAZE_KEY:
		m_colour = setColour(YELLOW, BLACK);
		m_symbol = (unsigned char)12;
		m_type = c;
		break;
	case MAZE_EXIT:
		m_colour = setColour(YELLOW, BLACK);
		m_symbol = (unsigned char)10;
		m_type = c;
		break;
	default:
		m_type = MAZE_ERROR;
		result = false;
		m_symbol = 'E';
		break;
	}
	return result;
}
void CMazeTile::showTile()
{
	if (SetConsoleTextAttribute(m_hStdout, m_colour))
		cout << unsigned char(m_symbol);
	else
		cerr << "setText failed error code: " << GetLastError() << endl;
}
bool CMaze::loadMaze(std::string file)
{
	ifstream inFile;
	inFile.open(file);
	
	int row = 0;
	int col = 0;
	string line;

	if (!inFile.is_open())
	{
		cout << "error reading file" << endl;
		return false;
	}

	inFile >> row;//read first line
	inFile >> col;//reads second
	if (row == 0 || col == 0)
	{
		cerr << "error no cols and/or rows" << endl;
	}
	inFile.ignore(10000, '\n');//ignores big whitespace at end of carriage return(end of last read line) until new line
	for (int r = 0; r < row; r++)
	{
		getline(inFile, line, '\n');
		if (inFile.fail())
		{
			cout << "error row " << r << "expected: " << row << " but rows stopped" << endl;
		}

		if (line.size() != col)
		{
			cout << "error column" << r << "expected: " << col << " chars, but found" << line.size() << endl;
		}

		vector<CMazeTile> rowVect;
		for (unsigned int i = 0; i < line.size(); i++)
		{
			CMazeTile tile;

			if (tile.setTileFromCharacter(line[i]) == false)// for X or " " in the string 'line'
			{
				cout << "error character" << line[i] << endl;
			}
			rowVect.push_back(tile);// add tile to rowVect vector
			
			if (tile.getType() == MAZE_START)
			{
				m_startPos.X = r;
				m_startPos.X = i;
			}
		}
		m_theMaze.push_back(rowVect); 
		if (m_theMaze.at(r).size() == rowVect.size())
		{
			m_rows = row;
			m_cols = col;
		}
	}// end for
	return true;
}
void CMaze::showMaze()
{
	HANDLE hStdout;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD coord;
	BOOL result;
	coord.X = m_cols;
	coord.Y = m_rows;
	result = SetConsoleScreenBufferSize(hStdout, coord);

	struct _SMALL_RECT screenRect;
	screenRect.Left = 0;
	screenRect.Top = 0;
	screenRect.Right = m_cols + 1;  // x is your desired width
	screenRect.Bottom = m_rows + 1;  // y is desired height
	SetConsoleWindowInfo(hStdout, true, &screenRect);

	for (int r = 0; r < m_rows; r++)
	{
		for (int c = 0; c < m_cols; c++)
		{
			m_theMaze[r][c].showTile();//for each row vector show tile at each column dunno if works
		}
		cout << "\n";
	}
}
MazeType CMazeTile::getType()
{
	return m_type;
}
COORD CMaze::getStartCoo()
{
	return m_startPos;
}
void CMaze::setTileType(COORD pos, MazeType t)
{
	m_theMaze[pos.Y][pos.X].setTile(t);
}