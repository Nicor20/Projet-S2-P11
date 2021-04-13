#include "Affichage.h"



//------------------Constructeurs et Destructeurs
Affichage::Affichage()
{
	//---Paremètre la fenêtre principale
	PageActuelle = new QWidget;
	menuprincipal = new PageMenuPrincipal();

	CreationActions();
	CreationMenus();

	statusBar(); // ajoute une status bar
	setCentralWidget(menuprincipal);

	//---Ajoute les éléments suivant à l'affichage TEMPORAIRE
	//CreationZonedeJeu(5); // Ajoute la zone de Jeu au mode spécifier à la fenêtre

	//---
	setWindowTitle(tr("Super 2048"));
	setMinimumSize(160, 160);
	resize(600, 600);

	show();
}

Affichage::~Affichage()
{

	qDebug() << "page detruite";
}


//-------------------Utilitaire
void Affichage::CreationActions()
{
	//creer les action:
	//Mode 3x3
	Mode3 = new QAction(tr("&Grille 3X3"), this);
	Mode3->setStatusTip(tr("Recommencer une nouvelle partie dans le mode 3X3"));
	connect(Mode3, &QAction::triggered, this, &Affichage::mode3);

	//Mode 4x4
	Mode4 = new QAction(tr("&Grille 4X4"), this);
	Mode4->setStatusTip(tr("Recommencer une nouvelle partie dans le mode 4X4"));
	connect(Mode4, &QAction::triggered, this, &Affichage::mode4);

	//Mode 5x5
	Mode5 = new QAction(tr("&Grille 5X5"), this);
	Mode5->setStatusTip(tr("Recommencer une nouvelle partie dans le mode 5X5"));
	connect(Mode5, &QAction::triggered, this, &Affichage::mode5);

	//Mode 6x6
	Mode6 = new QAction(tr("&Grille 6X6"), this);
	Mode6->setStatusTip(tr("Recommencer une nouvelle partie dans le mode 6X6"));
	connect(Mode6, &QAction::triggered, this, &Affichage::mode6);

	//Mode 7x7
	Mode7 = new QAction(tr("&Grille 7X7"), this);
	Mode7->setStatusTip(tr("Recommencer une nouvelle partie dans le mode 7X7"));
	connect(Mode7, &QAction::triggered, this, &Affichage::mode7);

	//Mode 8x8
	Mode8 = new QAction(tr("&Grille 8X8"), this);
	Mode8->setStatusTip(tr("Recommencer une nouvelle partie dans le mode 8X8"));
	connect(Mode8, &QAction::triggered, this, &Affichage::mode8);

	//ChargerPartie
	ChargerPartie = new QAction(tr("&Charger Partie"), this);
	ChargerPartie->setStatusTip(tr("(NON FONCTIONNEL) Charge la dernière partie sauvegarder"));
	connect(ChargerPartie, &QAction::triggered, this, &Affichage::Charger);
	
	//SauvegarderPartie
	SauvegarderPartie = new QAction(tr("&Sauvegarder Partie"), this);
	SauvegarderPartie->setStatusTip(tr("(NON FONCTIONNEL) Sauvegarde la partie actuelle"));
	connect(SauvegarderPartie, &QAction::triggered, this, &Affichage::Sauvegarder);
	
	//QuitterPartie
	QuitterPartie = new QAction(tr("&Quitter Partie"), this);
	QuitterPartie->setStatusTip(tr("Quitte la partie et ramenne au menu principal"));
	connect(QuitterPartie, &QAction::triggered, this, &Affichage::Quitter);
}

void Affichage::CreationMenus()
{
	//---Parametre les Menu déroulants
	//Menu
	Menu = menuBar()->addMenu(tr("&Menu"));
	NouvellePartie = Menu->addMenu(tr("&Nouvelle Partie"));
	Menu->addAction(ChargerPartie);
	Menu->addAction(SauvegarderPartie);
	Menu->addSeparator();
	Menu->addAction(QuitterPartie);

	//Nouvelle Parti\Mode
	Mode = NouvellePartie->addMenu(tr("&Mode"));
	Mode->addAction(Mode3);
	Mode->addAction(Mode4);
	Mode->addAction(Mode5);
	Mode->addAction(Mode6);
	Mode->addAction(Mode7);
	Mode->addAction(Mode8);
}

void Affichage::ChangePage(QWidget* page)
{
	if (page == NULL)
	{
		qDebug() << "Cette page Nexiste pas";
	}
	else
	{
		this->takeCentralWidget();
		setCentralWidget(page);
		PageActuelle = page;
		page->setFocus();
	}
	
}

void Affichage::CreationZonedeJeu(int mode)
{
	if (pagejeu->getExist()==true)
	{
		pagejeu->~PageJeu();
		jeu->~Jeu();
	}
	pagejeu = new PageJeu(mode);
	jeu = new Jeu();
}

QWidget* Affichage::getPageActuelle()
{
	return PageActuelle;
}

//-------------------Menus

void Affichage::Charger()
{
	qDebug() << "NON IMPLEMENTER WIP Doit Permettre de charger une partie WIP";
	//jeu->Menu_Load();
}

void Affichage::Sauvegarder()
{
	qDebug() << "NON IMPLEMENTER WIP Doit sauvegarger la partie actuelle WIP";
	//jeu->Menu_Sauvegarde();
}

void Affichage::Quitter()
{
	//Ferme la partie actuelle et affiche la fenêtre principale
	ChangePage(menuprincipal);
	pagejeu->~PageJeu();
}

void Affichage::mode3()
{
	CreationZonedeJeu(3);
	ChangePage(pagejeu);
}
void Affichage::mode4()
{
	CreationZonedeJeu(4);
	ChangePage(pagejeu);
}
void Affichage::mode5()
{
	CreationZonedeJeu(5);
	ChangePage(pagejeu);
}
void Affichage::mode6()
{
	CreationZonedeJeu(6);
	ChangePage(pagejeu);
}
void Affichage::mode7()
{
	CreationZonedeJeu(7);
	ChangePage(pagejeu);
}
void Affichage::mode8()
{
	CreationZonedeJeu(8);
	ChangePage(pagejeu);
}

