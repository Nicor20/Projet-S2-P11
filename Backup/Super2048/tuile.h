#define TUILE_H
#ifdef TUILE_H

#include <QGraphicsRectItem>

class Tuile: public QGraphicsRectItem // cr�e les tuiles du jeux
{
public:
	Tuile();

	~Tuile();

	Tuile(int type); //0 == tuile vide autre == tuiles de jeux
	
	// getter
	int getValeur();

	//Setter
	int setValeur(int NewValeur);

private:
	int valeur; // valeur de la tuile
};

#endif TUILE
