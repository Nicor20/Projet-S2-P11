#ifndef ACCUEIL_H
#define ACCUEIL_H

#include <QFile>
#include <QTextStream>

class Accueil
{
public:
    Accueil();
    ~Accueil();

    bool CheckStats();
    bool CheckSave();
};

#endif // ACCUEIL_H
