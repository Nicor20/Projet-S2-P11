#include "tuile.h"
#include <QDebug>

Tuile::Tuile()
{
	//qDebug() << "tuile defaut";
}

Tuile::Tuile(int type)
{
	// dessine une tuile 113x113 pixels
	//qDebug() << "vraituile creer";
	setRect(0, 0, 113, 113);
	valeur = type;
}

Tuile::~Tuile()
{
	qDebug() << "tuile detruite";
}