/*
	Auteur : Nicolas Cantin
*/

#pragma once
#include <random>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

using namespace std;

class Tableau
{
public:
	Tableau(int i);
	Tableau();
	~Tableau();


	void Bouge_Droit();		// Pour combiner et bouger les cases vers la droite
	void Bouge_Gauche();	// Pour combiner et bouger les cases vers la gauche
	void Bouge_Haut();		// Pour combiner et bouger les cases vers le haut
	void Bouge_Bas();		// Pour combiner et bouger les cases vers le bas

	void Ajout_Random();	// Ajoute une case de valeur aléatoire (2 ou 4) dans une case vide de facon aléatoire

	bool Move_Possible();	// Vérifie si il y à possiblité pour le jouer d'effectuer un mouvement

	void Afficher();		// Affiche la grille de jeu ainsi que les info pertinente

	int Get_Max();			// Renvoi la valeur maximale présente dans la grille de jeu
	int Get_Move();			// Renvoi le nombre de mouvement effectuer durant la partie actuel
	int Get_Score();		// Renvoi le pointage de la partie
	int Get_Size();			// Renvoi le grosseur de la grille

	int random(int high);	// Renvoie un valeur random

	void Save();			// Sauvegarde les informations pertinente pour le menu statistique

private:
	int ratio = 5;			// Ratio de 2 pour chaque 4
	int size;				// Taille de la grille
	int score = 0;			// Pointage de la partie
	int Nb_Move = 0;		// Nombre de mouvement

	vector<int> two_four;	// Vecteur de 2 et de 4

	int** tableau;			// pointeur de pointeur pour faire le tableau adaptif
};


