#ifndef __27C75412950FA36F48C27__HIGHSCORE__HPP__
#define __27C75412950FA36F48C27__HIGHSCORE__HPP__

#include <kos.h>
#include "../../dccommon/src/linkedlist.hpp"

class CScore
{
private:
	char *m_pName, *m_pDate;
	int m_iScore;
	CScore *m_pNext, *m_pPrev;
public:
	void SetName(char *name);
	char* GetName(){return(m_pName);};
	void SetScore(int score){m_iScore=score;};
	int GetScore(){return(m_iScore);};
	void SetDate(char *date);
	char* GetDate(){return(m_pDate);};
	void SetNext(CScore *next){m_pNext=next;};
	CScore* GetNext(){return(m_pNext);};
	void SetPrev(CScore *prev){m_pPrev=prev;};
	CScore* GetPrev(){return(m_pPrev);};
	CScore(char *name, char *date, int score);
	~CScore(void);
};

struct score
{
	char name[11];
	char date[11];
	int score;
};

class CHighScore
{
private:
	CScore *m_pFirst, *m_pLast, *m_pCurrent;
	int m_iLimit;
	bool m_bAsc;
	CLinkedList m_List;
public:
	void Clear(){delete m_pFirst;m_pFirst=NULL;};
	void Trim(int limit);
	void SetLimit(int limit){m_iLimit=limit;};
	int GetLimit(){return(m_iLimit);};
	void Add( char *name,  char *date, int score);
	void SetOrder(bool asc){m_bAsc=asc;};
	bool GetOrder(){return(m_bAsc);};
	CScore* GetScore(){return(m_pFirst);};
	CHighScore();
	~CHighScore();
};
#endif // __27C75412950FA36F48C27__HIGHSCORE__HPP__
