/*
	Auteur : Nicolas Cantin
*/

#ifndef JEU_H
#define JEU_H

#include <stdlib.h>
#include <iostream>
#include <conio.h>
#include "Tableau.h"

using namespace std;



class Jeu
{
public:
	Jeu();
	~Jeu();

	//void Run(); Vétuste
	
	void Menu_Accueil();

	void Menu_Jeu();

	void Menu_Load();

	void Load(string st);

	void Menu_Sauvegarde();

	void Menu_Stats();

	void Setup_Grid(int nb);
	

private:
	//Grille de jeu
	Tableau* tab = new Tableau();

	//Boucle pour Run
	bool run = true;

	string window_to_show;
};

#endif //JEU_H




