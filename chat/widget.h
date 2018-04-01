#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <mapwidget.h>
#include <voiceplay.h>
#include <voicerecord.h>
class QUdpSocket;
class MapWidget;
class TcpServer;
class VoicePlay;
class VoiceRecord;
#include <QTextCharFormat>

namespace Ui {
class Widget;
}


enum MessageType{Message, NewParticipant, ParticipantLeft, FileName, VoiceFile,Refuse};


class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void newParticipant(QString userName,
                        QString localHostName, QString ipAddress);
    void participantLeft(QString userName,
                         QString localHostName, QString time);
    void sendMessage(MessageType type, QString serverAddress="");

    QString getIP();
    QString getUserName();
    QString getMessage();


    void hasPendingFile(QString userName, QString serverAddress,
                        QString clientAddress, QString fileName);

    bool saveFile(const QString& fileName);

    void closeEvent(QCloseEvent *);

private:
    Ui::Widget *ui;
    QUdpSocket *udpSocket;
    qint16 port;

    QString fileName;
    QString voiceFile;
    TcpServer *server;
    MapWidget *mapWidget;
    QColor color;
    VoiceRecord *voiceRecord;
    VoicePlay *voicePlay;
public slots:
    //bool sendMessageSlot(MessageType type, QString serverAddress="");
private slots:
    void processPendingDatagrams();

    void on_sendButton_clicked();

    void getFileName(QString);
    void getVoiceFile(QString);
    void on_sendToolBtn_clicked();
    void on_fontComboBox_currentFontChanged(QFont f);
    void on_sizeComboBox_currentIndexChanged(QString );
    void on_boldToolBtn_clicked(bool checked);
    void on_italicToolBtn_clicked(bool checked);
    void on_underlineToolBtn_clicked(bool checked);
    void on_colorToolBtn_clicked();

    void currentFormatChanged(const QTextCharFormat &format);
    void on_saveToolBtn_clicked();
    void on_clearToolBtn_clicked();
    void on_exitButton_clicked();
    void on_mapButton_clicked();
    void on_micToolBtn_clicked();
    void on_speakerButton_clicked();
};

#endif // WIDGET_H
