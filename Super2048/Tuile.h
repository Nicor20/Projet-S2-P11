#ifndef TUILE_H
#define TUILE_H

#include <QGraphicsRectItem>

using namespace std;
class Tuile : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
public:
	Tuile();
	Tuile(int valeur);
	~Tuile();

	int getSize(); //retourne la taille d'un coté de tuile en pixel
	void setSize(int NouvSize); //change la taille de toutes les futures tuiles générées
	

public slots:
	//void Mouve(int direction); // 0 = stop, 1 = haut, 2 = bas, 3 = gauche, 4 = droite

private:
	int Valeur; //valeur de la tuile 0 = tuiles grille(fixe), autre = Tuile dynamique(dynamique) 
	int Size = 60; // taille d'un côté de tuile

};



#endif //TUILE_H