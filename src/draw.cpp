#include "draw.hpp"

CDraw::CDraw()
{
	m_iInitCounter=0;
	m_iTVTestCounter=0;
	m_iMenuBorder=0;
	m_iTetrisLogo=0;
	m_iPreview=0;
	m_BackgroundHandler.Current=0;
	m_BackgroundHandler.iCurrent=0;
	m_BackgroundHandler.iBackgrounds=0;
}

CDraw::~CDraw()
{
	UnloadTheme();
}

//Init GL system
void CDraw::GLInit()
{
	dbglog(DBG_INFO, "--CDraw::GLInit()\n");
	glKosInit();

	SetPerspective();

	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_NONE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_FILTER, GL_FILTER_BILINEAR);

	LoadFontData();

#ifdef _TETRIS_DEBUG_
	LoadFont("/cd/master/graphics/font/arial_black.png",m_iBlackFont);
	LoadFont("/cd/master/graphics/font/arial_white.png",m_iWhiteFont);
	LoadFont("/cd/master/graphics/font/arial_blue.png",m_iBlueFont);
	LoadFont("/cd/master/graphics/font/arial_orange.png",m_iOrangeFont);
#elif _TETRIS_RELEASE_
	LoadFont("/cd/graphics/font/arial_black.png",m_iBlackFont);
	LoadFont("/cd/graphics/font/arial_white.png",m_iWhiteFont);
	LoadFont("/cd/graphics/font/arial_blue.png",m_iBlueFont);
	LoadFont("/cd/graphics/font/arial_orange.png",m_iOrangeFont);
#endif
}

