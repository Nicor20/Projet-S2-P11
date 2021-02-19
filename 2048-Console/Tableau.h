#pragma once
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

class Tableau
{
public:
	Tableau(int i);
	Tableau();
	~Tableau();

	void Bouge_Droit();
	void Bouge_Gauche();
	void Bouge_Haut();
	void Bouge_Bas();

	void Ajout_Random();

	bool Move_Possible();

	void Afficher();

	int Get_Highest();

	int random(int high);

private:
	int ratio = 5;
	int size;
	int score = 0;

	vector<int> two_four;

	int** tableau;
};


