#ifndef __C59CD94D73DCC9E9911867__TETRIS__HPP__
#define __C59CD94D73DCC9E9911867__TETRIS__HPP__

#include <kos.h>
#include <math.h>
#include <mp3/sndserver.h>

#include "draw.hpp"
#include "game.hpp"
#include "player.hpp"
#include "control.hpp"
#include "highscore.hpp"
#include "sound/music.hpp"
#include "sound/cdda.hpp"
#include "sound/filemusic.hpp"
#include "../../dccommon/src/dccontrol.hpp"
#include "../../dccommon/src/linkedlist.hpp"

#include "theme/themeinfo.hpp"
#include "theme/themehandler.hpp"

class CTetris
{
private:
	CGame *m_pGame;
	CControl *m_pControl;
	CDraw *m_pDraw;
	kthread_t *m_pInitThread;
	uint32 m_iCDHandler;

	void Run();
	void Init();
	void AutoLoad();
	static void ReadDir(char *dir, CFileMusic *music);
public:
	CGame* GetGame(){return(m_pGame);};

	static void thd_Init(void *v);
	static void CDCheck(uint32 code);
	static void CDInit(void *v);

	static CTetris* m_pThis;
	static int m_iLastCDStatus;
	static int m_iLastDiskType;

	int Start();
	CTetris();
	~CTetris();
};

#endif // __C59CD94D73DCC9E9911867__TETRIS__HPP__
