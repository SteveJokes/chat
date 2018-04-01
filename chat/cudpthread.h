#ifndef CUDPTHREAD_H
#define CUDPTHREAD_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QByteArray>
#include <QUdpSocket>
#include <QThread>
class CUdpThread : public QObject
{
    Q_OBJECT

public:
    CUdpThread();
    ~CUdpThread();
public:
    static QString IpAddress;
private:
    QUdpSocket * udpsocketSend;
    QUdpSocket * udpSocketRecv;
    bool stopFlag;
private slots:
     void ReadPendingDatagrams();
     void run();
     void slotSendData(const QByteArray &byte_array);
signals:
     void signalSendData(const QByteArray &byte_array);
};

#endif // CUDPTHREAD_H
