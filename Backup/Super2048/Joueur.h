#define JOUEUR_H
#ifdef JOUEUR_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

class joueur : public QGraphicsRectItem
{
public:
	void keyPressEvent(QKeyEvent* event); //g�re les contr�les du joueur

};

#endif JOUEUR_H