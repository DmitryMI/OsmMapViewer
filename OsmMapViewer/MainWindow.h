#pragma once

#include <QMainWindow>
#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>
#include <QtNetwork/QSslError>
#include <QtNetwork/QNetworkReply>
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
	double osmChunkSize = 0.001;

	QNetworkAccessManager qnam;
	QScopedPointer<QNetworkReply, QScopedPointerDeleteLater> reply;

	void SetViewCenterToBerlin();

	void SetViewCenterAndSize(double lat, double lon, double size);

	QString GetBboxString(double lat0, double lon0, double lat1, double lon1);

	void DownloadOsmBbox(double lat0, double lon0, double lat1, double lon1);

	void HttpFinished();

	void SslErrors(const QList<QSslError>& errors);
};
