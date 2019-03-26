#include "control.hpp"

CControl::CControl()
{
}

CControl::~CControl()
{
}

void CControl::Respond(CGame *pGame, int iPlayer, unsigned long int frmctr)
{
	static int MusicDelay;
	pPlayer=pGame->GetPlayer(iPlayer);
	pControl=pPlayer->GetControl();
	if(!pControl->Init(frmctr))
		return;

#ifdef _TETRIS_DEBUG_
	if(iPlayer==1)
	{
		if(pControl->YDown())
			vid_screen_shot("/pc/tmp/kalle.ppm");
		if(pControl->DLeft(5))
			pGame->XX-=1.0f;
		else if(pControl->DRight(5))
			pGame->XX+=1.0f;
		else if(pControl->DUp(5))
			pGame->YY+=1.0f;
		else if(pControl->DDown(5))
			pGame->YY-=1.0f;
		else if(pControl->ADown())
		  dbglog(DBG_INFO, "XX: %f, YY: %f\n",pGame->XX,pGame->YY);
		if(!pControl->StartDown())
			return;
	}
#endif

	// Global music control.
	if((iPlayer==0)&&(pGame->GetMusic()!=NULL))
	{
		if((pControl->GetJoy1XChange())&&(pControl->GetJoy1X()>200))
		{
			pGame->GetMusic()->Next();
		}
		else if((pControl->GetJoy1XChange())&&(pControl->GetJoy1X()<55))
		{
			pGame->GetMusic()->Prev();
		}
		else if((pControl->GetJoy1YChange())&&(pControl->GetJoy1Y()<55))
		{
			if(pGame->GetMusic()->Playing())
				pGame->GetMusic()->Pause();
			else
				pGame->GetMusic()->Resume();
		}
		else if((pControl->GetJoy1YChange())&&(pControl->GetJoy1Y()>200))
		{
			pGame->GetMusic()->Stop();
		}
	}
	if((pGame->GetStatus()==CGame::STATUS_INIT))
	{
		// Set TV mode (50hz, 60hz or VGA) or ask if its a pal DC or X is hold down.
		// Dont ask if TV mode has been loaded from the VMU.
		if(vid_check_cable()==CT_VGA)
		{
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		}
		else if((!flashrom_get_region()==FLASHROM_REGION_EUROPE)&&(!pControl->X(0))&&(!pGame->GetTVModeLoaded()))
		{
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		}
		else if((pGame->GetTVModeLoaded())&&(!pControl->X(0)))
		{
			if(pGame->GetPal())
				vid_set_mode(DM_640x480_PAL_IL,PM_RGB565);
			else
				vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		}
		else
		{
			pGame->SetStatus(CGame::STATUS_TVMODE_SELECT);
		}
	}
	if((pGame->GetStatus()==CGame::STATUS_TVMODE_SELECT)&&(iPlayer==0))
	{
		if((pControl->DLeft(20))&&(pGame->GetTVMenuPos()>0))
		{
			pGame->PlaySound(1);
			pGame->SetTVMenuPos(pGame->GetTVMenuPos()-1);
		}
		if((pControl->DRight(20))&&(pGame->GetTVMenuPos()<2))
		{
			pGame->PlaySound(1);
			pGame->SetTVMenuPos(pGame->GetTVMenuPos()+1);
		}
		if(pControl->ADown())
		{
			if(pGame->GetTVMenuPos()==0)
			{
				vid_set_mode(DM_640x480_PAL_IL,PM_RGB565);
				pGame->SetPal(true);
				pGame->SetStatus(CGame::STATUS_MAIN_MENU);
			}
			else if(pGame->GetTVMenuPos()==1)
			{
				vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
				pGame->SetPal(false);
				pGame->SetStatus(CGame::STATUS_MAIN_MENU);
			}
			else if(pGame->GetTVMenuPos()==2)
			{
				vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
				pGame->SetStatus(CGame::STATUS_TVMODE_TEST);
			}
		}
	}
	else if((pGame->GetStatus()==CGame::STATUS_MAIN_MENU)&&(iPlayer==0))
	{
		if(pControl->DDown(20)&&(pGame->GetMainMenuPos()<6))
		{
			pGame->PlaySound(1);
			pGame->SetMainMenuPos(pGame->GetMainMenuPos()+1);
		}
		if(pControl->DUp(20)&&(pGame->GetMainMenuPos()>0))
		{
			pGame->PlaySound(1);
			pGame->SetMainMenuPos(pGame->GetMainMenuPos()-1);
		}
#ifdef _TETRIS_DEBUG_
		if(pControl->YDown())
			pGame->SetStatus(CGame::STATUS_EXIT);
#endif
		if(pControl->ADown())
		{
			if((pGame->GetMainMenuPos()==0)&&(pGame->GetPlayers()>0))
			{
				pGame->GetPlayer(0)->Reset();
				pGame->GetPlayer(0)->GetField()->NewBlock();
				pGame->GetPlayer(0)->SetLastMove(frmctr);
				pGame->GetPlayer(0)->SetModeSelectPos(0);
				pGame->GetPlayer(0)->SetPower(0);
				pGame->GetPlayer(0)->SetReady(false);
				pGame->GetPlayer(0)->SetPaused(false);
				pGame->SetStatus(pGame->STATUS_MODE_SELECT);
				pGame->SetGameMode(CGame::GAME_MODE_1PLAYER);
				pGame->GetDraw()->ResetBackground();
				pGame->GetDraw()->Background(1);
			}
			else if((pGame->GetMainMenuPos()==1)&&(pGame->GetPlayers()>1))
			{
				for(int i=0;i<2;i++)
				{
					pGame->GetPlayer(i)->Reset();
					pGame->GetPlayer(i)->GetField()->NewBlock();
					pGame->GetPlayer(i)->SetLastMove(frmctr);
					pGame->GetPlayer(i)->SetModeSelectPos(0);
					pGame->GetPlayer(0)->SetPower(0);
					pGame->GetPlayer(i)->SetReady(false);
					pGame->GetPlayer(i)->SetPaused(false);
				}
				pGame->SetStatus(CGame::STATUS_MODE_SELECT);
				pGame->SetGameMode(CGame::GAME_MODE_2PLAYER);
				pGame->GetDraw()->Background(1);
			}
			else if(pGame->GetMainMenuPos()==2)
			{
				pGame->SetStatus(CGame::STATUS_HIGH_SCORE);
			}
			else if(pGame->GetMainMenuPos()==3)
			{
				pGame->SetStatus(CGame::STATUS_OPTION_MENU);
			}
			else if(pGame->GetMainMenuPos()==4)
			{
				pGame->SetVMUMenuPos(0);
				pGame->SetStatus(CGame::STATUS_VMU_LOAD_MENU);
			}
			else if(pGame->GetMainMenuPos()==5)
			{
				pGame->SetVMUMenuPos(0);
				pGame->SetStatus(CGame::STATUS_VMU_SAVE_MENU);
			}
			else if(pGame->GetMainMenuPos()==6)
			{
				pGame->SetStatus(CGame::STATUS_CREDITS);
			}
		}
	}
	else if(pGame->GetStatus()==CGame::STATUS_RUN)
	{
		if(pPlayer->GetField()->GetStatus()==CField::STATUS_NORMAL)
		{
			if(pControl->DLeft(7))
				pPlayer->GetField()->Move(CField::MOVE_LEFT);
			if(pControl->DRight(7))
				pPlayer->GetField()->Move(CField::MOVE_RIGHT);
			if(pControl->DDown(2))
			{
				if(pPlayer->GetField()->Move(CField::MOVE_DOWN))
				{
					pPlayer->SetLastMove(frmctr);
					pPlayer->AddPoints(1);
				}
			}
			if(pControl->A(15))
				pPlayer->GetField()->Rotate(CField::ROTATE_LEFT);
			if(pControl->B(15))
			{
				if(pGame->GetGameType()==CGame::GAME_TYPE_FLIP)
				{
					pPlayer->GetField()->Flip();
				}
			}
			if((pControl->GetRightTrigger()==255)&&(pPlayer->GetPower()>=100)&&((pGame->GetGameType()==CGame::GAME_TYPE_COMBAT)||(pGame->GetGameType()==CGame::GAME_TYPE_FAST_COMBAT)))
			{
				if(iPlayer==0)
					pGame->GetPlayer(1)->GetField()->AddSolidBlocks(1);
				else
					pGame->GetPlayer(0)->GetField()->AddSolidBlocks(1);
				pPlayer->SetPower(0);
			}
			if((pControl->GetLeftTrigger()==255)&&(pPlayer->GetPower()>=100)&&(pGame->GetGameType()==CGame::GAME_TYPE_COMBAT))
			{
				if(pPlayer->GetField()->RemoveSolidBlocks(1)!=0)
					pPlayer->SetPower(0);
			}
			if(pControl->X(15))
				pPlayer->GetField()->Rotate(CField::ROTATE_RIGHT);
			if(pControl->Y(15))
				pPlayer->SetShowNext(!pPlayer->GetShowNext());
		}
		if(pControl->StartDown())
		{
			pGame->SetStatus(CGame::STATUS_PAUSE);
			pPlayer->SetPaused(true);
		}
	}
	else if(pGame->GetStatus()==CGame::STATUS_PAUSE)
	{
		if(pPlayer->GetPaused()==false)
			return;
		if(pControl->DDown(20))
		{
			pGame->PlaySound(1);
			if(pGame->GetPauseMenuPos()==0)
				pGame->SetPauseMenuPos(1);
			else
				pGame->SetPauseMenuPos(0);
		}
		if(pControl->DUp(20))
		{
			pGame->PlaySound(1);
			if(pGame->GetPauseMenuPos()==0)
				pGame->SetPauseMenuPos(1);
			else
				pGame->SetPauseMenuPos(0);
		}
		if(pControl->ADown())
		{
			pPlayer->SetPaused(false);
			if(pGame->GetPauseMenuPos()==0)
				pGame->SetStatus(CGame::STATUS_RUN);
			else if(pGame->GetPauseMenuPos()==1)
				pGame->SetStatus(CGame::STATUS_MAIN_MENU);
			pGame->SetPauseMenuPos(0);
		}
		if(pControl->StartDown())
		{
			pPlayer->SetPaused(false);
			pGame->SetStatus(CGame::STATUS_RUN);
		}
	}
	else if((pGame->GetStatus()==CGame::STATUS_THEME_BROWSER)&&(iPlayer==0))
	{
		if((pControl->DDown(20))&&(pGame->GetThemeBrowserMenuPos()<pGame->GetThemeList()->GetItems()-1))
		{
			pGame->PlaySound(1);
			pGame->SetThemeBrowserMenuPos(pGame->GetThemeBrowserMenuPos()+1);
		}
		else if((pControl->DUp(20))&&(pGame->GetThemeBrowserMenuPos()>0))
		{
			pGame->PlaySound(1);
			pGame->SetThemeBrowserMenuPos(pGame->GetThemeBrowserMenuPos()-1);
		}
		else if(pControl->YDown())
		{
			pGame->SetStatus(CGame::STATUS_OPTION_MENU);
		}
		else if(pControl->ADown())
		{
			pGame->SetPreviewTheme(pGame->GetThemeByPos(pGame->GetThemeBrowserMenuPos()));
			pGame->SetStatus(CGame::STATUS_THEME_BROWSER_INFO);
		}
	}
	else if((pGame->GetStatus()==CGame::STATUS_THEME_BROWSER_PREVIEW)&&(iPlayer==0))
	{
		if(pControl->YDown())
		{
			pGame->GetDraw()->UnloadPreviewBackground();
			pGame->SetStatus(CGame::STATUS_THEME_BROWSER_INFO);
		}
		else if(pControl->DLeft(20))
		{
			if(pGame->GetPreviewBackground()->GetPrev()!=NULL)
			{
				pGame->SetPreviewBackground(pGame->GetPreviewBackground()->GetPrev());
				pGame->GetDraw()->LoadPreviewBackground(pGame->GetPreviewBackground()->GetPath());
			}
		}
		else if(pControl->DRight(20))
		{
			if(pGame->GetPreviewBackground()->GetNext()!=NULL)
			{
				pGame->SetPreviewBackground(pGame->GetPreviewBackground()->GetNext());
				pGame->GetDraw()->LoadPreviewBackground(pGame->GetPreviewBackground()->GetPath());
			}
		}
	}
	else if((pGame->GetStatus()==CGame::STATUS_THEME_BROWSER_INFO)&&(iPlayer==0))
	{
		if(pControl->ADown())
		{
			pGame->SetPreviewBackground(pGame->GetPreviewTheme()->GetFirstBackground());
			pGame->GetDraw()->LoadPreviewBackground(pGame->GetPreviewBackground()->GetPath());
			pGame->SetStatus(CGame::STATUS_THEME_BROWSER_PREVIEW);
		}
		if(pControl->BDown())
		{
			pGame->GetDraw()->UnloadTheme();
			pGame->SetCurrentTheme(pGame->GetPreviewTheme());
			pGame->GetDraw()->LoadTheme();
			pGame->SetStatus(CGame::STATUS_THEME_BROWSER);
		}
		if(pControl->YDown())
			pGame->SetStatus(CGame::STATUS_THEME_BROWSER);
	}
	else if((pGame->GetStatus()==CGame::STATUS_OPTION_MENU)&&(iPlayer==0))
	{
		if((pControl->DDown(20))&&(pGame->GetOptionMenuPos()<6))
		{
			pGame->PlaySound(1);
			pGame->SetOptionMenuPos(pGame->GetOptionMenuPos()+1);
			if((pGame->GetPlayers()==1)&&(pGame->GetOptionMenuPos()==4))
				pGame->SetOptionMenuPos(pGame->GetOptionMenuPos()+1);
		}
		if((pControl->DUp(20))&&(pGame->GetOptionMenuPos()>0))
		{
			pGame->PlaySound(1);
			pGame->SetOptionMenuPos(pGame->GetOptionMenuPos()-1);
			if((pGame->GetPlayers()==1)&&(pGame->GetOptionMenuPos()==4))
				pGame->SetOptionMenuPos(pGame->GetOptionMenuPos()-1);
		}
		if(pControl->YDown())
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		if(pControl->ADown())
		{
			pGame->PlaySound(1);
			if(pGame->GetOptionMenuPos()==0)
				pGame->SetStatus(CGame::STATUS_THEME_BROWSER);
			else if(pGame->GetOptionMenuPos()==1)
				pGame->SetSound(!pGame->GetSound());
			else if((pGame->GetOptionMenuPos()==2)&&((MusicDelay+200)<frmctr))
			{
				pGame->SetPlayMusic(!pGame->GetPlayMusic());
				MusicDelay=frmctr;
			}
			else if(pGame->GetOptionMenuPos()==3)
				pGame->GetPlayer(0)->SetRumble(!pGame->GetPlayer(0)->GetRumble());
			else if((pGame->GetOptionMenuPos()==4)&&(pGame->GetPlayer(1)!=NULL))
				pGame->GetPlayer(1)->SetRumble(!pGame->GetPlayer(1)->GetRumble());
			else if(pGame->GetOptionMenuPos()==5)
				pGame->SetAutoSave(!pGame->GetAutoSave());
			else if(pGame->GetOptionMenuPos()==6)
				pGame->SetStatus(CGame::STATUS_TVMODE_SELECT);
		}
	}
	else if(pGame->GetStatus()==CGame::STATUS_CREDITS)
	{
		if(pControl->YDown()||pControl->ADown())
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
	}
	else if(pGame->GetStatus()==CGame::STATUS_GAMEOVER)
	{
		if((pControl->StartDown())||(pControl->ADown()))
		{
			pGame->GetDraw()->ResetBackground();
			pGame->SetStatus(CGame::STATUS_HIGH_SCORE);
		}
	}
	else if(pGame->GetStatus()==CGame::STATUS_HIGH_SCORE)
	{
		if((pControl->YDown())||(pControl->ADown()))
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
	}
	else if(pGame->GetStatus()==CGame::STATUS_MODE_SELECT)
	{
		if((pControl->XDown())&&(pPlayer->GetModeSelectPos()==0)&&(!pPlayer->GetReady()))
		{
			pGame->PlaySound(1);
			pPlayer->PrevLetter();
		}
		if((pControl->ADown())&&(pPlayer->GetModeSelectPos()==0)&&(!pPlayer->GetReady()))
		{
			pGame->PlaySound(1);
			pPlayer->NextLetter();
		}
		if(pControl->DRight(7)&&(!pPlayer->GetReady()))
		{
			if((pPlayer->GetModeSelectPos()==0)&&(pPlayer->GetCursorPos()<9)&&(pPlayer->GetLetter(pPlayer->GetCursorPos())!='|'))
			{
				
				if(pPlayer->GetLetter(pPlayer->GetCursorPos())!='ö')
				{
					pGame->PlaySound(1);
					pPlayer->NextCursorPos();
				}
			}
			if((pPlayer->GetModeSelectPos()==2)&&(pPlayer->GetHeightMenuPos()<5))
			{
				pGame->PlaySound(1);
				pPlayer->SetHeightMenuPos(pPlayer->GetHeightMenuPos()+1);
			}
			if((pPlayer->GetModeSelectPos()==1)&&(pPlayer->GetLevelMenuPos()<9))
			{
				pGame->PlaySound(1);
				pPlayer->SetLevelMenuPos(pPlayer->GetLevelMenuPos()+1);
			}
			if((iPlayer==0)&&(pPlayer->GetModeSelectPos()==3))
			{
				if(((pGame->GetGameMode()==CGame::GAME_MODE_1PLAYER)&&(pPlayer->GetGameModeMenuPos()<1))||
					((pGame->GetGameMode()==CGame::GAME_MODE_2PLAYER)&&(pPlayer->GetGameModeMenuPos()<3)))
				{
					pGame->PlaySound(1);
					pPlayer->SetGameModeMenuPos(pPlayer->GetGameModeMenuPos()+1);
				}
			}
		}
		if(pControl->DLeft(7)&&(!pPlayer->GetReady()))
		{
			if((pPlayer->GetModeSelectPos()==0)&&(pPlayer->GetCursorPos()>0))
			{
				pGame->PlaySound(1);
				pPlayer->PrevCursorPos();
			}
			if((pPlayer->GetModeSelectPos()==2)&&(pPlayer->GetHeightMenuPos()>0))
			{
				pGame->PlaySound(1);
				pPlayer->SetHeightMenuPos(pPlayer->GetHeightMenuPos()-1);
			}
			if((pPlayer->GetModeSelectPos()==1)&&(pPlayer->GetLevelMenuPos()>0))
			{
				pGame->PlaySound(1);
				pPlayer->SetLevelMenuPos(pPlayer->GetLevelMenuPos()-1);
			}
			if((iPlayer==0)&&(pPlayer->GetModeSelectPos()==3)&&(pPlayer->GetGameModeMenuPos()>0))
			{
				pGame->PlaySound(1);
				pPlayer->SetGameModeMenuPos(pPlayer->GetGameModeMenuPos()-1);
			}
		}
		if((pControl->YDown())&&(!pPlayer->GetReady()))
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		else if((pControl->YDown())&&(pPlayer->GetReady()))
			pPlayer->SetReady(false);
		if((pControl->DDownDown())&&(((iPlayer==0)&&(pPlayer->GetModeSelectPos()<3))||((iPlayer==1)&&(pPlayer->GetModeSelectPos()<2))))
			pPlayer->SetModeSelectPos(pPlayer->GetModeSelectPos()+1);
		if((pControl->DUpDown())&&(!pPlayer->GetReady()&&(pPlayer->GetModeSelectPos()>0)))
			pPlayer->SetModeSelectPos(pPlayer->GetModeSelectPos()-1);
		if(pControl->StartDown()&&(!pPlayer->GetReady()))
		{
			pPlayer->SetDisplayName();
			pPlayer->SetCursorPos(0);
			pPlayer->GetField()->SetStartHeight(pPlayer->GetStartHeight(pPlayer->GetHeightMenuPos()));
			pPlayer->SetLevel(pPlayer->GetLevelMenuPos());
			pPlayer->SetReady(true);
			if(iPlayer==0)
			{
				switch(pPlayer->GetGameModeMenuPos())
				{
					case 0:
						pGame->SetGameType(CGame::GAME_TYPE_NORMAL);
						break;
					case 1:
						pGame->SetGameType(CGame::GAME_TYPE_FLIP);
						break;
					case 2:
						pGame->SetGameType(CGame::GAME_TYPE_COMBAT);
						break;
					case 3:
						pGame->SetGameType(CGame::GAME_TYPE_FAST_COMBAT);
						break;
				}
			}
			pGame->Ready();
		}
	}
	else if(pGame->GetStatus()==CGame::STATUS_VMU_LOAD_MENU)
	{
		if((pControl->DDownDown())&&(pGame->GetVMUMenuPos()<(pGame->GetVMU()->GetVMUItems()-1)))
		{
			pGame->PlaySound(1);
			pGame->SetVMUMenuPos(pGame->GetVMUMenuPos()+1);
		}
		if((pControl->DUpDown())&&(pGame->GetVMUMenuPos()>0))
		{
			pGame->PlaySound(1);
			pGame->SetVMUMenuPos(pGame->GetVMUMenuPos()-1);
		}
		if(pControl->ADown())
		{
			CVMUnit *pVMUnit=pGame->GetVMU()->GetFirstVMUnit();
			for(int i=0;i<pGame->GetVMUMenuPos();i++)
				pVMUnit=pVMUnit->GetNext();
			pGame->Load(pVMUnit->GetVMU());
			pGame->SetActiveVMU(pVMUnit->GetVMU());
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		}
		if(pControl->YDown())
		{
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		}
	}
	else if(pGame->GetStatus()==CGame::STATUS_VMU_SAVE_MENU)
	{
		if((pControl->DDownDown())&&(pGame->GetVMUMenuPos()<(pGame->GetVMU()->GetVMUItems()-1)))
		{
			pGame->PlaySound(1);
			pGame->SetVMUMenuPos(pGame->GetVMUMenuPos()+1);
		}
		if((pControl->DUpDown())&&(pGame->GetVMUMenuPos()>0))
		{
			pGame->PlaySound(1);
			pGame->SetVMUMenuPos(pGame->GetVMUMenuPos()-1);
		}
		if(pControl->ADown())
		{
			CVMUnit *pVMUnit=pGame->GetVMU()->GetFirstVMUnit();
			for(int i=0;i<pGame->GetVMUMenuPos();i++)
				pVMUnit=pVMUnit->GetNext();
			pGame->Save(pVMUnit->GetVMU());
			pGame->SetActiveVMU(pVMUnit->GetVMU());
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		}
		if(pControl->YDown())
		{
			pGame->SetStatus(CGame::STATUS_MAIN_MENU);
		}
	}
}
