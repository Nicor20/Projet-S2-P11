/*
	Auteur : Nicolas Cantin
	Modifier par: Walan Brousseau
*/

#include <QApplication>
#include "Jeu.h"
#include "Affichage.h"

//Le menu de base vas ici
int main(int argc, char* argv[])
{
	QApplication app(argc, argv); //cette boucle fait tourner l'application constament
	Affichage affichage;
	affichage.setFocusPolicy(Qt::StrongFocus);
	affichage.setFocus();
	qDebug() << "Initialisation terminer";
	
	return app.exec();

}
