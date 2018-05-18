#include "five_son_chess.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	five_son_chess w;
	w.show();
	return a.exec();
}
