/*
	Auteur : Nicolas Cantin
*/

#include "Tableau.h"

Tableau::Tableau(int z)
{	
	size = z;

	// Rempli le vecteur de 2 et de 4
	for (int i = 0; i < ratio*10; i++)
	{
		if (i % ratio != 0)
		{
			two_four.push_back(2);
		}
		else
		{
			two_four.push_back(4);
		}
	}

	//vecteur pour les case vide
	vector<int> vec;

	//Création du tableau adaptif selon la valeur de size
	tableau = new int* [size];
	for (int i = 0; i < size; i++)
	{
		tableau[i] = new int[size];
	}

	// Remplis la grille de 0
	for (int i = 0; i < size * size; i++)
	{
		tableau[(int)floor(i / size)][i % size] = 0;
		vec.push_back(i);
	}

	//Détermine 2 position de case pour les valeurs de départ
	for (int i = 0; i < 2; i++)
	{
		int pos = vec[random(vec.size())];
		tableau[(int)floor(pos / size)][pos % size] = two_four[random(ratio*10)];
		vec.erase(vec.begin() + pos);
	}
}

Tableau::Tableau()
{

}

Tableau::~Tableau()
{
	for (int i = 0; i < size; ++i)
	{
		delete[] tableau[i];
	}
	delete[] tableau;
}

void Tableau::Bouge_Droit()
{
	bool move = false;
	int x = 0, y = 0, z = 0;

	// Passe à travers chaque rangé du tableau du haut vers le bas
	for (y = 0; y < size; y++)
	{
		// De la droie vers la gauche
		for (x = size-1; x >= 0; x--)
		{
			// Si la case n'est pas vide
			if (tableau[y][x] != 0)
			{
				// Vérifie chacune des case à la gauche de celle-ci
				for (z = x - 1; z >= 0; z--)
				{
					// Si la case n'est pas vide
					if (tableau[y][z] != 0)
					{
						// Si les deux case ont la meme valeur on vas les joindres
						if (tableau[y][x] == tableau[y][z])
						{
							score += tableau[y][x] + tableau[y][z];
							tableau[y][x] *= 2;
							tableau[y][z] = 0;
						}
						break;
					}
				}
			}
		}
		
		// De la droite vers la gauche
		for (x = size-1; x >= 0; x--)
		{
			// Si la case est vide
			if (tableau[y][x] == 0)
			{
				// Vérifie chacune des case à la gauche de celle-ci
				for (z = x - 1; z >= 0; z--)
				{
					// Si la case n'est pas vide la bouger 
					if (tableau[y][z] != 0)
					{
						tableau[y][x] = tableau[y][z];
						tableau[y][z] = 0;
						move = true;
						break;
					}
				}
			}
		}
	}

	// Si une case à bouger augmenter de un le nombre de mouvement 
	if (move == true)
	{
		Nb_Move++;
	}
	
	// Ajout d'un 2 ou d'un 4 à une case vide
	Ajout_Random();
}

void Tableau::Bouge_Gauche()
{
	bool move = false;
	int x = 0, y = 0, z = 0;

	// Passe à travers chaque rangé du tableau du haut vers le bas
	for (y = 0; y < size; y++)
	{
		// De la gauche vers la droite
		for (x = 0; x < size; x++)
		{
			// Si la case n'est pas vide
			if (tableau[y][x] != 0)
			{
				// Vérifie chacune des case à la droite de celle-ci
				for (z = x + 1; z < size; z++)
				{
					// Si la case n'est pas vide
					if (tableau[y][z] != 0)
					{
						// Si les deux case ont la meme valeur on vas les joindres
						if (tableau[y][x] == tableau[y][z])
						{
							score += tableau[y][x] + tableau[y][z];
							tableau[y][x] *= 2;
							tableau[y][z] = 0;
						}
						break;
					}
				}
			}
		}

		// De la gauche vers la droite
		for (x = 0; x < size; x++)
		{
			// Si la case est vide
			if (tableau[y][x] == 0)
			{
				// Vérifie chacune des case à la droite de celle-ci
				for (z = x + 1; z < size; z++)
				{
					// Si la case n'est pas vide la déplacer
					if (tableau[y][z] != 0)
					{
						tableau[y][x] = tableau[y][z];
						tableau[y][z] = 0;
						move = true;
						break;
					}
				}
			}
		}
	}

	// Si une case à bouger augmenter de un le nombre de mouvement 
	if (move == true)
	{
		Nb_Move++;
	}

	// Ajout d'un 2 ou d'un 4 à une case vide
	Ajout_Random();
}

