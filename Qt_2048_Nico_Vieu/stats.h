#ifndef STATS_H
#define STATS_H

#include "include.h"
#include "accueil.h"
#include <QFileDialog>

class Stats : public QMainWindow
{
    Q_OBJECT
public:
    Stats(int size, int mode);
    ~Stats();

    QPushButton* Create_Button(QString nom,QString text,int size, bool bold);
    QLabel* Create_Label(QString nom,QString text,int size, bool bold);


private slots:
    void Menu_clicked();

private:
    QWidget *centralWidget;
    QGridLayout *gLayout;
    QGridLayout *Stats_gLayout;
    QVBoxLayout *vLayout;

    QLabel *titre;
    QLabel **label;
    QPushButton **button;

    int GridSize;
    int GameMode;
};

#endif // STATS_H
