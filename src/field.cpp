#include "field.hpp"

CField::CField()
{
	Reset();
}

CField::~CField()
{
}

void CField::Reset()
{
	for(int y=0;y<WIDTH;y++)
	{
		for(int x=0;x<HEIGHT;x++)
		{
			iField[y][x]=MAKELONG(BLOCK_COLOR_NONE,0);
		}
	}
	iNext=-1;
	iResets=0;
	iStartHeight=0;
	iStatus=STATUS_NORMAL;
}

void CField::NewBlock()
{
	if(iNext==-1)
	{
		iNext=(Randnum(7000)/1000)+20;
		NewBlock(iNextBlock,iNext,true);
	}
	NewBlock(iBlock,iNext,false);
	iNext=(Randnum(7000)/1000)+20;
	NewBlock(iNextBlock,iNext,true);
}

void CField::ClearBlock(int block[][4])
{
	for(int x=0;x<4;x++)
	{
		for(int y=0;y<4;y++)
		{
			block[x][y]=BLOCK_COLOR_NONE;
		}
	}
}

void CField::NewBlock(int block[][4],int type, bool next)
{
	if(next)
		iNextColor=type-20;
	ClearBlock(block);
	if(type==BLOCK_SHAPE_L)
	{
		block[0][1]=BLOCK_COLOR_DARKPINK;
		block[1][1]=BLOCK_COLOR_DARKPINK;
		block[2][1]=BLOCK_COLOR_DARKPINK;
		block[2][0]=BLOCK_COLOR_DARKPINK;
		if(!next)
		{
			iAngle=1;
			iBlockType=BLOCK_SHAPE_L;
			iColor=BLOCK_COLOR_DARKPINK;
			iX=3;
			iY=3;
		}
	}
	else if(type==BLOCK_SHAPE_RL)
	{
		block[0][1]=BLOCK_COLOR_BROWN;
		block[1][1]=BLOCK_COLOR_BROWN;
		block[2][1]=BLOCK_COLOR_BROWN;
		block[0][0]=BLOCK_COLOR_BROWN;
		if(!next)
		{
			iAngle=3;
			iBlockType=BLOCK_SHAPE_RL;
			iColor=BLOCK_COLOR_BROWN;
			iX=3;
			iY=3;
		}
	}
	else if(type==BLOCK_SHAPE_Z)
	{
		block[0][0]=BLOCK_COLOR_PINK;
		block[1][1]=BLOCK_COLOR_PINK;
		block[1][0]=BLOCK_COLOR_PINK;
		block[2][1]=BLOCK_COLOR_PINK;
		if(!next)
		{
			iAngle=1;
			iBlockType=BLOCK_SHAPE_Z;
			iColor=BLOCK_COLOR_PINK;
			iX=3;
			iY=3;
		}
	}
	else if(type==BLOCK_SHAPE_RZ)
	{
		block[0][2]=BLOCK_COLOR_YELLOW;
		block[1][2]=BLOCK_COLOR_YELLOW;
		block[1][1]=BLOCK_COLOR_YELLOW;
		block[2][1]=BLOCK_COLOR_YELLOW;
		if(!next)
		{
			iAngle=1;
			iBlockType=BLOCK_SHAPE_RZ;
			iColor=BLOCK_COLOR_YELLOW;
			iX=3;
			iY=2;
		}
	}
	else if(type==BLOCK_SHAPE_I)
	{
		block[0][1]=BLOCK_COLOR_RED;
		block[1][1]=BLOCK_COLOR_RED;
		block[2][1]=BLOCK_COLOR_RED;
		block[3][1]=BLOCK_COLOR_RED;
		if(!next)
		{
			iAngle=1;
			iBlockType=BLOCK_SHAPE_I;
			iColor=BLOCK_COLOR_RED;
			iX=3;
			iY=3;
		}
	}
	else if(type==BLOCK_SHAPE_T)
	{
		block[1][0]=BLOCK_COLOR_GREEN;
		block[1][1]=BLOCK_COLOR_GREEN;
		block[2][1]=BLOCK_COLOR_GREEN;
		block[0][1]=BLOCK_COLOR_GREEN;
		if(!next)
		{
			iAngle=2;
			iBlockType=BLOCK_SHAPE_T;
			iColor=BLOCK_COLOR_GREEN;
			iX=3;
			iY=3;
		}
	}
	else if(type==BLOCK_SHAPE_O)
	{
		block[0][0]=BLOCK_COLOR_BLUE;
		block[0][1]=BLOCK_COLOR_BLUE;
		block[1][0]=BLOCK_COLOR_BLUE;
		block[1][1]=BLOCK_COLOR_BLUE;
		if(!next)
		{
			iAngle=0;
			iBlockType=BLOCK_SHAPE_O;
			iColor=BLOCK_COLOR_BLUE;
			iX=3;
			iY=3;
		}
	}
	if(!next)
		Put();
}

