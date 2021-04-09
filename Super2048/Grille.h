#ifndef GRILLE_H
#define GRILLE_H

#include <QVector>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Tuile.h"

class Grille
{
public:
	Grille();
	Grille(int mode);											// ajoute une grille de jeux de la taille correspondant au mode de jeux
	
	Tuile* getTuile_XY(int colone, int ranger);					//retourne le poineur de la tuile dans la liste correspondant à l'index XY
	Tuile* getTuile_List(int index);							//retourne la tuile à l'index de la list
	void setTuilePoss(int colone, int ranger, Tuile* Newtuile); //change ou determine la position d'une tuile dans la grille
	void setCoordGrille(int coord_X, int coord_Y);				//determine la position de la grille sur la scene
	int getSize();												//retourne la taille de la liste de tuile de la grille
	int getMode();												//retourne le mode(taille) de la grille
	int getTuile_XY_Position(int colone, int ranger);			//retourne la position dans la liste(index) d'une tuile au coordonee XY de la grille

private:
	int Mode; // définit la longueur d'un côté de la grille et le mode de jeux

	QVector<Tuile*> ListTuileGrille; //listes des tuiles dans la grilles selon l ordre de créations de celles-ci

};
#endif //GRILLE_H