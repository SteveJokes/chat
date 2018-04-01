#include "mapwidget.h"
#include "ui_map_widget.h"
#include <QDebug>

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MapWidget)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slotTimeout()));
    timer->start(10000);
    QString strMapPath="file://";
    strMapPath+=QCoreApplication::applicationDirPath();
    strMapPath+="/release/map.html";
    QUrl url("file:///nfs/chat/release/map.html");
    ui->webView->load(url);
    ui->webView->setContentsMargins(0,0,0,0);
    ui->webView->setTextSizeMultiplier(1);//设置网页字体大小
    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(slotPopulateJavaScriptWindowObject()));
}

MapWidget::~MapWidget()
{
    delete ui;
}

void MapWidget::getCoordinate(QString lon,QString lat)
{
    QString tempLon="mouse lon:"+lon+"°";
    QString tempLat="mouse lat:"+lat+"°";
    ui->labelMouseLongitude->setText(tempLon);
    ui->labelMouseLatitude->setText(tempLat);
}

void MapWidget::setCoordinate(QString lon,QString lat)
{
    QWebFrame *webFrame = ui->webView->page()->mainFrame();
    QString cmd = QString("showAddress(\"%1\",\"%2\")").arg(lon).arg(lat);
    webFrame->evaluateJavaScript(cmd);
}

void MapWidget::slotTimeout()
{
    static double tempLon=116.468278;
    tempLon+=0.01;

    setCoordinate(QString::number(tempLon),QString::number(39.922965));
}

void MapWidget::on_pushButtonStreetMap_clicked()
{
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("showStreetMap()");
    frame->evaluateJavaScript(cmd);
}

void MapWidget::on_pushButtonSatelliteMap_clicked()
{
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("showSatelliteMap()");
    frame->evaluateJavaScript(cmd);
}

void MapWidget::slotPopulateJavaScriptWindowObject()
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("ReinforcePC", this);
}
