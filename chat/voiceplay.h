#ifndef VOICEPLAY_H
#define VOICEPLAY_H

#include <QDialog>
#include <QFile>
#include <widget.h>
#include <QProcess>
class QSound;
namespace Ui {
class VoicePlay;
}

class VoicePlay : public QDialog
{
    Q_OBJECT
    
public:
    explicit VoicePlay(QWidget *parent = 0);
    ~VoicePlay();
    

private slots:
    void on_playBtn_clicked();

    void on_exitBtn_clicked();
    void slotAddVoiceFile(QString voiceFile);
private:
    Ui::VoicePlay *ui;
    QSound *sound;
    QString soundfile;
    QFile *f;
    QProcess *playProcess;
};

#endif // VOICEPLAY_H
