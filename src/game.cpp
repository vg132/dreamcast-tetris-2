#include "game.hpp"

CGame::CGame()
{
	m_pPlayers[0]=NULL;
	m_pPlayers[1]=NULL;
	m_pMusic=NULL;
	m_pDraw=NULL;
	m_pCurrentThemeInfo=NULL;
	m_pPreviewThemeInfo=NULL;
	m_pThemeList=NULL;
	m_pHighScore=new CHighScore();
	m_pHighScore->SetLimit(10);
	m_pHighScore->SetOrder(false);

	m_pHighScore->Add("Noe","2004-02-03",1000);
	m_pHighScore->Add("Viktor","2004-02-03",900);
	m_pHighScore->Add("Magnus","2004-02-03",800);
	m_pHighScore->Add("Takayama","2004-02-03",700);
	m_pHighScore->Add("Calle","2004-02-03",600);
	m_pHighScore->Add("Dan","2004-02-03",500);
	m_pHighScore->Add("Roger","2004-02-03",400);
	m_pHighScore->Add("Jeffrey","2004-02-03",300);
	m_pHighScore->Add("Sega","2004-02-03",200);
	m_pHighScore->Add("KOS","2004-02-03",100);

	m_pVMU=new CVMU();
	m_pActiveVMU=NULL;

	m_iPlayers=0;
	m_bSound=true;
	m_bMusic=true;
	m_bAutoSave=true;
	m_bTVModeLoaded=false;
	m_pSound=new CSound();
	m_pSound->InitSound();
	XX=0;
	YY=0;
	m_iMainMenuPos=0;
	m_iPauseMenuPos=0;
	m_iOptionMenuPos=0;
	m_iThemeBrowserMenuPos=0;
	m_iVMUMenuPos=0;
	m_iSoundVolume=144;
	m_iMusicVolume=5;
	m_iTVMenuPos=0;
}

CGame::~CGame()
{
	for(int i=0;i<2;i++)
	{
		if(m_pPlayers[i]!=NULL)
			delete m_pPlayers[i];
	}
	if(m_pSound!=NULL)
		delete m_pSound;
	if(m_pHighScore!=NULL)
		delete m_pHighScore;
	if(m_pVMU!=NULL)
		delete m_pVMU;
	if(m_pThemeList!=NULL)
		delete m_pThemeList;
	if(m_pMusic!=NULL)
		delete m_pMusic;
}

void CGame::SetMusic(CMusic *music)
{
	if(m_pMusic!=NULL)
		delete m_pMusic;
	m_pMusic=music;
	if((m_bMusic)&&(m_pMusic!=NULL))
		m_pMusic->Play();
}

void CGame::SetPlayMusic(bool music)
{
	m_bMusic=music;
	if((m_bMusic)&&(m_pMusic!=NULL))
		m_pMusic->Play();
	else if(m_pMusic!=NULL)
		m_pMusic->Stop();
}

bool CGame::AddPlayer(CPlayer *player)
{
	if(m_iPlayers>1)
		return(false);
	m_pPlayers[m_iPlayers++]=player;
	return(true);
}

void CGame::SetHighScore()
{
	tm TimeStruct;
	char* buffer=new char[12];
	time_t t=rtc_unix_secs();
	localtime_r(&t, &TimeStruct);
	sprintf(buffer,"%04d-%02d-%02d",TimeStruct.tm_year+1900,TimeStruct.tm_mon+1,TimeStruct.tm_mday);
	GetHighScore()->Add(GetPlayer(0)->GetDisplayName(),buffer,GetPlayer(0)->GetPoints());
	if(GetGameMode()==GAME_MODE_2PLAYER)
		GetHighScore()->Add(GetPlayer(1)->GetDisplayName(),buffer,GetPlayer(1)->GetPoints());
}

void CGame::Ready()
{
	if(GetGameMode()==GAME_MODE_1PLAYER)
	{
		SetStatus(CGame::STATUS_RUN);
	}
	else if(GetGameMode()==GAME_MODE_2PLAYER)
	{
		if((m_pPlayers[0]->GetReady())&&(m_pPlayers[1]->GetReady()))
			SetStatus(CGame::STATUS_RUN);
	}
}

int CGame::GetActivePlayers()
{
	if(GetGameMode()==GAME_MODE_1PLAYER)
		return(1);
	else if(GetGameMode()==GAME_MODE_2PLAYER)	
		return(2);
	return(0);
}

