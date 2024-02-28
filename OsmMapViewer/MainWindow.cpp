#include "MainWindow.h"
#include <QMessageBox>
#include <QtNetwork/QHttpMultiPart>

MainWindow::MainWindow(QWidget *parent)	: QMainWindow(parent)
{
	ui.setupUi(this);
    
    connect(ui.viewToBerlinButton, &QPushButton::pressed, this, &MainWindow::SetViewCenterToBerlin);

    SetViewCenterToBerlin();
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

    ui.viewCenterLabel->setText(QString::asprintf("Lat: %f, Lon: %f", lat, lon));
    ui.viewSizeLabel->setText(QString::asprintf("%f degrees", size));

    double lat0 = lat - size;
    double lat1 = lat + size;
    double lon0 = lon - size;
    double lon1 = lon + size;

    DownloadOsmBbox(lat0, lon0, lat1, lon1);
}

QString MainWindow::GetBboxString(double lat0, double lon0, double lat1, double lon1)
{
    return QString::asprintf("%f,%f,%f,%f", lat0, lon0, lat1, lon1);
}

void MainWindow::DownloadOsmBbox(double lat0, double lon0, double lat1, double lon1)
{
    const QString urlSpec = ui.overpassUrlBox->text().trimmed();
    if (urlSpec.isEmpty())
    {
        return;
    }

    const QUrl newUrl = QUrl::fromUserInput(urlSpec);
    if (!newUrl.isValid()) 
    {
        QMessageBox::information(this, tr("Error"),
            tr("Invalid URL: %1: %2").arg(urlSpec, newUrl.errorString()));
        return;
    }

    QString bboxStr = GetBboxString(lat0, lon0, lat1, lon1);
    QString overpassCode = QString("[out:xml][timeout:25];(way[\"highway\"=\"primary\"](%1););out geom;").arg(bboxStr);

    QByteArray postData = "data=" + QUrl::toPercentEncoding(overpassCode);

    QNetworkReply* replyPtr = qnam.post(QNetworkRequest(newUrl), postData);
    reply.reset(replyPtr);
    connect(reply.get(), &QNetworkReply::finished, this, &MainWindow::HttpFinished);
    connect(reply.get(), &QNetworkReply::sslErrors, this, &MainWindow::SslErrors);
}

void MainWindow::SslErrors(const QList<QSslError>& errors)
{
    QString errorString;
    for (const QSslError& error : errors)
    {
        if (!errorString.isEmpty())
            errorString += '\n';
        errorString += error.errorString();
    }

    if (QMessageBox::warning(this, tr("TLS Errors"),
        tr("One or more TLS errors has occurred:\n%1").arg(errorString),
        QMessageBox::Ignore | QMessageBox::Abort)
        == QMessageBox::Ignore) {
        reply->ignoreSslErrors();
    }
}

void MainWindow::HttpFinished()
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    QByteArray responsePayload = reply->readAll();
    if (statusCode == 200)
    {
        qInfo() << "Overpass request result: " << QString(responsePayload);
    }
    else
    {
        QString responseStr = QString(responsePayload);
        qFatal() << "Overpass request failed with code " << statusCode << ". Message: " << responseStr;
    }
    
}