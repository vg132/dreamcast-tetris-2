#include "themehandler.hpp"

CThemeHandler::CThemeHandler()
{
}

CThemeHandler::~CThemeHandler()
{
}

void CThemeHandler::ReadDir(const char *dir, CLinkedList *list)
{
	file_t d;
	dirent_t *de(NULL);
	char* tmp;
	d=fs_open(dir,O_RDONLY|O_DIR);
	while((de=fs_readdir(d)))
	{
		tmp=new char[strlen(dir)+strlen(de->name)+5];
		strcpy(tmp,dir);
		strcat(tmp,"/");
		strcat(tmp,de->name);
		if(de->size==-1)
		{
			ReadDir(tmp,list);
			delete[] tmp;
		}
		else
		{
			if(!strcmp(&tmp[strlen(tmp)-6],".theme"))
				list->AddItem(tmp);
			else
				delete[] tmp;
		}
	};
	fs_close(d);
}

CLinkedList* CThemeHandler::LoadThemes(const char *folder)
{
	CLinkedList themes;
	CLinkedList *ll=NULL;
	ReadDir(folder,&themes);
	CListItem *listItem=themes.GetFirst();
	if(listItem!=NULL)
	{
		ll=new CLinkedList();
		do
		{
			char *fileName=(char*)listItem->GetData();
			ll->AddItem(LoadTheme(fileName));
			delete[] fileName;
		}while((listItem=listItem->GetNext())!=NULL);
	}
	return(ll);
}

CThemeInfo* CThemeHandler::LoadTheme(const char *fileName)
{
	void *buffer(NULL);
	int size(0);
	m_InBackground=false;
	m_CurrentInfo=new CThemeInfo();
	size=fs_load(fileName,&buffer);
	if(size!=-1)
	{
		Init();
		m_CurrentInfo->SetPath(fileName);
		Execute((char*)buffer,size);
		Reset();
	}
	if(buffer!=NULL)
		delete (char*)buffer;
	return(m_CurrentInfo);
}

void CThemeHandler::StartElement(const char *name, const char **atts)
{
	m_Text[0]='\0';
  if(!strcmp(name,"background"))
	{
    m_InBackground=true;
    m_CurrentBackground=new CBackground();
		m_CurrentBackground->SetNext(NULL);
  }
}

void CThemeHandler::EndElement(const char *name)
{
	Trim(m_Text);
	if(m_InBackground)
	{
		if(!strcmp(name,"background"))
		{
			m_CurrentInfo->AddBackground(m_CurrentBackground);
			m_InBackground=false;
		}
		else if(!strcmp(name,"name"))
		{
			m_CurrentBackground->SetName(m_Text);
		}
		else if(!strcmp(name,"description"))
		{
			m_CurrentBackground->SetDescription(m_Text);
		}
		else if(!strcmp(name,"path"))
		{
			char buffer[255];
			sprintf(buffer,"%s%s",m_CurrentInfo->GetBasePath(),m_Text);
			m_CurrentBackground->SetPath(buffer);
		}
		else if(!strcmp(name,"start-line"))
		{
			m_CurrentBackground->SetStartLine(m_Text);
		}
		else if(!strcmp(name,"url"))
		{
			m_CurrentBackground->SetURL(m_Text);
		}
		else if(!strcmp(name,"artist"))
		{
			m_CurrentBackground->SetArtist(m_Text);
		}
	}
	else
	{
		if(!strcmp(name,"author"))
			m_CurrentInfo->SetAuthor(m_Text);
		else if(!strcmp(name,"email"))
			m_CurrentInfo->SetEmail(m_Text);
		else if(!strcmp(name,"url"))
			m_CurrentInfo->SetURL(m_Text);
		else if(!strcmp(name,"description"))
			m_CurrentInfo->SetDescription(m_Text);
		else if(!strcmp(name,"name"))
			m_CurrentInfo->SetName(m_Text);
	}
}

void CThemeHandler::EndData(const char *data, int len)
{
	if((strlen(m_Text)+len)<5000)
		strncat(m_Text,data,len);
}

char* CThemeHandler::Trim(char *str)
{
	int len=strlen(str);
	int st=0;
	while((st<len)&&(str[st]<=' '))
		st++;

	while((st<len)&&(str[len-1]<=' '))
		len--;

	char *tmp=new char[len-st+1];
	strncpy(tmp,&str[st],len-st);
	tmp[len-st]='\0';
	strcpy(str,tmp);
	return(str);
}
