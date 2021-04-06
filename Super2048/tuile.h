#define TUILE_H
#ifdef TUILE_H

#include <QGraphicsRectItem>

class Tuile: public QGraphicsRectItem // crée les tuiles du jeux
{
public:
	Tuile();
	
	// getter
	int getValeur();

	//Setter
	int setValeur(int NewValeur);

private:
	int valeur; // valeur de la tuile
};

#endif TUILE
