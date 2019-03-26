#ifndef __1A604A194813C63CC29993__CONTROL__HPP__
#define __1A604A194813C63CC29993__CONTROL__HPP__

#include "../../dccommon/src/dccontrol.hpp"
#include "game.hpp"
#include "field.hpp"
#include "highscore.hpp"
#include "draw.hpp"

class CControl
{
private:
	CDCControl *pControl;
	CPlayer *pPlayer;
public:
	void Respond(CGame *pGame, int iPlayer, unsigned long int frmctr);
	CControl();
	~CControl();
};

#endif // __1A604A194813C63CC29993__CONTROL__HPP__