void Tableau::Bouge_Haut()
{
	bool move = false;
	int x = 0, y = 0, z = 0;

	// Passe à travers chaque colone du tableau de la gauche vers la droite
	for (x = 0; x < size; x++)
	{
		// Du haut vers le bas
		for (y = 0; y < size; y++)
		{
			// Si la case n'est pas vide
			if (tableau[y][x] != 0)
			{
				// Vérifie chacune des case en bas de celle-ci
				for (z = y + 1; z < size; z++)
				{
					// Si la case n'est pas vide
					if (tableau[z][x] != 0)
					{
						// Si les deux case ont la meme valeur on vas les joindres
						if (tableau[y][x] == tableau[z][x])
						{
							score += tableau[y][x] + tableau[z][x];
							tableau[y][x] *= 2;
							tableau[z][x] = 0;
						}
						break;
					}
				}
			}
		}

		// Du haut vers le bas
		for (y = 0; y < size; y++)
		{
			// Si la case est vide
			if (tableau[y][x] == 0)
			{
				// Vérifie chacune des case en bas de celle-ci
				for (z = y + 1; z < size; z++)
				{
					// Si la case n'est pas vide la bouger
					if (tableau[z][x] != 0)
					{
						tableau[y][x] = tableau[z][x];
						tableau[z][x] = 0;
						move = true;
						break;
					}
				}
			}
		}
	}

	// Si une case à bouger augmenter de un le nombre de mouvement 
	if (move == true)
	{
		Nb_Move++;
	}

	// Ajout d'un 2 ou d'un 4 à une case vide
	Ajout_Random();
}

void Tableau::Bouge_Bas()
{
	bool move = false;
	int x = 0, y = 0, z = 0;

	// Passe à travers chaque colone du tableau de la gauche vers la droite
	for (x = 0; x < size; x++)
	{
		// Du bas vers le haut
		for (y = size-1; y >=0 ; y--)
		{
			// Si la case n'est pas vide
			if (tableau[y][x] != 0)
			{
				// Vérifie chacune des case en haut de celle-ci
				for (z = y - 1; z >= 0; z--)
				{
					// Si la case n'est pas vide
					if (tableau[z][x] != 0)
					{
						// Si les deux case ont la meme valeur on vas les joindres
						if (tableau[y][x] == tableau[z][x])
						{
							score += tableau[y][x] + tableau[z][x];
							tableau[y][x] *= 2;
							tableau[z][x] = 0;
						}
						break;
					}
				}
			}
		}

		// Du bas vers le haut
		for (y = size-1; y >= 0; y--)
		{
			// Si la case est vide
			if (tableau[y][x] == 0)
			{
				// Vérifie chacune des case en bas de celle-ci
				for (z = y - 1; z >= 0; z--)
				{
					// Si la case n'est pas vide la bouger
					if (tableau[z][x] != 0)
					{
						tableau[y][x] = tableau[z][x];
						tableau[z][x] = 0;
						move = true;
						break;
					}
				}
			}
		}
	}

	// Si une case à bouger augmenter de un le nombre de mouvement 
	if (move == true)
	{
		Nb_Move++;
	}

	// Ajout d'un 2 ou d'un 4 à une case vide
	Ajout_Random();
}

void Tableau::Ajout_Random()
{
	// Remplis le vecteur avec la position des case vide du graphique 
	vector<int> vec;
	for (int i = 0; i < size*size; i++)
	{
		if (tableau[(int)floor(i / size)][i % size] == 0)
		{
			vec.push_back(i);
		}
	}

	// Si il y a une case de vide déterminer une position aléatoire et insert 2 ou 4
	if (vec.size() > 0)
	{
		int pos = vec[random(vec.size())];
		tableau[(int)floor(pos / size)][pos % size] = two_four[random(ratio*10)];
	}
}

