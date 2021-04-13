#include "PageJeu.h"

//------------------Jeux
PageJeu::PageJeu()
{

}

PageJeu::PageJeu(int mode)
{

	//---Paramètre la Zone de jeux
	existe = true;
	scene = new QGraphicsScene(/*0,0,scene_width,scene_height*/);
	//QBrush brush;
	//brush.setTextureImage(QImage(":/Resource/Resource/BG.png"));
	QPixmap pim(":/Resource/Resource/BG.png");

	//scene->setBackgroundBrush(pim.scaled(scene_width,scene_height,Qt::IgnoreAspectRatio,Qt::SmoothTransformation));
	view = new  QGraphicsView(scene);
	view->setFocusPolicy(Qt::NoFocus); // Empêche de prendre le focus pour les key event


	//---Cree les Scores Boards
	scoreboard = new Score("Score");
	nbmouve = new Score("Nombre de Mouvements");

	//---Cree le tableau de jeux
	tableau = new Tableau(mode);

	//---Cree la grille de tuile fixe et les affiche a lecrant
	grillefixe = new Grille(mode, scene_width, scene_height);
	AfficheGrille(grillefixe);

	//---Cree la grille de tuile dynamique
	grilledynamique = new Grille(mode, scene_width, scene_height);

	//---syncronise les valeur des tuiles du tableaudynamique et les valeurs du tableau de jeu
	SyncronisationDesGrilles();

	//---sycronyse les valeurs initiales des score
	UpdateScore();

	//---Paramètre l'affichages des éléments de jeux
	QGridLayout* layout = new QGridLayout;
	layout->addWidget(scoreboard->Board, 0, 5, 1, 1, Qt::AlignCenter);
	layout->addWidget(nbmouve->Board, 1, 5, 1, 1, Qt::AlignCenter);
	layout->addWidget(view, 0, 1, 4, 4, Qt::AlignCenter);
	this->setLayout(layout);
}

PageJeu::~PageJeu()
{
	existe = false;
	scoreboard->~Score();
	nbmouve->~Score();
	grilledynamique->~Grille();
	grillefixe->~Grille();
	tableau->~Tableau();
	view->~QGraphicsView();
	scene ->~QGraphicsScene();
	qDebug() << "Page de Jeu detruite";
}

void PageJeu::AddTuile(int coord_X, int coord_Y, int valeur)
{
	//---Paramètre la tuile à ajouté à l'écrant
	Tuile* tuile = new Tuile(valeur);
	scene->addItem(tuile); // Ajoute la tuile à la scene avec les paramètre indiquées
	grilledynamique->setTuilePoss(coord_X, coord_Y, tuile);
}

void PageJeu::AfficheGrille(Grille* grille)
{
	int taille_cote = grille->getMode();

	for (int i = 0; i < taille_cote * taille_cote; i++)
	{
		scene->addItem(grille->getTuile_List(i));
	}
}

void PageJeu::SyncronisationDesGrilles()
{
	int mode = grilledynamique->getMode();
	int valeur = 0;

	for (int x = 0; x < mode; x++)
	{
		for (int y = 0; y < mode; y++)
		{
			//qDebug() << "coord X: " << x << "coord y: " << y;
			valeur = tableau->getTableauValeur(x, y);
			//qDebug() << "Valeur Lue pour tuile : " << valeur;
			AddTuile(x, y, valeur);
			UpdateScore();
		}
	}
}

void PageJeu::UpdateScore()
{
	int nbMouve = 0;
	int score = 0;
	nbMouve = tableau->Get_Move();
	score = tableau->Get_Score();
	scoreboard->setScore(score);
	nbmouve->setScore(nbMouve);
}

void PageJeu::keyPressEvent(QKeyEvent* event)
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

QGraphicsScene* PageJeu::getScene()
{
	return scene;
}

QGraphicsView* PageJeu::getView()
{
	return view;
}

bool PageJeu::getExist()
{
	return existe;
}