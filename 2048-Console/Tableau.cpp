#include "Tableau.h"


Tableau::Tableau()
{	
	//Détermine 2 position de case pour les valeurs de départ
	int pos_1 = rand() % 16 + 1;
	int pos_2 = rand() % 16 + 1;
	int NbCase = 1;
	Next_Move_Possible = true;
	while (pos_2 == pos_1)
	{
		pos_2 = rand() % 16 + 1;
	}


	//Remplir le tableau avec 
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (NbCase == pos_1)
			{
				int val = rand() % 2 + 1;
				if (val == 1)
				{
					tableau[y][x] = 2;
				}
				else
				{
					tableau[y][x] = 4;
				}
			}
			else if (NbCase == pos_2)
			{
				int val = rand() % 2 + 1;
				if (val == 1)
				{
					tableau[y][x] = 2;
				}
				else
				{
					tableau[y][x] = 4;
				}
			}
			else
			{
				tableau[y][x] = 0;
			}
			NbCase++;
		}
	}

	Afficher();
}

Tableau::~Tableau()
{

}

void Tableau::Bouge_Droit()
{
	for (int y = 0; y < 4; y++)
	{
		if (tableau[y][0] == 0 && tableau[y][1] == 0 && tableau[y][2] == 0 && tableau[y][3] == 0)
		{
			//0000 -> 0000
		}
		else if (tableau[y][0] == 0 && tableau[y][1] == 0 && tableau[y][2] == 0 && tableau[y][3] != 0)
		{
			//0001 -> 0001
		}
		else if (tableau[y][0] == 0 && tableau[y][1] == 0 && tableau[y][2] != 0 && tableau[y][3] == 0)
		{
			//0010 -> 0001
			tableau[y][3] = tableau[y][2];
			tableau[y][2] = 0;
		}
		else if (tableau[y][0] == 0 && tableau[y][1] == 0 && tableau[y][2] != 0 && tableau[y][3] != 0)
		{
			//0011 
			if (tableau[y][2] == tableau[y][3])
			{
				//0011 -> 0002
				tableau[y][3] += tableau[y][2];
				tableau[y][2] = 0;
				score += tableau[y][3];
			}
			else
			{
				//0011 -> 0011
			}
		}
		else if (tableau[y][0] == 0 && tableau[y][1] != 0 && tableau[y][2] == 0 && tableau[y][3] == 0)
		{
			//0100 -> 0001
			tableau[y][3] = tableau[y][1];
			tableau[y][1] = 0;
		}
		else if (tableau[y][0] == 0 && tableau[y][1] != 0 && tableau[y][2] == 0 && tableau[y][3] != 0)
		{
			//0101
			if (tableau[y][1] == tableau[y][3])
			{
				//0101 -> 0002
				tableau[y][3] += tableau[y][1];
				tableau[y][1] = 0;
				score += tableau[y][3];
			}
			else
			{
				//0101 -> 0011
				tableau[y][2] = tableau[y][1];
				tableau[y][1] = 0;
			}
		}
		else if (tableau[y][0] == 0 && tableau[y][1] != 0 && tableau[y][2] != 0 && tableau[y][3] == 0)
		{
			//0110
			if (tableau[y][1] == tableau[y][2])
			{
				//0110 -> 0002
				tableau[y][3] = tableau[y][1] + tableau[y][2];
				tableau[y][2] = 0;
				tableau[y][1] = 0;
				score += tableau[y][3];
			}
			else
			{
				//0110 -> 0011
				tableau[y][3] = tableau[y][2];
				tableau[y][2] = tableau[y][1];
				tableau[y][1] = 0;
			}
		}
		else if (tableau[y][0] == 0 && tableau[y][1] != 0 && tableau[y][2] != 0 && tableau[y][3] != 0)
		{
			//0111
			if (tableau[y][2] == tableau[y][3])
			{
				//0111 -> 0012
				tableau[y][3] += tableau[y][2];
				tableau[y][2] = tableau[y][1];
				tableau[y][1] = 0;
				score += tableau[y][3];
			}
			else if (tableau[y][1] == tableau[y][2])
			{
				//0111 -> 0021
				tableau[y][2] += tableau[y][1];
				tableau[y][1] = 0;
				score += tableau[y][2];
			}
			else
			{
				//0111 -> 0111
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] == 0 && tableau[y][2] == 0 && tableau[y][3] == 0)
		{
			//1000 -> 0001
			tableau[y][3] = tableau[y][0];
			tableau[y][0] = 0;
		}
		else if (tableau[y][0] != 0 && tableau[y][1] == 0 && tableau[y][2] == 0 && tableau[y][3] != 0)
		{
			//1001
			if (tableau[y][0] == tableau[y][3])
			{
				//1001 -> 0002
				tableau[y][3] += tableau[y][0];
				tableau[y][0] = 0;
				score += tableau[y][3];
			}
			else
			{
				//1001 -> 0011
				tableau[y][2] = tableau[y][0];
				tableau[y][0] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] == 0 && tableau[y][2] != 0 && tableau[y][3] == 0)
		{
			//1010
			if (tableau[y][0] == tableau[y][2])
			{
				//1010 -> 0002
				tableau[y][3] = tableau[y][0] + tableau[y][2];
				tableau[y][2] = 0;
				tableau[y][0] = 0;
				score += tableau[y][3];
			}
			else
			{
				//1010 -> 0011
				tableau[y][3] = tableau[y][2];
				tableau[y][2] = tableau[y][0];
				tableau[y][0] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] == 0 && tableau[y][2] != 0 && tableau[y][3] != 0)
		{
			//1011
			if (tableau[y][3] == tableau[y][2])
			{
				//1011 -> 0012
				tableau[y][3] += tableau[y][2];
				tableau[y][2] = tableau[y][0];
				tableau[y][0] = 0;
				score += tableau[y][3];
			}
			else if (tableau[y][2] == tableau[y][0])
			{
				//1011 -> 0021
				tableau[y][2] += tableau[y][0];
				tableau[y][0] = 0;
				score += tableau[y][2];
			}
			else
			{
				//1011 -> 0111
				tableau[y][1] = tableau[y][0];
				tableau[y][0] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] != 0 && tableau[y][2] == 0 && tableau[y][3] == 0)
		{
			//1100
			if (tableau[y][0] == tableau[y][1])
			{
				//1100 -> 0002
				tableau[y][3] = tableau[y][0] + tableau[y][1];
				tableau[y][1] = 0;
				tableau[y][0] = 0;
				score += tableau[y][3];
			}
			else
			{
				//1100 -> 0011
				tableau[y][3] = tableau[y][1];
				tableau[y][2] = tableau[y][0];
				tableau[y][1] = 0;
				tableau[y][0] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] != 0 && tableau[y][2] == 0 && tableau[y][3] != 0)
		{
			//1101
			if (tableau[y][3] == tableau[y][1])
			{
				//1101 -> 0012
				tableau[y][3] += tableau[y][1];
				tableau[y][2] = tableau[y][0];
				tableau[y][1] = 0;
				tableau[y][0] = 0;
				score += tableau[y][3];
			}
			else if (tableau[y][1] == tableau[y][0])
			{
				//1101 -> 0021
				tableau[y][2] = tableau[y][0] + tableau[y][1];
				tableau[y][1] = 0;
				tableau[y][0] = 0;
				score += tableau[y][2];
			}
			else
			{
				//1101 -> 0111
				tableau[y][2] = tableau[y][1];
				tableau[y][1] = tableau[y][0];
				tableau[y][0] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] != 0 && tableau[y][2] != 0 && tableau[y][3] == 0)
		{
			//1110
			if (tableau[y][1] == tableau[y][2])
			{
				//1110 -> 0012
				tableau[y][3] = tableau[y][2] + tableau[y][1];
				tableau[y][2] = tableau[y][0];
				tableau[y][1] = 0;
				tableau[y][0] = 0;
				score += tableau[y][3];
			}
			else if (tableau[y][0] == tableau[y][1])
			{
				//1110 -> 0021
				tableau[y][3] = tableau[y][2];
				tableau[y][2] = tableau[y][0] + tableau[y][1];
				tableau[y][1] = 0;
				tableau[y][0] = 0;
				score += tableau[y][2];
			}
			else
			{
				//1110 -> 0111
				tableau[y][3] = tableau[y][2];
				tableau[y][2] = tableau[y][1];
				tableau[y][1] = tableau[y][0];
				tableau[y][0] = 0;
			}
		}
		else
		{
			//1111
			if (tableau[y][3] == tableau[y][2] && tableau[y][1] == tableau[y][0])
			{
				//1111 -> 0022
				tableau[y][3] += tableau[y][2];
				tableau[y][2] = tableau[y][1] + tableau[y][0];
				tableau[y][1] = 0;
				tableau[y][0] = 0;
				score += tableau[y][3];
				score += tableau[y][2];
			}
			else if (tableau[y][3] == tableau[y][2] && tableau[y][1] != tableau[y][0])
			{
				//1111 -> 0112
				tableau[y][3] += tableau[y][2];
				tableau[y][2] = tableau[y][1];
				tableau[y][1] = tableau[y][0];
				tableau[y][0] = 0;
				score += tableau[y][3];
			}
			else if (tableau[y][2] == tableau[y][1])
			{
				//1111 -> 0121
				tableau[y][2] += tableau[y][1];
				tableau[y][1] = tableau[y][0];
				tableau[y][0] = 0;
				score += tableau[y][2];
			}
			else if (tableau[y][1] == tableau[y][0])
			{
				//1111 -> 0211
				tableau[y][1] += tableau[y][0];
				tableau[y][0] = 0;
				score += tableau[y][1];
			}
			else
			{
				//1111 -> 1111
			}
		}
	}
	Ajout_Random();
}

