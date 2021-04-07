#define TABLEAUTUILE_H
#ifdef TABLEAUTUILE_H

#include "tuile.h"
#include <QList>

class tableauTuile : public Tuile
{
public:
	//constructor
	tableauTuile();
	//getters
	QList<Tuile*> getTuiles();
	// public method
	void placegrille(int x, int y, int colones, int range, QGraphicsScene* scene); //crée un tablea de tuile au coordoéée XY indiqué de longueur rangé et de largeur colonnes dans la scene :scene

private:
	QList<Tuile*> Tuiles;

};
#endif TABLEAUTUILE_H