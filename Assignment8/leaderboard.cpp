#include"leaderboard.h"

CScoreItem::CScoreItem(string name, int score) : m_name(name), m_score(score)
{
}
void CScoreItem::setScore(int score)
{
	m_score = score;
}
int CScoreItem::getScore()
{
	return m_score;
}
bool CScoreItem::operator< (const CScoreItem &rhs) const 
{ 
	return (m_score < rhs.m_score); 
}
//-----
int CLeaderboard::addItem(CScoreItem score)
{
	m_scoreList.sort();
	m_scoreList.pop_back();//delete lowest item off sorted list
	m_scoreList.push_back(score);
	//cout << "there are: " << m_scoreList.size() << " entries on the leaderboard" << endl;
	return m_scoreList.size();
}
std::list<CScoreItem> CLeaderboard::getList()
{
	return m_scoreList;
}
bool CLeaderboard::compareItems(CScoreItem score)
{
	getList().sort();
	for (std::list<CScoreItem>::iterator it = getList().begin(); it != getList().end(); ++it)
	{
		if (score.getScore() > it->getScore())
			return true;
	}
	return false;
}