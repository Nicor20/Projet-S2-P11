#include "Affichage.h"


//------------------Constructeurs et Destructeurs
Affichage::Affichage()
{
	//---Paremètre la fenêtre principale
	statusBar(); // ajoute une status bar
	widget = new QWidget;
	setCentralWidget(widget);

	//---Ajoute les éléments suivant à l'affichage TEMPORAIRE
	LoadZonedeJeu(5); // Ajoute la zone de Jeu au mode spécifier à la fenêtre

	//---Paramètre l'affichages des éléments de jeux
	QGridLayout* layout = new QGridLayout;
	layout->addWidget(scoreboard->Board, 0, 5, 1, 1);
	layout->addWidget(nbmouve->Board, 1, 5, 1, 1);
	layout->addWidget(view, 0, 1, 4,4);
	widget->setLayout(layout);

	QString message = tr("A context menu is available by right-clicking");
	statusBar()->showMessage(message);
	
	//---paramètre la barre de menu et leurs actions
	CreationActions();
	CreationMenus();

	setWindowTitle(tr("Super 2048"));
	setMinimumSize(160, 160);
	resize(600, 600);

	show();
}

Affichage::~Affichage()
{
	scoreboard->~Score();
	nbmouve->~Score();
	grilledynamique->~Grille();
	grillefixe->~Grille();
	tableau->~Tableau();
	view->~QGraphicsView();
	scene ->~QGraphicsScene();
	qDebug() << "page detruite";

}


//-------------------Utilitaire
void Affichage::CreationActions()
{
	//creer les action:
	//NouvellePartie
	NouvellePartie = new QAction(tr("&Nouvelle Partie"), this);
	NouvellePartie->setStatusTip(tr("Recommencer une nouvelle partie dans le mode actuelle"));
	connect(NouvellePartie, &QAction::triggered, this, &Affichage::Recommencer);
	
	//ChargerPartie
	ChargerPartie = new QAction(tr("&Charger Partie"), this);
	ChargerPartie->setStatusTip(tr("Charge la dernière partie sauvegarder"));
	connect(ChargerPartie, &QAction::triggered, this, &Affichage::Charger);
	
	//SauvegarderPartie
	SauvegarderPartie = new QAction(tr("&Sauvegarder Partie"), this);
	SauvegarderPartie->setStatusTip(tr("Sauvegarde la partie actuelle"));
	connect(SauvegarderPartie, &QAction::triggered, this, &Affichage::Sauvegarder);
	
	//QuitterPartie
	QuitterPartie = new QAction(tr("&Quitter Partie"), this);
	QuitterPartie->setStatusTip(tr("Quitte la partie actuelle Sans Sauvegarder"));
	connect(QuitterPartie, &QAction::triggered, this, &Affichage::Quitter);
}

void Affichage::CreationMenus()
{
	//---Parametre les Menu déroulants
	//Menu
	Menu = menuBar()->addMenu(tr("&Menu"));
	Menu->addAction(NouvellePartie);
	Menu->addAction(ChargerPartie);
	Menu->addAction(SauvegarderPartie);
	Menu->addSeparator();
	Menu->addAction(QuitterPartie);
}

void Affichage::Message(const char* message)
{
	statusBar()->showMessage(message);
}

QGraphicsScene* Affichage::getScene()
{
	return scene;
}

QGraphicsView* Affichage::getView()
{
	return view;
}


//-------------------Menus
void Affichage::Recommencer()
{
	qDebug() << "NON IMPLEMENTER WIP Doit permettre de recommencer une nouvelle partie avec le mode actuell WIP";
}

void Affichage::Charger()
{
	qDebug() << "NON IMPLEMENTER WIP Doit Permettre de charger une partie WIP";
}

void Affichage::Sauvegarder()
{
	qDebug() << "NON IMPLEMENTER WIP Doit sauvegarger la partie actuelle WIP";
}

void Affichage::Quitter()
{
	//Ferme l'interface
	qDebug() << "NON IMPLEMENTER WIP Doit quitter la partie actuelle et retourner au menu principale WIP";
}


//------------------Jeux
void Affichage::LoadZonedeJeu(int mode)
{
	//---Paramètre la Zone de jeux
	scene = new QGraphicsScene(/*0,0,scene_width,scene_height*/);
	//QBrush brush;
	//brush.setTextureImage(QImage(":/Resource/Resource/BG.png"));
	QPixmap pim(":/Resource/Resource/BG.png");
	
	scene->setBackgroundBrush(pim.scaled(scene_width,scene_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	view = new  QGraphicsView(scene);
	view->setFocusPolicy(Qt::NoFocus); // Empêche de prendre le focus pour les key event


	//---Cree les Scores Boards
	scoreboard = new Score("Score");
	nbmouve = new Score("Nombre de Mouvements");

	//---Cree le tableau de jeux
	tableau = new Tableau(mode);

	//---Cree la grille de tuile fixe et les affiche a lecrant
	grillefixe = new Grille(mode,scene_width,scene_height);
	AfficheGrille(grillefixe);

	//---Cree la grille de tuile dynamique
	grilledynamique = new Grille(mode,scene_width,scene_height);

	//---syncronise les valeur des tuiles du tableaudynamique et les valeurs du tableau de jeu
	SyncronisationDesGrilles();

	//---sycronyse les valeurs initiales des score
	UpdateScore();

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
		show();
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
			UpdateScore();
			show();
		}
	}
}

void Affichage::UpdateScore()
{
	int nbMouve = 0;
	int score = 0;
	nbMouve = tableau->Get_Move();
	score = tableau->Get_Score();
	scoreboard->setScore(score);
	nbmouve->setScore(nbMouve);
}

void Affichage::keyPressEvent(QKeyEvent* event)
{
	
	if (event->key() == Qt::Key_Left) // bouge vers la gauche
	{
		qDebug() << "Bouge Gauche";
		tableau->Bouge_Haut();
		SyncronisationDesGrilles();
	}
	else if (event->key() == Qt::Key_Right) // bouge vers la droite
	{
		qDebug() << "Bouge Droite";
		tableau->Bouge_Bas();
		SyncronisationDesGrilles();
	}
	else if (event->key() == Qt::Key_Up) // bouge vers le haut
	{
		qDebug() << "Bouge Haut";
		tableau->Bouge_Gauche();
		SyncronisationDesGrilles();
	}
	else if (event->key() == Qt::Key_Down) // bouge vers le bas
	{
		qDebug() << "Bouge Bas";
		tableau->Bouge_Droit();
		SyncronisationDesGrilles();
	}
}