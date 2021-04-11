#include "Affichage.h"

Affichage::Affichage()
{
	//---Paremètre la fenêtre principale
	statusBar(); // ajoute une status bar
	show(); // Affiche la fenêtre
	//setMinimumSize(600, 600);

	//---Ajoute les éléments suivant à l'affichage
	LoadZonedeJeu(8); // Ajoute la zone de Jeu au mode spécifier à la fenêtre
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

}

void Affichage::Message(const char* message)
{
	statusBar()->showMessage(message);
}

void Affichage::LoadZonedeJeu(int mode)
{
	//---Paramètre la Zone de jeux
	
	scene = new QGraphicsScene(/*0,0,scene_width,scene_height*/);
	//QBrush brush;
	//brush.setTextureImage(QImage(":/Resource/Resource/BG.png"));
	QPixmap pim(":/Resource/Resource/BG.png");
	
	scene->setBackgroundBrush(pim/*.scaled(scene_width,scene_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation)*/);
	view = new  QGraphicsView(scene);
	view->setFocusPolicy(Qt::NoFocus); // Empêche de prendre le focus pour les key event

	QGridLayout* layout = new QGridLayout;
	QWidget* widget = new QWidget;
	layout->addWidget(view,1,1,2,1);
	widget->setLayout(layout);
	widget->setFocusPolicy(Qt::NoFocus); // Empêche de prendre le focus pour les key event
	setCentralWidget(widget);


	//---Cree les Scores Boards
	scoreboard = new Score(QString("Score"));
	scene->addItem(scoreboard);
	nbmouve = new Score(QString("Nombre de Mouvements"));
	scene->addItem(nbmouve);
	nbmouve->setPos(0,20);

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

QGraphicsScene* Affichage::getScene()
{
	return scene;
}

QGraphicsView* Affichage::getView()
{
	return view;
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