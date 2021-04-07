#include "tableauTuile.h"
#include <QGraphicsScene>

tableauTuile::tableauTuile()
{

}

QList<Tuile*> tableauTuile::getTuiles()
{
	return Tuiles;
}

void tableauTuile::placegrille(int x, int y, int colones, int range, QGraphicsScene* scene)
{
	for(size_t i=0, n = colones; i<n; i++ )
	{
		for (size_t j = 0, n = range; j < n; j++)
		{
			Tuile* tuile = new Tuile(0);
			tuile->setPos(x, y + 113 * j);
			Tuiles.append(tuile);
			scene->addItem(tuile);
		};

		x += 113;
	}
	
}


