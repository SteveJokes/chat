#-------------------------------------------------
#
# Project created by QtCreator 2017-2-19T19:53:56
#
#-------------------------------------------------
QT       += core gui webkit
QT       += core gui
QT       += network
QT       += multimediawidgets
TARGET = chat
TEMPLATE = app

SOURCES += main.cpp\
        widget.cpp \
    tcpserver.cpp \
    tcpclient.cpp \
    myinputpanelcontext.cpp \
    myinputpanel.cpp \
    mapwidget.cpp \
    voicerecord.cpp \
    voiceplay.cpp \
    cudpthread.cpp

HEADERS  += widget.h \
    tcpserver.h \
    tcpclient.h \
    myinputpanelcontext.h \
    myinputpanel.h \
    mapwidget.h \
    voicerecord.h \
    voiceplay.h \
    cudpthread.h

FORMS    += widget.ui \
    tcpserver.ui \
    tcpclient.ui \
    myinputpanelform.ui \
    map_widget.ui \
    voicerecord.ui \
    voiceplay.ui

RESOURCES += \
    images.qrc
