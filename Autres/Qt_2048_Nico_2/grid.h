#ifndef GRID_H
#define GRID_H

#include <QVector>
#include <QString>
#include <QFile>
#include <QTextStream>

class Grid
{
public:
    Grid(int size, bool load);
    ~Grid();

    QString Droit();
    QString Gauche();
    QString Haut();
    QString Bas();

    void AddRandom();
    int Get(int row, int column);

    bool Lose();
    bool Win();
    int random(int high);

    int GetMax();
    int GetScore();
    int GetNbMove();
    int GetSize();

private:
    int** grid;
    int ratio = 5;
    int GridSize;
    int score = 0;
    int NbMove = 0;
    QVector<int> twoFour;
};

#endif // GRID_H
