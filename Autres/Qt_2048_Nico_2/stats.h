#ifndef STATS_H
#define STATS_H

#include "include.h"
#include "accueil.h"
#include <QFileDialog>


struct Game
{
    QString Status;
    QString Size;
    int Score;
    int NbMove;
    int Max;

    int Overall;
};

class Stats : public QMainWindow
{
    Q_OBJECT
public:
    Stats(int size);
    ~Stats();

    QWidget* Get_Widget();

    void Read();
    void Sort();

    QPushButton* Create_Button(QString nom,QString text,int size, bool bold);
    QLabel* Create_Label(QString nom,QString text,int size, bool bold);
    void Color_Label(QLabel *label, int num, QString rule);
    void Frame_Label(QLabel* labe, int style, int l1, int l2);

private slots:
    void Button_clicked();

private:
    QWidget *centralWidget;
    QGridLayout *gLayout;
    QGridLayout *Stats_gLayout;
    QVBoxLayout *vLayout;
    QFrame* frame;

    QLabel* label_Titre;
    QLabel* label_Position;
    QLabel* label_Status;
    QLabel* label_Size;
    QLabel* label_Score;
    QLabel* label_NbMove;
    QLabel* label_Max;

    QPushButton* button_Menu;

    QList<Game> ListGame;

    int GridSize;
    int Shown = 15;
};

#endif // STATS_H
