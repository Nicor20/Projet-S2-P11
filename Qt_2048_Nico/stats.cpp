#include "stats.h"

Stats::Stats()
{
    //Read
    {
        int i = 1;
        QFile file("Stats.txt");

        if (file.exists())
        {
            QString line;
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                while (!in.atEnd())
                {
                    line = in.readLine();
                    Game g;
                    g.Status = line.split("/")[0];
                    g.Size = line.split("/")[1];
                    g.Score = line.split("/")[2].toInt();
                    g.NbMove = line.split("/")[3].toInt();
                    g.Max = line.split("/")[4].toInt();
                    ListGame.append(g);
                }
            }
            file.close();
        }
        else
        {
            qDebug() << "Error. File not found";
        }
    }
    
    //Sort
    {
        //Overall = (Max + (score/Move))/size

        for (int i = 0; i < ListGame.size(); i++)
        {
            ListGame[i].Overall = ListGame[i].Max;
            ListGame[i].Overall += ListGame[i].Score / ListGame[i].NbMove;
            ListGame[i].Overall /= ListGame[i].Size.split("x")[0].toInt();
        }

        QList<Game> temp;
        while (ListGame.size() != 0)
        {
            int pos = 0;
            for (int i = 0; i < ListGame.size(); i++)
            {
                if (ListGame[i].Overall >= ListGame[pos].Overall)
                {
                    pos = i;
                }
            }
            temp.append(ListGame[pos]);
            ListGame.removeAt(pos);
        }
        ListGame = temp;
    }
}

Stats::~Stats()
{

}

int Stats::GetNbToShow()
{
    return (ListGame.size() > Shown ? Shown: ListGame.size());
}

Game Stats::GetGameAt(int i)
{
    return ListGame[i];
}