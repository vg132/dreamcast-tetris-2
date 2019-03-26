#ifndef __11EDD2A675264A166A21D__FILEMUSIC__HPP__
#define __11EDD2A675264A166A21D__FILEMUSIC__HPP__

#include <math.h>
#include <mp3/sndserver.h>

#include "music.hpp"
#include "../draw.hpp"
#include "../game.hpp"
#include "../../../dccommon/src/id3.hpp"

class CTrack
{
private:
	CTrack *m_pNext;
	CTrack *m_pPrev;
	char *m_pPath;
	bool m_bFirst;
public:
	CTrack(char *path, CTrack *next, CTrack *prev)
	{
		m_pPath=new char[strlen(path)+1];
		strcpy(m_pPath,path);
		m_pNext=next;
		m_pPrev=prev;
		m_bFirst=false;
	};
	~CTrack()
	{
		delete[] m_pPath;
		if((m_pNext!=NULL)&&(!m_pNext->IsFirst()))
			delete m_pNext;
	};
	bool IsFirst(){return(m_bFirst);};
	void SetFirst(){m_bFirst=true;};
	char* GetPath(){return(m_pPath);};
	void SetNext(CTrack *next){m_pNext=next;};
	CTrack* GetNext(){return(m_pNext);};
	void SetPrev(CTrack *prev){m_pPrev=prev;};
	CTrack* GetPrev(){return(m_pPrev);};
};

class CFileMusic : public CMusic
{
private:
	CTrack *m_pFirst, *m_pLast,*m_pCurrent;
	int m_iTracks;
	CID3 m_ID3;
public:
	static const int SNDMP3_STATUS_READY=1;
	static const int SNDMP3_STATUS_PLAYING=3;
	
	static CFileMusic *m_pThis;
	static bool m_bCanSkipp;
	static int m_iStatus;
	static int m_iOldStatus;

	void AddTrack(char *path);
	int GetTracks(){return(m_iTracks);};
	CID3* GetID3(){return(&m_ID3);};

	void Play();
	void Next();
	void Prev();
	void Stop();
	void Pause();
	void Resume();
	bool Playing();
	
	static void MusicLoop(void *v);
	static void Status(int status);
	
	CFileMusic(void);
	~CFileMusic(void);
};

#endif // __11EDD2A675264A166A21D__FILEMUSIC__HPP__
