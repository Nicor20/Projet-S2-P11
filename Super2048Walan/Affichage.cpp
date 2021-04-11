#include "Affichage.h"

Affichage::Affichage()
{
	//---Paremètre la fenêtre principale
	statusBar(); // ajoute une status bar
	show(); // Affiche la fenêtre
	setMinimumSize(600, 600);

	//---Ajoute les éléments suivant à l'affichage
	LoadZonedeJeu(5); // Ajoute la zone de Jeu au mode spécifier à la fenêtre
	show();

	//---TEST DES CAPACITÉ DE LA GRILLE				  
	//qDebug() << "Taille debut: " << grilledynamique->getSize();
	//AddTuile(0, 0, 8); //Ajoute une tuile 
	//qDebug() << "Taille apres tuile 1: " << grilledynamique->getSize();
	//grilledynamique->setTuilePoss(2, 0, grilledynamique->getTuile_XY(0, 0)); // exemple de commande de déplacement de tuile
	//qDebug() << "Taille deplacement tuile 1: " << grilledynamique->getSize();
	//AddTuile(2, 5, 1024);
	//qDebug() << "Taille apres tuile 2: " << grilledynamique->getSize();
}

Affichage::~Affichage()
{
	grilledynamique->~Grille();
	grillefixe->~Grille();
	tableau->~Tableau();
	view->~QGraphicsView();
	scene ->~QGraphicsScene();
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

	//---Cree le tableau de jeux
	tableau = new Tableau(mode);


	//---Cree la grille de tuile fixe et les affiche a lecrant
	grillefixe = new Grille(mode);
	AfficheGrille(grillefixe);

	//---Cree la grille de tuile dynamique
	grilledynamique = new Grille(mode);

	//---syncronise les valeur des tuiles du tableaudynamique et les valeurs du tableau de jeu
	SyncronisationDesGrilles();

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
	scene->addItem(tuile); // Ajoute la tuile à la scene avec les paramètre indiquées
	grilledynamique->setTuilePoss(coord_X, coord_Y, tuile);
}

void Affichage::AfficheGrille(Grille* grille)
{
	int taille_cote = grille->getMode();

	for (int i = 0; i < taille_cote * taille_cote; i++)
	{
		scene->addItem(grille->getTuile_List(i));
	}
}

void Affichage::SyncronisationDesGrilles()
{
	int mode = grilledynamique->getMode();
	int valeur = 0;

	for (int x = 0; x < mode; x++)
	{
		for (int y = 0; y < mode; y++)
		{
			//qDebug() << "coord X: " << x << "coord y: " << y;
			valeur = tableau->getTableauValeur(x,y);
			//qDebug() << "Valeur Lue pour tuile : " << valeur;
			AddTuile(x, y, valeur);
		}
	}
}

QGraphicsScene* Affichage::getScene()
{
	return scene;
}

QGraphicsView* Affichage::getView()
{
	return view;
}

/*Joueur* Affichage::getJoueur()

{
	return joueur;
}*/


void Affichage::keyPressEvent(QKeyEvent* event)
{
	
	if (event->key() == Qt::Key_Left) // bouge vers la gauche
	{
		//qDebug() << "Bouge Gauche";
		tableau->Bouge_Haut();
		SyncronisationDesGrilles();
	}
	else if (event->key() == Qt::Key_Right) // bouge vers la droite
	{
		//qDebug() << "Bouge Droite";
		tableau->Bouge_Bas();
		SyncronisationDesGrilles();
	}
	else if (event->key() == Qt::Key_Up) // bouge vers le haut
	{
		//qDebug() << "Bouge Haut";
		tableau->Bouge_Gauche();
		SyncronisationDesGrilles();
	}
	else if (event->key() == Qt::Key_Down) // bouge vers le bas
	{
		//qDebug() << "Bouge Bas";
		tableau->Bouge_Droit();
		SyncronisationDesGrilles();
	}
}