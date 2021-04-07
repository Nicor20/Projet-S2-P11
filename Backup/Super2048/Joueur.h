#define JOUEUR_H
#ifdef JOUEUR_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

class joueur : public QGraphicsRectItem
{
public:
	void keyPressEvent(QKeyEvent* event); //gère les contrôles du joueur

};

#endif JOUEUR_H