#ifndef UI_H
#define UI_H

#include <QApplication>
#include <QWindow>
#include <QMainWindow>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QSpacerItem>
#include <QDebug>
#include <QList>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>
#include <QGroupBox>
#include <QStackedWidget>

#include "accueil.h"
#include "jeu.h"
#include "stats.h"

#include <iostream>

class UI : public QMainWindow
{
    Q_OBJECT
public:
    UI();
    ~UI();

    //Accueil
    void Load_Accueil();
    QPushButton* Create_Button_Accueil(QString nom, QString text, int size, bool bold, bool custom);
    QLabel* Create_Label_Accueil(QString nom, QString text, int size, bool bold, bool custom = false);

    //Jeu
    void Load_Jeu(bool load);
    void CustomLabel(QLabel* label);
    QPushButton* Create_Button_Jeu(QString nom, QString text, int size, bool bold, bool custom);
    QLabel* Create_Label_Jeu(QString nom, QString text, int size, bool bold, bool info, bool custom);
    void Refresh_Grid();
    void keyPressEvent(QKeyEvent* event);

    //Stats
    void Load_Stats();
    QPushButton* Create_Button_Stats(QString nom, QString text, int size, bool bold, bool custom);
    QLabel* Create_Label_Stats(QString nom, QString text, int size, bool bold, bool info, bool stats, int num = 0);
    

private slots:
    void Button_clicked();
    void Button_Pressed();
    void Button_Released();
    void FPGA_Timer();

private:
    //Accueil
    QLabel* label_GridSize;
    Accueil* accueil;

    //Jeu
    Jeu* jeu;
    QLabel*** labelGrid;
    QLabel* label_Score;
    QLabel* label_NbMove;
    QLabel* label_Max;
    QTimer* Timer;

    //Stats
    Stats* stats;


    //All
    void CheckMove(QString s);
    int GridSize = 4;
};

#endif // UI_H