//Load tetris data from VMU
bool CGame::Load(maple_device_t *dev)
{
	dbglog(DBG_INFO,"Load\n");
	uint8 *dest_data(NULL);
	int dest_size(0);
	vmu_pkg_t pkg;
	st_high_score hs[10];
	st_options options;

	dest_size=sizeof(hs)+sizeof(options)+100;
	dest_data=new uint8[dest_size];

	if(!m_pVMU->Read(dev,"tetris2.sys",&pkg))
		return(false);
	if(m_pVMU->BZDecompress(dest_data,&dest_size,pkg.data,pkg.data_len)!=0)
		return(false);

	memcpy(&hs,dest_data,sizeof(hs));
	GetHighScore()->Clear();
	for(int i=0;i<10;i++)
		GetHighScore()->Add(hs[i].name,hs[i].date,hs[i].score);

	memcpy(&options,&dest_data[sizeof(hs)],sizeof(options));

	SetAutoSave(options.autosave);
	SetPlayMusic(options.music);
	SetSound(options.sound);
	SetPal(options.pal);
	SetTVModeLoaded(true);

	if(m_iPlayers>0)
	{
		GetPlayer(0)->SetName(options.p1name);
		GetPlayer(0)->SetRumble(options.rumblep1);
	}
	if(m_iPlayers>1)
	{
		GetPlayer(1)->SetName(options.p2name);
		GetPlayer(1)->SetRumble(options.rumblep2);
	}
	SetCurrentTheme(GetThemeByPath(options.theme));
	return(true);
}

//Save tetris game data to VMU 
bool CGame::Save(maple_device_t *dev)
{
	dbglog(DBG_INFO,"Save\n");
	vmu_pkg_t	pkg;
	uint8 *pkg_out;
	int pkg_size(0),i(0);

	//Save highscore in struct
	st_high_score hs[10];
	CScore *pScore;
	pScore=GetHighScore()->GetScore();
	i=0;
	while(pScore!=NULL)
	{
		strcpy(hs[i].name,pScore->GetName());
		strcpy(hs[i].date,pScore->GetDate());
		hs[i].score=pScore->GetScore();
		pScore=pScore->GetNext();
		i++;
	}

	// Save all other options in a struct
	st_options options;
	options.autosave=m_bAutoSave;
	options.music=m_bMusic;
	options.sound=m_bSound;
	options.pal=m_bPal;
	strcpy(options.p1name,GetPlayer(0)->GetName());
	options.rumblep1=GetPlayer(0)->GetRumble();
	if(GetPlayers()>1)
	{
		strcpy(options.p2name,GetPlayer(1)->GetName());
		options.rumblep2=GetPlayer(1)->GetRumble();
	}
	else
	{
		strcpy(options.p2name,"Player 2");
		options.rumblep2=true;
	}
	strcpy(options.theme,m_pCurrentThemeInfo->GetPath());

	// Pack data
	int src_size=sizeof(hs)+sizeof(st_options);
	int dest_size=src_size+1000;
	uint8 *src_data=new uint8[src_size];
	uint8 *dest_data=new uint8[dest_size];

	memcpy((void*)src_data,&hs,sizeof(hs));
	memcpy((void*)&src_data[sizeof(hs)],&options,sizeof(options));

	if(m_pVMU->BZCompress(dest_data,&dest_size,src_data,src_size)!=0)
		return(false);

	//Build VMU package
	strcpy(pkg.desc_short, "Tetris 2 Save");
	strcpy(pkg.desc_long, "Tetris 2 Save");
	strcpy(pkg.app_id, "Tetris 2");

	pkg.icon_cnt = 1;
	pkg.icon_anim_speed = 0;
	pkg.icon_data = m_pVMU->LoadIcon("/rd/icon/tetris.bmp",pkg.icon_pal);
	pkg.eyecatch_type = VMUPKG_EC_NONE;

	pkg.data_len=dest_size;
	pkg.data=(uint8*)dest_data;
	vmu_pkg_build(&pkg,&pkg_out,&pkg_size);
	m_pVMU->Write(dev,"tetris2.sys",pkg_out,pkg_size);
	SetActiveVMU(dev);
	return(true);
}

void CGame::SetVMU(CVMU *vmu)
{
	if(m_pVMU!=NULL)
		delete m_pVMU;
	m_pVMU=vmu;
}
void CGame::PlaySound(int id, int vol, int pan)
{
  if(m_bSound)
	{
		if(vol==-1)
			vol=m_iSoundVolume;
		if(vol>255)
			vol=255;
		else if(vol<0)
			vol=0;
		m_pSound->Play(id,vol,pan);
	}
}

CThemeInfo* CGame::GetThemeByName(const char *name)
{
	CListItem *item=m_pThemeList->GetFirst();
	while(item!=NULL)
	{
		if(!strcmp(name,((CThemeInfo*)item->GetData())->GetName()))
			return((CThemeInfo*)item->GetData());
	}
	return(NULL);
}

CThemeInfo* CGame::GetThemeByPath(const char *path)
{
	CListItem *item=m_pThemeList->GetFirst();
	while(item!=NULL)
	{
		if(!strcmp(path,((CThemeInfo*)item->GetData())->GetPath()))
			return((CThemeInfo*)item->GetData());
		item=item->GetNext();
	}
	return(NULL);
}

CThemeInfo* CGame::GetThemeByPos(int pos)
{
	CListItem *item=m_pThemeList->GetFirst();
	int i=0;
	while((item!=NULL)&&(i!=pos))
	{
		item=item->GetNext();
		i++;
	};
	if(item!=NULL)
		return((CThemeInfo*)item->GetData());
	return(NULL);
}
