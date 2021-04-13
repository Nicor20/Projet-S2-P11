#ifndef SCORE_H
#define SCORE_H

#include <QLabel>
#include <QFont>
#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>

class Score : public QGroupBox
{
public:
	Score(QString titre);
	~Score();

	QGroupBox* Board;
	

	void setScore(int NouvValeur);
	int getScore();

private:
	QLabel* Titre;
	QLabel* TextValeur;
	int Valeur;

};

#endif // SCORE_H