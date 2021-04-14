#include "accueil.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Accueil w;
    w.showMaximized();
    return a.exec();
}
