#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWebKit>
#include <QtWebKit/QWebFrame>
#include <QTimer>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    void setCoordinate(QString lon,QString lat);

private:
    Ui::Widget *ui;
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
