/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 15/04/2021
* Nom de fichier : main.cpp
* Description : Lance l'application
*/
#include <QApplication>
#include "UI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UI w;
    w.showMaximized();
    return a.exec();
}
