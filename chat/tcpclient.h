#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QDialog>
#include <QHostAddress>
#include <QFile>
#include <QTime>
class QTcpSocket;

namespace Ui {
class TcpClient;
}

class TcpClient : public QDialog
{
    Q_OBJECT

public:
    explicit TcpClient(QWidget *parent = 0);
    ~TcpClient();

    void setHostAddress(QHostAddress address);//设置主机地址
    void setFileName(QString fileName);//设置文件名

protected:
    void closeEvent(QCloseEvent *);//关闭事件

private:
    Ui::TcpClient *ui;

    QTcpSocket *tcpClient;//tcp客户端 一种tcpsocket类
    quint16 blockSize;//块尺寸
    QHostAddress hostAddress;//主机地址
    qint16 tcpPort;//tcp端口号

    qint64 TotalBytes;//要发送总的比特数
    qint64 bytesReceived;//接收到的比特数
    qint64 bytesToReceive;//还需要接受打比特数
    qint64 fileNameSize;//文件名的大小
    QString fileName;//文件名
    QFile *clocalFile;//本地文件
    QByteArray inBlock;

    QTime time;

private slots:
    void on_tcpClientCancleBtn_clicked();//客户端取消按钮槽函数
    void on_tcpClientCloseBtn_clicked();//关闭按钮

    void newConnect();//新的tcp连接
    void readMessage();//读数据
    void displayError(QAbstractSocket::SocketError);//显示错误信息
signals:
    void sigGetVoiceFile(QString voiceFile);
};

#endif // TCPCLIENT_H
