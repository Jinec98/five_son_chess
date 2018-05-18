#pragma once
#include <vector>
#include "ChessPoint.h"

using namespace std;

enum GameStatus
{
	PLAYING,
	WIN,
	DEAD,
};

const int BoardSizeNum = 14;


class GameModel
{
public:
	GameModel();

	int gameMapVec[BoardSizeNum+1][BoardSizeNum+1];
	vector<ChessPoint> cp;
	bool playerFlag;
	bool mode = true;
	GameStatus gameStatus;

	void startGame();
	void setChess(int row, int col);
	bool isWin(int row, int col);
	bool isDead();
};