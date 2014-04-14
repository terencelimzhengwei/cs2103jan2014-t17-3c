//@author A0097330H
#include <QtWidgets/QApplication>
#include "timewisegui.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	TimeWiseGUI w;
	w.show();
	return a.exec();
}
