#include "cdda.hpp"

int CCdda::m_iStatus=CMusic::STATUS_ZOMBIE;
bool CCdda::m_bCanSkipp=true;
CCdda *CCdda::m_pThis=NULL;
int CCdda::m_iPlayList[99];
int *CCdda::m_pCurTrack=NULL;
int *CCdda::m_pEnd=NULL;

CCdda::CCdda(void)
{
	m_pEnd=m_pCurTrack=m_iPlayList;
	m_pThis=this;
	m_iTracks=0;
}

CCdda::~CCdda(void)
{
	Stop();
}

void CCdda::MusicLoop(void *v)
{
	int iCDStatus, iDiscType;
	while(m_iStatus!=CMusic::STATUS_QUIT)
	{
		switch(m_iStatus)
		{
			case CMusic::STATUS_NEXT:
				m_bCanSkipp=false;
				m_iStatus=CMusic::STATUS_PLAY;
				m_pCurTrack++;
				if(m_pCurTrack==m_pEnd)
					m_pCurTrack=m_iPlayList;
				break;
			case CMusic::STATUS_PREV:
				m_bCanSkipp=false;
				m_pCurTrack--;
				if(m_pCurTrack<m_iPlayList)
					m_pCurTrack=m_pEnd-1;
				m_iStatus=CMusic::STATUS_PLAY;
				break;
			case CMusic::STATUS_PLAY:
				cdrom_cdda_play(*m_pCurTrack, *m_pCurTrack, 0, CDDA_TRACKS);
				m_iStatus=CMusic::STATUS_PLAYING;
				break;
			case CMusic::STATUS_RESUME:
				cdrom_cdda_resume();
				break;
			case CMusic::STATUS_PAUSE:
				cdrom_cdda_pause();
				break;
			case CMusic::STATUS_STOP:
				cdrom_cdda_pause();
				cdrom_spin_down();
				m_iStatus=CMusic::STATUS_QUIT;
				break;
			default:
				if(!m_bCanSkipp)
				{
					thd_sleep(2000);
					m_bCanSkipp=true;
				}
				if(m_iStatus==CMusic::STATUS_PLAYING)
				{
					cdrom_get_status(&iCDStatus,&iDiscType);
					if(iCDStatus!=CD_STATUS_PLAYING)
						m_iStatus=CMusic::STATUS_NEXT;
				}
				thd_pass();
				break;
		}
	}
	m_iStatus=STATUS_ZOMBIE;
}

void CCdda::AddTrack(int track)
{
	m_iTracks++;
	*m_pEnd=track;
	m_pEnd++;
}

void CCdda::Play()
{
	if(m_pEnd!=m_iPlayList)
	{
		m_iStatus=CMusic::STATUS_PLAY;
		thd_create(MusicLoop,NULL);
	}
}

void CCdda::Stop()
{
	if(m_iStatus!=CMusic::STATUS_ZOMBIE)
	{
		m_iStatus=CMusic::STATUS_STOP;
		while(m_iStatus!=CMusic::STATUS_ZOMBIE)
			thd_pass();
	}
}

void CCdda::Prev()
{
	if(m_bCanSkipp)
		m_iStatus=CMusic::STATUS_PREV;
}

void CCdda::Next()
{
	if(m_bCanSkipp)
		m_iStatus=CMusic::STATUS_NEXT;
}

void CCdda::Pause()
{
	m_iStatus=CMusic::STATUS_PAUSE;
}

void CCdda::Resume()
{
	if(m_iStatus!=CMusic::STATUS_ZOMBIE)
		m_iStatus=CMusic::STATUS_PLAY;
	else
		Play();
}

bool CCdda::Playing()
{
	if(m_iStatus==CMusic::STATUS_PLAYING)
		return(true);
	return(false);
}
