
#include "Tuile.h"

Tuile::Tuile()
{

}

Tuile::Tuile(int valeur)
{
	//crée la tuile
	setRect(0,0, Size, Size);
	valeur = Valeur;
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