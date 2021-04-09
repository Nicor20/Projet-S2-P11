#include "Affichage.h"

Affichage::Affichage()
{
	//---Parem�tre la fen�tre principale
	statusBar(); // ajoute une status bar
	show(); // Affiche la fen�tre
	setMinimumSize(600, 600);

	//---Ajoute les �l�ments suivant � l'affichage
	LoadZonedeJeu(5); // Ajoute la zone de Jeu au mode sp�cifier � la fen�tre
	
	//---TEST DES CAPACIT� DE LA GRILLE				  
	//qDebug() << "Taille debut: " << grilledynamique->getSize();
	AddTuile(0, 0, 2); //Ajoute
	//qDebug() << "Taille apres tuile 1: " << grilledynamique->getSize();
	grilledynamique->setTuilePoss(2, 0, grilledynamique->getTuile_XY(0, 0));
	//qDebug() << "Taille deplacement tuile 1: " << grilledynamique->getSize();
	AddTuile(2, 5, 2);
	//qDebug() << "Taille apres tuile 2: " << grilledynamique->getSize();
}

Affichage::~Affichage()
{
	qDebug() << "page detruite";
	destroy(this);
}

void Affichage::Message(const char* message)
{
	statusBar()->showMessage(message);
}

void Affichage::LoadZonedeJeu(int mode)
{
	//---Param�tre la Zone de jeux
	scene = new QGraphicsScene();
	view = new  QGraphicsView(scene);
	view->setScene(scene);
	setCentralWidget(view);

	//comment redimentionner les tuiles AVANT DE LES CR�ER?

	//---Cree la grille de tuile fixe et les affiche a lecrant
	grillefixe = new Grille(mode);
	AfficheGrille(grillefixe);

	//---Cree la grille de tuile dynamique
	grilledynamique = new Grille(mode);
	


	//---Message correspondant au mode dans la status Bar
	if (mode > 2 && mode < 9)
	{
		const char* message = "On joue";
		Message(message);
	}
	else
	{
		Message("Unkown Mode, Please retry...");
	}
}

void Affichage::AddTuile(int coord_X, int coord_Y, int valeur)
{
	//---Param�tre la tuile � ajout� � l'�crant
	Tuile * tuile = new Tuile(valeur);
	scene->addItem(tuile); // Ajoute la tuile � la scene avec les param�tre indiqu�es
	grilledynamique->setTuilePoss(coord_X, coord_Y, tuile);
}

void Affichage::AfficheGrille(Grille* grille)
{
	int taille_cote = grille->getMode();

	for (int i = 0; i < taille_cote * taille_cote; i++)
	{	
		qDebug() << "affiche tuile de grille";
		scene->addItem(grille->getTuile_List(i));
	}
	show();

}
