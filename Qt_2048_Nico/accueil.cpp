#include "accueil.h"

Accueil::Accueil()
{
    
}

Accueil::~Accueil()
{

}

bool Accueil::CheckSave()
{
    QFile file("Save.txt");

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            if(in.readLine().length()>5)
            {
                return true;
            }
            else
            {
                return false;
            }
            file.close();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Accueil::CheckStats()
{
    QFile file("Stats.txt");

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            if(in.readLine().length()>5)
            {
                return true;
            }
            else
            {
                return false;
            }
            file.close();
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

}

