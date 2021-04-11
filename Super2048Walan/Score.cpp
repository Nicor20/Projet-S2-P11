#include "Score.h"

Score::Score(QString titre)
{
	//---initialise le score board
	Valeur = 0;
	Titre = titre;

	//---dessine le text du score board
	setPlainText(QString(Titre) + QString::number(Valeur));
	setDefaultTextColor(Qt::white);
	setFont(QFont("times", 16));
}

void Score::setScore(int NouvValeur)
{
	Valeur = NouvValeur;
	setPlainText(QString(Titre) + ": " + QString::number(Valeur));
}

int Score::getScore()
{
	return Valeur;
}
