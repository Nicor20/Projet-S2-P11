
#include <QBrush>
#include "Tuile.h"


Tuile::Tuile()
{
	qDebug() << "Tuile basique creer";
}

Tuile::Tuile(int valeur)
{
	//crée la tuile
	setRect(0,0, Size, Size);
	Valeur = valeur;
	qDebug() << Valeur;

	if (Valeur == 2)
	{
		qDebug() << "tuile rouge";
		setBrush(Qt::red);
	}
	else
	{
		qDebug() << "tuile blanche";
		setBrush(Qt::white);
	}
}

Tuile::~Tuile()
{
	qDebug() << "Tuile Detruite";
}

int Tuile::getSize()
{
	return Size;
}

void Tuile::setSize(int NouvSize)
{
	Size = NouvSize;
}

int Tuile::getValeur()
{
	return Valeur;
}

int Tuile::getExiste()
{
	return Existe;
}