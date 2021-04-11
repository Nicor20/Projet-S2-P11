#ifndef TUILE_H
#define TUILE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPixmap>
#include <QDebug>

using namespace std;
class Tuile : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	Tuile();
	Tuile(int valeur);
	~Tuile();

	int getSize(); //retourne la taille d'un cot� de tuile en pixel
	int getValeur(); //retourne la valeur de la tuile
	int getExiste(); // retourne 1 si la tuiles est deja sur le plateau de jeux
	void setSize(int NouvSize); //change la taille de toutes les futures tuiles g�n�r�es
	void setValeur(int NouvValeur); //Change la valeur de la tuile

public slots:
	

private:
	int Valeur = 0; //valeur de la tuile 0 = tuiles grille(fixe), autre = Tuile dynamique(dynamique) 
	int Size = 60; // taille d'un c�t� de tuile
	int Existe = 0; // determine si la tuile �tais d�j� sur la grille (pour les d�placements)

};



#endif //TUILE_H