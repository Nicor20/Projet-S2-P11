#include "Affichage.h"

Affichage::Affichage()
{
	//---Paremètre la fenêtre principale
	statusBar(); // ajoute une status bar
	show(); // Affiche la fenêtre
	setMinimumSize(600, 600);

	//---Ajoute les éléments suivant à l'affichage
	LoadZonedeJeu(8); // Ajoute la zone de Jeu au mode spécifier à la fenêtre 
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
	AddGrille(mode);
}

void Affichage::AddTuile(int coord_X, int coord_Y, int valeur)
{
	//---Paramètre la tuile à ajouté à l'écrant
	Tuile * tuile = new Tuile(valeur);
	tuile->setPos(coord_X, coord_Y);

	scene->addItem(tuile); // Ajoute la tuile à la scene avec les paramètre indiquées

}

void Affichage::AddGrille(int mode)
{
	//---crée la liste des tuiles de la grille
	for (int i = 0; i < mode * mode; i++)
	{
		Tuile* tuile = new Tuile(0);
		ListTuileGrille.append(tuile);
	}

	//---Crée la grille de jeux selon la taille demandé (Mode de jeux)
	TuileGrille = new Tuile * *[mode];
	for (int i = 0; i < mode; i++)
	{
		TuileGrille[i] = new Tuile * [mode];
	}

	//---Détermine la position de départ de la créaton de tableau
	int origine_X = ((view->width()) / 2) - ((ListTuileGrille[1]->getSize() *113) / 2);
	int origine_Y = ((view->height()) / 2) - ((ListTuileGrille[1]->getSize() * 113) / 2);


	//---Place les Tuiles de la liste des tuile dans la grille et donne leur coordonnée
	for (int i = 0; i < mode*mode; i++)
	{
		int ranger = i / mode;
		int colone = i % mode;
		TuileGrille[ranger][colone] = ListTuileGrille[i];
		//qDebug() << "i: " << i;
		//qDebug() << "colone: " << colone;
		//qDebug() << "ranger: " << ranger;
	}

	for (size_t i = 0; i < mode; i++)
	{
		
		for (size_t j = 0; j < mode; j++)
		{
			int Pos_X = origine_X + (i * TuileGrille[i][j]->getSize());
			int Pos_Y = origine_Y + (j * TuileGrille[i][j]->getSize());
			TuileGrille[i][j]->setPos(Pos_X, Pos_Y);
			//qDebug() << "pos y: " << Pos_Y;
			//qDebug() << "pos x: " << Pos_X;
			scene->addItem(TuileGrille[i][j]);
		};
	}

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