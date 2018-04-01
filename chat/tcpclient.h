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

    void setHostAddress(QHostAddress address);//����������ַ
    void setFileName(QString fileName);//�����ļ���

protected:
    void closeEvent(QCloseEvent *);//�ر��¼�

private:
    Ui::TcpClient *ui;

    QTcpSocket *tcpClient;//tcp�ͻ��� һ��tcpsocket��
    quint16 blockSize;//��ߴ�
    QHostAddress hostAddress;//������ַ
    qint16 tcpPort;//tcp�˿ں�

    qint64 TotalBytes;//Ҫ�����ܵı�����
    qint64 bytesReceived;//���յ��ı�����
    qint64 bytesToReceive;//����Ҫ���ܴ������
    qint64 fileNameSize;//�ļ����Ĵ�С
    QString fileName;//�ļ���
    QFile *clocalFile;//�����ļ�
    QByteArray inBlock;

    QTime time;

private slots:
    void on_tcpClientCancleBtn_clicked();//�ͻ���ȡ����ť�ۺ���
    void on_tcpClientCloseBtn_clicked();//�رհ�ť

    void newConnect();//�µ�tcp����
    void readMessage();//������
    void displayError(QAbstractSocket::SocketError);//��ʾ������Ϣ
signals:
    void sigGetVoiceFile(QString voiceFile);
};

#endif // TCPCLIENT_H
