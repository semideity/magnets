#include "widget.h"
#include <QApplication>
#include <QDesktopWidget> // 窗口居中

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    // 窗口居中显示
    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);

    return a.exec();
}
