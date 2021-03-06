#include "tcpclient.h"
#include "ui_tcpclient.h"

#include <QTcpSocket>
#include <QDebug>
#include <QMessageBox>

TcpClient::TcpClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpClient)
{
    ui->setupUi(this);

    setFixedSize(350,180);

    TotalBytes = 0;
    bytesReceived = 0;
    fileNameSize = 0;

    tcpClient = new QTcpSocket(this);
    tcpPort = 8000;
    connect(tcpClient, SIGNAL(readyRead()), this, SLOT(readMessage()));
    connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this,
            SLOT(displayError(QAbstractSocket::SocketError)));
}

TcpClient::~TcpClient()
{
    delete ui;
}


void TcpClient::setFileName(QString fileName)
{
    clocalFile = new QFile(fileName);
}


void TcpClient::setHostAddress(QHostAddress address)
{
    hostAddress = address;
    newConnect();
}


void TcpClient::newConnect()
{
    blockSize = 0;
    tcpClient->abort();
    tcpClient->connectToHost(hostAddress, tcpPort);
    time.start();
}


void TcpClient::readMessage()
{
    QDataStream in(tcpClient);
    in.setVersion(QDataStream::Qt_4_7);

    float useTime = time.elapsed();

    if (bytesReceived <= sizeof(qint64)*2) {
        if ((tcpClient->bytesAvailable()
             >= sizeof(qint64)*2) && (fileNameSize == 0))
        {
            in>>TotalBytes>>fileNameSize;
            bytesReceived += sizeof(qint64)*2;
        }
        if((tcpClient->bytesAvailable() >= fileNameSize) && (fileNameSize != 0)){
            in>>fileName;
            bytesReceived +=fileNameSize;

            if(!clocalFile->open(QFile::WriteOnly)){
                QMessageBox::warning(this,tr("application"),tr("can't read : %1:\n%2.")
                                     .arg(fileName).arg(clocalFile->errorString()));
                return;
            }
        } else {
            return;
        }
    }
    if (bytesReceived < TotalBytes) {
        bytesReceived += tcpClient->bytesAvailable();
        inBlock = tcpClient->readAll();
        clocalFile->write(inBlock);
        inBlock.resize(0);
    }
    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesReceived);

    double speed = bytesReceived / useTime;
    ui->tcpClientStatusLabel->setText(tr("receaved %1MB (%2MB/s) "
                                         "\nof%3MB used time:%4s\n remain%5s")
                                      .arg(bytesReceived / (1024*1024))
                                      .arg(speed*1000/(1024*1024),0,'f',2)
                                      .arg(TotalBytes / (1024 * 1024))
                                      .arg(useTime/1000,0,'f',0)
                                      .arg(TotalBytes/speed/1000 - useTime/1000,0,'f',0));
    if(bytesReceived == TotalBytes)
    {
        clocalFile->close();
        tcpClient->close();
        ui->tcpClientStatusLabel->setText(tr("receive %1 completed")
                                          .arg(fileName));
        emit sigGetVoiceFile(fileName);
        tcpClient->abort();
        if (clocalFile->isOpen())
            clocalFile->close();
        close();
    }
}

//
void TcpClient::displayError(QAbstractSocket::SocketError socketError)
{
    switch(socketError)
    {
    case QAbstractSocket::RemoteHostClosedError : break;
    default : qDebug() << tcpClient->errorString();
    }
}



void TcpClient::on_tcpClientCancleBtn_clicked()
{
    tcpClient->abort();
    if (clocalFile->isOpen())
        clocalFile->close();
}


void TcpClient::on_tcpClientCloseBtn_clicked()
{
    tcpClient->abort();
    if (clocalFile->isOpen())
        clocalFile->close();
    close();
}


void TcpClient::closeEvent(QCloseEvent *)
{
    on_tcpClientCloseBtn_clicked();
}