// Loads textures that are used for the loading screen on startup
void CDraw::LoadInitTextures()
{
	dbglog(DBG_INFO, "--CDraw::LoadInitTextures()\n");
#ifdef _TETRIS_DEBUG_
	LoadPngTxrToVRAM("/cd/master/graphics/load/load.png",&m_iLoad[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/load/load1.png",&m_iLoad[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/load/load2.png",&m_iLoad[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/load/load3.png",&m_iLoad[3],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/load/load4.png",&m_iLoad[4],PNG_FULL_ALPHA);
#elif _TETRIS_RELEASE_
	LoadPngTxrToVRAM("/cd/graphics/load/load.png",&m_iLoad[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/load/load1.png",&m_iLoad[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/load/load2.png",&m_iLoad[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/load/load3.png",&m_iLoad[3],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/load/load4.png",&m_iLoad[4],PNG_FULL_ALPHA);
#endif
}

// Unload the textures when the game has loaded
void CDraw::UnloadInitTextures()
{
	for(int i=0;i<5;i++)
		glDeleteTextures(1,&m_iLoad[i]);
}

// Change background if needed.
void CDraw::Background(int line)
{
	if((m_BackgroundHandler.iCurrent!=-1)&&(m_Backgrounds[m_BackgroundHandler.iCurrent].StartLine<=line))
	{
		while((m_Backgrounds[m_BackgroundHandler.iCurrent+1].StartLine<=line)&&(m_BackgroundHandler.iCurrent+1<m_BackgroundHandler.iBackgrounds))
			m_BackgroundHandler.iCurrent++;

		if(m_BackgroundHandler.Current!=0)
			glDeleteTextures(1,&m_BackgroundHandler.Current);

		long texturesize = 512*512*sizeof (short);
		char* ptr = (char*)((unsigned long)m_Backgrounds[m_BackgroundHandler.iCurrent].Background.data + texturesize - 16*1024);
		icache_flush_range((uint32)&ptr,16384);

		LoadTxrToVRAM((void*)m_Backgrounds[m_BackgroundHandler.iCurrent].Background.data,&(m_BackgroundHandler.Current),1);
		m_BackgroundHandler.iCurrent++;
		if(m_BackgroundHandler.iCurrent>=m_BackgroundHandler.iBackgrounds)
			m_BackgroundHandler.iCurrent=-1;		
	}
}

void CDraw::ResetBackground()
{
	if(m_BackgroundHandler.Current!=0)
		glDeleteTextures(1,&m_BackgroundHandler.Current);
	m_BackgroundHandler.Current=0;
	m_BackgroundHandler.iCurrent=0;
}

void CDraw::LoadTextures()
{
	dbglog(DBG_INFO, "--CDraw::LoadTextures()\n");
	//Load background textures
#ifdef _TETRIS_DEBUG_
	LoadPngTxrToVRAM("/cd/master/graphics/misc/tvmode_test.png",&m_iTVTest);
	LoadPngTxrToVRAM("/cd/master/graphics/misc/title.png",&m_iTetrisLogo,PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/misc/field_1p.png",&m_iField[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/misc/field_2p1.png",&m_iField[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/misc/field_2p2.png",&m_iField[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/misc/info.png",&m_iThemeInfo,PNG_FULL_ALPHA);
#elif _TETRIS_RELEASE_
	LoadPngTxrToVRAM("/cd/graphics/misc/tvmode_test.png",&m_iTVTest);
	LoadPngTxrToVRAM("/cd/graphics/misc/title.png",&m_iTetrisLogo,PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/misc/field_1p.png",&m_iField[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/misc/field_2p1.png",&m_iField[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/misc/field_2p2.png",&m_iField[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/misc/info.png",&m_iThemeInfo,PNG_FULL_ALPHA);
#endif

	//Load tetris block textures
#ifdef _TETRIS_DEBUG_
	LoadPngTxrToVRAM("/cd/master/graphics/block/block1.png",&m_iBlock[0]);
	LoadPngTxrToVRAM("/cd/master/graphics/block/block2.png",&m_iBlock[1]);
	LoadPngTxrToVRAM("/cd/master/graphics/block/block3.png",&m_iBlock[2]);
	LoadPngTxrToVRAM("/cd/master/graphics/block/block4.png",&m_iBlock[3]);
	LoadPngTxrToVRAM("/cd/master/graphics/block/block5.png",&m_iBlock[4]);
	LoadPngTxrToVRAM("/cd/master/graphics/block/block6.png",&m_iBlock[5]);
	LoadPngTxrToVRAM("/cd/master/graphics/block/block7.png",&m_iBlock[6]);
	LoadPngTxrToVRAM("/cd/master/graphics/block/block8.png",&m_iBlock[7]);
#elif _TETRIS_RELEASE_
	LoadPngTxrToVRAM("/cd/graphics/block/block1.png",&m_iBlock[0]);
	LoadPngTxrToVRAM("/cd/graphics/block/block2.png",&m_iBlock[1]);
	LoadPngTxrToVRAM("/cd/graphics/block/block3.png",&m_iBlock[2]);
	LoadPngTxrToVRAM("/cd/graphics/block/block4.png",&m_iBlock[3]);
	LoadPngTxrToVRAM("/cd/graphics/block/block5.png",&m_iBlock[4]);
	LoadPngTxrToVRAM("/cd/graphics/block/block6.png",&m_iBlock[5]);
	LoadPngTxrToVRAM("/cd/graphics/block/block7.png",&m_iBlock[6]);
	LoadPngTxrToVRAM("/cd/graphics/block/block8.png",&m_iBlock[7]);
#endif

	//Next
#ifdef _TETRIS_DEBUG_
	LoadPngTxrToVRAM("/cd/master/graphics/next/l.png",&m_iNextImg[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/next/rl.png",&m_iNextImg[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/next/z.png",&m_iNextImg[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/next/rz.png",&m_iNextImg[3],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/next/i.png",&m_iNextImg[4],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/next/t.png",&m_iNextImg[5],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/master/graphics/next/o.png",&m_iNextImg[6],PNG_FULL_ALPHA);
#elif _TETRIS_RELEASE_
	LoadPngTxrToVRAM("/cd/graphics/next/l.png",&m_iNextImg[0],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/next/rl.png",&m_iNextImg[1],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/next/z.png",&m_iNextImg[2],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/next/rz.png",&m_iNextImg[3],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/next/i.png",&m_iNextImg[4],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/next/t.png",&m_iNextImg[5],PNG_FULL_ALPHA);
	LoadPngTxrToVRAM("/cd/graphics/next/o.png",&m_iNextImg[6],PNG_FULL_ALPHA);
#endif
/*
	uint32 msec1, msec2;
	timer_ms_gettime(NULL, &msec1);
	timer_ms_gettime(NULL, &msec2);
	pvr_mem_stats();
	malloc_stats();
*/
}

void CDraw::UnloadTheme()
{
	ResetBackground();
	for(int i=0;i<m_BackgroundHandler.iBackgrounds;i++)
		kos_img_free(&m_Backgrounds[i].Background,0);
	delete[] m_Backgrounds;
}

void CDraw::LoadTheme()
{
	//Load background textures from CD and Theme
	m_Backgrounds=new ThemeBackground[m_pGame->GetCurrentTheme()->GetNrOfBackgrounds()];
	m_BackgroundHandler.iBackgrounds=m_pGame->GetCurrentTheme()->GetNrOfBackgrounds();
	CBackground *bg=m_pGame->GetCurrentTheme()->GetFirstBackground();
	int i=0;
	while((bg!=NULL))
	{
		m_Backgrounds[i].StartLine=bg->GetStartLine();
		LoadPngTxrToRAM(bg->GetPath(),PNG_NO_ALPHA,&m_Backgrounds[i].Background);
		i++;
		bg=bg->GetNext();
	}
}

//Read font space data from text file
void CDraw::LoadFontData()
{
	uint32 size;
	char *data=NULL;

#ifdef _TETRIS_DEBUG_
	size=fs_load("/cd/master/graphics/font/font_size.txt",(void**)&data);
#elif _TETRIS_RELEASE_
	size=fs_load("/cd/graphics/font/font_size.txt",(void**)&data);
#endif
	if(size!=-1)
	{
		char ch;
		char buffer[10];
		uint32 iLoop(0),i(0),tmp(0);

		while(i<strlen(data))
		{
			ch=data[i++];
			if(ch!=',')
			{
				buffer[iLoop++]=ch;
				buffer[iLoop]='\0';
			}
			else
			{
				m_iFontSize[tmp++]=atoi(buffer);
				iLoop=0;
			}
		}
	}
	if(data!=NULL)
		delete data;
}

//Read font texture and move all chars into own texture
void CDraw::LoadFont(char *fn, GLuint *font)
{
	kos_img_t img;
	png_to_img(fn,PNG_FULL_ALPHA,&img);
	pvr_ptr_t txr_addr;

	char *tmp_img,*data;
	unsigned int blocks(16),characters(0);
	tmp_img=(char*)malloc((img.w*img.h)*2);
	data=(char*)malloc(((img.w/blocks)*(img.h/blocks))*2);
	memcpy(tmp_img,img.data,img.byte_count);

	unsigned int bh(0),bw(0),h(0),w(0);
	while(bh<6)
	{
		while(bw<blocks)
		{
			while(h<(img.w/blocks))
			{
				while(w<((img.w/blocks)*2))
				{
					data[(h*((img.w/blocks)*2))+w]=tmp_img[((bh*(img.w*((img.w/blocks)*2)))+(h*(img.w*2))+(bw*((img.w/blocks)*2)))+w];
					w++;
				}
				w=0;
				h++;
			}
			txr_addr=pvr_mem_malloc(((img.w/blocks)*(img.h/blocks))*2);
			pvr_txr_load_ex((void*)data,txr_addr,img.w/blocks,img.h/blocks,PVR_TXRLOAD_16BPP);
			glGenTextures(1,&font[(bh*blocks)+bw]);
			glBindTexture(GL_TEXTURE_2D, font[(bh*blocks)+bw]);
			glKosTex2D(GL_ARGB4444_TWID,img.w/blocks,img.h/blocks,txr_addr);
			h=0;
			characters++;
			bw++;
		}
		bw=0;
		bh++;
	}
	free(data);
	free(tmp_img);
	kos_img_free(&img,0);
}

//Draw current scene
void CDraw::DrawScene()
{
	char* buffer=new char[20];
	glKosBeginFrame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	if(m_pGame->GetStatus()==CGame::STATUS_INIT)
	{
		DrawInit();
	}
	else if((m_pGame->GetStatus()==CGame::STATUS_RUN)||(m_pGame->GetStatus()==CGame::STATUS_PAUSE)||(m_pGame->GetStatus()==CGame::STATUS_GAMEOVER))
	{
		DrawBackground(m_BackgroundHandler.Current);
		if(m_pGame->GetGameMode()==CGame::GAME_MODE_1PLAYER)
		{
			if((m_pGame->GetStatus()!=CGame::STATUS_PAUSE)&&(m_pGame->GetStatus()!=CGame::STATUS_GAMEOVER))
				DrawField(m_pGame->GetPlayer(0)->GetField(),ALIGN_CENTER);
			glKosFinishList();
			glDepthMask(GL_TRUE);
			DrawBorder(0,1);
		}
		else if(m_pGame->GetGameMode()==CGame::GAME_MODE_2PLAYER)
		{
			if((m_pGame->GetStatus()!=CGame::STATUS_PAUSE)&&(m_pGame->GetStatus()!=CGame::STATUS_GAMEOVER))
			{
				DrawField(m_pGame->GetPlayer(0)->GetField(),CDraw::ALIGN_LEFT);
				DrawField(m_pGame->GetPlayer(1)->GetField(),CDraw::ALIGN_RIGHT);
			}
			glKosFinishList();
			if((m_pGame->GetGameType()==CGame::GAME_TYPE_FAST_COMBAT)||(m_pGame->GetGameType()==CGame::GAME_TYPE_COMBAT))
			{
				DrawPowerMeter(0);
				DrawPowerMeter(1);
			}
			glDepthMask(GL_TRUE);
			DrawBorder(0,2);
			DrawBorder(1,2);
		}
		if(m_pGame->GetStatus()==CGame::STATUS_PAUSE)
		{
			DrawPause();
		}
		else if(m_pGame->GetStatus()==CGame::STATUS_GAMEOVER)
		{
			DrawGameOver();
		}
	}
	else if((m_pGame->GetStatus()==CGame::STATUS_CREDITS)||
					(m_pGame->GetStatus()==CGame::STATUS_VMU_SAVE_MENU)||
					(m_pGame->GetStatus()==CGame::STATUS_VMU_LOAD_MENU)||
					(m_pGame->GetStatus()==CGame::STATUS_HIGH_SCORE)||
					(m_pGame->GetStatus()==CGame::STATUS_MODE_SELECT)||
					(m_pGame->GetStatus()==CGame::STATUS_MAIN_MENU)||
					(m_pGame->GetStatus()==CGame::STATUS_OPTION_MENU)||
					(m_pGame->GetStatus()==CGame::STATUS_THEME_BROWSER)||
					(m_pGame->GetStatus()==CGame::STATUS_THEME_BROWSER_INFO)||
					(m_pGame->GetStatus()==CGame::STATUS_TVMODE_SELECT))
	{
		DrawTitleMenu();
		glDepthMask(GL_TRUE);
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_TVMODE_TEST)
	{
		DrawTVModeTest();
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_THEME_BROWSER_PREVIEW)
	{
		DrawBackgroundPreview();
	}
	glKosFinishFrame();
	delete[] buffer;
}

void CDraw::DrawTVModeTest()
{
	DrawBackground(m_iTVTest);
	glKosFinishList();
	m_iTVTestCounter++;
	if(m_iTVTestCounter>300)
	{
		m_iTVTestCounter=0;
		m_pGame->SetStatus(CGame::STATUS_TVMODE_SELECT);
		vid_set_mode(DM_640x480_PAL_IL,PM_RGB565);
	}
}

//Draw load tetris screen
void CDraw::DrawInit()
{
	DrawBackground(m_iLoad[0]);
	glKosFinishList();
	
	PushMatrices();
	SetOrtho();
	
	m_iInitCounter++;

	if(m_iInitCounter<15)
	{
		glBindTexture(GL_TEXTURE_2D, m_iLoad[4]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(290.0f,220.0f,10.0f,10.0f);

		glBindTexture(GL_TEXTURE_2D, m_iLoad[1]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(310.0f,220.0f,10.0f,10.0f);

		glBindTexture(GL_TEXTURE_2D, m_iLoad[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(330.0f,220.0f,10.0f,10.0f);

		glBindTexture(GL_TEXTURE_2D, m_iLoad[3]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(350.0f,220.0f,10.0f,10.0f);
	}
	else if(m_iInitCounter<30)
	{
		glBindTexture(GL_TEXTURE_2D, m_iLoad[3]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(290.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[4]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(310.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[1]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(330.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(350.0f,220.0f,10.0f,10.0f);
	}
	else if(m_iInitCounter<45)
	{
		glBindTexture(GL_TEXTURE_2D, m_iLoad[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(290.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[3]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(310.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[4]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(330.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[1]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(350.0f,220.0f,10.0f,10.0f);
	}
	else if(m_iInitCounter<60)
	{
		glBindTexture(GL_TEXTURE_2D, m_iLoad[1]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(290.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[2]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(310.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[3]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(330.0f,220.0f,10.0f,10.0f);
		glBindTexture(GL_TEXTURE_2D, m_iLoad[4]);
		glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		Rect(350.0f,220.0f,10.0f,10.0f);
	}
	if(m_iInitCounter>60)
		m_iInitCounter=0;

	PopMatrices();
}

void CDraw::DrawTVModeSelect()
{
	if(m_pGame->GetTVMenuPos()==0)
	{
		DrawString("\00350Hz",35.0f,3,150.0f,254.0f,CDraw::ALIGN_LEFT,m_iWhiteFont);
		DrawString("\002Can be displayed on all PAL televisions.",20.0f,2,82.0f,204.0f,CDraw::ALIGN_LEFT);
	}
	else
	{
		DrawString("\00250Hz",35.0f,3,150.0f,254.0f,CDraw::ALIGN_LEFT);
	}
	if(m_pGame->GetTVMenuPos()==1)
	{
		DrawString("\00360Hz",35.0f,3,280.0f,254.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
		DrawString("\002Requires a televisions that supports 60Hz.",20.0f,2,82.0f,204.0f,CDraw::ALIGN_LEFT);
	}
	else
	{
		DrawString("\00260Hz",35.0f,3,280.0f,254.0f,CDraw::ALIGN_LEFT);
	}
	if(m_pGame->GetTVMenuPos()==2)
	{
		DrawString("\003Test",35.0f,3,480.0f,254.0f,CDraw::ALIGN_LEFT);
		DrawString("\002A picture of Tetris will be displayed for 5 seconds.",20.0f,2,82.0f,204.0f,CDraw::ALIGN_LEFT);
		DrawString("\002If the picture appers, your TV supports 60Hz.",20.0f,2,82.0f,184.0f,CDraw::ALIGN_LEFT);
		DrawString("\002If nothing appears, your tv can only display at 50Hz.",20.0f,2,82.0f,164.0f,CDraw::ALIGN_LEFT);
	}
	else
	{
		DrawString("\002Test",35.0f,3,480.0f,254.0f,CDraw::ALIGN_LEFT);
	}
	DrawInfo("\003A: \002Select option");
}

void CDraw::DrawVMULoad()
{
	m_pGame->GetVMU()->Refresh();
	CVMUnit *pVMUnit=m_pGame->GetVMU()->GetFirstVMUnit();
	if(pVMUnit==NULL)
	{
		DrawString("\002No Visual Memory Unit (VMU) Found",20.0f,2,320.0f,204.0f,CDraw::ALIGN_CENTER);
		DrawInfo("\003Y: \002Back");
	}
	else
	{
		DrawString("\002Select VMU to load from",20.0f,2,320.0f,204.0f,CDraw::ALIGN_CENTER);
		int i(0);
		char buffer[50];
		while(pVMUnit!=NULL)
		{
			sprintf(buffer,"%s - %d Free Blocks.",m_pGame->GetVMU()->GetVMUName(pVMUnit->GetVMU()),pVMUnit->GetFreeBlocks());
			if(i==m_pGame->GetVMUMenuPos())
				DrawString(buffer,20.0f,2,320.0f,174-(i*20),CDraw::ALIGN_CENTER,m_iBlueFont);
			else
				DrawString(buffer,20.0f,2,320.0f,174-(i*20),CDraw::ALIGN_CENTER,m_iBlackFont);
			pVMUnit=pVMUnit->GetNext();
		}
		DrawInfo("\003A: \002Load \003Y: \002Back");
	}
}

void CDraw::DrawVMUSave()
{
	m_pGame->GetVMU()->Refresh();
	CVMUnit *pVMUnit=m_pGame->GetVMU()->GetFirstVMUnit();
	if(pVMUnit==NULL)
	{
		DrawString("\002No Visual Memory Unit (VMU) Found",20.0f,2,320.0f,204.0f,CDraw::ALIGN_CENTER);
		DrawInfo("\003Y: \002Back");
	}
	else
	{
		DrawString("\002Select VMU to save to",20.0f,2,320.0f,204.0f,CDraw::ALIGN_CENTER);
		int i(0);
		char buffer[50];
		while(pVMUnit!=NULL)
		{
			sprintf(buffer,"%s - %d Free Blocks.",m_pGame->GetVMU()->GetVMUName(pVMUnit->GetVMU()),pVMUnit->GetFreeBlocks());
			if(i==m_pGame->GetVMUMenuPos())
				DrawString(buffer,20.0f,2,320.0f,174-(i*20),CDraw::ALIGN_CENTER,m_iBlueFont);
			else
				DrawString(buffer,20.0f,2,320.0f,174-(i*20),CDraw::ALIGN_CENTER,m_iBlackFont);
			pVMUnit=pVMUnit->GetNext();
		}
		DrawInfo("\003A: \002Save \003Y: \002Back");
	}
}

void CDraw::LoadPreviewBackground(const char *path)
{
	if(m_iPreview!=0)
		glDeleteTextures(1,&m_iPreview);
	LoadPngTxrToVRAM(path,&m_iPreview);
}

void CDraw::DrawBackgroundPreview()
{
	DrawBackground(m_iPreview);
	glKosFinishList();
	
	PushMatrices();
	SetOrtho();
	glBindTexture(GL_TEXTURE_2D, m_iThemeInfo);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	Rect(7.0f,304.0f,128.0f,128.0f);
	PopMatrices();
}

void CDraw::UnloadPreviewBackground()
{
	if(m_iPreview!=0)
		glDeleteTextures(1,&m_iPreview);
	m_iPreview=0;
}

void CDraw::DrawThemeInformation()
{
	CThemeInfo *info=m_pGame->GetPreviewTheme();

	char buffer[10000];
	strcpy(buffer,"\003Name: \002");
	strcat(buffer,info->GetName());
	DrawString(buffer,20.0f,2,320.0f,204.0f,CDraw::ALIGN_CENTER);
	strcpy(buffer,"\003Author: \002");
	strcat(buffer,info->GetAuthor());
	DrawString(buffer,20.0f,2,320.0f,184.0f,CDraw::ALIGN_CENTER);
	strcpy(buffer,"\003Email: \002");
	strcat(buffer,info->GetEmail());
	DrawString(buffer,20.0f,2,320.0f,164.0f,CDraw::ALIGN_CENTER);
	strcpy(buffer,"\003URL: \002");
	strcat(buffer,info->GetURL());
	DrawString(buffer,20.0f,2,320.0f,144.0f,CDraw::ALIGN_CENTER);

	DrawString("Description",20.0f,2,320.0f,124.0f,CDraw::ALIGN_CENTER,m_iBlueFont);
	strcpy(buffer,info->GetDescription());

	int endPos(0),startPos(0), len(strlen(buffer));
	float line(104.0f);
	char *descText=new char[46];

	while(endPos<len)
	{
		while((buffer[endPos]==' ')&&(endPos<len))
			endPos++;
		startPos=endPos;
		endPos+=45;
		if(endPos>len)
		{
			endPos=len;
		}
		else
		{
			int k(0);
			while(((buffer[endPos]!=' ')&&(buffer[endPos]!='\0'))&&(++k<25))
				endPos--;
		}
		strncpy(descText,&buffer[startPos],endPos-startPos);
		descText[endPos-startPos]='\0';
		DrawString(descText,20.0f,2,320.0f,line,CDraw::ALIGN_CENTER,m_iBlackFont);
		line-=20.0f;
	}
	DrawInfo("\003B: \002Select theme \003A: \002Preview theme \003Y: \002Back");
}

void CDraw::DrawThemeBrowser()
{
	CListItem *item=m_pGame->GetThemeList()->GetFirst();
	int i=0;
	int base=0;
	int menuPos=m_pGame->GetThemeBrowserMenuPos();
	char buffer[100];

	if((menuPos>6)&&(m_pGame->GetThemeList()->GetItems()>10))
	{
		base=menuPos-7;
		for(i=0;i<base;i++)
			item=item->GetNext();
	}
	i=0;
	while((item!=NULL)&&(i<10))
	{
		(menuPos==(i+base))?strcpy(buffer,"\003"):strcpy(buffer,"\002");
		strcat(buffer,((CThemeInfo*)item->GetData())->GetName());
		if(!strcmp(m_pGame->GetCurrentTheme()->GetName(),((CThemeInfo*)item->GetData())->GetName()))
			strcat(buffer," *");
		DrawString(buffer,20.0f,2,320.0f,204.0f-(20*i),CDraw::ALIGN_CENTER);
		i++;
		item=item->GetNext();
	};
	DrawInfo("\003A: \002About \003Y: \002Back");
}

void CDraw::DrawOptionMenu()
{
	char buffer[100];
	float bottom=204.0f;
	(m_pGame->GetOptionMenuPos()==0)?strcpy(buffer,"\003Theme Browser"):strcpy(buffer,"\002Theme Browser");
	DrawString(buffer,20.0f,2,320.0f,bottom,CDraw::ALIGN_CENTER);
	bottom-=20.0f;
	(m_pGame->GetOptionMenuPos()==1)?strcpy(buffer,"\003Sound: "):strcpy(buffer,"\002Sound: ");
	(m_pGame->GetSound())?strcat(buffer,"On"):strcat(buffer,"Off");
	DrawString(buffer,20.0f,2,320.0f,bottom,CDraw::ALIGN_CENTER);
	bottom-=20.0f;
	(m_pGame->GetOptionMenuPos()==2)?strcpy(buffer,"\003Music: "):strcpy(buffer,"\002Music: ");
	(m_pGame->GetPlayMusic())?strcat(buffer,"On"):strcat(buffer,"Off");
	DrawString(buffer,20.0f,2,320.0f,bottom,CDraw::ALIGN_CENTER);
	bottom-=20.0f;
	(m_pGame->GetOptionMenuPos()==3)?strcpy(buffer,"\003Rumble P1: "):strcpy(buffer,"\002Rumble P1: ");
	(m_pGame->GetPlayer(0)->GetRumble())?strcat(buffer,"On"):strcat(buffer,"Off");
	DrawString(buffer,20.0f,2,320.0f,bottom,CDraw::ALIGN_CENTER);
	bottom-=20.0f;
	if(m_pGame->GetPlayers()>1)
	{
		(m_pGame->GetOptionMenuPos()==4)?strcpy(buffer,"\003Rumble P2: "):strcpy(buffer,"\002Rumble P2: ");
		(m_pGame->GetPlayer(1)->GetRumble())?strcat(buffer,"On"):strcat(buffer,"Off");
		DrawString(buffer,20.0f,2,320.0f,bottom,CDraw::ALIGN_CENTER);
		bottom-=20.0f;
	}
	(m_pGame->GetOptionMenuPos()==5)?strcpy(buffer,"\003Autosave: "):strcpy(buffer,"\002Autosave: ");
	(m_pGame->GetAutoSave())?strcat(buffer,"On"):strcat(buffer,"Off");
	DrawString(buffer,20.0f,2,320.0f,bottom,CDraw::ALIGN_CENTER);
	bottom-=20.0f;
	(m_pGame->GetOptionMenuPos()==6)?strcpy(buffer,"\003TV Mode"):strcpy(buffer,"\002TV Mode");
	DrawString(buffer,20.0f,2,320.0f,bottom,CDraw::ALIGN_CENTER);

	DrawInfo("\003A: \002Select option \003Y: \002Back");
}

void CDraw::DrawCredits()
{
	DrawString("\003Programming, Graphics and Testing:\002 Viktor Gars",20.0f,2,56.0f,204.0f,CDraw::ALIGN_LEFT);
	DrawString("\003Backgrounds:\002 Jens Tappendorf, http://viperv6.deviantart.com/",20.0f,2,56.0f,184.0f,CDraw::ALIGN_LEFT);
	DrawString("\003Special Thanks",20.0f,2,56.0f,164.0f,CDraw::ALIGN_LEFT);
	DrawString("\002Dan Potter",20.0f,2,56.0f,144.0f,CDraw::ALIGN_LEFT);
	DrawString("\002Roger Cattermle",20.0f,2,56.0f,124.0f,CDraw::ALIGN_LEFT);
	DrawString("\002Takayama Fumihiko",20.0f,2,56.0f,104.0f,CDraw::ALIGN_LEFT);
	DrawString("\002Everyone on DCDev and Cadcdev-kallistios mailing lists",20.0f,2,56.0f,84.0f,CDraw::ALIGN_LEFT);
	DrawString("\002Kamjin and SinisterTengu for Puru Puru support.",20.0f,2,56.0f,64.0f,CDraw::ALIGN_LEFT);
	DrawString("\003Web:\002 http://www.vgsoftware.com/",20.0f,2,56.0f,44.0f,CDraw::ALIGN_LEFT);
	DrawInfo("\003Y: \002Back");
}

void CDraw::DrawGameOver()
{
	PushMatrices();
	SetOrtho();
	if(m_pGame->GetGameMode()==CGame::GAME_MODE_1PLAYER)
	{
		DrawString("\001Game Over",25.0f,2,311.0f,225.1f,CDraw::ALIGN_CENTER);
		DrawString("\001Single:",20.0f,2,264.0f,200.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Double:",20.0f,2,264.0f,180.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Triple:",20.0f,2,264.0f,160.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Tetris:",20.0f,2,264.0f,140.0f,CDraw::ALIGN_LEFT);

		char buffer[10];
		for(int i=0;i<4;i++)
		{
			sprintf(buffer,"\001%d",m_pGame->GetPlayer(0)->GetLines(i));
			DrawString(buffer,20.0f,2,361.0f,200.0f-(i*20),CDraw::ALIGN_RIGHT);
		}
	}
	else
	{
		DrawString("\001Game Over",25.0f,2,207.0f,225.1f,CDraw::ALIGN_CENTER);
		DrawString("\001Single:",20.0f,2,160.0f,200.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Double:",20.0f,2,160.0f,180.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Triple:",20.0f,2,160.0f,160.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Tetris:",20.0f,2,160.0f,140.0f,CDraw::ALIGN_LEFT);

		char buffer[10];
		int i(0);
		for(i=0;i<4;i++)
		{
			sprintf(buffer,"\001%d",m_pGame->GetPlayer(0)->GetLines(i));
			DrawString(buffer,20.0f,2,257.0f,200.0f-(i*20),CDraw::ALIGN_RIGHT);
		}

		DrawString("\001Game Over",25.0f,2,444.0f,225.1f,CDraw::ALIGN_CENTER);
		DrawString("\001Single:",20.0f,2,397.0f,200.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Double:",20.0f,2,397.0f,180.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Triple:",20.0f,2,397.0f,160.0f,CDraw::ALIGN_LEFT);
		DrawString("\001Tetris:",20.0f,2,397.0f,140.0f,CDraw::ALIGN_LEFT);

		for(i=0;i<4;i++)
		{
			sprintf(buffer,"\001%d",m_pGame->GetPlayer(1)->GetLines(i));
			DrawString(buffer,20.0f,2,494.0f,200.0f-(i*20),CDraw::ALIGN_RIGHT);
		}
	}
	PopMatrices();
}

void CDraw::DrawPause()
{
	PushMatrices();
	SetOrtho();
	int Right(0);
	if(m_pGame->GetGameMode()==CGame::GAME_MODE_1PLAYER)
		Right=108;
	else if((m_pGame->GetGameMode()==CGame::GAME_MODE_2PLAYER)&&(m_pGame->GetPlayer(1)->GetPaused()))
		Right=237;

	DrawString("\001Pause",25.0f,2,207.0f+Right,225.0f,CDraw::ALIGN_CENTER);
	if(m_pGame->GetPauseMenuPos()==0)
	{
		DrawString("\003Continue",20.0f,2,207.0f+Right,200.0f,CDraw::ALIGN_CENTER);
		DrawString("\001Exit",20.0f,2,207.0f+Right,180.0f,CDraw::ALIGN_CENTER);
	}
	else
	{
		DrawString("\001Continue",20.0f,2,207.0f+Right,200.0f,CDraw::ALIGN_CENTER);
		DrawString("\003Exit",20.0f,2,207.0f+Right,180.0f,CDraw::ALIGN_CENTER);
	}		
	PopMatrices();
}

void CDraw::DrawBorder(int player, int players)
{
	PushMatrices();
	SetOrtho();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	char buffer[12];

	for(;player<players;player++)
	{
		//Border
		if(players==1)
		{
			glBindTexture(GL_TEXTURE_2D, m_iField[0]);
			glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			Rect(64.0f,-33.0f,512.0f,512.0f);
		}
		else if(player==0)
		{
			glBindTexture(GL_TEXTURE_2D, m_iField[1]);
			glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			Rect(-53.0f,-33.0f,512.0f,512.0f);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, m_iField[2]);
			glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			Rect(180.0f,-33.0f,512.0f,512.0f);
		}

		//Next
		if((m_pGame->GetPlayer(player)->GetShowNext())&&(!m_pGame->GetStatus()!=CGame::STATUS_PAUSE))
		{
			glBindTexture(GL_TEXTURE_2D, m_iNextImg[m_pGame->GetPlayer(player)->GetField()->GetNextBlock(1,1)]);
			glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			if(players==1)
				Rect(430.0f,304.0f,64.0f,64.0f);
			else if(player==0)
				Rect(29.0f,301.0f,64.0f,64.0f);
			else
				Rect(543.0f,301.0f,64.0f,64.0f);
		}

		//Player name
		if(players==1)
			DrawString(m_pGame->GetPlayer(player)->GetDisplayName(),16,2,240.0f,404.0f,CDraw::ALIGN_LEFT,m_iWhiteFont);
		else if(player==0)
			DrawString(m_pGame->GetPlayer(player)->GetDisplayName(),16,2,122.0f,404.0f,CDraw::ALIGN_LEFT,m_iWhiteFont);
		else
			DrawString(m_pGame->GetPlayer(player)->GetDisplayName(),16,2,357.0f,404.0f,CDraw::ALIGN_LEFT,m_iWhiteFont);

		//Points
		sprintf(buffer,"%d",m_pGame->GetPlayer(player)->GetPoints());
		if(players==1)
			DrawString(buffer,16,2,219.0f,249.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);
		else if(player==0)
			DrawString(buffer,16,2,102.0f,153.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);
		else
			DrawString(buffer,16,2,618.0f,152.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);

		//Level
		sprintf(buffer,"%d",m_pGame->GetPlayer(player)->GetLevel()+1);
		if(players==1)
			DrawString(buffer,16,2,219.0f,347.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);
		else if(player==0)
			DrawString(buffer,16,2,104.0f,251.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);
		else
			DrawString(buffer,16,2,572.0f,251.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);

		//Lines
		sprintf(buffer,"%d",m_pGame->GetPlayer(player)->GetLines(4));
		if(players==1)
			DrawString(buffer,16,2,219.0f,299.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);
		else if(player==0)
			DrawString(buffer,16,2,104.0f,202.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);
		else
			DrawString(buffer,16,2,572.0f,202.0f,CDraw::ALIGN_RIGHT,m_iWhiteFont);
	}
	PopMatrices();
}

void CDraw::DrawPowerMeter(int player)
{
	if(m_pGame->GetPlayer(player)->GetPower()>=100)
	{
		int flash=m_pGame->GetPlayer(player)->GetPowerFlash();
		m_pGame->GetPlayer(player)->SetPowerFlash(++flash);
		if(flash<15)
			return;
		else if(flash>30)
			m_pGame->GetPlayer(player)->SetPowerFlash(0);
	}

	if(player==0)
		glTranslatef(-0.3f,-4.9f,-17.0f);
	else if(player==1)
		glTranslatef(0.6f,-4.9f,-17.0f);
	
	// Black cover meter
	GLfloat bottom=0.02*m_pGame->GetPlayer(player)->GetPower();
	glBegin(GL_QUADS);
		glColor3f(0.0f,0.0f,0.0f);
		glVertex3f(-0.4f, 1.0f,0.1f);
		glVertex3f( 0.0f, 1.0f,0.1f);
		glVertex3f( 0.0f,(-1.0+bottom),0.1f);
		glVertex3f(-0.4f,(-1.0+bottom),0.1f);
	glEnd();

	// Power meter
	glBegin(GL_QUADS);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-0.4f, 1.0f,0.0f);
		glVertex3f( 0.0f, 1.0f,0.0f);
		glVertex3f( 0.0f,-1.0f,0.0f);
		glVertex3f(-0.4f,-1.0f,0.0f);
	glEnd();
	if(player==0)
		glTranslatef(0.3f,4.9f,17.0f);
	else if(player==1)
		glTranslatef(-0.6f,4.9f,17.0f);
}

void CDraw::DrawBackground(GLuint txr)
{
	PushMatrices();
	SetOrtho();
	glDisable(GL_KOS_AUTO_UV);
	glBindTexture(GL_TEXTURE_2D, txr);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBegin(GL_QUADS);
		//Top-Left
		glTexCoord2f(0.0f, 1.0f);glVertex3f(0.0f, 0.0f,0.0f);
		//Top-Right
		glTexCoord2f(1.0f, 1.0f);glVertex3f(640.0f, 0.0f,0.0f);
		//Bottom-Right
		glTexCoord2f(1.0f, 0.0f);glVertex3f(640.0f, 480.0f,0.0f);
		//Bottom-Left
		glTexCoord2f(0.0f, 0.0f);glVertex3f(0.0f, 480.0f,0.0f);
	glEnd();
	glEnable(GL_KOS_AUTO_UV);
	PopMatrices();
}

void CDraw::DrawField(CField *pField, int align)
{
	int x(0),y(0);
	int type(CField::BLOCK_COLOR_NONE);
	int diff=(pField->GetHeight()-pField->GetVisibleHeight());
	for(y=diff;y<pField->GetHeight();y++)
	{
		for(x=0;x<pField->GetWidth();x++)
		{
			type=pField->GetBlock(x,y);
			if((LOWORD2(type)!=CField::BLOCK_COLOR_NONE)&&(HIWORD2(type)!=CField::BLOCK_REMOVE))
			{
				DrawBlock(x,y-diff,LOWORD2(type),align);
			}
			else if((pField->GetStatus()==CField::STATUS_REMOVE_LINE)&&(HIWORD2(type)==CField::BLOCK_REMOVE))
			{
				if(pField->GetFlashCounter()>10)
					DrawBlock(x,y-diff,(LOWORD2(type)),align);
			}
		}
	}
	if(pField->GetStatus()==CField::STATUS_REMOVE_LINE)
	{
		pField->SetFlashCounter(pField->GetFlashCounter()+1);
		if(pField->GetFlashCounter()>=20)
			pField->ResetFlashCounter();
	}
}

void CDraw::DrawBlock(int x, int y, int txr, int align)
{
	float fX=-1.5f+(x*0.3)+0.15f;
	float fY=2.7f-(y*0.3)-0.15f;
	if(align==ALIGN_CENTER)
		glTranslatef(0.0f, 0.0f, -10.0f);
	else if(align==ALIGN_LEFT)
		glTranslatef(-2.0f, 0.0f, -10.0f);
	else if(align==ALIGN_RIGHT)
		glTranslatef(2.0f, 0.0f, -10.0f);

	glBindTexture(GL_TEXTURE_2D, m_iBlock[txr]);
	Block((fX-0.15f), (fY+0.15f),0.3f,0.3f);
	
	if(align==ALIGN_CENTER)
		glTranslatef(0.0f, 0.0f, 10.0f);
	else if(align==ALIGN_LEFT)
		glTranslatef(2.0f, 0.0f, 10.0f);
	else if(align==ALIGN_RIGHT)
		glTranslatef(-2.0f, 0.0f, 10.0f);
}

void CDraw::DrawHighScore()
{
	char buffer[20];
	CScore *pScore=m_pGame->GetHighScore()->GetScore();

	int i=0;
	while(pScore!=NULL)
	{
		DrawString(pScore->GetName(),20.0f,2,257.0f,204-(i*20),CDraw::ALIGN_RIGHT,m_iBlueFont);
		DrawString(pScore->GetDate(),20.0f,2,320.0f,204-(i*20),CDraw::ALIGN_CENTER,m_iBlackFont);

		sprintf(buffer,"%d",pScore->GetScore());
		DrawString(buffer,20.0f,2,383.0f,204-(i*20),CDraw::ALIGN_LEFT,m_iBlueFont);
		pScore=pScore->GetNext();
		i++;
	};
	DrawInfo("\003Y: \002Back");
}

void CDraw::DrawTitleMenu()
{
	char buffer[10];
	PushMatrices();
	SetOrtho();
	glKosFinishList();

	glBindTexture(GL_TEXTURE_2D, m_iTetrisLogo);
	glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	Rect(109.0f,32.0f,400.0f,400.0f);

	if(m_pGame->GetStatus()!=CGame::STATUS_TVMODE_SELECT)
	{
		//Draw Menu Item
		switch(m_pGame->GetMainMenuPos())
		{
			case 0:
				DrawString("1 Player",35.0f,2,320.0f,238.0f,CDraw::ALIGN_CENTER,(m_pGame->GetStatus()==CGame::STATUS_MAIN_MENU?m_iBlueFont:m_iBlackFont));
				break;
			case 1:
				DrawString("2 Players",35.0f,2,320.0f,238.0f,CDraw::ALIGN_CENTER,(m_pGame->GetStatus()==CGame::STATUS_MAIN_MENU?m_iBlueFont:m_iBlackFont));
				break;
			case 2:
				DrawString("High Score",35.0f,2,320.0f,238.0f,CDraw::ALIGN_CENTER,(m_pGame->GetStatus()==CGame::STATUS_MAIN_MENU?m_iBlueFont:m_iBlackFont));
				break;
			case 3:
				DrawString("Options",35.0f,2,320.0f,238.0f,CDraw::ALIGN_CENTER,(m_pGame->GetStatus()==CGame::STATUS_MAIN_MENU?m_iBlueFont:m_iBlackFont));
				break;
			case 4:
				DrawString("Load",35.0f,2,320.0f,238.0f,CDraw::ALIGN_CENTER,(m_pGame->GetStatus()==CGame::STATUS_MAIN_MENU?m_iBlueFont:m_iBlackFont));
				break;
			case 5:
				DrawString("Save",35.0f,2,320.0f,238.0f,CDraw::ALIGN_CENTER,(m_pGame->GetStatus()==CGame::STATUS_MAIN_MENU?m_iBlueFont:m_iBlackFont));
				break;
			case 6:
				DrawString("Credits",35.0f,2,320.0f,238.0f,CDraw::ALIGN_CENTER,(m_pGame->GetStatus()==CGame::STATUS_MAIN_MENU?m_iBlueFont:m_iBlackFont));
				break;
		}
	}
	if(m_pGame->GetStatus()==CGame::STATUS_MODE_SELECT)
	{
		for(int player=0;player<m_pGame->GetActivePlayers();player++)
		{
			int posX(0);
			if((player==0)&&(m_pGame->GetActivePlayers()==1))
				posX=200;
			else if(player==1)
				posX=365;
			else
				posX=45;

			if(!m_pGame->GetPlayer(player)->GetReady())
			{
				if(m_pGame->GetPlayer(player)->GetModeSelectPos()==0)
					DrawString("Name:",20.0f,2,posX+5.0f,187.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
				else
					DrawString("Name:",20.0f,2,posX+5.0f,187.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
				if(m_pGame->GetPlayer(player)->GetModeSelectPos()==1)
					DrawString("Speed:",20.0f,2,posX+5.0f,167.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
				else
					DrawString("Speed:",20.0f,2,posX+5.0f,167.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
				if(m_pGame->GetPlayer(player)->GetModeSelectPos()==2)
					DrawString("Height:",20.0f,2,posX+5.0f,147.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
				else
					DrawString("Height:",20.0f,2,posX+5.0f,147.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
				if(player==0)
				{
					if(m_pGame->GetPlayer(player)->GetModeSelectPos()==3)
						DrawString("Mode:",20.0f,2,posX+5,127.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
					else
						DrawString("Mode:",20.0f,2,posX+5,127.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
				}

				//Name
				for(int i=0;i<10;i++)
				{
					sprintf(buffer,"%c",m_pGame->GetPlayer(player)->GetLetter(i));
					if(i==m_pGame->GetPlayer(player)->GetCursorPos())
						DrawString(buffer,20.0f,2,posX+75+(16*i),187.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
					else
						DrawString(buffer,20.0f,2,posX+75+(16*i),187.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
					if(buffer[0]=='ö')
						break;
				}

				//Level
				for(int i=0;i<10;i++)
				{
					sprintf(buffer,"%d",i);
					if(m_pGame->GetPlayer(player)->GetLevelMenuPos()==i)
						DrawString(buffer,20.0f,4,posX+75+(13*i),167.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
					else
						DrawString(buffer,20.0f,4,posX+75+(13*i),167.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
				}

				//Height
				for(int i=0;i<6;i++)
				{
					sprintf(buffer,"%d",m_pGame->GetPlayer(player)->GetStartHeight(i));
					if(m_pGame->GetPlayer(player)->GetHeightMenuPos()==i)
						DrawString(buffer,20.0f,4,posX+75+(13*i),147.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
					else
						DrawString(buffer,20.0f,4,posX+75+(13*i),147.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
				}

				//Mode
				if(player==0)
				{
					strcpy(buffer,"Normal");
					if(m_pGame->GetPlayer(player)->GetGameModeMenuPos()==0)
						DrawString(buffer,20.0f,2,posX+75.0f,127.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
					else
						DrawString(buffer,20.0f,2,posX+75.0f,127.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
					strcpy(buffer,"Flip");
					if(m_pGame->GetPlayer(player)->GetGameModeMenuPos()==1)
						DrawString(buffer,20.0f,2,posX+145.0f,127.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
					else
						DrawString(buffer,20.0f,2,posX+145.0f,127.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
					if(m_pGame->GetGameMode()==CGame::GAME_MODE_2PLAYER)
					{
						strcpy(buffer,"Combat");
						if(m_pGame->GetPlayer(player)->GetGameModeMenuPos()==2)
							DrawString(buffer,20.0f,2,posX+190.0f,127.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
						else
							DrawString(buffer,20.0f,2,posX+190.0f,127.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
						strcpy(buffer,"Fast Combat");
						if(m_pGame->GetPlayer(player)->GetGameModeMenuPos()==3)
							DrawString(buffer,20.0f,2,posX+267.0f,127.0f,CDraw::ALIGN_LEFT,m_iBlueFont);
						else
							DrawString(buffer,20.0f,2,posX+267.0f,127.0f,CDraw::ALIGN_LEFT,m_iBlackFont);
					}
				}
			}
			else
			{
				DrawString(m_pGame->GetPlayer(player)->GetDisplayName(),30.0f,2,posX+115,177.0f,CDraw::ALIGN_CENTER,m_iBlackFont);
				DrawString("Ready!",30.0f,2,posX+115,147.0f,CDraw::ALIGN_CENTER,m_iBlackFont);
			}
		}
		DrawInfo("\003Start: \002Start Game \003Y: \002Back");
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_HIGH_SCORE)
	{
		DrawHighScore();
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_VMU_LOAD_MENU)
	{
		DrawVMULoad();
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_VMU_SAVE_MENU)
	{
		DrawVMUSave();
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_CREDITS)
	{
		DrawCredits();
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_OPTION_MENU)
	{
		DrawOptionMenu();
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_THEME_BROWSER)
	{
		DrawThemeBrowser();
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_THEME_BROWSER_INFO)
	{
		DrawThemeInformation();
	}
	else if(m_pGame->GetStatus()==CGame::STATUS_TVMODE_SELECT)
	{
		DrawTVModeSelect();
	}
	PopMatrices();
}

void CDraw::Rect(float x, float y, float w, float h, float z)
{
	glBegin(GL_QUADS);
		//Top Left
		glColor4f(1,0,0,0.7);glVertex3f(x,y+h,z);
		//Top Right
		glColor4f(0,1,0,0.7);glVertex3f(x+w,y+h,z);
		//Bottom Left
		glColor4f(0,0,1,0.7);glVertex3f(x+w,y,z);
		//Bottom Right
		glColor4f(1,1,1,0.7);glVertex3f(x,y,z);
	glEnd();
}

void CDraw::Block(float x, float y, float w, float h)
{
	glBegin(GL_QUADS);
		//Top
		glTexCoord2f(0.0f, 0.0f);glVertex3f((x), (y), 0.3f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f((x+w), (y), 0.3f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f((x+w), (y-h), 0.3f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f((x), (y-h), 0.3f);

		//Back
		glTexCoord2f(0.0f, 0.0f);glVertex3f((x), (y), 0.0f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f((x+w), (y), 0.0f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f((x+w), (y-h), 0.0f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f((x), (y-h), 0.0f);

		//Top
		glTexCoord2f(0.0f, 0.0f);glVertex3f((x), (y), 0.0f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f((x+w), (y), 0.0f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f((x+w), (y), 0.3f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f((x), (y), 0.3f);

		//Bottom
		glTexCoord2f(0.0f, 0.0f);glVertex3f((x), (y-h), 0.0f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f((x+w), (y-h), 0.0f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f((x+w), (y-h), 0.3f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f((x), (y-h), 0.3f);

		//Left
		glTexCoord2f(0.0f, 0.0f);glVertex3f((x), (y), 0.0f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f((x), (y), 0.3f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f((x), (y-h), 0.3f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f((x), (y-h), 0.0f);

		//Right
		glTexCoord2f(0.0f, 0.0f);glVertex3f((x+w), (y), 0.0f);
		glTexCoord2f(1.0f, 0.0f);glVertex3f((x+w), (y), 0.3f);
		glTexCoord2f(1.0f, 1.0f);glVertex3f((x+w), (y-h), 0.3f);
		glTexCoord2f(0.0f, 1.0f);glVertex3f((x+w), (y-h), 0.0f);
	glEnd();
}

int CDraw::GetStringWidth(const char *text, float size, int letter_spacing)
{
	int posX(0);
	float tmpCount(0.0f);
	for(unsigned int i=0;i<strlen(text);i++)
	{
		tmpCount=(float)(size/32)*GetLetterSize(text[i]);
		posX+=(int)(tmpCount+0.5);
		posX+=letter_spacing;
	}
	return(posX);
}

/*
\001=White font
\002=Black font
\003=Blue font
\004=Orange font
*/
void CDraw::DrawString(const char *text, float size, int letter_spacing, float x, float y, int align, GLuint *font)
{
	int posX((int)x), tmpSpace(0);
	float tmpCount(0.0f);
	bool space(false);
	if(font==NULL)
		font=m_iWhiteFont;
	if((align==CDraw::ALIGN_CENTER)||(align==CDraw::ALIGN_RIGHT))
	{
		int tmp(0);
		for(unsigned int i=0;i<strlen(text);i++)
		{
			tmpSpace=GetLetterSize(text[i]);
			tmpCount=(float)(size/32)*tmpSpace;
			tmp+=(int)(tmpCount+0.5);
			tmp+=letter_spacing;
		}
		if(align==CDraw::ALIGN_RIGHT)
			posX-=tmp;
		else
			posX-=tmp/2;
		align=CDraw::ALIGN_LEFT;
	}
	for(unsigned int i=0;i<strlen(text);i++)
	{
		space=false;
		if(text[i]==1)
		{
			font=m_iWhiteFont;
		}
		else if(text[i]==2)
		{
			font=m_iBlackFont;
		}
		else if(text[i]==3)
		{
			font=m_iBlueFont;
		}
		else if(text[i]==4)
		{
			font=m_iOrangeFont;
		}
		else
		{
			if((text[i]>32)&&(text[i]<127))
			{
				glBindTexture(GL_TEXTURE_2D, font[text[i]-33]);
				glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			}
			else if(text[i]=='ö')
			{
				glBindTexture(GL_TEXTURE_2D, font[94]);
				glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_REPLACE);
			}
			else
			{
				space=true;
			}
			if(align==CDraw::ALIGN_LEFT)
			{
				if(!space)
					Rect(posX,y,size,size);
				tmpCount=(float)(size/32)*GetLetterSize(text[i]);
				posX+=(int)(tmpCount+0.5);
				posX+=letter_spacing;
			}
			else if(align==CDraw::ALIGN_RIGHT)
			{
				if(!space)
					Rect(posX,y,size,size);
				tmpCount=(float)(size/32)*GetLetterSize(text[i]);
				posX-=(int)(tmpCount+0.5);
				posX-=letter_spacing;
			}
		}
	}
}

int CDraw::GetLetterSize(char ch)
{
	if((ch>31)&&(ch<127))
		return(m_iFontSize[ch-32]);
	else if(ch=='ö')
		return(m_iFontSize[95]);
	else
		return(4);
}

void CDraw::DrawInfo(char *str)
{
	DrawString(str,20.0f,2,632.0f,17.0f,CDraw::ALIGN_RIGHT);
}
