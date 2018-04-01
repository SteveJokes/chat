#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(slotTimeout()));
    timer->start(1000);
    QString strMapPath="file://";
    strMapPath+=QCoreApplication::applicationDirPath();
    strMapPath+="/release/map.html";
    QUrl url("file:///usr/my_file/TestMap/release/map.html");
    ui->webView->load(url);
    ui->webView->setContentsMargins(0,0,0,0);
    ui->webView->setTextSizeMultiplier(1);//设置网页字体大小
    connect(ui->webView->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
            this, SLOT(slotPopulateJavaScriptWindowObject()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::getCoordinate(QString lon,QString lat)
{
    QString tempLon="鼠标经度:"+lon+"°";
    QString tempLat="鼠标纬度:"+lat+"°";
    ui->labelMouseLongitude->setText(tempLon);
    ui->labelMouseLatitude->setText(tempLat);
}

void Widget::setCoordinate(QString lon,QString lat)
{
    QWebFrame *webFrame = ui->webView->page()->mainFrame();
    QString cmd = QString("showAddress(\"%1\",\"%2\")").arg(lon).arg(lat);
    webFrame->evaluateJavaScript(cmd);
}

void Widget::slotTimeout()
{
    static double tempLon=116.468278;
    tempLon+=0.01;

    setCoordinate(QString::number(tempLon),QString::number(39.922965));
}

void Widget::on_pushButtonStreetMap_clicked()
{
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("showStreetMap()");
    frame->evaluateJavaScript(cmd);
}

void Widget::on_pushButtonSatelliteMap_clicked()
{
    QWebFrame *frame = ui->webView->page()->mainFrame();
    QString cmd = QString("showSatelliteMap()");
    frame->evaluateJavaScript(cmd);
}

void Widget::slotPopulateJavaScriptWindowObject()
{
    ui->webView->page()->mainFrame()->addToJavaScriptWindowObject("ReinforcePC", this);
}
