#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <QMainWindow>


//TEST LAYOUT
#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <QLabel>
#include <QLineEdit>
#include <QLayout>
#include <QPushButton>
//---------------

#include <QMenuBar>
#include "PageJeu.h"
#include "PageMenuPrincipal.h"
#include "Jeu.h"

using namespace std;

class Affichage : public QMainWindow
{
	Q_OBJECT
public:

	//constructeur
	Affichage();
	~Affichage();

	void CreationZonedeJeu(int mode);							//mode == nombre de cases par cotes de la grille (mode X mode)
	void ChangePage(QWidget* page);
	QWidget* getPageActuelle();


private slots:

	void Charger();
	void Sauvegarder();
	void Quitter();

	void mode3();
	void mode4();
	void mode5();
	void mode6();
	void mode7();
	void mode8();

private:

	//---MenuBar EXemple
	void CreationActions();
	void CreationMenus();
	
	PageJeu* pagejeu;
	PageMenuPrincipal* menuprincipal;
	Jeu* jeu;
	QWidget* PageActuelle;

	QMenu* Menu;
	QMenu* NouvellePartie;
	QMenu* Mode;

	QAction* ChargerPartie;
	QAction* SauvegarderPartie;
	QAction* QuitterPartie;

	QAction* Mode3;
	QAction* Mode4;
	QAction* Mode5;
	QAction* Mode6;
	QAction* Mode7;
	QAction* Mode8;

};
#endif //AFFICHAGE_H

