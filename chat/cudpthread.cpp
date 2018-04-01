#include "cudpthread.h"
#include <QDebug>
QString CUdpThread::IpAddress;

CUdpThread::CUdpThread()
{
    stopFlag=true;
}
CUdpThread::~CUdpThread()
{
    stopFlag=false;
}

void CUdpThread::run()
{
    udpsocketSend=new QUdpSocket(this);
    udpSocketRecv = new QUdpSocket(this);
    udpSocketRecv->bind(25000, QUdpSocket::ShareAddress);
    //connect
    connect(udpSocketRecv, SIGNAL(readyRead()), this, SLOT(ReadPendingDatagrams()),Qt::DirectConnection);
}

void CUdpThread::ReadPendingDatagrams()//receave data(slot function connected to udpSocketRecv readyRead()
{
    QByteArray datagram;
    while (udpSocketRecv->hasPendingDatagrams())
    {
           datagram.resize(udpSocketRecv->pendingDatagramSize());
           QHostAddress sender;
           quint16 senderPort;

           udpSocketRecv->readDatagram(
           datagram.data(),
           datagram.size(),
           &sender,
           &senderPort);
           if(datagram.size()>0)
           {
               emit signalSendData(datagram);//send the data to father object using a signal
           }
     }
}

void CUdpThread::slotSendData(const QByteArray &byte_array)//send the data to the udp client
{
    udpsocketSend->writeDatagram(byte_array,QHostAddress(IpAddress), 25000);
}
