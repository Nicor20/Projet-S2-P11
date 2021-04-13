#ifndef ACCUEIL_H
#define ACCUEIL_H

#include "jeu.h"
#include "stats.h"
#include "include.h"

class Accueil : public QMainWindow
{
    Q_OBJECT
public:
    Accueil(int size = 4);
    ~Accueil();

    QWidget* Get_Widget();

    QPushButton* Create_Button(QString nom,QString text,int size, bool bold);
    QLabel* Create_Label(QString nom,QString text,int size, bool bold);

    void CheckStats();
    void CheckSave();

private slots:
    void Button_clicked();

private:
    QWidget *centralWidget;
    QGridLayout *gLayout;
    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout1;

    QLabel *label_Titre;
    QLabel *label_Sub;
    QLabel *label_GridSize;
           
    QPushButton* button_Moin;
    QPushButton* button_Plus;
    QPushButton* button_Jouer;
    QPushButton* button_Charger;
    QPushButton* button_Stats;
    QPushButton* button_Quitter;

    int GridSize;
};

#endif // ACCUEIL_H
