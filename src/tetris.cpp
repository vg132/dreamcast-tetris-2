#include "tetris.hpp"

CTetris* CTetris::m_pThis=NULL;
int CTetris::m_iLastCDStatus=CD_STATUS_OPEN;
int CTetris::m_iLastDiskType=-1;

CTetris::CTetris()
{
	m_pGame=NULL;
	m_pDraw=NULL;
	m_pControl=NULL;
	CTetris::m_pThis = this;
}

CTetris::~CTetris()
{
	if(m_pGame!=NULL)
		delete m_pGame;
	if(m_pDraw!=NULL)
		delete m_pDraw;
	if(m_pControl!=NULL)
		delete m_pControl;
}

void CTetris::CDCheck(uint32 code)
{
	int iStatus(0), iDiscType(0);
	if(cdrom_get_status(&iStatus, &iDiscType)<0)
    return;
	if((CTetris::m_iLastCDStatus==CD_STATUS_OPEN)&&(iStatus!=CTetris::m_iLastCDStatus))
	{
		CTetris::m_iLastCDStatus=iStatus;
		dbglog(DBG_INFO, "New Disc\n");
		thd_create(CDInit,NULL);
	}
	else if((iStatus==CD_STATUS_OPEN)&&(CTetris::m_iLastCDStatus!=CD_STATUS_OPEN))
	{
		m_pThis->m_pGame->SetMusic(NULL);
		CTetris::m_iLastCDStatus=iStatus;
		dbglog(DBG_INFO, "Disc Tray Open\n");
	}
}

void CTetris::Run()
{
	dbglog(DBG_INFO, "--Run()\n");
	unsigned long int frmctr(0);
	int i(0);
	//int iControls(0),i(0);
	CPlayer *m_pPlayer=NULL;

	//Create a control handeling object
	m_pControl=new CControl();

	//Init control for player one and setup display mode
	if(m_pGame->GetPlayers()>0)
		m_pControl->Respond(GetGame(),0,1);

	timer_spin_sleep(500);
	m_iCDHandler = vblank_handler_add(CDCheck);
	timer_spin_sleep(500);
	dbglog(DBG_INFO, "Start main loop\n");
	while(m_pGame->GetStatus()!=CGame::STATUS_EXIT)
	{
		for(i=0;i<m_pGame->GetPlayers();i++)
			m_pControl->Respond(m_pGame,i,frmctr);
		if(m_pGame->GetStatus()==CGame::STATUS_RUN)
		{
			for(i=0;i<m_pGame->GetActivePlayers();i++)
			{
				m_pPlayer=m_pGame->GetPlayer(i);
				if((m_pPlayer->GetField()->GetStatus()==CField::STATUS_NORMAL)&&
					((m_pPlayer->GetLastMove()+m_pPlayer->GetMoveSize())<frmctr))
				{
					if(m_pPlayer->GetField()->Move(CField::MOVE_DOWN)==false)
					{
						// Base points for moving a block down.
						m_pPlayer->AddPoints(10);
						int rows=m_pPlayer->GetField()->CheckFullRow();
						if(rows==0)
						{
							m_pPlayer->Rumble(0x011a7010);
							m_pGame->PlaySound(0);
							m_pPlayer->GetField()->NewBlock();
							m_pPlayer->GetField()->ClearPos();
							if(!m_pPlayer->GetField()->CanMove(CField::MOVE_DOWN))
							{
								m_pPlayer->GetField()->Put();
								m_pGame->SetHighScore();
								if(m_pGame->GetAutoSave())
									m_pGame->Save(m_pGame->GetActiveVMU());
								m_pGame->SetStatus(CGame::STATUS_GAMEOVER);
								m_pGame->SetMainMenuPos(2);
							}
							m_pGame->GetPlayer(0)->GetField()->Put();
						}
						else
						{
							m_pPlayer->Rumble(0x02153810);
							m_pGame->PlaySound(2);
							switch(rows)
							{
							case 1:
								m_pPlayer->AddPoints(100*((m_pPlayer->GetLevel()/10)+1));
								break;
							case 2:
								m_pPlayer->AddPoints(300*((m_pPlayer->GetLevel()/10)+1));
								break;
							case 3:
								m_pPlayer->AddPoints(1200*((m_pPlayer->GetLevel()/10)+1));
								break;
							case 4:
								m_pPlayer->AddPoints(5100*((m_pPlayer->GetLevel()/10)+1));
								break;
							}
							m_pPlayer->SetRows(rows);
							// Only change background based on player 1's lines
							if(i==0)
								m_pDraw->Background(m_pPlayer->GetLines(4));
							if(m_pPlayer->GetLines(4)>=((m_pPlayer->GetLevel()+1)*10))
								m_pPlayer->SetLevel(m_pPlayer->GetLevel()+1);
						}
					}
					m_pPlayer->SetLastMove(frmctr);
				}
			}
		}
		m_pDraw->DrawScene();
		frmctr++;
	}
	vblank_handler_remove(m_iCDHandler);

	dbglog(DBG_INFO, "Exit Tetris\n");
}

int CTetris::Start()
{
	dbglog(DBG_INFO, "--Start()\n");
	Init();
	Run();
	return(0);
}

