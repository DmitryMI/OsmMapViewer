// OsmMapViewer.cpp : Defines the entry point for the application.
//

#include "OsmMapViewer.h"
#include <QApplication.h>
#include "MainWindow.h"

using namespace std;

int main(int argc, char** argv)
{
	QApplication app(argc, argv);

	MainWindow mainWindow;
	mainWindow.show();

	return app.exec();
}
