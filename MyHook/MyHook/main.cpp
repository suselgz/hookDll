#include "MyHook.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyHook w;
	w.show();
	return a.exec();
}
