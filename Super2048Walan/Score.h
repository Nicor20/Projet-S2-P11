#ifndef SCORE_H
#define SCORE_H

#include <QLabel>
#include <QFont>
#include <QWidget>
#include <QVBoxLayout>

class Score : public QLabel
{
public:
	Score(QString titre);
	~Score();

	QWidget* Board;

	void setScore(int NouvValeur);
	int getScore();

private:
	QLabel* Titre;
	QLabel* TextValeur;
	
	int Valeur;

};

#endif // SCORE_H