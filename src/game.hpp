#ifndef __8EB22FACEE81CD2F4E35__GAME__HPP__
#define __8EB22FACEE81CD2F4E35__GAME__HPP__

typedef struct hs
{
	char name[11];
	char date[11];
	int score;
}st_high_score;

typedef struct op
{
	bool autosave;
	bool music;
	bool sound;
	bool rumblep1;
	bool rumblep2;
	bool pal;
	char theme[256];
	char p1name[11];
	char p2name[11];
}st_options;

#include <arch/rtc.h>
#include <time.h>
#include <stdlib.h>
#include <kos.h>

#include "../../dccommon/src/vmu.hpp"
#include "../../dccommon/src/linkedlist.hpp"
#include "player.hpp"
#include "sound/sound.hpp"
#include "highscore.hpp"
#include "theme/themeinfo.hpp"
#include "sound/music.hpp"

class CDraw;

class CGame
{
private:
	CLinkedList *m_pThemeList;
	CThemeInfo *m_pCurrentThemeInfo, *m_pPreviewThemeInfo;
	CBackground *m_pPreviewBackground;
	CDraw *m_pDraw;
	int m_iPlayers, m_iStatus, m_iMainMenuPos, m_iOptionMenuPos, m_iGameMode, m_iThemeBrowserMenuPos;
	int m_iVMUMenuPos, m_iMusicVolume, m_iSoundVolume, m_iTVMenuPos;
	int m_iPauseMenuPos;
	bool m_bMusic, m_bSound, m_bAutoSave, m_bTVModeLoaded, m_bPal;

	CPlayer *m_pPlayers[2];

	CSound *m_pSound;
	CMusic *m_pMusic;
	CHighScore *m_pHighScore;
	int m_iGameType;

	CVMU *m_pVMU;
	maple_device_t *m_pActiveVMU;

public:

	bool GetTVModeLoaded(){return(m_bTVModeLoaded);};
	void SetTVModeLoaded(bool modeLoaded){m_bTVModeLoaded=modeLoaded;};
	void SetPal(bool pal){m_bPal=pal;};
	bool GetPal(){return(m_bPal);};

	void SetPlayMusic(bool music);
	bool GetPlayMusic(){return(m_bMusic);};
	void SetMusic(CMusic *music);
	CMusic* GetMusic(){return(m_pMusic);};

	// Menu position data
	void SetMainMenuPos(int pos){m_iMainMenuPos=pos;};
	int GetMainMenuPos(){return(m_iMainMenuPos);};
	void SetOptionMenuPos(int pos){m_iOptionMenuPos=pos;};
	int GetOptionMenuPos(){return(m_iOptionMenuPos);};
	void SetTVMenuPos(int pos){m_iTVMenuPos=pos;};
	int GetTVMenuPos(){return(m_iTVMenuPos);};
	void SetPauseMenuPos(int pos){m_iPauseMenuPos=pos;};
	int GetPauseMenuPos(){return(m_iPauseMenuPos);};
	void SetThemeBrowserMenuPos(int pos){m_iThemeBrowserMenuPos=pos;};
	int GetThemeBrowserMenuPos(){return(m_iThemeBrowserMenuPos);};

	// Theme handeling functions
	void SetThemeList(CLinkedList *list){m_pThemeList=list;};
	CThemeInfo* GetThemeByName(const char *name);
	CThemeInfo* GetThemeByPath(const char *path);
	// 0 based pos
	CThemeInfo* GetThemeByPos(int pos);
	CLinkedList* GetThemeList(){return(m_pThemeList);};
	void SetCurrentTheme(CThemeInfo *info){m_pCurrentThemeInfo=info;};
	CThemeInfo* GetCurrentTheme(){return(m_pCurrentThemeInfo);};
	void SetPreviewTheme(CThemeInfo *info){m_pPreviewThemeInfo=info;};
	CThemeInfo* GetPreviewTheme(){return(m_pPreviewThemeInfo);};
	void SetPreviewBackground(CBackground *back){m_pPreviewBackground=back;};
	CBackground* GetPreviewBackground(){return(m_pPreviewBackground);};

	// Other functions
	int GetVMUMenuPos(){return(m_iVMUMenuPos);};
	void SetVMUMenuPos(int pos){m_iVMUMenuPos=pos;};

	void SetDraw(CDraw *draw){m_pDraw=draw;};
	CDraw* GetDraw(){return(m_pDraw);};


	bool Save(maple_device_t *dev);
	bool Load(maple_device_t *dev);

	void SetVMU(CVMU *vmu);
	CVMU* GetVMU(){return(m_pVMU);};


	void Ready();
	int GetActivePlayers();
	maple_device_t* GetActiveVMU(){return(m_pActiveVMU);};
	void SetActiveVMU(maple_device_t *dev){m_pActiveVMU=dev;};

	bool AddPlayer(CPlayer *player);


	float XX,YY;
	CGame();
	~CGame();
	static const int STATUS_STOP=80;
	static const int STATUS_RUN=81;
	static const int STATUS_PAUSE=82;
	static const int STATUS_GAMEOVER=83;
	static const int STATUS_MAIN_MENU=84;
	static const int STATUS_OPTION_MENU=85;
	static const int STATUS_EXIT=86;
	static const int STATUS_MODE_SELECT=89;
	static const int STATUS_HIGH_SCORE=90;
	static const int STATUS_CREDITS=91;
	static const int STATUS_VMU_LOAD_MENU=92;
	static const int STATUS_VMU_SAVE_MENU=93;
	static const int STATUS_TVMODE_SELECT=94;
	static const int STATUS_INIT=95;
	static const int STATUS_THEME_BROWSER=96;
	static const int STATUS_THEME_BROWSER_INFO=97;
	static const int STATUS_THEME_BROWSER_PREVIEW=98;
	static const int STATUS_TVMODE_TEST=99;

	static const int GAME_MODE_1PLAYER=110;
	static const int GAME_MODE_2PLAYER=111;
	static const int GAME_MODE_NONE=112;

	static const int GAME_TYPE_NORMAL=130;
	static const int GAME_TYPE_FLIP=131;
	static const int GAME_TYPE_FAST_COMBAT=132;
	static const int GAME_TYPE_COMBAT=133;

	void SetGameMode(int mode){m_iGameMode=mode;};
	int GetGameMode(){return(m_iGameMode);};
	
	// Sound -- Start
	void PlaySound(int id,int vol=-1,int pan=128);
	void SetSound(bool sound){m_bSound=sound;};
	bool GetSound(){return(m_bSound);};
	void SetSoundVolume(int volume){m_iSoundVolume=volume;};
	int GetSoundVolume(){return(m_iSoundVolume);};
	// Sound -- End
	
	int GetStatus(){return(m_iStatus);};
	void SetStatus(int status){m_iStatus=status;};
	void SetPlayers(int players){m_iPlayers=players;};
	CPlayer* GetPlayer(int player){return(m_pPlayers[player]);};
	int GetPlayers(){return(m_iPlayers);};
	void SetAutoSave(bool save){m_bAutoSave=save;};
	bool GetAutoSave(){return(m_bAutoSave);};
	void SetHighScore();
	CHighScore* GetHighScore(){return(m_pHighScore);};

	int GetGameType(){return(m_iGameType);};
	void SetGameType(int gameType){m_iGameType=gameType;};
};

#endif // __8EB22FACEE81CD2F4E35__GAME__HPP__