void Tableau::Afficher()
{
	// Vide la console
	system("cls");

	//Affiche les info importante ainsi que la grille de jeu
	cout << "Mode " << size << "x" << size << endl << endl;
	cout << "Score : " << score << endl;
	cout << "Max : " << Get_Max() << "/2048" << endl;
	
	for (int y = 0; y < size; y++)
	{
		if (y == 0)
		{
			cout << char(218);
			for (int i = 0; i < size; i++)
			{
				cout << char(196) << char(196) << char(196) << char(196);
				if (i != size-1)
				{
					cout << char(194);
				}
			}
			cout << char(191) << endl;
		}

		cout << char(179);
		for (int x = 0; x < size; x++)
		{
			if (tableau[y][x] == 0)
			{
				cout << "    " << char(179);
			}
			else if (tableau[y][x] < 10)
			{
				cout << " 0" << tableau[y][x] << " " << char(179);
			}
			else if (tableau[y][x] < 100)
			{
				cout << " " << tableau[y][x] << " " << char(179);
			}
			else if (tableau[y][x] < 1000)
			{
				cout << " " << tableau[y][x] << char(179);
			}
			else
			{
				cout << tableau[y][x] << char(179);
			}
		}
		cout << endl;

		if (y == size - 1)
		{
			cout << char(192);
			for (int i = 0; i < size; i++)
			{
				cout << char(196) << char(196) << char(196) << char(196);
				if (i != size-1)
				{
					cout << char(193);
				}
			}
			cout << char(217) << endl;
		}
		else
		{
			cout << char(195);
			for (int i = 0; i < size; i++)
			{
				cout << char(196) << char(196) << char(196) << char(196);
				if (i != size-1)
				{
					cout << char(197);
				}
			}
			cout << char(180) << endl;
		}
	}
	
	cout << "Nombre de mouvement : " << Nb_Move << endl << endl;
}

bool Tableau::Move_Possible()
{
	int Nb_empty = 0;

	// Compile le nombre de case vide
	for (int i = 0; i < size*size; i++)
	{
		if (tableau[(int)floor(i / size)][i % size] == 0)
		{
			Nb_empty++;
		}
	}

	// Si il n'y a pas de case vide vérifier si il est possible de joindre des case
	if (Nb_empty == 0)
	{		
		int x = 0, y = 0, z = 0;

		bool droit = false;
		for (y = 0; y < size; y++)
		{
			for (x = size - 1; x >= 0; x--)
			{
				if (tableau[y][x] != 0)
				{
					for (z = x - 1; z >= 0; z--)
					{
						if (tableau[y][z] != 0)
						{
							if (tableau[y][x] == tableau[y][z])
							{
								droit = true;
							}
							break;
						}
					}
				}
			}
		}

		bool gauche = false;
		for (y = 0; y < size; y++)
		{
			for (x = 0; x < size; x++)
			{
				if (tableau[y][x] != 0)
				{
					for (z = x + 1; z < size; z++)
					{
						if (tableau[y][z] != 0)
						{
							if (tableau[y][x] == tableau[y][z])
							{
								gauche = true;
							}
							break;
						}
					}
				}
			}
		}

		bool haut = false;
		for (x = 0; x < size; x++)
		{
			for (y = 0; y < size; y++)
			{
				if (tableau[y][x] != 0)
				{
					for (z = y + 1; z < size; z++)
					{
						if (tableau[z][x] != 0)
						{
							if (tableau[y][x] == tableau[z][x])
							{
								haut = true;
							}
							break;
						}
					}
				}
			}
		}

		bool bas = false;
		for (x = 0; x < size; x++)
		{
			for (y = size - 1; y >= 0; y--)
			{
				if (tableau[y][x] != 0)
				{
					for (z = y - 1; z >= 0; z--)
					{
						if (tableau[z][x] != 0)
						{
							if (tableau[y][x] == tableau[z][x])
							{
								bas = true;
							}
							break;
						}
					}
				}
			}
		}

		if (droit == false && gauche == false && haut == false && bas == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		return true;
	}
}

int Tableau::Get_Max()
{
	//Détermine la valeur maximal présente dans la grille
	int max = 0;
	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			if (tableau[y][x] > max)
			{
				max = tableau[y][x];
			}
		}
	}
	return max;
}

int Tableau::Get_Move()
{
	//Retourne le nombre de mouvement
	return Nb_Move;
}

int Tableau::Get_Score()
{
	// Retourne le pointage
	return score;
}

int Tableau::Get_Size()
{
	//Retourne la taille de la grille
	return size;
}

int Tableau::random(int high)
{
	//retourne une valeur random entre 0 et high
	srand((int)time(0));
	return rand() % high;
}

void Tableau::Save()
{
	//Sauvegarde les info pertinante dans le fichier .txt
	ofstream file;

	file.open("Stats.txt", ios_base::app);

	if (score > 0)
	{
		if (file.is_open())
		{
			file << "Mode(" << size << "x" << size << ") - Pointage(" << score << ") - Nombre de mouvement(" << Nb_Move << ") - Valeur de case maximal(" << Get_Max() << ")" << endl;
			file.close();
		}
	}
}