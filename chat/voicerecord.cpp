#include "voicerecord.h"
#include "ui_voicerecord.h"
#include <sys/ioctl.h>
#include <fcntl.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <iostream>
#include <tcpserver.h>
//#include <QtMultimedia>
const QString voiceFilePath="/tmp/";
VoiceRecord::VoiceRecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VoiceRecord)
{
   //char buf[32];
    ui->setupUi(this);
    process=NULL;
//    TcpServer *tcpSend=new TcpServer;
//    connect(this,SIGNAL(signalSendVoice(QString)),tcpSend,SLOT(slotVoiceSend(QFile*)));
    ::system("amixer cset name='Headphone Volume' 27,27");//127
    ::system("/usr/bin/amixer sset 'MIXINR IN3R' on");
    ::system("amixer sset 'INPGAR IN3R' on");
    ::system("amixer cset name='Capture Volume' 63,63");
    connect(ui->cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
}

VoiceRecord::~VoiceRecord()
{
    delete ui;
}

void VoiceRecord::on_recordBtn_clicked()
{
    QDateTime dt;
    QDate date;
    QTime time;

    if(process)
    {
        delete process;
        process = NULL;//second click lead to the stop of process
    }
    if(ui->recordBtn->text() == QString("record"))
    {
        ui->recordBtn->setText("stop");

        process = new QProcess();

        dt.setDate(date.currentDate());
        dt.setTime(time.currentTime());
        filename = dt.toString("yyyyMMddhhmmss")+QString(".mp3");
        process->start("/usr/bin/gst-launch alsasrc num-buffers=240 blocksize=44100 ! mfw_mp3encoder ! filesink location=/tmp/"+ filename);//main point
    }
    else
    {
        ui->recordBtn->setText("record");
//        if(!filename.isEmpty())
//            saveFile(filename);
        delete process;
        process= NULL;
        emit signalSendVoice(voiceFilePath+filename);
        //emit signalSendVoice("/tmp/text.mp3");
    }
}

void VoiceRecord::on_cancelBtn_clicked()
{
    emit closeServer();
}
