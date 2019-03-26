#ifndef __2E8628C9E69AB67E813075__FIELD__HPP__
#define __2E8628C9E69AB67E813075__FIELD__HPP__

#include <stdlib.h>

class CField
{
private:
	static const int WIDTH=10;
	static const int HEIGHT=24;
	static const int VISIBLE_HEIGHT=20;
	int iBlock[4][4];
	int iNextBlock[4][4];
  int iField[WIDTH][HEIGHT];
	int iAngle, iBlockType, iX, iY, iNext, iStatus, iFlashCounter, iResets, iNextColor, iColor, iStartHeight;
	
	int Randnum(int limit);
	void ClearBlock(int block[][4]);
	void RemoveFullRow(int row);
	void SetRemoveFullRow(int row);
	inline int LOWORD(int i){return(i & 0xFFFF);};
	inline int HIWORD(int i){return(i >> 16);};
	inline int MAKELONG(int low, int hi){return((low & 0xFFFF) | ((hi & 0xFFFF) << 16));};

public:
	static const int BLOCK_COLOR_DARKPINK=0;
	static const int BLOCK_COLOR_BROWN=1;
	static const int BLOCK_COLOR_PINK=2;
	static const int BLOCK_COLOR_YELLOW=3;
	static const int BLOCK_COLOR_RED=4;
	static const int BLOCK_COLOR_GREEN=5;
	static const int BLOCK_COLOR_BLUE=6;
	static const int BLOCK_COLOR_GRAY=7;
	static const int BLOCK_COLOR_NONE=8;

	static const int BLOCK_SHAPE_L=20;
	static const int BLOCK_SHAPE_RL=21;
	static const int BLOCK_SHAPE_Z=22;
	static const int BLOCK_SHAPE_RZ=23;
	static const int BLOCK_SHAPE_I=24;
	static const int BLOCK_SHAPE_T=25;
	static const int BLOCK_SHAPE_O=26;

	static const int MOVE_DOWN=60;
	static const int MOVE_UP=61;
	static const int MOVE_LEFT=62;
	static const int MOVE_RIGHT=63;
	static const int ROTATE_LEFT=64;
	static const int ROTATE_RIGHT=65;

	static const int STATUS_REMOVE_LINE=87;
	static const int STATUS_NORMAL=88;

	static const int BLOCK_REMOVE=160;
	static const int BLOCK_SOLID=161;

	void Flip();
	void Reset();
	void SetStartHeight(int height);
	int GetStartHeight(){return(iStartHeight);};
	void SetFlashCounter(int flash){iFlashCounter=flash;};
	int GetFlashCounter(){return(iFlashCounter);};
	void ResetFlashCounter();
	void SetStatus(int status){iStatus=status;};
	int GetStatus(){return(iStatus);};
	void Put();
	void ClearPos();
	bool CanMove(int direction);
	int GetBlock(int x, int y){return(iField[x][y]);};
	int GetNextBlock(int x, int y){return(iNextBlock[x][y]);};
	bool Move(int direction);
	void Rotate(int direction);
	int GetWidth(){return(WIDTH);};
	int GetHeight(){return(HEIGHT);};
	int GetVisibleHeight(){return(VISIBLE_HEIGHT);};
	void NewBlock();
	void NewBlock(int block[][4], int type, bool next);

	bool AddSolidBlocks(int nr);
	int RemoveSolidBlocks(int nr);

	CField();
	~CField();
	int CheckFullRow(void);
};
#endif // __2E8628C9E69AB67E813075__FIELD__HPP__
