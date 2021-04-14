#include <QApplication>
#include "UI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UI w;
    w.showMaximized();
    return a.exec();
}
