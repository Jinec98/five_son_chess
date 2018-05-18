#pragma once

#include <QtWidgets/QMainWindow>
#include <QApplication>
#include <QThread>
#include <QTextCodec>
#include <QPainter>
#include <QPushButton>
#include <QToolBar>
#include <QMouseEvent>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDebug>
#include <math.h>
#include "GameModel.h"

class five_son_chess : public QMainWindow
{
	Q_OBJECT

public:
	five_son_chess(QWidget *parent = Q_NULLPTR);
	~five_son_chess();

protected:
	void paintEvent(QPaintEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	GameModel * game;
	QPushButton *playBtn;
	QPushButton *retractBtn;
	QPushButton *submitBtn;
	QPushButton *drawBtn;
	QPushButton *showBtn;
	int clickPosRow, clickPosCol;
	int thisPosRow, thisPosCol;
	void initGame();

private slots:
	void play();
	void retract();
	void draw();
	void submit();
	void replay();
};
