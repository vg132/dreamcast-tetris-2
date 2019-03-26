#ifndef __74A87112F9F3F89D4916A1__THEMEINFO__HPP__
#define __74A87112F9F3F89D4916A1__THEMEINFO__HPP__

#include <kos.h>
#include "background.hpp"

class CThemeInfo
{
private:
	char *m_pAuthor;
	char *m_pEmail;
	char *m_pURL;
	char *m_pDescription;
	char *m_pName;
	char *m_pPath;
	char *m_pBasePath;
	CBackground *m_pFirstBackground;
	int m_Backgrounds;
public:
	int GetNrOfBackgrounds(){return(m_Backgrounds);};
	void AddBackground(CBackground *background);
	void SetFirstBackground(CBackground *first){m_pFirstBackground=first;};
	CBackground* GetFirstBackground(){return(m_pFirstBackground);};
	void SetAuthor(const char *author);
	char* GetAuthor(){return(m_pAuthor);};
	void SetEmail(const char *email);
	char* GetEmail(){return(m_pEmail);};
	void SetURL(const char *url);
	char* GetURL(){return(m_pURL);};
	void SetDescription(const char *description);
	char* GetDescription(){return(m_pDescription);};
	void SetName(const char *name);
	char* GetName(){return(m_pName);};
	void SetPath(const char *path);
	char* GetPath(){return(m_pPath);};
	char* GetBasePath(){return(m_pBasePath);};
	CThemeInfo(void);
	~CThemeInfo(void);
};

#endif // __74A87112F9F3F89D4916A1__THEMEINFO__HPP__
