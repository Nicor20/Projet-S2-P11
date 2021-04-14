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

