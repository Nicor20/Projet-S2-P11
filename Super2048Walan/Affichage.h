
#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QString>
#include <QStatusBar>
#include <QDebug>
#include <QKeyEvent>

//TEST LAYOUT
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>
//---------------

#include <QMenuBar>
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

	void Message(const char* message); // message �crit dans la Status Bar de l'interface

	void LoadZonedeJeu(int mode); //mode == nombre de cases par cotes de la grille ("mode" X "mode")
	
	//---Fonctions de Jeux
	void AddTuile(int coord_X, int coord_Y, int valeur); // cr�e une tuile aux coordonn�s indiquer
	void AfficheGrille(Grille* grille);	// Affiche la grille indiquer
	void SyncronisationDesGrilles();	// Sycronise et Met � jour la position et les valeurs des tuiles dynamique et du tableau de jeux
	void UpdateScore(); // met � jour l'affichage des score ("Score" et "Nombre de Mouvements")sur l'interface
	void keyPressEvent(QKeyEvent* event); // recois les entr� du clavier

	QGraphicsScene* getScene(); // Renvois la scene du central Widget de la page de jeux
	QGraphicsView* getView();	// Renvois la vue du central Widget de la page de jeux


private slots:
	void Recommencer();
	void Charger();
	void Sauvegarder();
	void Quitter();


private:

	int scene_width = 1024; //d�termine la largeur de la scene en pixel
	int scene_height = 760; // d�termine la hauteur de la scene en pixel
	QWidget* widget;

	//---MenuBar EXemple
	void CreationActions();
	void CreationMenus();

	QMenu* Menu;
	QAction* NouvellePartie;
	QAction* ChargerPartie;
	QAction* SauvegarderPartie;
	QAction* QuitterPartie;

	//---Lorsque Zone de jeux est Loader---//
	QGraphicsScene* scene; // Pointe la scene correspondant � la zone de jeux
	QGraphicsView* view; // pointe la vue de la Scene de la zone de Jeux
	Grille* grillefixe; // point Grille de tuile
	Grille* grilledynamique; // pointe Grille de tuile
	Tableau* tableau; // pointe Tableau de base de jeux
	Score* scoreboard; // pointe le score Board "Score"
	Score* nbmouve; // pointe le score Board "Nombre de Mouvement"


};
#endif //AFFICHAGE_H

