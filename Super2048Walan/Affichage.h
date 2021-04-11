
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QStatusBar>
#include <QDebug>
#include <QKeyEvent>
#include "Grille.h"
#include "Tableau.h"


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
	void AfficheGrille(Grille* grille);
	void SyncronisationDesGrilles();
	
	//void RunJeux();
	
	QGraphicsScene* getScene();
	QGraphicsView* getView();
	//Joueur* getJoueur();
	void keyPressEvent(QKeyEvent* event);

private:

	//---Lorsque Zone de jeux est Loader---//
	QGraphicsScene* scene; // Pointe la scene correspondant à la zone de jeux
	QGraphicsView* view; // Vois la Scene de la zone de Jeux
	Grille* grillefixe; // Grille de tuile
	Grille* grilledynamique; // Grille de tuile
	Tableau* tableau;
	//Joueur* joueur;
};
#endif //AFFICHAGE_H