void CField::Put()
{
	for(int x=0;x<4;x++)
	{
		for(int y=0;y<4;y++)
		{
			if(iBlock[x][y]!=BLOCK_COLOR_NONE)
				iField[iX+x][iY+y]=MAKELONG(iBlock[x][y],0);
		}
	}
}

void CField::ClearPos()
{
	for(int x=0;x<4;x++)
	{
		for(int y=0;y<4;y++)
		{
			if(iBlock[x][y]!=BLOCK_COLOR_NONE)
				iField[iX+x][iY+y]=MAKELONG(BLOCK_COLOR_NONE,0);
		}
	}
}

bool CField::Move(int direction)
{
	bool retVal=true;
	ClearPos();
	if(CanMove(direction))
	{
		if(direction==MOVE_DOWN)
			iY++;
		else if(direction==MOVE_LEFT)
			iX--;
		else if(direction==MOVE_RIGHT)
			iX++;
		else if(direction==MOVE_UP)
			iY--;
	}
	else
	{
		retVal=false;
	}
	Put();
	return(retVal);
}

bool CField::CanMove(int direction)
{
	ClearPos();
	for(int y=0;y<4;y++)
	{
		for(int x=0;x<4;x++)
		{
			if(iBlock[x][y]!=BLOCK_COLOR_NONE)
			{
				if((direction==MOVE_DOWN)&&(((iY+y)>=(HEIGHT-1))||(LOWORD(iField[iX+x][iY+y+1])!=BLOCK_COLOR_NONE)))
					return(false);
				else if((direction==MOVE_LEFT)&&(((x+iX)<=0)||(LOWORD(iField[iX+x-1][iY+y])!=BLOCK_COLOR_NONE)))
					return(false);
				else if((direction==MOVE_RIGHT)&&(((x+iX)>=(WIDTH-1))||(LOWORD(iField[iX+x+1][iY+y])!=BLOCK_COLOR_NONE)))
					return(false);
			}
		}
	}
	return(true);
}

