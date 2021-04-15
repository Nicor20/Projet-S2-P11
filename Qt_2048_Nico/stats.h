/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 15/04/2021
* Nom de fichier : stats.h
* Description : Permet de créer l'interface de classement et de gérer son fonctionnement et ces intéractions
*/
#ifndef STATS_H
#define STATS_H

#include "needed.h"

struct Game
{
    QString Status;
    QString Size;
    int Score;
    int NbMove;
    int Max;

    int Overall;
};

class Stats : public QWidget
{
public:
    Stats();
    ~Stats();

    void Read();
    void Sort();

    QPushButton* Create_Button_Stats(QString nom, QString text, int size, bool bold, bool custom);
    QLabel* Create_Label_Stats(QString nom, QString text, int size, bool bold, bool info, bool stats, int num = 0);

    QPushButton* button_Accueil;
private slots:
    void Button_clicked();
private:
    QList<Game> ListGame;

    int NbToShow = 10;
};

#endif // STATS_H
