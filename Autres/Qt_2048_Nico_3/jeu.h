#ifndef JEU_H
#define JEU_H

#include "include.h"
#include "accueil.h"
#include "grid.h"

class Jeu : public QMainWindow
{
    Q_OBJECT
public:
    Jeu(int size = 1, int mode = 4, bool load = false);
    ~Jeu();

    void RefreshGrid();
    void CustomLabel(QLabel *label);
    void SaveGame();
    void SaveStats(QString s);
    void ClearFile();

    QPushButton* Create_Button(QString nom,QString text,int size, bool bold);
    QLabel* Create_Label(QString nom,QString text,int size, bool bold);

private slots:
    void Menu_clicked();
    void Haut_clicked();
    void Bas_clicked();
    void Gauche_clicked();
    void Droit_clicked();

private:
    QWidget *centralWidget;
    QGridLayout *gLayout;
    QVBoxLayout *vLayout;
    QGridLayout *Button_gLayout;
    QGridLayout *Game_gLayout;
    QGridLayout *Stats_gLayout;
    QLabel **label;
    QPushButton **button;

    int ModeJeu;
    int GridSize;
    Grid *grid;
    QLabel ***labelGrid;

    bool Loaded;
};

#endif // JEU_H