void CTetris::Init()
{
	m_pGame=new CGame();
	m_pDraw=new CDraw();

	m_pGame->SetDraw(m_pDraw);
	m_pDraw->SetGame(m_pGame);
	pvr_dma_init();
	m_pDraw->GLInit();
	m_pDraw->LoadInitTextures();
	m_pGame->SetStatus(CGame::STATUS_INIT);
	//Set video mode for init and tv mode screen
	if(vid_check_cable()==CT_VGA)
		vid_set_mode(DM_640x480_VGA, PM_RGB565);
	else if(flashrom_get_region()==FLASHROM_REGION_EUROPE)
		vid_set_mode(DM_640x480_PAL_IL,PM_RGB565);
	else
		vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
	m_pInitThread=thd_create(thd_Init,NULL);
	do
	{
		m_pDraw->DrawScene();
	}while(thd_by_tid(m_pInitThread->tid)!=NULL);
	m_pDraw->UnloadInitTextures();
}

void CTetris::thd_Init(void *v)
{
	//Init seed
	srand(rtc_unix_secs());

	//Add players (max 2), take the first two controls
	dbglog(DBG_INFO, "Add players\n");
	int iControls(0);
	char buffer[11];
	uint8 maple;
	cont_cond_t cond;
	for(int i=0;i<4;i++)
	{
		maple=maple_create_addr(i,0);
		if(cont_get_cond(maple,&cond)==0)
		{
			m_pThis->GetGame()->AddPlayer(new CPlayer());
			sprintf(buffer,"Player %d",iControls+1);
			m_pThis->GetGame()->GetPlayer(iControls)->SetName(buffer);
			m_pThis->GetGame()->GetPlayer(iControls)->SetField(new CField());
			m_pThis->GetGame()->GetPlayer(iControls)->SetControl(new CDCControl(maple));
			if(++iControls>=2)
				break;
		}
	}

	//Load themes
	CThemeHandler handler;
#ifdef _TETRIS_DEBUG_
	m_pThis->GetGame()->SetThemeList(handler.LoadThemes("/cd/theme_test"));
#elif _TETRIS_RELEASE_
	m_pThis->GetGame()->SetThemeList(handler.LoadThemes("/cd/themes"));
#endif

	//Autoload data from VMU
	m_pThis->AutoLoad();
	
	// Check if we loaded a theme from the VMU, if not load the default theme
	if(m_pThis->GetGame()->GetCurrentTheme()==NULL)
#ifdef _TETRIS_DEBUG_
		m_pThis->GetGame()->SetCurrentTheme(m_pThis->GetGame()->GetThemeByPath("/cd/theme_test/default/viperv6.theme"));
#elif _TETRIS_RELEASE_
		m_pThis->GetGame()->SetCurrentTheme(m_pThis->GetGame()->GetThemeByPath("/cd/themes/default/viperv6.theme"));
#endif

	//Load textures
	m_pThis->GetGame()->GetDraw()->LoadTheme();
	m_pThis->GetGame()->GetDraw()->LoadTextures();
}

//Find first VMU with Tetris save file on.
void CTetris::AutoLoad()
{
	dbglog(DBG_INFO, "Autoload from VMU\n");
	//Auto Load and set default memory card
	m_pThis->GetGame()->GetVMU()->Refresh();
	CVMUnit *m_pVMUnit=m_pThis->GetGame()->GetVMU()->GetFirstVMUnit();
	while(m_pVMUnit!=NULL)
	{
		if(m_pThis->GetGame()->Load(m_pVMUnit->GetVMU()))
		{
			m_pThis->GetGame()->SetActiveVMU(m_pVMUnit->GetVMU());
			break;
		}
		m_pVMUnit=m_pVMUnit->GetNext();
	}
}

void CTetris::CDInit(void *v)
{
	int iStatus, iDiscType;
	cdrom_reinit();
	do
	{
		thd_sleep(500);
		cdrom_get_status(&iStatus,&iDiscType);
	}while((iStatus!=CD_STATUS_STANDBY)&&(iStatus!=CD_STATUS_PAUSED)&&(iStatus!=CD_STATUS_NO_DISC));

	if(iStatus==CD_STATUS_NO_DISC)
	{
		dbglog(DBG_INFO, "No disc\n");
		return;
	}
	else if(iDiscType!=CD_CDDA)
	{
		dbglog(DBG_INFO,"Data Disc\n");
		CFileMusic* music=new CFileMusic();
		ReadDir("/cd",music);
		if(music->GetTracks()>0)
		{
			m_pThis->GetGame()->SetMusic(music);
		}
		else
		{
			delete music;
		}
	}
	if(iDiscType==CD_CDDA)
	{
		dbglog(DBG_INFO,"CDDA Disc\n");
		CDROM_TOC toc;
		cdrom_reinit();
		cdrom_read_toc(&toc,0);
		int track(0);
		CCdda *music=new CCdda();
		while(toc.entry[track]!=-1)
		{
			if(TOC_CTRL(toc.entry[track++])==0)
				music->AddTrack(track);
		}
		if(music->GetTracks()>0)
			m_pThis->GetGame()->SetMusic(music);
		else
			delete music;
	}
}

void CTetris::ReadDir(char *dir, CFileMusic *music)
{
	file_t d;
	dirent_t *de;
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
			ReadDir(tmp,music);
			delete tmp;
		}
		else
		{
			if((!stricmp(&tmp[strlen(tmp)-4],".mp3"))&&(strlen(tmp)<65))
				music->AddTrack(tmp);
		}
	}
	fs_close(d);
}
