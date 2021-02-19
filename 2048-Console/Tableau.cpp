﻿#include "Tableau.h"

using namespace std;

Tableau::Tableau(int z)
{	
	size = z;
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

	//Détermine 2 position de case pour les valeurs de départ
	vector<int> vec;

	tableau = new int* [z];

	for (int i = 0; i < z; i++)
	{
		tableau[i] = new int[z];
	}

	for (int i = 0; i < z * z; i++)
	{
		tableau[(int)floor(i / z)][i % z] = 0;
		vec.push_back(i);
	}

	for (int i = 0; i < 2; i++)
	{
		int pos = vec[random(vec.size())];
		tableau[(int)floor(pos / z)][pos % z] = two_four[random(ratio*10)];
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
	int y;
	int x;
	int z;

	for (y = 0; y < size; y++)
	{
		//Joindre
		for (x = size-1; x >= 0; x--)
		{
			if (tableau[y][x] != 0)
			{
				for (z = x - 1; z >= 0; z--)
				{
					if (tableau[y][z] != 0)
					{
						if (tableau[y][x] == tableau[y][z])
						{
							score += tableau[y][x] + tableau[y][z];
							tableau[y][x--] *= 2;
							tableau[y][z] = 0;
						}
						break;
					}
				}
			}
		}
		
		//Bouger vers la droite
		for (x = size-1; x >= 0; x--)
		{
			if (tableau[y][x] == 0)
			{
				for (z = x - 1; z >= 0; z--)
				{
					if (tableau[y][z] != 0)
					{
						tableau[y][x] = tableau[y][z];
						tableau[y][z] = 0;

						break;
					}
				}
			}
		}
	}

	Ajout_Random();
}

void Tableau::Bouge_Gauche()
{
	int y;
	int x;
	int z;

	for (y = 0; y < size; y++)
	{
		//Joindre
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
							score += tableau[y][x] + tableau[y][z];
							tableau[y][x++] *= 2;
							tableau[y][z] = 0;
						}
						break;
					}
				}
			}
		}

		//Bouger vers la gauche
		for (x = 0; x < size; x++)
		{
			if (tableau[y][x] == 0)
			{
				for (z = x + 1; z < size; z++)
				{
					if (tableau[y][z] != 0)
					{
						tableau[y][x] = tableau[y][z];
						tableau[y][z] = 0;

						break;
					}
				}
			}
		}
	}

	Ajout_Random();
}

void Tableau::Bouge_Haut()
{
	int y;
	int x;
	int z;

	for (x = 0; x < size; x++)
	{
		//Joindre
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
							score += tableau[y][x] + tableau[z][x];
							tableau[y++][x] *= 2;
							tableau[z][x] = 0;
						}
						break;
					}
				}
			}
		}

		//Bouger vers le haut
		for (y = 0; y < size; y++)
		{
			if (tableau[y][x] == 0)
			{
				for (z = y + 1; z < size; z++)
				{
					if (tableau[z][x] != 0)
					{
						tableau[y][x] = tableau[z][x];
						tableau[z][x] = 0;

						break;
					}
				}
			}
		}
	}

	Ajout_Random();
}

void Tableau::Bouge_Bas()
{
	int y;
	int x;
	int z;

	for (x = 0; x < size; x++)
	{
		//Joindre
		for (y = size-1; y >=0 ; y--)
		{
			if (tableau[y][x] != 0)
			{
				for (z = y - 1; z >= 0; z--)
				{
					if (tableau[z][x] != 0)
					{
						if (tableau[y][x] == tableau[z][x])
						{
							score += tableau[y][x] + tableau[z][x];
							tableau[y--][x] *= 2;
							tableau[z][x] = 0;
						}
						break;
					}
				}
			}
		}

		//Bouger vers le bas
		for (y = size-1; y >= 0; y--)
		{
			if (tableau[y][x] == 0)
			{
				for (z = y - 1; z >= 0; z--)
				{
					if (tableau[z][x] != 0)
					{
						tableau[y][x] = tableau[z][x];
						tableau[z][x] = 0;
						break;
					}
				}
			}
		}
	}

	Ajout_Random();
}

void Tableau::Ajout_Random()
{
	//Faire l'ajout
	vector<int> vec;
	for (int i = 0; i < size*size; i++)
	{
		if (tableau[(int)floor(i / size)][i % size] == 0)
		{
			vec.push_back(i);
		}
	}

	int pos = vec[random(vec.size())];
	tableau[(int)floor(pos / size)][pos % size] = two_four[random(ratio*10)];
}

void Tableau::Afficher()
{
	system("cls");
	cout << "Mode " << size << "x" << size << endl << endl;
	cout << "Score : " << score << endl;
	cout << "Max : " << Get_Highest() << endl;

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
	cout << endl;
}

bool Tableau::Move_Possible()
{
	int Nb_full = 0;
	for (int i = 0; i < size*size; i++)
	{
		if (tableau[(int)floor(i / size)][i % size] != 0)
		{
			Nb_full++;
		}
	}

	if (Nb_full == size*size)
	{		
		int y,x,z;

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

		if (droit == false && gauche == false && haut == false && bas == true)
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

int Tableau::Get_Highest()
{
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

int Tableau::random(int high)
{
	srand((int)time(0));
	return rand() % high;
}