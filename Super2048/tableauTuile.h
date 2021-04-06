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
	void placeTuiles(int x, int y, int colones, int range, QGraphicsScene* scene); //crée un tablea de tuile au coordoéée XY indiqué de longueur rangé et de largeur colonnes dans la scene :scene

private:
	void creeColonneTuiles(int x, int y, int z, QGraphicsScene* scene); //crée une colone de tuile au coordoéée XY indiqué de longueur z dans la scene :scene
	QList<Tuile*> Tuiles;

};
#endif TABLEAUTUILE_H