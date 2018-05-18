#include "five_son_chess.h"

const int BoardMargin = 30;
const int Radius = 15;
const int MarkSize = 6;
const int MarkRadius = 3;
const int BlockSize = 40;
const int PosDelta = 20;
const int BtnArea = 50;

five_son_chess::five_son_chess(QWidget *parent)
	: QMainWindow(parent)
{
	game = new GameModel;
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GBK"));
	setWindowTitle(QString::fromLocal8Bit("五子棋@Jinec"));
	setFixedSize(BoardMargin * 2 + BlockSize * BoardSizeNum, BoardMargin * 2 + BlockSize * BoardSizeNum + BtnArea);
	setMouseTracking(true);

	playBtn = new QPushButton(QString::fromLocal8Bit("开始"), this);
	playBtn->setGeometry(45,BoardMargin * 2 + BlockSize * BoardSizeNum,50,30);
	connect(playBtn, SIGNAL(clicked()), this, SLOT(play()));

	retractBtn = new QPushButton(QString::fromLocal8Bit("悔棋"), this);
	retractBtn->setGeometry(165, BoardMargin * 2 + BlockSize * BoardSizeNum, 50, 30);
	connect(retractBtn, SIGNAL(clicked()), this, SLOT(retract()));

	drawBtn = new QPushButton(QString::fromLocal8Bit("求和"), this);
	drawBtn->setGeometry(285, BoardMargin * 2 + BlockSize * BoardSizeNum, 50, 30);
	connect(drawBtn, SIGNAL(clicked()), this, SLOT(draw()));

	submitBtn = new QPushButton(QString::fromLocal8Bit("认输"), this);
	submitBtn->setGeometry(405, BoardMargin * 2 + BlockSize * BoardSizeNum, 50, 30);
	connect(submitBtn, SIGNAL(clicked()), this, SLOT(submit()));

	showBtn = new QPushButton(QString::fromLocal8Bit("复盘"), this);
	showBtn->setGeometry(525, BoardMargin * 2 + BlockSize * BoardSizeNum, 50, 30);
	connect(showBtn, SIGNAL(clicked()), this, SLOT(replay()));

}

five_son_chess::~five_son_chess()
{
	if (game)
	{
		delete game;
		game = nullptr;
	}
}

void five_son_chess::play()
{
	initGame();
	playBtn->setEnabled(false);
}

void five_son_chess::retract()
{
	if (game->gameStatus == PLAYING)
	{
		int ans;
		if (game->gameMapVec[thisPosRow][thisPosCol] == 1)
			ans = QMessageBox::question(this, QString::fromLocal8Bit("悔棋"), QString::fromLocal8Bit("白棋请求悔棋，请问黑棋是否同意？"), QMessageBox::Yes, QMessageBox::No);
		else if (game->gameMapVec[thisPosRow][thisPosCol] == -1)
			ans = QMessageBox::question(this, QString::fromLocal8Bit("悔棋"), QString::fromLocal8Bit("黑棋请求悔棋，请问白棋是否同意？"), QMessageBox::Yes, QMessageBox::No);

		if (ans == QMessageBox::Yes)
		{
			game->gameMapVec[thisPosRow][thisPosCol] = 0;
			game->cp.erase(game->cp.end()-1);
			game->playerFlag = !game->playerFlag;
			repaint();
			update();
		}
	}
}


void five_son_chess::draw()
{
	if (game->gameStatus == PLAYING)
	{
		int ans;
		if (game->gameMapVec[thisPosRow][thisPosCol] == 1)
			ans = QMessageBox::question(this, QString::fromLocal8Bit("求和"), QString::fromLocal8Bit("黑棋求和，请问白棋是否同意？"), QMessageBox::Yes, QMessageBox::No);
		else if (game->gameMapVec[thisPosRow][thisPosCol] == -1)
			ans = QMessageBox::question(this, QString::fromLocal8Bit("求和"), QString::fromLocal8Bit("白棋求和，请问黑棋是否同意？"), QMessageBox::Yes, QMessageBox::No);

		if (ans == QMessageBox::Yes)
		{
			QMessageBox::information(this, QString::fromLocal8Bit("和棋"), QString::fromLocal8Bit("和棋，没有人获胜！"), QMessageBox::Ok);

			game->gameStatus = DEAD;
			playBtn->setEnabled(true);
		}
	}
}

