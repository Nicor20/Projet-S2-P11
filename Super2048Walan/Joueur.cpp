#include "joueur.h"
#include <QDebug>
using namespace std;


void Joueur::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Left) // bouge vers la gauche
	{
		qDebug() << "event recus";
		
	}
	else if (event->key() == Qt::Key_Right) // bouge vers la droite
	{
		qDebug() << "event recus";
	}
	else if (event->key() == Qt::Key_Up) // bouge vers le haut
	{
		qDebug() << "event recus";
	}
	else if (event->key() == Qt::Key_Down) // bouge vers le bas
	{
		qDebug() << "event recus";
	}
}