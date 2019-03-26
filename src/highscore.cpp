#include "highscore.hpp"

//--------- CScore ---------//

CScore::CScore(char *name, char *date, int score)
{
	m_pName=new char[strlen(name)];
	m_pDate=new char[strlen(date)];
	m_iScore=score;
	m_pNext=NULL;
	strcpy(m_pName,name);
	strcpy(m_pDate,date);
}

CScore::~CScore()
{
	if(m_pNext!=NULL)
		delete m_pNext;
	delete[] m_pName;
	delete[] m_pDate;
}

void CScore::SetName(char *name)
{
	if(m_pName!=NULL)
		delete[] m_pName;
	m_pName=new char[strlen(name)];
	strcpy(m_pName,name);
}

void CScore::SetDate(char *date)
{
	if(m_pDate!=NULL)
		delete[] m_pDate;
	m_pDate=new char[strlen(date)];
	strcpy(m_pDate,date);
}

//--------- CHighScore ---------//

CHighScore::CHighScore()
{
	m_pFirst=NULL;
	m_pLast=NULL;
	m_pCurrent=NULL;
}

CHighScore::~CHighScore()
{
	if(m_pFirst!=NULL)
		delete m_pFirst;
}

void CHighScore::Trim(int limit)
{
	int i(0);
	m_pCurrent=m_pFirst;
	while((m_pCurrent!=NULL)&&(++i<=m_iLimit))
	{
		m_pCurrent=m_pCurrent->GetNext();
	};
	if((m_pCurrent!=NULL)&&(i>=m_iLimit))
	{
		m_pLast=m_pCurrent->GetPrev();
		m_pLast->SetNext(NULL);
		delete m_pCurrent;
	}
}

void CHighScore::Add( char *name,  char *date, int score)
{
	CScore *pTmp=new CScore(name,date,score);
	m_pCurrent=m_pFirst;
	if(m_pFirst==NULL)
	{
		m_pFirst=pTmp;
		m_pLast=pTmp;
		pTmp->SetNext(NULL);
		pTmp->SetPrev(NULL);
	}
	else
	{
		while((m_pCurrent!=NULL)&&(((!m_bAsc)&&(m_pCurrent->GetScore()>=score))||((m_bAsc)&&(m_pCurrent->GetScore()<=score))))
		{
			m_pCurrent=m_pCurrent->GetNext();
		};
		if(m_pCurrent==m_pFirst)
		{
			pTmp->SetNext(m_pCurrent);
			pTmp->SetPrev(NULL);
			m_pCurrent->SetPrev(pTmp);
			m_pFirst=pTmp;
		}
		else if(m_pCurrent!=NULL)
		{
			pTmp->SetNext(m_pCurrent);
			m_pCurrent=m_pCurrent->GetPrev();
			pTmp->GetNext()->SetPrev(pTmp);
			pTmp->SetPrev(m_pCurrent);
			m_pCurrent->SetNext(pTmp);
		}
		else if(m_pCurrent==NULL)
		{
			m_pLast->SetNext(pTmp);
			pTmp->SetPrev(m_pLast);
			pTmp->SetNext(NULL);
			m_pLast=pTmp;
		}
	}
	Trim(m_iLimit);
}
