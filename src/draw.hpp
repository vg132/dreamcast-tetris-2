#ifndef __D2461369E619C153DE48A8__DRAW__HPP__
#define __D2461369E619C153DE48A8__DRAW__HPP__

#include <stdlib.h>
#include "game.hpp"
#include "../../dccommon/src/gldraw.hpp"

#include "theme/themeinfo.hpp"
#include "theme/background.hpp"

#define SCREEN_X 640
#define SCREEN_Y 480

struct ThemeBackground
{
	int StartLine;
	kos_img_t Background;
};

struct BGHandler
{
	int iBackgrounds;
	int iCurrent;
	GLuint Current;
};

class CDraw : public CGLDraw
{
private:
	ThemeBackground *m_Backgrounds;
	GLuint m_iLoad[5];
	GLuint m_iMenuBorder, m_iTetrisLogo, m_iField[3];

	BGHandler m_BackgroundHandler;

	int m_iInitCounter;
	int m_iTVTestCounter;

	GLuint m_iWhiteFont[256];
	GLuint m_iBlackFont[256];
	GLuint m_iBlueFont[256];
	GLuint m_iOrangeFont[256];

	GLuint m_iPreview;
	GLuint m_iThemeInfo;
	GLuint m_iTVTest;

	GLuint m_iBlock[8];
	GLuint m_iNextImg[7];

	GLuint m_iText[7];

	int m_iFontSize[256];

	CGame *m_pGame;

	int GetLetterSize(char ch);
	void LoadFontData();
	void LoadFont(char *fn, GLuint *font);
	void DrawTVModeSelect();
	void DrawString(const char *text, float size, int letter_spacing, float x, float y, int align, GLuint *font=NULL);
	int GetStringWidth(const char *text, float size, int letter_spacing);
	void DrawBorder(int player, int players);
	void DrawBackground(GLuint txr);
	void DrawField(CField* pField, int align);
	void DrawBlock(int x, int y, int txr,int align);
	void DrawTitleMenu();
	void DrawOptionMenu();
	void DrawPause();
	void DrawGameOver();
	void DrawVMULoad();
	void DrawVMUSave();
	void DrawHighScore();
	void DrawCredits();
	void DrawThemeBrowser();
	void DrawThemeInformation();
	void DrawBackgroundPreview();
	void DrawTVModeTest();
	void DrawPowerMeter(int align);
	void DrawInit();
	void DrawInfo(char *str);
	void Rect(float x, float y, float w, float h, float a=0.0f);
	void Block(float x, float y, float w, float h);
	inline int LOWORD2(int i){return(i & 0xFFFF);};
	inline int HIWORD2(int i){return(i >> 16);};
	static const int ALIGN_CENTER=40;
	static const int ALIGN_LEFT=41;
	static const int ALIGN_RIGHT=42;
public:
	void SetGame(CGame *game){m_pGame=game;};
	void GLInit();
	void LoadInitTextures();
	void UnloadInitTextures();
	void UnloadTheme();
	void LoadTheme();
	void LoadTextures();
	void LoadPreviewBackground(const char *path);
	void UnloadPreviewBackground();
	void Background(int line);
	void ResetBackground();
	void DrawScene();
	CDraw();
	~CDraw();
};
#endif // __D2461369E619C153DE48A8__DRAW__HPP__