void five_son_chess::submit()
{
	if (game->gameStatus == PLAYING)
	{
		int ans;
		ans = QMessageBox::question(this, QString::fromLocal8Bit("认输"), QString::fromLocal8Bit("确定要认输吗？"), QMessageBox::Yes, QMessageBox::No);

		if (ans == QMessageBox::Yes)
		{
			if (game->gameMapVec[thisPosRow][thisPosCol] == 1)
				QMessageBox::information(this, QString::fromLocal8Bit("恭喜"), QString::fromLocal8Bit("白棋获胜！"), QMessageBox::Ok);
			else if (game->gameMapVec[thisPosRow][thisPosCol] == -1)
				QMessageBox::information(this, QString::fromLocal8Bit("恭喜"), QString::fromLocal8Bit("黑棋获胜！"), QMessageBox::Ok);

			game->gameStatus = WIN;
			playBtn->setEnabled(true);
		}
	}
}
void five_son_chess::replay()
{
	if (game->gameStatus != PLAYING)
	{
		game->mode = false;
		game->startGame();
		repaint();
		update();
		QThread::msleep(500);
		for (auto p : game->cp)
		{
			game->setChess(p.x, p.y);
			repaint();
			update();
			QThread::msleep(300);
		}
		game->mode = true;
		QMessageBox::information(this, QString::fromLocal8Bit("复盘"), QString::fromLocal8Bit("复盘结束！"), QMessageBox::Ok);
	}
}

void five_son_chess::initGame()
{
	game->gameStatus = PLAYING;
	game->startGame();
	update();
}

void five_son_chess::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	for (int i = 0; i <= BoardSizeNum ; i++)
	{
		painter.drawLine(BoardMargin + BlockSize * i, BoardMargin, BoardMargin + BlockSize * i, size().height() - BoardMargin - BtnArea);
		painter.drawLine(BoardMargin, BoardMargin + BlockSize * i, size().width() - BoardMargin, BoardMargin + BlockSize * i);
	}

	QBrush brush;
	brush.setStyle(Qt::SolidPattern);

	brush.setColor(Qt::black);
	painter.setBrush(brush);
	painter.drawEllipse(BoardMargin + BlockSize * 3 - MarkRadius, BoardMargin + BlockSize * 3 - MarkRadius, MarkRadius * 2, MarkRadius * 2);
	painter.drawEllipse(BoardMargin + BlockSize * 11 - MarkRadius, BoardMargin + BlockSize * 3 - MarkRadius, MarkRadius * 2, MarkRadius * 2);
	painter.drawEllipse(BoardMargin + BlockSize * 3 - MarkRadius, BoardMargin + BlockSize * 11 - MarkRadius, MarkRadius * 2, MarkRadius * 2);
	painter.drawEllipse(BoardMargin + BlockSize * 11 - MarkRadius, BoardMargin + BlockSize * 11 - MarkRadius, MarkRadius * 2, MarkRadius * 2);
	painter.drawEllipse(BoardMargin + BlockSize * 7 - MarkRadius, BoardMargin + BlockSize * 7 - MarkRadius, MarkRadius * 2, MarkRadius * 2);
	
	if (clickPosRow >= 0 && clickPosRow <= BoardSizeNum &&
		clickPosCol >= 0 && clickPosCol <= BoardSizeNum &&
		game->gameMapVec[clickPosRow][clickPosCol] == 0)
	{
		if (game->playerFlag)
			brush.setColor(Qt::white);
		else
			brush.setColor(Qt::black);
		painter.setBrush(brush);
		painter.drawRect(BoardMargin + BlockSize * clickPosCol - MarkSize / 2, BoardMargin + BlockSize * clickPosRow - MarkSize / 2, MarkSize, MarkSize);
	}
	for(int i = 0; i <= BoardSizeNum; i++)
		for (int j = 0; j <= BoardSizeNum; j++)
		{
			if (game->gameMapVec[i][j] == 1)
			{
				brush.setColor(Qt::white);
				painter.setBrush(brush);
				painter.drawEllipse(BoardMargin + BlockSize * j - Radius, BoardMargin + BlockSize * i - Radius, Radius * 2, Radius * 2);
			}
			else if (game->gameMapVec[i][j] == -1)
			{
				brush.setColor(Qt::black);
				painter.setBrush(brush);
				painter.drawEllipse(BoardMargin + BlockSize * j - Radius, BoardMargin + BlockSize * i - Radius, Radius * 2, Radius * 2);
			}
		}

}

