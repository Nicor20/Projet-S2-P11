/*
* Nom des cr�ateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de cr�ation : 05/04/2021 � 15/04/2021
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
