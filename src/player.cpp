#include "player.hpp"

CPlayer::CPlayer()
{
	m_pControl=NULL;
	m_pField=NULL;
  m_iPoints=0;
  m_iLevel=0;
	m_iPower=0;
	for(int i=0;i<4;i++)
		m_iLines[i]=0;
  moveSize=50;
  m_bShowNext=true;
	m_bRumble=true;
  m_iCursorPos=0;
	m_iGameModeMenuPos=0;

  m_pLetters=new char[66];
	strcpy(m_pLetters,"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.0123456789_ ö");
	SetName("Player");

	m_iStartHeight[0]=0;
	m_iStartHeight[1]=1;
	m_iStartHeight[2]=3;
	m_iStartHeight[3]=6;
	m_iStartHeight[4]=9;
	m_iStartHeight[5]=13;

	m_iHeightMenuPos=0;
	m_iLevelMenuPos=0;
	m_iModeSelectPos=0;

	m_iPowerFlash=0;
}

CPlayer::~CPlayer()
{
  if(m_pField!=NULL)
		delete m_pField;
  if(m_pControl!=NULL)
		delete m_pControl;
}

void CPlayer::Reset()
{
	if(m_pField!=NULL)
		delete m_pField;
	m_pField=new CField();
  m_iPoints=0;
  m_iLevel=0;
	m_iPower=0;
	for(int i=0;i<4;i++)
		m_iLines[i]=0;
}

void CPlayer::Rumble(int frequence)
{
	int port(0),unit(0);
	if(m_bRumble==true)
	{
		maple_raddr(m_pControl->GetMapleAddress(),&port,&unit);
		maple_device_t *purudev;
		purudev=maple_enum_dev(port,2);
		if((purudev!=NULL)&&(!strcmp(purudev->drv->name,"PuruPuru (Vibration) Pack")))
			purupuru_rumble(purudev,frequence);
	}
}

void CPlayer::SetName(char* name)
{
  int k(0),i(0);
	strncpy(m_Name,name,10);
	strcat(m_Name,"ö");
	for(i=0;i<10;i++)
	{
		k=0;
		while((m_Name[i]!=m_pLetters[k])&&(k<69))
		{
			k++;
		};
		if(k<69)
			m_iLetterPos[i]=k;
		else
			m_iLetterPos[i]=0;
	}
}

void CPlayer::SetDisplayName()
{
	for(int i=0;i<10;i++)
	{
		if(m_Name[i]!='ö')
			m_DisplayName[i]=m_Name[i];
		else
			m_DisplayName[i]='\0';
	}
}

void CPlayer::SetLevel(int level)
{
  m_iLevel=level;
  if(m_iLevel==0)
		moveSize=50;
  else if(m_iLevel==1)
		moveSize=40;
  else if(m_iLevel==2)
		moveSize=35;
  else if(m_iLevel==3)
		moveSize=30;
  else if(m_iLevel==4)
		moveSize=25;
  else if(m_iLevel==5)
		moveSize=20;
  else if(m_iLevel==6)
		moveSize=17;
  else if(m_iLevel==7)
		moveSize=15;
  else if(m_iLevel==8)
		moveSize=12;
  else if(m_iLevel==9)
		moveSize=10;
	else if(m_iLevel>9)
		moveSize=6;
}

void CPlayer::DeleteField()
{
	if(m_pField!=NULL)
		delete m_pField;
	m_pField=NULL;
}

void CPlayer::SetField(CField* field)
{
	if(m_pField!=NULL)
		delete m_pField;
	m_pField=field;
}

void CPlayer::SetRows(int rows)
{
	m_iLines[rows-1]++;
	switch(rows)
	{
		case 1:
			m_iPower+=5;
			break;
		case 2:
			m_iPower+=15;
			break;
		case 3:
			m_iPower+=25;
			break;
		case 4:
			m_iPower+=50;
			break;
	}
	if(m_iPower>100)
		m_iPower=100;
}

int CPlayer::GetLines(int index)
{
	if(index<4)
		return(m_iLines[index]);
	else
		return(m_iLines[0]+(m_iLines[1]*2)+(m_iLines[2]*3)+(m_iLines[3]*4));
}

void CPlayer::NextLetter()
{
	if(m_iLetterPos[m_iCursorPos]==65)
		m_iLetterPos[m_iCursorPos]=0;
	else
		m_iLetterPos[m_iCursorPos]++;
	m_Name[m_iCursorPos]=m_pLetters[m_iLetterPos[m_iCursorPos]];
}

void CPlayer::PrevLetter()
{
	if(m_iLetterPos[m_iCursorPos]==0)
		m_iLetterPos[m_iCursorPos]=65;
	else
		m_iLetterPos[m_iCursorPos]--;
	m_Name[m_iCursorPos]=m_pLetters[m_iLetterPos[m_iCursorPos]];
}

void CPlayer::NextCursorPos()
{
	if(m_iCursorPos<10)
		m_iCursorPos++;
}

void CPlayer::PrevCursorPos()
{
	if(m_iCursorPos>0)
		m_iCursorPos--;
}

void CPlayer::SetControl(CDCControl *control)
{
	if(m_pControl!=NULL)
		delete m_pControl;
	m_pControl=control;
}
