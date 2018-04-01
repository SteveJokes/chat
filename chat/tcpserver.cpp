#include "tcpserver.h"
#include "ui_tcpserver.h"

#include <QFile>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

TcpServer::TcpServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TcpServer)
{
    ui->setupUi(this);
    setFixedSize(350,180);
    tcpPort = 8000;
    fileFlag=0;
    tcpServer = new QTcpServer(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendMessage()));
    //connect(tcpServer, SIGNAL(newConnection()), this, SLOT(sendMessage()));
    initServer();
}

TcpServer::~TcpServer()
{
    delete ui;
}


void TcpServer::initServer()
{
    payloadSize = 64*1024;
    TotalBytes = 0;
    bytesWritten = 0;
    bytesToWrite = 0;

    ui->serverStatusLabel->setText(tr("select the file"));
    ui->progressBar->reset();
    ui->serverOpenBtn->setEnabled(true);
    ui->serverSendBtn->setEnabled(false);

    //tcpServer->close();
}


void TcpServer::sendMessage()
{
    //if(fileFlag==0)
    {
        ui->serverSendBtn->setEnabled(false);//图形界面相应变化
        clientConnection = tcpServer->nextPendingConnection();
        connect(clientConnection, SIGNAL(bytesWritten(qint64)),
                this, SLOT(updateClientProgress(qint64)));
        ui->serverStatusLabel->setText(tr("sending file %1 ").arg(theFileName));
    }
    //通过文件名新建一个文件对象，然后调用发送文件函数
    localFile = new QFile(fileName);
    if(!localFile->open((QFile::ReadOnly))){
        QMessageBox::warning(this, tr("app"), tr("can't send file' %1:\n%2")
                             .arg(fileName).arg(localFile->errorString()));
        return;
    }
    TotalBytes = localFile->size();
    QDataStream sendOut(&outBlock, QIODevice::WriteOnly);
    sendOut.setVersion(QDataStream::Qt_4_7);
    time.start();  // ʼʱ
    QString currentFile = fileName.right(fileName.size()
                                         - fileName.lastIndexOf('/')-1);
    sendOut << qint64(0) << qint64(0) << currentFile;
    TotalBytes += outBlock.size();
    sendOut.device()->seek(0);
    sendOut << TotalBytes << qint64((outBlock.size() - sizeof(qint64)*2));
    bytesToWrite = TotalBytes - clientConnection->write(outBlock);
    outBlock.resize(0);
}


void TcpServer::updateClientProgress(qint64 numBytes)
{
    qApp->processEvents();
    bytesWritten += (int)numBytes;
    if (bytesToWrite > 0) {
        outBlock = localFile->read(qMin(bytesToWrite, payloadSize));
        bytesToWrite -= (int)clientConnection->write(outBlock);
        outBlock.resize(0);
    } else {
        localFile->close();
    }
    ui->progressBar->setMaximum(TotalBytes);
    ui->progressBar->setValue(bytesWritten);

    float useTime = time.elapsed();
    double speed = bytesWritten / useTime;
    ui->serverStatusLabel->setText(tr("sended %1MB (%2MB/s) "
                                      "\nof%3MB time:%4S\nt_remain%5")
                                   .arg(bytesWritten / (1024*1024))
                                   .arg(speed*1000 / (1024*1024), 0, 'f', 2)
                                   .arg(TotalBytes / (1024 * 1024))
                                   .arg(useTime/1000, 0, 'f', 0)
                                   .arg(TotalBytes/speed/1000 - useTime/1000, 0, 'f', 0));

    if(bytesWritten == TotalBytes) {
        localFile->close();
        tcpServer->close();
        if(fileFlag==1)
        {
            clientConnection->abort();
            fileFlag=0;
            close();
        }
        ui->serverStatusLabel->setText(tr("send %1 succed").arg(theFileName));

    }
}


void TcpServer::on_serverOpenBtn_clicked()
{
    QFileDialog *FileDialog=new QFileDialog;
    FileDialog->setFixedSize(300,200);
    //FileDialog->show();
    fileName = FileDialog->getOpenFileName(this);
    if(!fileName.isEmpty())
    {
        theFileName = fileName.right(fileName.size() - fileName.lastIndexOf('/')-1);
        ui->serverStatusLabel->setText(tr("file:%1 ").arg(theFileName));
        ui->serverSendBtn->setEnabled(true);
        ui->serverOpenBtn->setEnabled(false);
    }
}


void TcpServer::on_serverSendBtn_clicked()//点击了发送文件按钮，发射发送文件信号
{
    if(!tcpServer->listen(QHostAddress::Any,tcpPort))//始
    {
        qDebug() << tcpServer->errorString();
        close();
        return;
    }
    ui->serverStatusLabel->setText(tr("waiting... ..."));
    emit sendFileName(theFileName);
}


void TcpServer::on_serverCloseBtn_clicked()//关闭按钮相应函数，执行关闭tcp客户端和文件，断开连接并关闭界面
{
    if(tcpServer->isListening())
    {
        tcpServer->close();
        if (localFile->isOpen())
            localFile->close();
        clientConnection->abort();
    }
    close();
}

void TcpServer::slotVoiceSend(QString voiceFile)//发送语音信息
{
    tcpServer->listen(QHostAddress::Any,tcpPort);
    fileName=voiceFile;
    fileFlag=1;
}



void TcpServer::refused()
{
    tcpServer->close();
    ui->serverStatusLabel->setText(tr("refused !"));
}


void TcpServer::closeEvent(QCloseEvent *)
{
    on_serverCloseBtn_clicked();
}

