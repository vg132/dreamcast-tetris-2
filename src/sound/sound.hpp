#ifndef __1AFD61A6A896A9D212F64__SOUND__HPP__
#define __1AFD61A6A896A9D212F64__SOUND__HPP__

#include <kos.h>

class CSound
{
private:
	int iEnd, iStart, iLvol, iRvol;
	bool bPlay;

	sfxhnd_t sndfxid[3];	//Handels to the sounds
public:
	void InitSound();
	void Play(int id, int vol, int pan);

	bool IsPlaying();

	bool CheckDisk();
	int GetFirstTrackNrCD(){return(iStart);};
	int GetLastTrackNrCD(){return(iEnd);};
	void PlayCD();
	void StopCD();
	void PauseCD();
	void ResumeCD();
	void SetTotalVolCD(int vol);
	int GetTotalVolCD(){return(iLvol);};

	CSound(void);
	~CSound(void);
};
#endif // __1AFD61A6A896A9D212F64__SOUND__HPP__
