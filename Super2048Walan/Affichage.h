
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
#include "Score.h"


using namespace std;

class Affichage : public QMainWindow
{
	Q_OBJECT
public:

	//constructeur
	Affichage();
	~Affichage();

	void Message(const char* message); // message écrit dans la Status Bar de l'interface

	void LoadZonedeJeu(int mode); //mode == nombre de cases par cotes de la grille ("mode" X "mode")
	
	//---Fonctions de Jeux
	void AddTuile(int coord_X, int coord_Y, int valeur); // crée une tuile aux coordonnés indiquer
	void AfficheGrille(Grille* grille);	// Affiche la grille indiquer
	void SyncronisationDesGrilles();	// Sycronise et Met à jour la position et les valeurs des tuiles dynamique et du tableau de jeux
	void UpdateScore(); // met à jour l'affichage des score ("Score" et "Nombre de Mouvements")sur l'interface
	void keyPressEvent(QKeyEvent* event); // recois les entré du clavier

	QGraphicsScene* getScene(); // Renvois la scene du central Widget de la page de jeux
	QGraphicsView* getView();	// Renvois la vue du central Widget de la page de jeux
	

private:

	//---Lorsque Zone de jeux est Loader---//
	QGraphicsScene* scene; // Pointe la scene correspondant à la zone de jeux
	QGraphicsView* view; // pointe la vue de la Scene de la zone de Jeux
	Grille* grillefixe; // point Grille de tuile
	Grille* grilledynamique; // pointe Grille de tuile
	Tableau* tableau; // pointe Tableau de base de jeux
	Score* scoreboard; // pointe le score Board "Score"
	Score* nbmouve; // pointe le score Board "Nombre de Mouvement"

	int scene_width = 1024; //détermine la largeur de la scene en pixel
	int scene_height = 760; // détermine la hauteur de la scene en pixel
};
#endif //AFFICHAGE_H

