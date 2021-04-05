/*
	Auteur : Nicolas Cantin
*/
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

	void Run();
	
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






