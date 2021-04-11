#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>
#include <QFont>

class Score : public QGraphicsTextItem
{
public:
	Score(QString titre);

	void setScore(int NouvValeur);
	int getScore();
	

private:
	QString Titre;
	int Valeur;
};

#endif // SCORE_H