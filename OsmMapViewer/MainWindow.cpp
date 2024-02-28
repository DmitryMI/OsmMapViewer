#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)	: QMainWindow(parent)
{
	ui.setupUi(this);
}

MainWindow::~MainWindow()
{
}

void MainWindow::SetViewCenterToBerlin()
{
	double lat = 52.520008;
	double lon = 13.404954;
	SetViewCenterAndSize(lat, lon, viewSize);
}

void MainWindow::SetViewCenterAndSize(double lat, double lon, double size)
{
	viewCenterLat = lat;
	viewCenterLon = lon;
	viewSize = size;
}
