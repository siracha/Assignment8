#include"player.h"

CPlayer::CPlayer(unsigned char c)
{
	m_symbol = c;
	m_pos = { 0, 0 };
	m_hStdin = GetStdHandle(STD_INPUT_HANDLE);
	m_hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
}
void CPlayer::getPos(int & x, int & y)
{
	x = m_pos.X;
	y = m_pos.Y;
}
COORD CPlayer::getPos()
{
	return m_pos;
}
void CPlayer::setPos(int x, int y)
{
	m_pos.X = x;
	m_pos.Y = y;
}
void CPlayer::setPos(COORD pos)
{
	m_pos = pos;
}
void CPlayer::showPlayer()
{
	SetConsoleCursorPosition(m_hStdout, m_pos);
	std::cout << (unsigned char)m_symbol;
}