void CField::Rotate(int direction)
{
	ClearPos();
	bool rotated=false;
	if(direction==ROTATE_LEFT)
		iAngle--;
	else if(direction==ROTATE_RIGHT)
		iAngle++;
	if(iAngle>3)
		iAngle=0;
	else if(iAngle<0)
		iAngle=3;
	if(iBlockType==BLOCK_SHAPE_I)
	{
		/*	#
				#
				#
				#
		*/
		if((iAngle==0)||(iAngle==2))
		{
			if(
				(iY<=20)
				&&(LOWORD(iField[iX+3][iY+2])==BLOCK_COLOR_NONE)
				&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)
				&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
				&&(LOWORD(iField[iX+1][iY+3])==BLOCK_COLOR_NONE)
				&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
				)
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[1][2]=iColor;
				iBlock[1][3]=iColor;
			}
		}
		/*####*/
		else if((iAngle==1)||(iAngle==3))
		{
			if(
					(iX>=0)&&(iX<=6)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+3][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+3][iY+2])==BLOCK_COLOR_NONE)
				)
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[0][1]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[3][1]=iColor;
			}
		}
	}
	else if(iBlockType==BLOCK_SHAPE_T)
	{
		/**
			#[#]#
			  #
		*/
		if(iAngle==0)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[0][1]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[1][2]=iColor;
			}
		}
		/**
			 #
			[#]#
			 #
		*/
		else if(iAngle==1)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[1][2]=iColor;
			}
		}
		/**
			  #
			#[#]#
		*/
		else if(iAngle==2)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[0][1]=iColor;
			}
		}
		/**
			  #
			#[#]
			  #
		*/
		else if(iAngle==3)
		{
			if(
				(
					(direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
				)
				||
				(
					(direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)
				)
				)
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[1][2]=iColor;
				iBlock[0][1]=iColor;
			}
		}
	}
	else if(iBlockType==BLOCK_SHAPE_RL)
	{
		/**
			  #
			 [#]
			 ##
		*/
		if(iAngle==0)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[1][2]=iColor;
				iBlock[0][2]=iColor;
			}
		}
		/**
			#[#]#
			    #
		*/
		else if(iAngle==1)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[0][1]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[2][2]=iColor;
			}
		}
		/**
			 ##
			[#]
			 #
		*/
		else if(iAngle==2)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[1][2]=iColor;
				iBlock[2][0]=iColor;
			}
		}
		/**
			#
			#[#]#
		*/
		else if(iAngle==3)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[0][1]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[0][0]=iColor;
			}
		}
	}
	else if(iBlockType==BLOCK_SHAPE_L)
	{
		/**
			 #
			[#]
			 ##
		*/
		if(iAngle==0)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[1][2]=iColor;
				iBlock[2][2]=iColor;
			}
		}
		/**
			    #
			#[#]#
		*/
		else if(iAngle==1)
		{
			if(((direction==ROTATE_RIGHT)
						&&(iX>=0)&&(iX<=7)
						&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE))
					||((direction==ROTATE_LEFT)
						&&(iX<=7)&&(iX>=0)
						&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[0][1]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[2][0]=iColor;
			}
		}
		/**
			 ##
			 [#]
			  #
		*/
		else if(iAngle==2)
		{
			if(((direction==ROTATE_RIGHT)
						&&(iX>=0)&&(iX<=7)&&(iY<=21)
						&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE))
					||((direction==ROTATE_LEFT)
						&&(iX>=0)&&(iX<=7)
						&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
						&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[1][2]=iColor;
				iBlock[0][0]=iColor;
			}
		}
		/**
			#[#]#
			#
		*/
		else if(iAngle==3)
		{
			if(((direction==ROTATE_RIGHT)
					&&(iX>=0)&&(iX<=7)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE))
				||((direction==ROTATE_LEFT)
					&&(iX>=0)&&(iX<=7)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[0][1]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[0][2]=iColor;
			}
		}
	}
	else if(iBlockType==BLOCK_SHAPE_Z)
	{
		/**
			   #
			[#]#
			 #
		*/
		if((iAngle==0)||(iAngle==2))
		{
			if((iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[2][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[1][2]=iColor;
			}
		}
		/**
			 ##
			 [#]#
		*/
		else if((iAngle==1)||(iAngle==3))
		{
			if((iX>=0)&&(iX<=7)&&(iY<=21)
				&&(LOWORD(iField[iX][iY])==BLOCK_COLOR_NONE)
				&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE)
				&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
				&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[0][0]=iColor;
				iBlock[1][1]=iColor;
				iBlock[1][0]=iColor;
				iBlock[2][1]=iColor;
			}
		}
	}
	else if(iBlockType==BLOCK_SHAPE_RZ)
	{
		/**
			 #
			[#]#
			   #
		*/
		if((iAngle==0)||(iAngle==2))
		{
			if((iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX+1][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+2])==BLOCK_COLOR_NONE))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[1][0]=iColor;
				iBlock[2][2]=iColor;
			}
		}
		/**
			 [#]#
			 ##
		*/
		else if((iAngle==1)||(iAngle==3))
		{
			if((iX>=0)&&(iX<=7)&&(iY<=21)
					&&(LOWORD(iField[iX+2][iY])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+2][iY+1])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX][iY+2])==BLOCK_COLOR_NONE)
					&&(LOWORD(iField[iX+1][iY+2])==BLOCK_COLOR_NONE))
			{
				rotated=true;
				ClearBlock(iBlock);
				iBlock[1][1]=iColor;
				iBlock[2][1]=iColor;
				iBlock[0][2]=iColor;
				iBlock[1][2]=iColor;
			}
		}
	}
	if(rotated==false)
	{
		if(direction==ROTATE_LEFT)
			iAngle++;
		else if(direction==ROTATE_RIGHT)
			iAngle--;
		if(iAngle>3)
			iAngle=0;
		else if(iAngle<0)
			iAngle=3;
	}
	Put();
}

int CField::Randnum(int limit)
{
	return((rand())%limit);
}

