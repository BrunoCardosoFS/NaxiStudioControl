#include "frontend/control.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/images/icons/logo.ico"));

    Control w;
    w.show();
    return a.exec();
}
