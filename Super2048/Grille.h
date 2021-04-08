#ifndef GRILLE_H
#define GRILLE_H

#include <QVector>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Tuile.h"

class Grille : public Tuile
{
	Q_OBJECT
public:
	Grille();

	void AddGrille(int mode, QGraphicsView* view, QGraphicsScene* scene); // ajoute une grille de jeux de la taille correspondant au mode de jeux
	void AfficheGrille(int mode, QGraphicsScene* scene);

private:
	int MaxGrid_Heiht;
	int MaxGrid_Leght;
	int origine_X;
	int origine_Y;

	QVector<Tuile*> ListTuileGrille; //listes des tuiles dans la grilles selon l'ordre de créations de celles-ci
	Tuile*** TuileGrille; //tableau 2D des tuilles dans le tableau

};
#endif //GRILLE_H