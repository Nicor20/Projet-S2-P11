#ifndef JOUEUR_H
#define JOUEUR_H

#include <QObject>

class Joueur : public QObject
{
	Q_OBJECT
public:
	Joueur();
	~Joueur();


public slots:
	void Mouve();

private:


};

#endif //JOUEUR_H