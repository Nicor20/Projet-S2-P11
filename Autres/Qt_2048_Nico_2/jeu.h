#ifndef JEU_H
#define JEU_H

#include "include.h"
#include "accueil.h"
#include "grid.h"
#include "FPGA.h"

class Jeu : public QMainWindow
{
    Q_OBJECT
public:
    Jeu(int size = 1, bool load = false);
    ~Jeu();

    QWidget* Get_Widget();

    void RefreshGrid();
    void CustomLabel(QLabel *label);
    void SaveGame();
    void SaveStats(QString s);
    void ClearFile();

    QPushButton* Create_Button(QString nom,QString text,int size, bool bold);
    QLabel* Create_Label(QString nom,QString text,int size, bool bold);

    void keyPressEvent(QKeyEvent* event);
    void closeEvent(QCloseEvent* event);

    void Menu();
    void Bouge_Haut();
    void Bouge_Droit();
    void Bouge_Bas();
    void Bouge_Gauche();

private slots:
    void FPGA_Timer();
    void Button_clicked();

private:
    QFrame* frame;
    QWidget *centralWidget;

    QGridLayout *gLayout;
    QVBoxLayout *vLayout;
    QGridLayout *Button_gLayout;
    QGridLayout *Game_gLayout;
    QGridLayout *Stats_gLayout;

    QTimer* Timer;

    QLabel* label_Score;
    QLabel* label_Max;
    QLabel* label_NbMove;
    QLabel ***labelGrid;

    QPushButton* button_Haut;
    QPushButton* button_Droit;
    QPushButton* button_Bas;
    QPushButton* button_Gauche;
    QPushButton* button_Menu;

    Grid *grid;
    FPGA *CarteFPGA;

    int GridSize;
    int interval_read = 10;
    int interval_wait = 250;

    bool Lecture_FPGA = false;
    bool Loaded;
};

#endif // JEU_H
