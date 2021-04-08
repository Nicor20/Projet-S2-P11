#include "Affichage.h"

Affichage::Affichage()
{
	//---Paremètre la fenêtre principale
	statusBar(); // ajoute une status bar
	show(); // Affiche la fenêtre
	setMinimumSize(600, 600);

	//---Ajoute les éléments suivant à l'affichage
	LoadZonedeJeu(5); // Ajoute la zone de Jeu au mode spécifier à la fenêtre 
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
	//---Paramètre la Zone de jeux
	scene = new QGraphicsScene();
	view = new  QGraphicsView(scene);
	view->setScene(scene);
	setCentralWidget(view);

	//comment redimentionner les tuiles AVANT DE LES CRÉER?

	//---Cree la grille de tuile fixe et les affiche a lecrant
	grillefixe = new Grille;
	grillefixe->AddGrille(mode, view, scene);
	grillefixe->AfficheGrille(mode, scene);

	//---Cree la grille de tuile dynamique
	grilledynamique = new Grille;
	grilledynamique->AddGrille(mode, view, scene);

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
	//---Paramètre la tuile à ajouté à l'écrant
	Tuile * tuile = new Tuile(valeur);
	tuile->setPos(coord_X, coord_Y);

	scene->addItem(tuile); // Ajoute la tuile à la scene avec les paramètre indiquées
}
