#ifndef VOICERECORD_H
#define VOICERECORD_H

#include <QDialog>
#include <QProcess>
#include <QFile>
#include <tcpserver.h>

namespace Ui {
class VoiceRecord;
}

class VoiceRecord : public QDialog
{
    Q_OBJECT
    
public:
    explicit VoiceRecord(QWidget *parent = 0);
    ~VoiceRecord();

private slots:
    void on_recordBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::VoiceRecord *ui;
    QProcess *process;
    QString filename;
signals:
    void signalSendVoice(QString voiceFile);
    void closeServer();
};

#endif // VOICERECORD_H
