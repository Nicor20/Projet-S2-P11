#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDebug>
#include "Joueur.h"
#include "tableauTuile.h"

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//----------------Param�tre la sc�ne
	// cree une Scene
	QGraphicsScene* scene = new QGraphicsScene;

	// ajoute une vu sur la scene
	QGraphicsView* view = new QGraphicsView();
	view->setScene(scene);
	view->show(); //affiche la scene -> LES WIDGETS SONT INVISIBLES DE BASE!!!

	//ajuste la taille de la fen�tre a une valeur fixe
	view->setFixedSize(1024, 600);
	scene->setSceneRect(0, 0, 1024, 600);

	//d�sactive le scoling
	view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


	//---------------Param�tre le tableau de jeu
	//cr�e le plateau de jeux
	tableauTuile* board = new tableauTuile();

	//position d'origine du tableau
	int hauteur = 4;
	int largeur = 4;
	int origine_X = ((view->width()) / 2) - ((largeur * 113) / 2);
	int origine_Y = ((view->height()) / 2) - ((hauteur * 113) / 2);

	//place les tuiles
	board->placeTuiles(origine_X, origine_Y, hauteur, largeur, scene);


	//---------------Param�tre le joueur
	// Cree un joueur
	joueur* J1 = new joueur;
	J1->setRect(100, 100, 113, 113);

	// ajoute le joueur � la scene
	scene->addItem(J1);

	// rend le joueur focussable
	J1->setFlag(QGraphicsItem::ItemIsFocusable);

	// met le joueur comme focus de la scenne (pour qu'il puisse re�evoir les KeyEvents)
	J1->setFocus();


	return a.exec();
}