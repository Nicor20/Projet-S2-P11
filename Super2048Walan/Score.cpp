#include "Score.h"

Score::Score(QString titre)
{

	//---initialise le score board
	Board = new QGroupBox;
	Titre = new QLabel;
	TextValeur = new QLabel;
	
	Valeur = 0;
	TextValeur->setNum(0);
	Titre->setText(titre);

	//---style
	QPalette palette;
	palette.setColor(QPalette::Text, Qt::white);
	setPalette(palette);
	setFont(QFont("times", 16));

	//---dessine le text du score board
	QGridLayout* layout = new QGridLayout;
	layout->addWidget(Titre,1,1,1,1);
	layout->addWidget(TextValeur,2,1,1,1);
	Board->setLayout(layout);

}

Score::~Score()
{

}

void Score::setScore(int NouvValeur)
{
	//---dessine le text du score board
	TextValeur->setNum(NouvValeur);
	Valeur=NouvValeur;
}

int Score::getScore()
{
	return Valeur;
}
