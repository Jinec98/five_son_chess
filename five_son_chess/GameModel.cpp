#include "GameModel.h"

GameModel::GameModel()
{

}

void GameModel::startGame()
{
	for (int i = 0; i <= BoardSizeNum; i++)
	{
		for (int j = 0; j <= BoardSizeNum; j++)
			gameMapVec[i][j] = 0;
	}
	
	if(mode)
		cp.clear();
	playerFlag = true;
}

void GameModel::setChess(int row, int col)
{
	if (playerFlag)
		gameMapVec[row][col] = 1;
	else
		gameMapVec[row][col] = -1;

	playerFlag = !playerFlag;

	if (mode)
	{
		ChessPoint p = ChessPoint(row, col);
		cp.push_back(p);
	}
}

bool GameModel::isWin(int row, int col)
{
	for (int i = 0; i < 5; i++)
	{
		if (col - i >= 0 && col - i + 4 <= BoardSizeNum &&
			gameMapVec[row][col - i] == gameMapVec[row][col - i + 1] &&
			gameMapVec[row][col - i] == gameMapVec[row][col - i + 2] &&
			gameMapVec[row][col - i] == gameMapVec[row][col - i + 3] &&
			gameMapVec[row][col - i] == gameMapVec[row][col - i + 4])
			return true;
	}
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 && row - i + 4 <= BoardSizeNum &&
			gameMapVec[row - i][col] == gameMapVec[row - i + 1][col] &&
			gameMapVec[row - i][col] == gameMapVec[row - i + 2][col] &&
			gameMapVec[row - i][col] == gameMapVec[row - i + 3][col] &&
			gameMapVec[row - i][col] == gameMapVec[row - i + 4][col])
			return true;
	}
	for (int i = 0; i < 5; i++)
	{
		if (row - i >= 0 && row - i + 4 <= BoardSizeNum && col - i >= 0 && col - i + 4 <= BoardSizeNum&&
			gameMapVec[row - i][col - i] == gameMapVec[row - i + 1][col - i + 1] &&
			gameMapVec[row - i][col - i] == gameMapVec[row - i + 2][col - i + 2] &&
			gameMapVec[row - i][col - i] == gameMapVec[row - i + 3][col - i + 3] &&
			gameMapVec[row - i][col - i] == gameMapVec[row - i + 4][col - i + 4])
			return true;
	}
	for (int i = 0; i < 5; i++)
	{
		if (row + i >= 0 && row + i - 4 <= BoardSizeNum && col - i >= 0 && col - i + 4 <= BoardSizeNum&&
			gameMapVec[row + i][col - i] == gameMapVec[row + i - 1][col - i + 1] &&
			gameMapVec[row + i][col - i] == gameMapVec[row + i - 2][col - i + 2] &&
			gameMapVec[row + i][col - i] == gameMapVec[row + i - 3][col - i + 3] &&
			gameMapVec[row + i][col - i] == gameMapVec[row + i - 4][col - i + 4])
			return true;
	}
	return false;
}

bool GameModel::isDead()
{
	for (int i = 0; i <= BoardSizeNum; i++)
		for (int j = 0; j <= BoardSizeNum; j++)
			if (!(gameMapVec[i][j] == 1 || gameMapVec[i][j] == -1))
				return false;
	return true;
}