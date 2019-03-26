#include "filemusic.hpp"

CFileMusic* CFileMusic::m_pThis=NULL;
bool CFileMusic::m_bCanSkipp=true;
int CFileMusic::m_iOldStatus=-1;
int CFileMusic::m_iStatus=CMusic::STATUS_ZOMBIE;

CFileMusic::CFileMusic()
{
	m_pFirst=NULL;
	m_pCurrent=NULL;
	m_pLast=NULL;
	m_iTracks=0;
	m_pThis=this;
}

CFileMusic::~CFileMusic(void)
{
	Stop();
	if(m_pFirst!=NULL)
		delete m_pFirst;
}

void CFileMusic::Status(int status)
{
	if((status==CFileMusic::SNDMP3_STATUS_READY)&&(m_iOldStatus==CFileMusic::SNDMP3_STATUS_PLAYING))
		m_iStatus=CMusic::STATUS_NEXT;
	else
		m_iOldStatus=status;
}

void CFileMusic::MusicLoop(void *v)
{
	while(m_iStatus!=CMusic::STATUS_QUIT)
	{
		switch(m_iStatus)
		{
			case CMusic::STATUS_NEXT:
			case CMusic::STATUS_PREV:
				m_bCanSkipp=false;
				if(m_iStatus==CMusic::STATUS_NEXT)
					m_pThis->m_pCurrent=m_pThis->m_pCurrent->GetNext();
				else
					m_pThis->m_pCurrent=m_pThis->m_pCurrent->GetPrev();
				m_pThis->m_ID3.Clear();
				mp3_stop();
				mp3_shutdown();
				m_iStatus=CMusic::STATUS_PLAY;
				break;
			case CMusic::STATUS_PLAY:
				mp3_init();
				m_pThis->m_ID3.Initialize();
				if(m_pThis->m_ID3.LoadID3(m_pThis->m_pCurrent->GetPath()))
					dbglog(DBG_INFO,"Error reading ID3: '%s'\n",m_pThis->m_pCurrent->GetPath());
				mp3_start(m_pThis->m_pCurrent->GetPath(),0,Status);
				m_iStatus=CMusic::STATUS_PLAYING;
				break;
			case CMusic::STATUS_PAUSE:
			case CMusic::STATUS_STOP:
				m_pThis->m_ID3.Clear();
				mp3_stop();
				mp3_shutdown();
				m_iStatus=CMusic::STATUS_QUIT;
				break;
			default:
				if(!m_bCanSkipp)
				{
					thd_sleep(2000);
					m_bCanSkipp=true;
				}
				thd_pass();
				break;
		}
	}
	m_iStatus=STATUS_ZOMBIE;
}

void CFileMusic::AddTrack(char *path)
{
	m_iTracks++;
	CTrack *track=new CTrack(path,m_pFirst,m_pLast);
	if(m_pFirst==NULL)
	{
		track->SetPrev(track);
		track->SetNext(track);
		m_pFirst=track;
		m_pLast=m_pFirst;
		m_pFirst->SetFirst();
	}
	else
	{
		m_pLast->SetNext(track);
		m_pFirst->SetPrev(track);
		m_pLast=track;
	}
}

void CFileMusic::Play()
{
	m_pCurrent=m_pFirst;
	if(m_pCurrent==NULL)
		return;
	m_iStatus=CMusic::STATUS_PLAY;
	thd_create(MusicLoop,NULL);
}

void CFileMusic::Stop()
{
	if(m_iStatus!=CMusic::STATUS_ZOMBIE)
	{
		m_iStatus=CMusic::STATUS_STOP;
		while(m_iStatus!=CMusic::STATUS_ZOMBIE)
			thd_pass();
	}
}

void CFileMusic::Prev()
{
	if(m_bCanSkipp)
	{
		m_iStatus=CMusic::STATUS_PREV;
		m_bCanSkipp=false;
	}
}

void CFileMusic::Next()
{
	if(m_bCanSkipp)
	{
		m_iStatus=CMusic::STATUS_NEXT;
		m_bCanSkipp=false;
	}
}

void CFileMusic::Pause()
{
	m_iStatus=CMusic::STATUS_PAUSE;
}

void CFileMusic::Resume()
{
	if(m_iStatus!=CMusic::STATUS_ZOMBIE)
		m_iStatus=CMusic::STATUS_PLAY;
	else
		Play();
}

bool CFileMusic::Playing()
{
	if(m_iStatus==CMusic::STATUS_PLAYING)
		return(true);
	return(false);
}
