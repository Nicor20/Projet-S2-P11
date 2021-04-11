/*
	Auteur : Nicolas Cantin
*/

#include <QApplication>
#include "Jeu.h"
#include "Affichage.h"

//Le menu de base vas ici
int main(int argc, char* argv[])
{
	QApplication app(argc, argv); //cette boucle fait tourner l'application constament
	
	Affichage affichage;
	affichage.setFocus();
	
	return app.exec();

}
