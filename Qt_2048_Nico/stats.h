#ifndef STATS_H
#define STATS_H

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

class Stats
{
public:
    Stats();
    ~Stats();

    int GetNbToShow();
    Game GetGameAt(int i);


private:
    QList<Game> ListGame;

    int Shown = 15;
};

#endif // STATS_H
