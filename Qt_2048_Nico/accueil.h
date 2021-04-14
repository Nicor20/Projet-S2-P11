#ifndef ACCUEIL_H
#define ACCUEIL_H

#include "needed.h"

class Accueil : public QWidget
{
public:
    Accueil(int* size);
    ~Accueil();

    QPushButton* Create_Button_Accueil(QString nom, QString text, int size, bool bold, bool custom);
    QLabel* Create_Label_Accueil(QString nom, QString text, int size, bool bold, bool custom = false);

    bool CheckStats();
    bool CheckSave();

    void CreateStats();
    void CreateSave();

    QPushButton* button_Jouer;
    QPushButton* button_Charger;
    QPushButton* button_Stats;
    QPushButton* button_Quitter;

private slots:
    void Button_clicked();
    void Button_Pressed();
    void Button_Released();

private:
    QLabel* label_GridSize;

    int* GridSize;
};

#endif // ACCUEIL_H
