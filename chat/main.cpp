#include <QtGui/QApplication>
#include "widget.h"
#include <QTextCodec>
#include "myinputpanelcontext.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    MyInputPanelContext *ic = new MyInputPanelContext;
    a.setInputContext(ic);//将输入上下文与应用程序关联
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("GB2312"));
    Widget w;
    w.show();
    return a.exec();
}