void Tableau::Bouge_Gauche()
{
	for (int y = 0; y < 4; y++)
	{
		if (tableau[y][0] == 0 && tableau[y][1] == 0 && tableau[y][2] == 0 && tableau[y][3] == 0)
		{
			//0000 -> 0000
		}
		else if (tableau[y][0] == 0 && tableau[y][1] == 0 && tableau[y][2] == 0 && tableau[y][3] != 0)
		{
			//0001 -> 1000
			tableau[y][0] = tableau[y][3];
			tableau[y][3] = 0;
		}
		else if (tableau[y][0] == 0 && tableau[y][1] == 0 && tableau[y][2] != 0 && tableau[y][3] == 0)
		{
			//0010 -> 1000
			tableau[y][0] = tableau[y][2];
			tableau[y][2] = 0;
		}
		else if (tableau[y][0] == 0 && tableau[y][1] == 0 && tableau[y][2] != 0 && tableau[y][3] != 0)
		{
			//0011 
			if (tableau[y][2] == tableau[y][3])
			{
				//0011 -> 2000
				tableau[y][0] = tableau[y][2] + tableau[y][3];
				tableau[y][2] = 0;
				tableau[y][3] = 0;
				score += tableau[y][0];
			}
			else
			{
				//0011 -> 1100
				tableau[y][0] = tableau[y][2];
				tableau[y][1] = tableau[y][3];
				tableau[y][2] = 0;
				tableau[y][3] = 0;
			}
		}
		else if (tableau[y][0] == 0 && tableau[y][1] != 0 && tableau[y][2] == 0 && tableau[y][3] == 0)
		{
			//0100 -> 1000
			tableau[y][0] = tableau[y][1];
			tableau[y][1] = 0;
		}
		else if (tableau[y][0] == 0 && tableau[y][1] != 0 && tableau[y][2] == 0 && tableau[y][3] != 0)
		{
			//0101
			if (tableau[y][1] == tableau[y][3])
			{
				//0101 -> 2000
				tableau[y][0] = tableau[y][1] + tableau[y][3];
				tableau[y][1] = 0;
				tableau[y][3] = 0;
				score += tableau[y][0];
			}
			else
			{
				//0101 -> 1100
				tableau[y][0] = tableau[y][1];
				tableau[y][1] = tableau[y][3];
				tableau[y][3] = 0;
			}
		}
		else if (tableau[y][0] == 0 && tableau[y][1] != 0 && tableau[y][2] != 0 && tableau[y][3] == 0)
		{
			//0110
			if (tableau[y][1] == tableau[y][2])
			{
				//0110 -> 2000
				tableau[y][0] = tableau[y][1] + tableau[y][2];
				tableau[y][1] = 0;
				tableau[y][2] = 0;
				score += tableau[y][0];
			}
			else
			{
				//0110 -> 1100
				tableau[y][0] = tableau[y][1];
				tableau[y][1] = tableau[y][2];
				tableau[y][2] = 0;
			}
		}
		else if (tableau[y][0] == 0 && tableau[y][1] != 0 && tableau[y][2] != 0 && tableau[y][3] != 0)
		{
			//0111
			if (tableau[y][1] == tableau[y][2])
			{
				//0111 -> 2100
				tableau[y][0] = tableau[y][1] + tableau[y][2];
				tableau[y][1] = tableau[y][3];
				tableau[y][2] = 0;
				tableau[y][3] = 0;
				score += tableau[y][0];
			}
			else if (tableau[y][2] == tableau[y][3])
			{
				//0111 -> 1200
				tableau[y][0] = tableau[y][1];
				tableau[y][1] = tableau[y][2] + tableau[y][3];
				tableau[y][2] = 0;
				tableau[y][3] = 0;
				score += tableau[y][1];
			}
			else
			{
				//0111 -> 1110
				tableau[y][0] = tableau[y][1];
				tableau[y][1] = tableau[y][2];
				tableau[y][2] = tableau[y][3];
				tableau[y][3] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] == 0 && tableau[y][2] == 0 && tableau[y][3] == 0)
		{
			//1000 -> 1000
		}
		else if (tableau[y][0] != 0 && tableau[y][1] == 0 && tableau[y][2] == 0 && tableau[y][3] != 0)
		{
			//1001
			if (tableau[y][0] == tableau[y][3])
			{
				//1001 -> 2000
				tableau[y][0] += tableau[y][3];
				tableau[y][3] = 0;
				score += tableau[y][0];
			}
			else
			{
				//1001 -> 1100
				tableau[y][1] = tableau[y][3];
				tableau[y][3] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] == 0 && tableau[y][2] != 0 && tableau[y][3] == 0)
		{
			//1010
			if (tableau[y][0] == tableau[y][2])
			{
				//1010 -> 2000
				tableau[y][0] += tableau[y][2];
				tableau[y][2] = 0;
				score += tableau[y][0];
			}
			else
			{
				//1010 -> 1100
				tableau[y][1] = tableau[y][2];
				tableau[y][2] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] == 0 && tableau[y][2] != 0 && tableau[y][3] != 0)
		{
			//1011
			if (tableau[y][0] == tableau[y][2])
			{
				//1011 -> 2100
				tableau[y][0] += tableau[y][2];
				tableau[y][1] = tableau[y][3];
				tableau[y][2] = 0;
				tableau[y][3] = 0;
				score += tableau[y][0];
			}
			else if (tableau[y][2] == tableau[y][3])
			{
				//1011 -> 1200
				tableau[y][1] = tableau[y][2] + tableau[y][3];
				tableau[y][2] = 0;
				tableau[y][3] = 0;
				score += tableau[y][1];
			}
			else
			{
				//1011 -> 1110
				tableau[y][1] = tableau[y][2];
				tableau[y][2] = tableau[y][3];
				tableau[y][3] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] != 0 && tableau[y][2] == 0 && tableau[y][3] == 0)
		{
			//1100
			if (tableau[y][0] == tableau[y][1])
			{
				//1100 -> 2000
				tableau[y][0] += tableau[y][1];
				tableau[y][1] = 0;
				score += tableau[y][0];
			}
			else
			{
				//1100 -> 1100
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] != 0 && tableau[y][2] == 0 && tableau[y][3] != 0)
		{
			//1101
			if (tableau[y][0] == tableau[y][1])
			{
				//1101 -> 2100
				tableau[y][0] += tableau[y][1];
				tableau[y][1] = tableau[y][3];
				tableau[y][3] = 0;
				score += tableau[y][0];
			}
			else if (tableau[y][1] == tableau[y][3])
			{
				//1101 -> 1200
				tableau[y][1] += tableau[y][3];
				tableau[y][3] = 0;
				score += tableau[y][1];
			}
			else
			{
				//1101 -> 1110
				tableau[y][2] = tableau[y][3];
				tableau[y][3] = 0;
			}
		}
		else if (tableau[y][0] != 0 && tableau[y][1] != 0 && tableau[y][2] != 0 && tableau[y][3] == 0)
		{
			//1110
			if (tableau[y][0] == tableau[y][1])
			{
				//1110 -> 2100
				tableau[y][0] += tableau[y][1];
				tableau[y][1] = tableau[y][2];
				tableau[y][2] = 0;
				score += tableau[y][0];
			}
			else if (tableau[y][1] == tableau[y][2])
			{
				//1110 -> 1200
				tableau[y][1] += tableau[y][2];
				tableau[y][2] = 0;
				score += tableau[y][1];
			}
			else
			{
				//1110 -> 1110
			}
		}
		else
		{
			//1111
			if (tableau[y][0] == tableau[y][1] && tableau[y][2] == tableau[y][3])
			{
				//1111 -> 2200
				tableau[y][0] += tableau[y][1];
				tableau[y][1] = tableau[y][2] + tableau[y][3];
				tableau[y][2] = 0;
				tableau[y][3] = 0;
				score += tableau[y][0];
				score += tableau[y][1];
			}
			else if (tableau[y][0] == tableau[y][1] && tableau[y][2] != tableau[y][3])
			{
				//1111 -> 2110
				tableau[y][0] += tableau[y][1];
				tableau[y][1] = tableau[y][2];
				tableau[y][2] = tableau[y][3];
				tableau[y][3] = 0;
				score += tableau[y][0];
			}
			else if (tableau[y][1] == tableau[y][2])
			{
				//1111 -> 1210
				tableau[y][1] += tableau[y][2];
				tableau[y][2] = tableau[y][3];
				tableau[y][3] = 0;
				score += tableau[y][1];
			}
			else if (tableau[y][2] == tableau[y][3])
			{
				//1111 -> 1120
				tableau[y][2] += tableau[y][3];
				tableau[y][3] = 0;
				score += tableau[y][2];
			}
			else
			{
				//1111 -> 1111
			}
		}
	}
	Ajout_Random();
}

