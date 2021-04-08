
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QString>
#include <QStatusBar>
#include <QDebug>
#include <QVector>
#include "Tuile.h"

using namespace std;

class Affichage : public QMainWindow
{
	Q_OBJECT
public:

	//constructeur
	Affichage();
	~Affichage();

	void LoadZonedeJeu(int mode); //mode == nombre de cases par cotes de la grille ("mode" X "mode")
	void AddTuile(int coord_X, int coord_Y, int valeur); // crée une tuile aux coordonnés indiqué
	void Message(const char* message); // message écrit dans la Status Bar de l'interface


private:

	//---Lorsque Zone de jeux est Loader---//
	QGraphicsScene* scene; // Pointe la scene correspondant à la zone de jeux
	QGraphicsView* view; // Vois la Scene de la zone de Jeux
	int MaxGrid_Heiht;
	int MaxGrid_Leght;

	void AddGrille(int mode); // ajoute une grille de jeux de la taille correspondant au mode de jeux
	QVector<Tuile*> ListTuileGrille; //listes des tuiles dans la grilles selon l'ordre de créations de celles-ci
	Tuile*** TuileGrille; //tableau 2D des tuilles dans le tableau


};
#endif //AFFICHAGE_H

