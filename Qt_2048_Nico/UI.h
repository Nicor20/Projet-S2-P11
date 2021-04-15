/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 15/04/2021
* Nom de fichier : UI.h
* Description : MainWindow qui permet d'afficher les différentes widget comme accueil, Jeu, et Classement
*/

#ifndef UI_H
#define UI_H

#include "needed.h"
#include "accueil.h"
#include "jeu.h"
#include "stats.h"

class UI : public QMainWindow
{
    Q_OBJECT
public:
    UI();
    ~UI();

    void Load_Accueil();
    void Load_Jeu(bool load);
    void Load_Stats();

private slots:
    void Button_clicked();

private:
    Accueil* accueil;
    Jeu* jeu;
    Stats* stats;

    int GridSize = 4;
};

#endif // UI_H

