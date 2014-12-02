#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include<iostream>
#include<list>
using namespace std;

class CScoreItem
{
	string m_name;
	int m_score;
public:
	CScoreItem(string, int);
	void setScore(int);
	int getScore();
	bool operator< (const CScoreItem &rhs) const;

};

class CLeaderboard
{
	list<CScoreItem> m_scoreList;
public:
	int addItem(CScoreItem);
	list<CScoreItem> getList();
	bool compareItems(CScoreItem);
};

#endif // LEADERBOARD_H