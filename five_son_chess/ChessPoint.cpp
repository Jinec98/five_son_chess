#include "ChessPoint.h"

ChessPoint::ChessPoint()
{

}

ChessPoint::ChessPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}

int ChessPoint::getX()
{
	return x;
}

int ChessPoint::getY()
{
	return y;
}
