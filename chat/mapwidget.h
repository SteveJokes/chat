#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include <QWidget>
//#include <QtWebKit>
#include <QtWebKit/QWebFrame>
#include <QTimer>

namespace Ui {
class MapWidget;
}

class MapWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MapWidget(QWidget *parent = 0);
    ~MapWidget();

private:
    void setCoordinate(QString lon,QString lat);

private:
    Ui::MapWidget *ui;
    QTimer *timer;
public slots:
    void getCoordinate(QString lon,QString lat);
private slots:
    void on_pushButtonStreetMap_clicked();
    void on_pushButtonSatelliteMap_clicked();
    void slotPopulateJavaScriptWindowObject();
    void slotTimeout();

};

#endif // WIDGET_H