void Tableau::Bouge_Haut()
{
	for (int x = 0; x < 4; x++)
	{
		if (tableau[0][x] == 0 && tableau[1][x] == 0 && tableau[2][x] == 0 && tableau[3][x] == 0)
		{
		  /*0 -> 0
			0 -> 0
			0 -> 0
			0 -> 0*/
		}
		else if (tableau[0][x] == 0 && tableau[1][x] == 0 && tableau[2][x] == 0 && tableau[3][x] != 0)
		{
		  /*0 -> 1
			0 -> 0
			0 -> 0
			1 -> 0*/
			tableau[0][x] = tableau[3][x];
			tableau[3][x] = 0;
		}
		else if (tableau[0][x] == 0 && tableau[1][x] == 0 && tableau[2][x] != 0 && tableau[3][x] == 0)
		{
		  /*0 -> 1
			0 -> 0
			1 -> 0
			0 -> 0*/
			tableau[0][x] = tableau[2][x];
			tableau[2][x] = 0;
		}
		else if (tableau[0][x] == 0 && tableau[1][x] == 0 && tableau[2][x] != 0 && tableau[3][x] != 0)
		{
		  /*0 
			0
			1
			1*/
			if (tableau[2][x] == tableau[3][x])
			{
			  /*0 -> 2
			    0 -> 0
			    1 -> 0
			    1 -> 0*/
				tableau[0][x] = tableau[2][x] + tableau[3][x];
				tableau[2][x] = 0;
				tableau[3][x] = 0;
				score += tableau[0][x];
			}
			else
			{
			  /*0 -> 1
				0 -> 1
				1 -> 0
				1 -> 0*/
				tableau[0][x] = tableau[2][x];
				tableau[1][x] = tableau[3][x];
				tableau[2][x] = 0;
				tableau[3][x] = 0;
			}
		}
		else if (tableau[0][x] == 0 && tableau[1][x] != 0 && tableau[2][x] == 0 && tableau[3][x] == 0)
		{
		  /*0 -> 1
			1 -> 0
			0 -> 0
			0 -> 0*/
			tableau[0][x] = tableau[1][x];
			tableau[1][x] = 0;
		}
		else if (tableau[0][x] == 0 && tableau[1][x] != 0 && tableau[2][x] == 0 && tableau[3][x] != 0)
		{
		  /*0
			1
			0
			1*/

			if (tableau[1][x] == tableau[3][x])
			{
			  /*0 -> 2
				1 -> 0
				0 -> 0
				1 -> 0*/
				tableau[0][x] = tableau[1][x] + tableau[3][x];
				tableau[1][x] = 0;
				tableau[3][x] = 0;
				score += tableau[0][x];
			}
			else
			{
			  /*0 -> 1
				1 -> 1
				0 -> 0
				1 -> 0*/
				tableau[0][x] = tableau[1][x];
				tableau[1][x] = tableau[3][x];
				tableau[3][x] = 0;
			}
		}
		else if (tableau[0][x] == 0 && tableau[1][x] != 0 && tableau[2][x] != 0 && tableau[3][x] == 0)
		{
		  /*0
			1
			1
			0*/
			if (tableau[1][x] == tableau[2][x])
			{
			  /*0 -> 2
				1 -> 0
				1 -> 0
				0 -> 0*/
				tableau[0][x] = tableau[1][x] + tableau[2][x];
				tableau[1][x] = 0;
				tableau[2][x] = 0;
				score += tableau[0][x];
			}
			else
			{
			  /*0 -> 1
				1 -> 1
				1 -> 0
				0 -> 0*/
				tableau[0][x] = tableau[1][x];
				tableau[1][x] = tableau[2][x];
				tableau[2][x] = 0;
			}
		}
		else if (tableau[0][x] == 0 && tableau[1][x] != 0 && tableau[2][x] != 0 && tableau[3][x] != 0)
		{
		  /*0
			1
			1
			1*/
			if (tableau[1][x] == tableau[2][x])
			{
				/*0 -> 2
				  1 -> 1
				  1 -> 0
				  1 -> 0*/
				tableau[0][x] = tableau[1][x] + tableau[2][x];
				tableau[1][x] = tableau[3][x];
				tableau[2][x] = 0;
				tableau[3][x] = 0;
			}
			else if(tableau[2][x] == tableau[3][x])
			{
				/*0 -> 1
				  1 -> 2
				  1 -> 0
				  1 -> 0*/
				tableau[0][x] = tableau[1][x];
				tableau[1][x] = tableau[2][x] + tableau[3][x];
				tableau[2][x] = 0;
				tableau[3][x] = 0;
				score += tableau[1][x];
			}
			else
			{
				/*0 -> 1
				  1 -> 1
				  1 -> 1
				  1 -> 0*/
				tableau[0][x] = tableau[1][x];
				tableau[1][x] = tableau[2][x];
				tableau[2][x] = tableau[3][x];
				tableau[3][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] == 0 && tableau[2][x] == 0 && tableau[3][x] == 0)
		{
		    /*1 -> 1
			  0 -> 0
			  0 -> 0
			  0 -> 0*/
		}
		else if (tableau[0][x] != 0 && tableau[1][x] == 0 && tableau[2][x] == 0 && tableau[3][x] != 0)
		{
		  /*1
			0
			0
			1*/
			if (tableau[0][x] == tableau[3][x])
			{
				/*1 -> 2
				  0 -> 0
				  0 -> 0
				  1 -> 0*/
				tableau[0][x] += tableau[3][x];
				tableau[3][x] = 0;
				score += tableau[0][x];
			}
			else
			{
				/*1 -> 1
				  0 -> 1
				  0 -> 0
				  1 -> 0*/
				tableau[1][x] = tableau[3][x];
				tableau[3][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] == 0 && tableau[2][x] != 0 && tableau[3][x] == 0)
		{
			/*1
			  0
			  1
			  0*/
			if (tableau[0][x] == tableau[2][x])
			{
				/*1 -> 2
				  0 -> 0
				  1 -> 0
				  0 -> 0*/
				tableau[0][x] += tableau[2][x];
				tableau[2][x] = 0;
				score += tableau[0][x];
			}
			else
			{
				/*1 -> 1
				  0 -> 1
				  1 -> 0
				  0 -> 0*/
				tableau[1][x] = tableau[2][x];
				tableau[2][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] == 0 && tableau[2][x] != 0 && tableau[3][x] != 0)
		{
			/*1
			  0
			  1
			  1*/
			if (tableau[0][x] == tableau[2][x])
			{
				/*1 -> 2
				  0 -> 1
				  1 -> 0
				  1 -> 0*/
				tableau[0][x] += tableau[2][x];
				tableau[1][x] = tableau[3][x];
				tableau[2][x] = 0;
				tableau[3][x] = 0;
				score += tableau[0][x];
			}
			else if(tableau[2][x] == tableau[3][x])
			{
				/*1 -> 1
				  0 -> 2
				  1 -> 0
				  1 -> 0*/
				tableau[1][x] = tableau[2][x] + tableau[3][x];
				tableau[2][x] = 0;
				tableau[3][x] = 0;
				score += tableau[1][x];
			}
			else
			{
				/*1 -> 1
				  0 -> 1
				  1 -> 1
				  1 -> 0*/
				tableau[1][x] = tableau[2][x];
				tableau[2][x] = tableau[3][x];
				tableau[3][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] != 0 && tableau[2][x] == 0 && tableau[3][x] == 0)
		{
			/*1
			  1
			  0
			  0*/
			if (tableau[0][x] == tableau[1][x])
			{
				/*1 -> 2
				  1 -> 0
				  0 -> 0
				  0 -> 0*/
				tableau[0][x] += tableau[1][x];
				tableau[1][x] = 0;
				score += tableau[0][x];
			}
			else
			{
				/*1 -> 1
				  1 -> 1
				  0 -> 0
				  0 -> 0*/
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] != 0 && tableau[2][x] == 0 && tableau[3][x] != 0)
		{
			/*1
		      1
		      0
		      1*/
			if (tableau[0][x] == tableau[1][x])
			{
				/*1 -> 2
				  1 -> 1
				  0 -> 0
				  1 -> 0*/
				tableau[0][x] += tableau[1][x];
				tableau[1][x] = tableau[3][x];
				tableau[3][x] = 0;
				score += tableau[0][x];
			}
			else if(tableau[1][x] == tableau[3][x])
			{
				/*1 -> 1
				  1 -> 2
				  0 -> 0
				  1 -> 0*/
				tableau[1][x] += tableau[3][x];
				tableau[3][x] = 0;
				score += tableau[1][x];
			}
			else
			{
				/*1 -> 1
				  1 -> 1
				  0 -> 1
				  1 -> 0*/
				tableau[2][x] = tableau[3][x];
				tableau[3][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] != 0 && tableau[2][x] != 0 && tableau[3][x] == 0)
		{
			/*1
			  1
			  1
			  0*/
			if (tableau[0][x] == tableau[1][x])
			{
				/*1 -> 2
				  1 -> 1
				  1 -> 0
				  0 -> 0*/
				tableau[0][x] += tableau[1][x];
				tableau[1][x] = tableau[3][x];
				tableau[2][x] = 0;
				score += tableau[0][x];
			}
			else if (tableau[1][x] == tableau[2][x])
			{
				/*1 -> 1
				  1 -> 2
				  1 -> 0
				  0 -> 0*/
				tableau[1][x] += tableau[2][x];
				tableau[2][x] = 0;
				score += tableau[1][x];
			}
			else
			{
				/*1 -> 1
				  1 -> 1
				  1 -> 1
				  0 -> 0*/
			}
		}
		else
		{
			/*1
		      1
		      1
		      1*/
			if (tableau[0][x] == tableau[1][x] && tableau[2][x] == tableau[3][x])
			{
				/*1 -> 2
				  1 -> 2
				  1 -> 0
				  1 -> 0*/
				tableau[0][x] += tableau[1][x];
				tableau[1][x] = tableau[2][x] + tableau[3][x];
				tableau[2][x] = 0;
				tableau[3][x] = 0;
				score += tableau[0][x];
				score += tableau[1][x];
			}
			else if (tableau[0][x] == tableau[1][x] && tableau[2][x] != tableau[3][x])
			{
				/*1 -> 2
				  1 -> 1
				  1 -> 1
				  1 -> 0*/
				tableau[0][x] += tableau[1][x];
				tableau[1][x] = tableau[2][x];
				tableau[2][x] = tableau[3][x];
				tableau[3][x] = 0;
				score += tableau[0][x];
			}
			else if (tableau[1][x] == tableau[2][x])
			{
				/*1 -> 1
				  1 -> 2
				  1 -> 1
				  1 -> 0*/
				tableau[1][x] += tableau[2][x];
				tableau[2][x] = tableau[3][x];
				tableau[3][x] = 0;
				score += tableau[1][x];
			}
			else if (tableau[2][x] == tableau[3][x])
			{
				/*1 -> 1
				  1 -> 1
				  1 -> 2
				  1 -> 0*/
				tableau[2][x] += tableau[3][x];
				tableau[3][x] = 0;
				score += tableau[2][x];
			}
			else
			{
				/*1 -> 1
				  1 -> 1
				  1 -> 1
				  1 -> 1*/
			}
		}
	}

	Ajout_Random();
}

void Tableau::Bouge_Bas()
{
	for (int x = 0; x < 4; x++)
	{
		if (tableau[0][x] == 0 && tableau[1][x] == 0 && tableau[2][x] == 0 && tableau[3][x] == 0)
		{
			/*0 -> 0
			  0 -> 0
			  0 -> 0
			  0 -> 0*/
		}
		else if (tableau[0][x] == 0 && tableau[1][x] == 0 && tableau[2][x] == 0 && tableau[3][x] != 0)
		{
			/*0 -> 0
			  0 -> 0
			  0 -> 0
			  1 -> 1*/
		}
		else if (tableau[0][x] == 0 && tableau[1][x] == 0 && tableau[2][x] != 0 && tableau[3][x] == 0)
		{
			/*0 -> 0
			  0 -> 0
			  1 -> 0
			  0 -> 1*/
			tableau[3][x] = tableau[2][x];
			tableau[2][x] = 0;
		}
		else if (tableau[0][x] == 0 && tableau[1][x] == 0 && tableau[2][x] != 0 && tableau[3][x] != 0)
		{
			/*0
			  0
			  1
			  1*/
			if (tableau[2][x] == tableau[3][x])
			{
				/*0 -> 0
				  0 -> 0
				  1 -> 0
				  1 -> 2*/
				tableau[3][x] += tableau[2][x];
				tableau[2][x] = 0;
				score += tableau[3][x];
			}
			else
			{
				/*0 -> 0
				  0 -> 0
				  1 -> 1
				  1 -> 1*/
			}
		}
		else if (tableau[0][x] == 0 && tableau[1][x] != 0 && tableau[2][x] == 0 && tableau[3][x] == 0)
		{
			/*0 -> 0
			  1 -> 0
			  0 -> 0
			  0 -> 1*/
			tableau[3][x] = tableau[1][x];
			tableau[1][x] = 0;
		}
		else if (tableau[0][x] == 0 && tableau[1][x] != 0 && tableau[2][x] == 0 && tableau[3][x] != 0)
		{
			/*0
			  1
			  0
			  1*/

			if (tableau[1][x] == tableau[3][x])
			{
				/*0 -> 0
				  1 -> 0
				  0 -> 0
				  1 -> 2*/
				tableau[3][x] += tableau[1][x];
				tableau[1][x] = 0;
				score += tableau[3][x];
			}
			else
			{
				/*0 -> 0
				  1 -> 0
				  0 -> 1
				  1 -> 1*/
				tableau[2][x] = tableau[1][x];
				tableau[1][x] = 0;
			}
		}
		else if (tableau[0][x] == 0 && tableau[1][x] != 0 && tableau[2][x] != 0 && tableau[3][x] == 0)
		{
			/*0
			  1
			  1
			  0*/
			if (tableau[1][x] == tableau[2][x])
			{
				/*0 -> 0
				  1 -> 0
				  1 -> 0
				  0 -> 2*/
				tableau[3][x] = tableau[1][x] + tableau[2][x];
				tableau[2][x] = 0;
				tableau[1][x] = 0;
				score += tableau[3][x];
			}
			else
			{
				/*0 -> 0
				  1 -> 0
				  1 -> 1
				  0 -> 1*/
				tableau[3][x] = tableau[2][x];
				tableau[2][x] = tableau[1][x];
				tableau[1][x] = 0;
			}
		}
		else if (tableau[0][x] == 0 && tableau[1][x] != 0 && tableau[2][x] != 0 && tableau[3][x] != 0)
		{
			/*0
			  1
			  1
			  1*/
			if (tableau[2][x] == tableau[3][x])
			{
				/*0 -> 0
				  1 -> 0
				  1 -> 1
				  1 -> 2*/
				tableau[3][x] += tableau[2][x];
				tableau[2][x] = tableau[1][x];
				tableau[1][x] = 0;
				score += tableau[3][x];
			}
			else if (tableau[1][x] == tableau[2][x])
			{
				/*0 -> 0
				  1 -> 0
				  1 -> 2
				  1 -> 1*/
				tableau[2][x] += tableau[1][x];
				tableau[1][x] = 0;
				score += tableau[2][x];
			}
			else
			{
				/*0 -> 0
				  1 -> 1
				  1 -> 1
				  1 -> 1*/
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] == 0 && tableau[2][x] == 0 && tableau[3][x] == 0)
		{
			/*1 -> 0
			  0 -> 0
			  0 -> 0
			  0 -> 1*/
			  tableau[3][x] = tableau[0][x];
			  tableau[0][x] = 0;
		}
		else if (tableau[0][x] != 0 && tableau[1][x] == 0 && tableau[2][x] == 0 && tableau[3][x] != 0)
		{
			/*1
			  0
			  0
			  1*/
			if (tableau[0][x] == tableau[3][x])
			{
				/*1 -> 0
				  0 -> 0
				  0 -> 0
				  1 -> 2*/
				tableau[3][x] += tableau[0][x];
				tableau[0][x] = 0;
				score += tableau[3][x];
			}
			else
			{
				/*1 -> 0
				  0 -> 0
				  0 -> 1
				  1 -> 1*/
				tableau[2][x] = tableau[0][x];
				tableau[0][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] == 0 && tableau[2][x] != 0 && tableau[3][x] == 0)
		{
			/*1
			  0
			  1
			  0*/
			if (tableau[0][x] == tableau[2][x])
			{
				/*1 -> 0
				  0 -> 0
				  1 -> 0
				  0 -> 2*/
				tableau[3][x] = tableau[0][x] + tableau[2][x];
				tableau[2][x] = 0;
				tableau[0][x] = 0;
				score += tableau[3][x];
			}
			else
			{
				/*1 -> 0
				  0 -> 0
				  1 -> 1
				  0 -> 1*/
				tableau[3][x] = tableau[2][x];
				tableau[2][x] = tableau[0][x];
				tableau[0][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] == 0 && tableau[2][x] != 0 && tableau[3][x] != 0)
		{
			/*1
			  0
			  1
			  1*/
			if (tableau[2][x] == tableau[3][x])
			{
				/*1 -> 0
				  0 -> 0
				  1 -> 1
				  1 -> 2*/
				tableau[3][x] += tableau[2][x];
				tableau[2][x] = tableau[0][x];
				tableau[0][x] = 0;
				score += tableau[3][x];
			}
			else if (tableau[0][x] == tableau[2][x])
			{
				/*1 -> 0
				  0 -> 0
				  1 -> 2
				  1 -> 1*/
				tableau[2][x] += tableau[0][x];
				tableau[0][x] = 0;
				score += tableau[2][x];
			}
			else
			{
				/*1 -> 0
				  0 -> 1
				  1 -> 1
				  1 -> 1*/
				tableau[1][x] = tableau[0][x];
				tableau[0][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] != 0 && tableau[2][x] == 0 && tableau[3][x] == 0)
		{
			/*1
			  1
			  0
			  0*/
			if (tableau[0][x] == tableau[1][x])
			{
				/*1 -> 0
				  1 -> 0
				  0 -> 0
				  0 -> 2*/
				tableau[3][x] = tableau[0][x] + tableau[1][x];
				tableau[1][x] = 0;
				tableau[0][x] = 0;
				score += tableau[3][x];
			}
			else
			{
				/*1 -> 0
				  1 -> 0
				  0 -> 1
				  0 -> 1*/
				tableau[3][x] = tableau[1][x];
				tableau[2][x] = tableau[0][x];
				tableau[1][x] = 0;
				tableau[0][x] = 0;

			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] != 0 && tableau[2][x] == 0 && tableau[3][x] != 0)
		{
			/*1
			  1
			  0
			  1*/
			if (tableau[1][x] == tableau[3][x])
			{
				/*1 -> 0
				  1 -> 0
				  0 -> 1
				  1 -> 2*/
				tableau[3][x] += tableau[1][x];
				tableau[2][x] = tableau[0][x];
				tableau[1][x] = 0;
				tableau[0][x] = 0;
				score += tableau[3][x];
			}
			else if (tableau[1][x] == tableau[3][x])
			{
				/*1 -> 0
				  1 -> 0
				  0 -> 2
				  1 -> 1*/
				tableau[2][x] = tableau[0][x] + tableau[1][x];
				tableau[1][x] = 0;
				tableau[0][x] = 0;
				score += tableau[2][x];
			}
			else
			{
				/*1 -> 0
				  1 -> 1
				  0 -> 1
				  1 -> 1*/
				tableau[2][x] = tableau[1][x];
				tableau[1][x] = tableau[0][x];
				tableau[0][x] = 0;
			}
		}
		else if (tableau[0][x] != 0 && tableau[1][x] != 0 && tableau[2][x] != 0 && tableau[3][x] == 0)
		{
			/*1
			  1
			  1
			  0*/
			if (tableau[1][x] == tableau[2][x])
			{
				/*1 -> 0
				  1 -> 0
				  1 -> 1
				  0 -> 2*/
				tableau[3][x] = tableau[1][x] + tableau[2][x];
				tableau[2][x] = tableau[0][x];
				tableau[1][x] = 0;
				tableau[0][x] = 0;
				score += tableau[3][x];
			}
			else if (tableau[0][x] == tableau[1][x])
			{
				/*1 -> 0
				  1 -> 0
				  1 -> 2
				  0 -> 1*/
				tableau[3][x] = tableau[2][x];
				tableau[2][x] = tableau[1][x] + tableau[0][x];
				tableau[1][x] = 0;
				tableau[0][x] = 0;
				score += tableau[2][x];
			}
			else
			{
				/*1 -> 0
				  1 -> 1
				  1 -> 1
				  0 -> 1*/
				tableau[3][x] = tableau[2][x];
				tableau[2][x] = tableau[1][x];
				tableau[1][x] = tableau[0][x];
				tableau[0][x] = 0;
			}
		}
		else
		{
			/*1
			  1
			  1
			  1*/
			if (tableau[2][x] == tableau[3][x] && tableau[0][x] == tableau[1][x])
			{
				/*1 -> 0
				  1 -> 0
				  1 -> 2
				  1 -> 2*/
				tableau[3][x] += tableau[2][x];
				tableau[2][x] = tableau[0][x] + tableau[1][x];
				tableau[1][x] = 0;
				tableau[0][x] = 0;
				score += tableau[3][x];
				score += tableau[2][x];
			}
			else if (tableau[2][x] == tableau[3][x] && tableau[0][x] != tableau[1][x])
			{
				/*1 -> 0
				  1 -> 1
				  1 -> 1
				  1 -> 2*/
				tableau[3][x] += tableau[2][x];
				tableau[2][x] = tableau[1][x];
				tableau[1][x] = tableau[0][x];
				tableau[0][x] = 0;
				score += tableau[3][x];
			}
			else if (tableau[1][x] == tableau[2][x])
			{
				/*1 -> 0
				  1 -> 1
				  1 -> 2
				  1 -> 1*/
				tableau[2][x] += tableau[1][x];
				tableau[1][x] = tableau[0][x];
				tableau[0][x] = 0;
				score += tableau[2][x];
			}
			else if (tableau[0][x] == tableau[1][x])
			{
				/*1 -> 0
				  1 -> 2
				  1 -> 1
				  1 -> 1*/
				tableau[1][x] += tableau[0][x];
				tableau[0][x] = 0;
				score += tableau[1][x];
			}
			else
			{
				/*1 -> 1
				  1 -> 1
				  1 -> 1
				  1 -> 1*/
			}
		}
	}
	Ajout_Random();
}

void Tableau::Ajout_Random()
{
	//Faire l'ajout
	bool place = false;

	do
	{
		int pos = rand() % 16 + 1;
		int NbCase = 1;

		for (int y = 0; y < 4; y++)
		{
			for (int x = 0; x < 4; x++)
			{
				if (NbCase == pos)
				{
					if (tableau[y][x] == 0)
					{
						int val = rand() % 2 + 1;
						if (val == 1)
						{
							tableau[y][x] = 2;
						}
						else
						{
							tableau[y][x] = 4;
						}
						place = true;
					}					
				}
				NbCase++;
			}
		}

	} while (place != true);

	Est_Plein();
}

void Tableau::Est_Plein()
{
	int Nb_Range_plein = 0;
	for (int y = 0; y < 4; y++)
	{
		if (tableau[y][0] != 0 && tableau[y][1] != 0 && tableau[y][2] != 0 && tableau[y][3] != 0)
		{
			Nb_Range_plein++;
		}
	}

	if (Nb_Range_plein == 4)
	{
		Move_Possible();
	}
	Afficher();
}

void Tableau::Move_Possible()
{
	for (int y = 0; y < 4; y++)
	{
		if (tableau[y][3] == tableau[y][2] && tableau[y][1] == tableau[y][0])
		{
			//1111 -> 0022
			Next_Move_Possible = true;
			break;
		}
		else if (tableau[y][3] == tableau[y][2] && tableau[y][1] != tableau[y][0])
		{
			//1111 -> 0112
			Next_Move_Possible = true;
			break;
		}
		else if (tableau[y][2] == tableau[y][1])
		{
			//1111 -> 0121
			Next_Move_Possible = true;
			break;
		}
		else if (tableau[y][1] == tableau[y][0])
		{
			//1111 -> 0211
			Next_Move_Possible = true;
			break;
		}
		else
		{
			//1111 -> 1111
			Next_Move_Possible = false;
		}
	}
}

void Tableau::Afficher()
{
	cout << "Score : " << score << endl;
	cout << "Max : " << Get_Highest() << endl;

	for (int y = 0; y < 4; y++)
	{
		cout << "|";

		for (int x = 0; x < 4; x++)
		{
			if (tableau[y][x] < 10)
			{
				cout << "  " << tableau[y][x] << " |";
			}
			else if (tableau[y][x] < 100)
			{
				cout << " " << tableau[y][x] << " |";
			}
			else if (tableau[y][x] < 1000)
			{
				cout << " " << tableau[y][x] << "|";
			}
			else
			{
				cout << tableau[y][x] << "|";
			}
		}
		cout << endl;
	}
	cout << endl;
}

int Tableau::Get_Highest()
{
	int max = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (tableau[y][x] > max)
			{
				max = tableau[y][x];
			}
		}
	}
	return max;
}