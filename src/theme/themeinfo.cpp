#include "themeinfo.hpp"

CThemeInfo::CThemeInfo()
{
	m_pAuthor=NULL;
	m_pEmail=NULL;
	m_pURL=NULL;
	m_pDescription=NULL;
	m_pFirstBackground=NULL;
	m_pName=NULL;
	m_pPath=NULL;
	m_pBasePath=NULL;
	m_Backgrounds=0;
}

CThemeInfo::~CThemeInfo()
{
	if(m_pAuthor!=NULL)
		delete[] m_pAuthor;
	if(m_pEmail!=NULL)
		delete[] m_pEmail;
	if(m_pURL!=NULL)
		delete[] m_pURL;
	if(m_pDescription!=NULL)
		delete[] m_pDescription;
	if(m_pFirstBackground!=NULL)
		delete m_pFirstBackground;
	if(m_pName!=NULL)
		delete[] m_pName;
	if(m_pPath!=NULL)
		delete[] m_pPath;
	if(m_pBasePath!=NULL)
		delete[] m_pBasePath;
}

void CThemeInfo::SetAuthor(const char *author)
{
	if(m_pAuthor!=NULL)
		delete[] m_pAuthor;
	m_pAuthor=new char[strlen(author)+1];
	strcpy(m_pAuthor,author);
}

void CThemeInfo::SetEmail(const char *email)
{
	if(m_pEmail!=NULL)
		delete[] m_pEmail;
	m_pEmail=new char[strlen(email)+1];
	strcpy(m_pEmail,email);
}

void CThemeInfo::SetURL(const char *url)
{
	if(m_pURL!=NULL)
		delete[] m_pURL;
	m_pURL=new char[strlen(url)+1];
	strcpy(m_pURL,url);
}

void CThemeInfo::SetDescription(const char *description)
{
	if(m_pDescription!=NULL)
		delete[] m_pDescription;
	m_pDescription=new char[strlen(description)+1];
	strcpy(m_pDescription,description);
}

void CThemeInfo::AddBackground(CBackground *background)
{
	m_Backgrounds++;
	if((m_pFirstBackground==NULL)||(m_pFirstBackground->GetStartLine()>background->GetStartLine()))
	{
		background->SetNext(m_pFirstBackground);
		background->SetPrev(NULL);
		m_pFirstBackground=background;
	}
	else
	{
		CBackground *bg=m_pFirstBackground;
		while((bg->GetNext()!=NULL)&&(bg->GetNext()->GetStartLine()<background->GetStartLine()))
			bg=bg->GetNext();
		background->SetNext(bg->GetNext());
		background->SetPrev(bg);
		bg->SetNext(background);
	}
}

void CThemeInfo::SetName(const char *name)
{
	if(m_pName!=NULL)
		delete[] m_pName;
	m_pName=new char[strlen(name)+1];
	strcpy(m_pName,name);
}

void CThemeInfo::SetPath(const char *path)
{
	if(m_pPath!=NULL)
		delete[] m_pPath;
	m_pPath=new char[strlen(path)+1];
	strcpy(m_pPath,path);

	int i=strlen(m_pPath);
	while((--i)&&(m_pPath[i]!='/'));
	if(m_pBasePath!=NULL)
		delete[] m_pBasePath;
	m_pBasePath=new char[i+2];
	strncpy(m_pBasePath,m_pPath,i+1);
	m_pBasePath[i+1]='\0';
}
