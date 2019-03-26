#include "sound.hpp"

CSound::CSound(void)
{
}

CSound::~CSound(void)
{
}

/* Load sounds and save the handle in a array*/
void CSound::InitSound()
{
	snd_stream_init(NULL);
#ifdef _TETRIS_DEBUG_
	sndfxid[0]=snd_sfx_load("/cd/master/sounds/block_down.wav");
	sndfxid[1]=snd_sfx_load("/cd/master/sounds/menu_change.wav");
	sndfxid[2]=snd_sfx_load("/cd/master/sounds/line_delete.wav");
#elif _TETRIS_RELEASE_
	sndfxid[0]=snd_sfx_load("/cd/sounds/block_down.wav");
	sndfxid[1]=snd_sfx_load("/cd/sounds/menu_change.wav");
	sndfxid[2]=snd_sfx_load("/cd/sounds/line_delete.wav");
#endif
}

/* Play a given sound at a given volume and pan (128=Center, 0=Left, 255=Right) */
void CSound::Play(int id, int vol, int pan)
{
	snd_sfx_play(sndfxid[id],vol,pan);
}
