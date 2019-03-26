#ifndef __B62F5A2320584D308F7B39__BACKGROUND__HPP__
#define __B62F5A2320584D308F7B39__BACKGROUND__HPP__

#include <kos.h>
#include <stdlib.h>

class CBackground
{
private:
	char *m_Name;
	char *m_Description;
	char *m_Path;
	char *m_URL;
	char *m_Artist;
	int m_StartLine;
	CBackground *m_Next, *m_pPrev;
public:
	void SetNext(CBackground *next){m_Next=next;};
	CBackground* GetNext(){return(m_Next);};
	void SetPrev(CBackground *prev){m_pPrev=prev;};
	CBackground* GetPrev(){return(m_pPrev);};
	void SetName(const char *name);
	char* GetName(){return(m_Name);};
	void SetDescription(const char *description);
	char* GetDescription(){return(m_Description);};
	void SetPath(const char *path);
	char* GetPath(){return(m_Path);};
	void SetStartLine(const char *startline);
	int GetStartLine(){return(m_StartLine);};
	void SetArtist(const char *artist);
	char* GetArtist(){return(m_Artist);};
	void SetURL(const char *url);
	char* GetURL(){return(m_URL);};
	CBackground(void);
	~CBackground(void);
};

#endif // __B62F5A2320584D308F7B39__BACKGROUND__HPP__