void five_son_chess::mouseMoveEvent(QMouseEvent *event)
{
	int x = event->x();
	int y = event->y();

	if (x >= BoardMargin  && x <= size().width() - BoardMargin &&
		y >= BoardMargin  && y <= size().height() - BoardMargin - BtnArea)
	{
		int col = x / BlockSize;
		int row = y / BlockSize;
		int leftTopPosX = BoardMargin + BlockSize * col;
		int leftTopPosY = BoardMargin + BlockSize * row;

		clickPosRow = -1;
		clickPosCol = -1;
		int len = 0;
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < PosDelta)
		{
			clickPosRow = row;
			clickPosCol = col;
		}
		len = sqrt((x - leftTopPosX - BlockSize) * (x - leftTopPosX - BlockSize) + (y - leftTopPosY) * (y - leftTopPosY));
		if (len < PosDelta)
		{
			clickPosRow = row;
			clickPosCol = col + 1;
		}
		len = sqrt((x - leftTopPosX) * (x - leftTopPosX) + (y - leftTopPosY - BlockSize) * (y - leftTopPosY - BlockSize));
		if (len < PosDelta)
		{
			clickPosRow = row + 1;
			clickPosCol = col;
		}
		len = sqrt((x - leftTopPosX - BlockSize) * (x - leftTopPosX - BlockSize) + (y - leftTopPosY - BlockSize) * (y - leftTopPosY - BlockSize));
		if (len < PosDelta)
		{
			clickPosRow = row + 1;
			clickPosCol = col + 1;
		}
	}
	update();
}

void five_son_chess::mouseReleaseEvent(QMouseEvent *event)
{
	if (game->gameStatus == PLAYING &&
		clickPosRow != -1 && clickPosCol != -1 &&
		game->gameMapVec[clickPosRow][clickPosCol] == 0)
	{
		thisPosRow = clickPosRow;
		thisPosCol = clickPosCol;
		game->setChess(clickPosRow, clickPosCol);
		update();
	}

	if (clickPosRow >= 0 && clickPosRow <= BoardSizeNum &&
		clickPosCol >= 0 && clickPosCol <= BoardSizeNum &&
		(game->gameMapVec[clickPosRow][clickPosCol] == 1 ||
			game->gameMapVec[clickPosRow][clickPosCol] == -1))
	{
		if (game->isWin(clickPosRow, clickPosCol) && game->gameStatus == PLAYING)
		{
			if (game->gameMapVec[clickPosRow][clickPosCol] == 1)
				QMessageBox::information(this, QString::fromLocal8Bit("恭喜"), QString::fromLocal8Bit("白棋获胜！"), QMessageBox::Ok);
			else if (game->gameMapVec[clickPosRow][clickPosCol] == -1)
				QMessageBox::information(this, QString::fromLocal8Bit("恭喜"), QString::fromLocal8Bit("黑棋获胜！"), QMessageBox::Ok);

			game->gameStatus = WIN;
			playBtn->setEnabled(true);
		}
	}

	if (game->isDead() && game->gameStatus == PLAYING)
	{
		QMessageBox::information(this, QString::fromLocal8Bit("和棋"), QString::fromLocal8Bit("和棋，没有人获胜！"), QMessageBox::Ok);

		game->gameStatus = DEAD;
		playBtn->setEnabled(true);
	}
}