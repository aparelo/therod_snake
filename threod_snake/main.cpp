#include "field.h"
#include <QtWidgets/QApplication>
#include <QtCore>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	field game;
	game.show();


	return a.exec();
}





