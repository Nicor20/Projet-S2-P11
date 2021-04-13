#ifndef PAGEJEUX_H
#define PAGEJEUX_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QStatusBar>
#include <QDebug>
#include <QKeyEvent>
#include "Grille.h"
#include "Tableau.h"
#include "Score.h"


class PageJeu : public QWidget
{
public:
    
	PageJeu();
	PageJeu(int mode);
	~PageJeu();

	QGraphicsView* getView();
	QGraphicsScene* getScene();

	void AddTuile(int coord_X, int coord_Y, int valeur);
	void AfficheGrille(Grille* grille);
	void SyncronisationDesGrilles();
	void UpdateScore();
	void keyPressEvent(QKeyEvent* event);
	bool getExist();

private:
	int scene_width = 1024;									//determine la largeur de la scene en pixel
	int scene_height = 760;									// determine la hauteur de la scene en pixel

	bool existe = false;

	//---Lorsque Zone de jeux est Loader---//
	QGraphicsScene* scene;									// Pointe la scene correspondant à la zone de jeux
	QGraphicsView* view;									// pointe la vue de la Scene de la zone de Jeux
	Grille* grillefixe;										// point Grille de tuile
	Grille* grilledynamique;								// pointe Grille de tuile
	Tableau* tableau;										// pointe Tableau de base de jeux
	Score* scoreboard;										// pointe le score Board Score
	Score* nbmouve;											// pointe le score Board Nombre de Mouvement

};

#endif // PAGEJEUX_H