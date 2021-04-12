#ifndef ACCUEIL_H
#define ACCUEIL_H

#include "jeu.h"
#include "stats.h"
#include "include.h"

class Accueil : public QMainWindow
{
    Q_OBJECT
public:
    Accueil(int size = 4, int mode =1);
    ~Accueil();

    QPushButton* Create_Button(QString nom,QString text,int size, bool bold);
    QLabel* Create_Label(QString nom,QString text,int size, bool bold);

    void CheckStats();
    void CheckSave();

private slots:
    void SizePlus_clicked();
    void SizeMoin_clicked();
    void ModePlus_clicked();
    void ModeMoin_clicked();
    void Jouer_clicked();
    void Charger_clicked();
    void Stats_clicked();
    void Quitter_clicked();
private:
    QWidget *centralWidget;
    QGridLayout *gLayout;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout1;
    QHBoxLayout *hLayout2;
    QLabel **label;
    QPushButton **button;

    int GridSize;
    int GameMode;
};

#endif // ACCUEIL_H
