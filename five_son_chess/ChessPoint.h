#pragma once
#include <QtWidgets/QMainWindow>
class ChessPoint
{
public:
	int x;
	int y;

	ChessPoint();
	ChessPoint(int x, int y);
	int getX();
	int getY();
};