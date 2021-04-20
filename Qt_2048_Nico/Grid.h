/*
* Nom des cr�ateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de cr�ation : 05/04/2021 � 19/04/2021
* Nom de fichier : Grid.h
* Description : Permet de g�rer le back end de la grille de jeu
*/
#ifndef GRID_H
#define GRID_H

#include "needed.h"

class Grid
{
public:
	Grid(int* size, bool load = false);
	~Grid();

    int Get(int row, int column);
    int GetScore();
    int GetNbMove();
    int GetMax();
    
    QString Move_Up();
    QString Move_Right();
    QString Move_Down();
    QString Move_Left();

    bool ChangeMade();

private:
    
    void AddRandom();
    int random(int high);
    bool Lose();
    bool Win();

    int** grid;
    int ratio = 5;
    int* GridSize;
    int score = 0;
    int NbMove = 0;
    QVector<int> twoFour;
};
#endif // GRID_H

