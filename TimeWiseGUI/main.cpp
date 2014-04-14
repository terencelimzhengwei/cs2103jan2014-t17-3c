//@Gian Jian Xiang A0097330H
#include "timewisegui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	TimeWiseGUI w;
	w.show();
	return a.exec();
}
