#include "joueur.h"
#include <QDebug>
using namespace std;

void joueur::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Left) // bouge vers la gauche
	{
		setPos(x() - 113, y());
	}
	else if (event->key() == Qt::Key_Right) // bouge vers la droite
	{
		setPos(x() + 113, y());
	}
	else if (event->key() == Qt::Key_Up) // bouge vers le haut
	{
		setPos(x(), y() - 113);
	}
	else if (event->key() == Qt::Key_Down) // bouge vers le bas
	{
		setPos(x(), y() + 113);
	}
}