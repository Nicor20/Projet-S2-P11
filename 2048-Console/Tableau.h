#pragma once
#include <random>
#include <iostream>

using namespace std;

class Tableau
{
public:

	bool Next_Move_Possible;
	Tableau();
	~Tableau();

	void Bouge_Droit();
	void Bouge_Gauche();
	void Bouge_Haut();
	void Bouge_Bas();

	void Ajout_Random();

	void Est_Plein();

	void Move_Possible();

	void Afficher();

	int Get_Highest();

	int random(int low, int high);

private:
	int tableau[4][4];
	int score = 0;
};


