#include "background.hpp"

CBackground::CBackground()
{
	m_Name=NULL;
	m_Description=NULL;
	m_Path=NULL;
	m_Next=NULL;
	m_Artist=NULL;
	m_URL=NULL;
	m_pPrev=NULL;
}

CBackground::~CBackground()
{
	if(m_Next!=NULL)
		delete m_Next;
	if(m_Name!=NULL)
		delete[] m_Name;
	if(m_Description!=NULL)
		delete[] m_Description;
	if(m_Path!=NULL)
		delete[] m_Path;
	if(m_URL!=NULL)
		delete[] m_URL;
	if(m_Artist!=NULL)
		delete[] m_Artist;
}

void CBackground::SetName(const char *name)
{
	if(m_Name!=NULL)
		delete[] m_Name;
	m_Name=new char[strlen(name)+1];
	strcpy(m_Name,name);
}

void CBackground::SetDescription(const char *description)
{
	if(m_Description!=NULL)
		delete[] m_Description;
	m_Description=new char[strlen(description)+1];
	strcpy(m_Description,description);
}

void CBackground::SetPath(const char *path)
{
	if(m_Path!=NULL)
		delete[] m_Path;
	m_Path=new char[strlen(path)+1];
	strcpy(m_Path,path);
}

void CBackground::SetStartLine(const char *startline)
{
	m_StartLine=atoi(startline);
}

void CBackground::SetArtist(const char *artist)
{
	if(m_Artist!=NULL)
		delete[] m_Artist;
	m_Artist=new char[strlen(artist)+1];
	strcpy(m_Artist,artist);
}

void CBackground::SetURL(const char *url)
{
	if(m_URL!=NULL)
		delete[] m_URL;
	m_URL=new char[strlen(url)+1];
	strcpy(m_URL,url);
}
