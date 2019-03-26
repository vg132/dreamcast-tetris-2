#ifndef __659E868C8C4C7A6A48EE0__PLAYER__HPP__
#define __659E868C8C4C7A6A48EE0__PLAYER__HPP__

#include "../../dccommon/src/dccontrol.hpp"
#include "field.hpp"

class CPlayer
{
private:
	int m_iPoints, m_iLevel, m_iLetterPos[10], m_iCursorPos, m_iHeightMenuPos, m_iLevelMenuPos, m_iModeSelectPos;
	bool m_bShowNext, m_bReady, m_bPaused, m_bRumble;
	CField *m_pField;
	unsigned long int moveSize, m_lLastMove;
	char *m_pLetters, m_Name[10], m_DisplayName[11];
	CDCControl *m_pControl;
	int m_iStartHeight[6], m_iGameModeMenuPos;
	int m_iLines[4];
	int m_iPower, m_iPowerFlash;

public:
  CPlayer();
  ~CPlayer();

	void SetPowerFlash(int flash){m_iPowerFlash=flash;};
	int GetPowerFlash(){return(m_iPowerFlash);};

	void Rumble(int frequence);

	bool GetRumble(){return(m_bRumble);};
	void SetRumble(bool rumble){m_bRumble=rumble;};

	int GetPower(){return(m_iPower);};
	void SetPower(int power){m_iPower=power;};

	int GetStartHeight(int pos){return(m_iStartHeight[pos]);};

	void SetReady(bool b){m_bReady=b;};
	bool GetReady(){return(m_bReady);};

	void SetPaused(bool pause){m_bPaused=pause;};
	bool GetPaused(){return(m_bPaused);};

	void Reset();
	void DeleteField();
	void NextCursorPos();
	void PrevCursorPos();
	void SetRows(int rows);
	void NextLetter();
	void PrevLetter();
	void SetName(char* name);
	void SetLevel(int level);
	void SetField(CField* field);
	void SetControl(CDCControl *control);

	char* GetName(){return(m_Name);};
	void SetDisplayName();
	char* GetDisplayName(){return(m_DisplayName);};

	int GetLevel(){return(m_iLevel);};
	int GetPoints(){return(m_iPoints);};
	CField* GetField(){return(m_pField);};
	bool GetShowNext(){return(m_bShowNext);};
	int GetCursorPos(){return(m_iCursorPos);};
	void SetCursorPos(int pos){m_iCursorPos=pos;};
	CDCControl* GetControl(){return(m_pControl);};
	void SetPoints(int points){m_iPoints=points;};
	void AddPoints(int points){m_iPoints+=points;};
	void SetShowNext(bool show){m_bShowNext=show;};
	void RemovePoints(int points){m_iPoints-=points;};
	unsigned long int GetMoveSize(){return(moveSize);};
	unsigned long int GetLastMove(){return(m_lLastMove);};
	void SetMoveSize(unsigned long int size){moveSize=size;};
	char GetLetter(int pos){return(m_pLetters[m_iLetterPos[pos]]);};
	void SetLastMove(unsigned long int lastMove){m_lLastMove=lastMove;};
	
	void SetHeightMenuPos(int pos){m_iHeightMenuPos=pos;};
	int GetHeightMenuPos(){return(m_iHeightMenuPos);};
	void SetLevelMenuPos(int pos){m_iLevelMenuPos=pos;};
	int GetLevelMenuPos(){return(m_iLevelMenuPos);};
	void SetModeSelectPos(int pos){m_iModeSelectPos=pos;};
	int GetModeSelectPos(){return(m_iModeSelectPos);};

	void SetGameModeMenuPos(int pos){m_iGameModeMenuPos=pos;};
	int GetGameModeMenuPos(){return(m_iGameModeMenuPos);};

	int GetLines(int index);
};
#endif // __659E868C8C4C7A6A48EE0__PLAYER__HPP__
