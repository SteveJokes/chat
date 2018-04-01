#include "voiceplay.h"
#include "ui_voiceplay.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <iostream>
#include <QSound>
#include <QProcess>
VoicePlay::VoicePlay(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoicePlay)
{
    ui->setupUi(this);
//    setFixedSize(300,200);
 //   ui->list->addItem(new QListWidgetItem("/sound.wav"));
    //connect(ui->exitBtn,SIGNAL(clicked()),this,SLOT(close()));
}

VoicePlay::~VoicePlay()
{
    delete ui;
}

void VoicePlay::on_playBtn_clicked()
{
    if(ui->playBtn->text()==QString("play"))
    {
        if(ui->list->currentItem() == NULL)
        {
            QMessageBox::about(this,"error","nothing selected!");
            return;
        }
        ui->playBtn->setText("stop");
        QString soundfile = "/tmp/tmp/"+ui->list->currentItem()->text();
        f=new QFile(soundfile);
        if(!f->exists())
        {
            QMessageBox::about(this,"error",tr("the file:'%1'doesn't exist!").arg(soundfile));
            return;
        }
  /*for wav format voice file*/
//       sound = new QSound(soundfile, this);
//        sound->play();
  /*for mp3 format voice file*/
        QString cmd = QString("/usr/bin/gplay ")+soundfile;
        playProcess=new QProcess();
        playProcess->start(cmd.toAscii());
    }
    else
    {
//        sound->stop();
        delete playProcess;
        ui->playBtn->setText("start");
    }
}

void VoicePlay::on_exitBtn_clicked()
{

//    if(f->isOpen())
//        f->close();
        close();

}
void VoicePlay::slotAddVoiceFile(QString voiceFile)
{
    ui->list->clear();
    ui->list->setCurrentRow(0);
    ui->list->addItem(new QListWidgetItem(voiceFile));
//    ui->list->setCurrentRow(ui->list->count()-1);
}
