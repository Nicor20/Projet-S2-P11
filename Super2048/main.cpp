#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsView>
#include <QDebug>
#include "Joueur.h"


int main(int argc, char * argv[])
{
	QApplication a(argc, argv);

	// cree une Scene
	QGraphicsScene * scene = new QGraphicsScene;
	
	// Cree un rectangle
	joueur * rect = new joueur;
	rect->setRect(0, 0, 50, 50);

	// ajoute un item à la scene
	scene->addItem(rect);
	
	// ajoute une vu sur la scene
	QGraphicsView* view = new QGraphicsView();
	view->setScene(scene);
	view->show(); //affiche la scene -> LES WIDGETS SONT INVISIBLES DE BASE!!!

	// rend le joueur focussable
	rect->setFlag(QGraphicsItem::ItemIsFocusable);
	// met le joueur comme focus de la scenne
	rect->setFocus();


	return a.exec();
}