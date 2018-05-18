/********************************************************************************
** Form generated from reading UI file 'five_son_chess.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIVE_SON_CHESS_H
#define UI_FIVE_SON_CHESS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_five_son_chessClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *five_son_chessClass)
    {
        if (five_son_chessClass->objectName().isEmpty())
            five_son_chessClass->setObjectName(QStringLiteral("five_son_chessClass"));
        five_son_chessClass->resize(600, 400);
        menuBar = new QMenuBar(five_son_chessClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        five_son_chessClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(five_son_chessClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        five_son_chessClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(five_son_chessClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        five_son_chessClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(five_son_chessClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        five_son_chessClass->setStatusBar(statusBar);

        retranslateUi(five_son_chessClass);

        QMetaObject::connectSlotsByName(five_son_chessClass);
    } // setupUi

    void retranslateUi(QMainWindow *five_son_chessClass)
    {
        five_son_chessClass->setWindowTitle(QApplication::translate("five_son_chessClass", "five_son_chess", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class five_son_chessClass: public Ui_five_son_chessClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIVE_SON_CHESS_H