int CField::CheckFullRow(void)
{
	bool fullrow=false;
	int rowCount=0;
	for(int y=(HEIGHT-1);y>=0;y--)
	{
		fullrow=true;
		for(int x=0;x<10;x++)
		{
			if((LOWORD(iField[x][y])==BLOCK_COLOR_NONE)||(HIWORD(iField[x][y])==BLOCK_SOLID))
				fullrow=false;
		}
		if(fullrow)
		{
			if(iStatus==STATUS_REMOVE_LINE)
				RemoveFullRow(y++);
			else
				SetRemoveFullRow(y);
			rowCount++;
		}
	}
	if(iStatus==STATUS_REMOVE_LINE)
		iStatus=STATUS_NORMAL;
	else if(rowCount>0)
	{
		iStatus=STATUS_REMOVE_LINE;
		SetFlashCounter(0);
	}
	return(rowCount);
}

void CField::SetRemoveFullRow(int row)
{
	int x(0);
	for(x=0;x<10;x++)
		iField[x][row]=MAKELONG(iField[x][row],BLOCK_REMOVE);
}

void CField::RemoveFullRow(int row)
{
	int y(0),x(0);
	for(y=row-1;y>=0;y--)
	{
		for(x=0;x<10;x++)
			iField[x][y+1]=iField[x][y];
	}
}

void CField::ResetFlashCounter()
{
	iFlashCounter=0;
	iResets++;
	if(iResets>2)
	{
		iResets=0;
		CheckFullRow();
		SetStatus(STATUS_NORMAL);
		NewBlock();
		ClearPos();
		Put();
	}	
}

void CField::SetStartHeight(int height)
{
	int block=0;
	for(int y=HEIGHT-1;y>(HEIGHT-(height+1));y--)
	{
		for(int x=0;x<WIDTH;x++)
		{
			block=Randnum(30);
			if(block<7)
				iField[x][y]=MAKELONG(block,0);
		}
	}
}

bool CField::AddSolidBlocks(int nr)
{
	int y(0), x(0);
	iY-=nr;
	if(iY<0)
		iY=0;
	//Check if there is room for more solid blocks
	for(y=0;y<nr;y++)
	{
		for(x=0;x<WIDTH;x++)
		{
			if(iField[x][y]!=LOWORD(BLOCK_COLOR_NONE))
				return(false);
		}
	}

	//Move blocks
	for(y=nr;y<HEIGHT;y++)
	{
		for(x=0;x<WIDTH;x++)
		{
			iField[x][y-nr]=iField[x][y];
		}
	}
	//Add solid blocks
	for(y=HEIGHT-nr;y<HEIGHT;y++)
	{
		for(x=0;x<WIDTH;x++)
		{
			iField[x][y]=MAKELONG(BLOCK_COLOR_GRAY,BLOCK_SOLID);
		}
	}
	return(true);
}

int CField::RemoveSolidBlocks(int nr)
{
	int y(0),x(0);
	ClearPos(); //Remove current block
	//Check if there are any solid block rows.
	for(y=HEIGHT-nr;y<HEIGHT;y++)
	{
		for(x=0;x<WIDTH;x++)
		{
			if(iField[x][y]!=MAKELONG(BLOCK_COLOR_GRAY,BLOCK_SOLID))
			{
				nr--;
				break;
			}
		}
	}

	//Move game field down
	for(y=HEIGHT-nr-1;y>=nr;y--)
	{
		for(x=0;x<WIDTH;x++)
			iField[x][y+nr]=iField[x][y];
	}
	Put(); //Add current block
	return(nr);
}

void CField::Flip()
{
	int found(-1),block(4),x(0),y(0);
	ClearPos(); //Remove current block
	while((found==-1)&&(y<HEIGHT))
	{
		while((found==-1)&&(x<WIDTH))
		{
			if(iField[x][y]!=LOWORD(BLOCK_COLOR_NONE))
			{
				found=y;
			}
			x++;
		};
		x=0;
		y++;
	};

	for(int y=0;y<4;y++)
	{
		for(int x=0;x<4;x++)
		{
			if(iBlock[x][y]!=BLOCK_COLOR_NONE)
				block=y+1;
		}
	}
	if((found!=-1)&&(found!=(HEIGHT-1))&&(found>block+iY))
	{
		int tmp(0),bottom(HEIGHT-1),x(0);
		int stop=(HEIGHT-found)/2+found;
		for(;found<stop;found++)
		{
			for(x=0;x<WIDTH;x++)
			{
				tmp=iField[x][found];
				iField[x][found]=iField[x][bottom];
				iField[x][bottom]=tmp;
			}
			bottom--;
		}
	}
	Put(); //Paint current block
}
