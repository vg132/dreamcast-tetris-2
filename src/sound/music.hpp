#ifndef __198B3151E208FE2474146__MUSIC__HPP__
#define __198B3151E208FE2474146__MUSIC__HPP__

#include <kos.h>

class CMusic
{
private:
public:
	static const int STATUS_PLAY=1;
	static const int STATUS_PAUSE=2;
	static const int STATUS_STOP=3;
	static const int STATUS_NEXT=4;
	static const int STATUS_PREV=5;
	static const int STATUS_QUIT=6;
	static const int STATUS_PLAYING=7;
	static const int STATUS_ZOMBIE=8;
	static const int STATUS_RESUME=9;

	virtual void Play(){};
	virtual void Next(){};
	virtual void Prev(){};
	virtual void Stop(){};
	virtual void Pause(){};
	virtual void Resume(){};
	virtual bool Playing(){return(false);};

	CMusic(void);
	virtual ~CMusic(void);
};

#endif // __198B3151E208FE2474146__MUSIC__HPP__
