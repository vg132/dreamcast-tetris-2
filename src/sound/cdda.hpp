#ifndef __D0A165B31FB718E6184FB__CDDA__HPP__
#define __D0A165B31FB718E6184FB__CDDA__HPP__

#include "music.hpp"

class CCdda : public CMusic
{
private:
	int m_iTracks;
public:
	static CCdda *m_pThis;
	static int m_iStatus;
	static bool m_bCanSkipp;
	static int m_iPlayList[99];
	static int *m_pCurTrack;
	static int *m_pEnd;


	static void MusicLoop(void *v);

	void AddTrack(int track);
	int GetTracks(){return(m_iTracks);};

	void Play();
	void Next();
	void Prev();
	void Stop();
	void Pause();
	void Resume();
	bool Playing();

	CCdda(void);
	~CCdda(void);
};

#endif // __D0A165B31FB718E6184FB__CDDA__HPP__
