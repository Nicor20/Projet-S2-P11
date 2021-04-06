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
	void placeTuiles(int x, int y, int colones, int range, QGraphicsScene* scene); //cr�e un tablea de tuile au coordo��e XY indiqu� de longueur rang� et de largeur colonnes dans la scene :scene

private:
	void creeColonneTuiles(int x, int y, int z, QGraphicsScene* scene); //cr�e une colone de tuile au coordo��e XY indiqu� de longueur z dans la scene :scene
	QList<Tuile*> Tuiles;

};
#endif TABLEAUTUILE_H