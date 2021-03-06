#include "Grille.h"

Grille::Grille()
{
	qDebug() << "Grille basique Creer";
}

Grille::Grille(int mode ,int scene_with, int scene_height)
{
	qDebug() << "Grille mode" << mode << "creer";
	//---cree la liste des tuiles de la grille
	for (int i = 0; i < mode * mode; i++)
	{
		Tuile* tuile = new Tuile(0);
		ListTuileGrille.append(tuile);
	}
	Mode = mode;

	Origine_X = (scene_with/2) - ((Mode * getTuile_List(0)->getSize())/2);
	Origine_Y = (scene_height/2) - ((Mode * getTuile_List(0)->getSize())/2);
	setCoordGrille(Origine_X,Origine_Y);
}

Grille::~Grille()
{
	qDebug() << "Grille detruite";
}

int Grille::getMode()
{
	return Mode;
}

int Grille::getSize()
{
	int taille = 0;
	taille = ListTuileGrille.size();
	return taille;
}

Tuile* Grille::getTuile_XY(int colone, int ranger)
{
	
	int position = 0;

	position = colone * Mode + ranger;
	return ListTuileGrille[position];

}

int Grille::getTuile_XY_Position(int colone, int ranger)
{

	int position = 0;

	position = colone * Mode + ranger;
	return position;

}

Tuile* Grille::getTuile_List(int index)
{
	return ListTuileGrille[index];
}

void Grille::setTuilePoss(int colone, int ranger, Tuile* tuile)
{
	//place la tuile � la position donn�e
	int index = 0;
	Tuile* tuileaenlever;

	index = getTuile_XY_Position(colone, ranger);
	tuileaenlever = getTuile_List(index);

	tuile->setPos(getTuile_List(index)->pos());
	ListTuileGrille.replace(index, tuile);

	//qDebug() << "Taille liste" << ListTuileGrille.size();
	tuileaenlever->~Tuile(); // d�truit la tuile remplacer
}

void Grille::setCoordGrille(int coord_x, int coord_y)
{
	// Assigne des coordonnees aux tuiles
	for (int i = 0; i < Mode; i++)
	{

		for (int j = 0; j < Mode; j++)
		{
			int Pos_X = coord_x + (i * getTuile_XY(i,j)->getSize());
			int Pos_Y = coord_y + (j * getTuile_XY(i, j)->getSize());
			getTuile_XY(i, j)->setPos(Pos_X, Pos_Y);
			//qDebug() << "pos y: " << Pos_Y;
			//qDebug() << "pos x: " << Pos_X;
		}
	}

}

/*
retourne index [position dans la liste] � partir des index [x][y]
x*colone+y=position dans la liste

retourne indexe [x][y] d'un item � partir d'une liste 1D
x = position dans la liste / taille de colone;
y = position dans la liste % ranger;*/
