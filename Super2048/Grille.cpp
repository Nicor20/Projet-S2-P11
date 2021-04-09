#include "Grille.h"

Grille::Grille()
{
	qDebug() << "Grille basique Creer";
}

Grille::Grille(int mode)
{
	qDebug() << "Grille moder Creer";
	//---cree la liste des tuiles de la grille
	for (int i = 0; i < mode * mode; i++)
	{
		Tuile* tuile = new Tuile(0);
		ListTuileGrille.append(tuile);
	}
	Mode = mode;
	setCoordGrille(0, 0);
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
	//place la tuile à la position donnée
	int index = 0;
	index = getTuile_XY_Position(colone, ranger);
	if (index >= Mode*Mode || index < 0) // Annule le placement si la tuile sort de la grille
	{
		qDebug() << "cette tuile ne peux pas sortir de la grille";
		tuile->destroyed();
	}
	else if (getTuile_List(index)->getValeur() > 1) // Annule le placement si la tuiledynamique en remplacerais une autre à l'index indiqué
	{
		qDebug() << "cette tuile ne peux pas apparetre au meme endroit quune autre tuile";
		tuile->destroyed();
	}
	else if (tuile->getExiste())
	{
		qDebug() << "cette tuile est deja sur le plateau, elle echange de position avec la tuile vide la ou elle va";
		int index_Actuel=0;
		index_Actuel = ListTuileGrille.indexOf(tuile);
		tuile->setPos(getTuile_List(index)->pos());

		ListTuileGrille.swapItemsAt(index_Actuel,index);
	}
	else
	{
		qDebug() << "cette tuile nest pas deja sur le plateau, elle en remplacera une vide";
		tuile->setPos(getTuile_List(index)->pos());
		ListTuileGrille.replace(index, tuile);
	}
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
			qDebug() << "pos y: " << Pos_Y;
			qDebug() << "pos x: " << Pos_X;
		}
	}

}



/*
retourne index [position dans la liste] à partir des index [x][y]
x*colone+y=position dans la liste

retourne indexe [x][y] d'un item à partir d'une liste 1D
x = position dans la liste / taille de colone;
y = position dans la liste % ranger;*/
