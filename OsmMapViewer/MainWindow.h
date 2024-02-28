#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow ui;
	double viewCenterLon = 0;
	double viewCenterLat = 0;
	double viewSize = 0.01;

	void SetViewCenterToBerlin();

	void SetViewCenterAndSize(double lat, double lon, double size);
};
