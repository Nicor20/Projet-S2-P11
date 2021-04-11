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

	int getSize(); //retourne la taille d'un coté de tuile en pixel
	int getValeur(); //retourne la valeur de la tuile
	int getExiste(); // retourne 1 si la tuiles est deja sur le plateau de jeux
	void setSize(int NouvSize); //change la taille de toutes les futures tuiles générées
	void setValeur(int NouvValeur); //Change la valeur de la tuile

public slots:
	

private:
	int Valeur = 0; //valeur de la tuile 0 = tuiles grille(fixe), autre = Tuile dynamique(dynamique) 
	int Size = 60; // taille d'un côté de tuile
	int Existe = 0; // determine si la tuile étais déjà sur la grille (pour les déplacements)

};



#endif //TUILE_H