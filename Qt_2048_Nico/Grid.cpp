#include "Grid.h"

Grid::Grid(int* size, bool load) : GridSize(size)
{
    // Rempli le vecteur de 2 et de 4
    for (int i = 0; i < ratio * 10; i++)
    {
        if (i % ratio != 0)
        {
            twoFour.push_back(2);
        }
        else
        {
            twoFour.push_back(4);
        }
    }

    if (load == true)
    {
        QFile file("Game.2048");

        if (file.exists())
        {
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream in(&file);
            QList temp = in.readLine().split("/");
            file.close();

            *size = temp[0].toInt();
            score = temp[1].toInt();
            NbMove = temp[2].toInt();
            grid = new int* [*size];
            for (int i = 0; i < *size; i++)
            {
                grid[i] = new int[*size];
            }

            for (int i = 0; i < *size * *size; i++)
            {
                grid[(int)floor(i / *size)][i % *size] = temp[i + 3].toInt();
            }
        }
    }
    else
    {
        //Création du tableau adaptif selon la valeur de size
        grid = new int* [*size];
        for (int i = 0; i < *size; i++)
        {
            grid[i] = new int[*size];
        }

        // Remplis la grille de 0
        for (int i = 0; i < (*size * *size); i++)
        {
            grid[(int)floor(i / *size)][i % *size] = 0;
        }

        AddRandom();
        AddRandom();
    }
}

Grid::~Grid()
{

}

void Grid::AddRandom()
{
    // Remplis le vecteur avec la position des case vide du graphique
    QVector<int> vec;
    for (int i = 0; i < *GridSize * *GridSize; i++)
    {
        if (grid[(int)floor(i / *GridSize)][i % *GridSize] == 0)
        {
            vec.push_back(i);
        }
    }

    // Si il y a une case de vide déterminer une position aléatoire et insert 2 ou 4
    if (vec.size() > 0)
    {
        int pos = vec[random(vec.size())];
        grid[(int)floor(pos / *GridSize)][pos % *GridSize] = twoFour[random(ratio * 10)];
    }
}

int Grid::random(int high)
{
    //retourne une valeur random entre 0 et high
    srand((int)time(0));
    return rand() % high;
}

QString Grid::Move_Up()
{
    bool move = false;
    int x = 0, y = 0, z = 0;

    // Passe à travers chaque colone du tableau de la gauche vers la droite
    for (x = 0; x < *GridSize; x++)
    {
        // Du haut vers le bas
        for (y = 0; y < *GridSize; y++)
        {
            // Si la case n'est pas vide
            if (grid[y][x] != 0)
            {
                // Vérifie chacune des case en bas de celle-ci
                for (z = y + 1; z < *GridSize; z++)
                {
                    // Si la case n'est pas vide
                    if (grid[z][x] != 0)
                    {
                        // Si les deux case ont la meme valeur on vas les joindres
                        if (grid[y][x] == grid[z][x])
                        {
                            move = true;
                            score += grid[y][x] + grid[z][x];
                            grid[y][x] *= 2;
                            grid[z][x] = 0;
                        }
                        break;
                    }
                }
            }
        }

        // Du haut vers le bas
        for (y = 0; y < *GridSize; y++)
        {
            // Si la case est vide
            if (grid[y][x] == 0)
            {
                // Vérifie chacune des case en bas de celle-ci
                for (z = y + 1; z < *GridSize; z++)
                {
                    // Si la case n'est pas vide la bouger
                    if (grid[z][x] != 0)
                    {
                        grid[y][x] = grid[z][x];
                        grid[z][x] = 0;
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
        NbMove++;
        // Ajout d'un 2 ou d'un 4 à une case vide
        AddRandom();

        if (Win() == true)
        {
            return "Gagne";
        }
        else if (Lose() == true)
        {
            return "Perdu";
        }
    }
    return "Good";
}

QString Grid::Move_Right()
{
    bool move = false;
    int x = 0, y = 0, z = 0;

    // Passe à travers chaque rangé du tableau du haut vers le bas
    for (y = 0; y < *GridSize; y++)
    {
        // De la droie vers la gauche
        for (x = *GridSize - 1; x >= 0; x--)
        {
            // Si la case n'est pas vide
            if (grid[y][x] != 0)
            {
                // Vérifie chacune des case à la gauche de celle-ci
                for (z = x - 1; z >= 0; z--)
                {
                    // Si la case n'est pas vide
                    if (grid[y][z] != 0)
                    {
                        // Si les deux case ont la meme valeur on vas les joindres
                        if (grid[y][x] == grid[y][z])
                        {
                            move = true;
                            score += grid[y][x] + grid[y][z];
                            grid[y][x] *= 2;
                            grid[y][z] = 0;
                        }
                        break;
                    }
                }
            }
        }

        // De la droite vers la gauche
        for (x = *GridSize - 1; x >= 0; x--)
        {
            // Si la case est vide
            if (grid[y][x] == 0)
            {
                // Vérifie chacune des case à la gauche de celle-ci
                for (z = x - 1; z >= 0; z--)
                {
                    // Si la case n'est pas vide la bouger
                    if (grid[y][z] != 0)
                    {
                        grid[y][x] = grid[y][z];
                        grid[y][z] = 0;
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
        NbMove++;
        // Ajout d'un 2 ou d'un 4 à une case vide
        AddRandom();

        if (Win() == true)
        {
            return "Gagne";
        }
        else if (Lose() == true)
        {
            return "Perdu";
        }
    }
    return "Good";
}

QString Grid::Move_Down()
{
    bool move = false;
    int x = 0, y = 0, z = 0;

    // Passe à travers chaque colone du tableau de la gauche vers la droite
    for (x = 0; x < *GridSize; x++)
    {
        // Du bas vers le haut
        for (y = *GridSize - 1; y >= 0; y--)
        {
            // Si la case n'est pas vide
            if (grid[y][x] != 0)
            {
                // Vérifie chacune des case en haut de celle-ci
                for (z = y - 1; z >= 0; z--)
                {
                    // Si la case n'est pas vide
                    if (grid[z][x] != 0)
                    {
                        // Si les deux case ont la meme valeur on vas les joindres
                        if (grid[y][x] == grid[z][x])
                        {
                            move = true;
                            score += grid[y][x] + grid[z][x];
                            grid[y][x] *= 2;
                            grid[z][x] = 0;
                        }
                        break;
                    }
                }
            }
        }

        // Du bas vers le haut
        for (y = *GridSize - 1; y >= 0; y--)
        {
            // Si la case est vide
            if (grid[y][x] == 0)
            {
                // Vérifie chacune des case en bas de celle-ci
                for (z = y - 1; z >= 0; z--)
                {
                    // Si la case n'est pas vide la bouger
                    if (grid[z][x] != 0)
                    {
                        grid[y][x] = grid[z][x];
                        grid[z][x] = 0;
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
        NbMove++;
        // Ajout d'un 2 ou d'un 4 à une case vide
        AddRandom();

        if (Win() == true)
        {
            return "Gagne";
        }
        else if (Lose() == true)
        {
            return "Perdu";
        }
    }
    return "Good";
}

QString Grid::Move_Left()
{
    bool move = false;
    int x = 0, y = 0, z = 0;

    // Passe à travers chaque rangé du tableau du haut vers le bas
    for (y = 0; y < *GridSize; y++)
    {
        // De la gauche vers la droite
        for (x = 0; x < *GridSize; x++)
        {
            // Si la case n'est pas vide
            if (grid[y][x] != 0)
            {
                // Vérifie chacune des case à la droite de celle-ci
                for (z = x + 1; z < *GridSize; z++)
                {
                    // Si la case n'est pas vide
                    if (grid[y][z] != 0)
                    {
                        // Si les deux case ont la meme valeur on vas les joindres
                        if (grid[y][x] == grid[y][z])
                        {
                            move = true;
                            score += grid[y][x] + grid[y][z];
                            grid[y][x] *= 2;
                            grid[y][z] = 0;
                        }
                        break;
                    }
                }
            }
        }

        // De la gauche vers la droite
        for (x = 0; x < *GridSize; x++)
        {
            // Si la case est vide
            if (grid[y][x] == 0)
            {
                // Vérifie chacune des case à la droite de celle-ci
                for (z = x + 1; z < *GridSize; z++)
                {
                    // Si la case n'est pas vide la déplacer
                    if (grid[y][z] != 0)
                    {
                        grid[y][x] = grid[y][z];
                        grid[y][z] = 0;
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
        NbMove++;
        // Ajout d'un 2 ou d'un 4 à une case vide
        AddRandom();

        if (Win() == true)
        {
            return "Gagne";
        }
        else if (Lose() == true)
        {
            return "Perdu";
        }
    }
    return "Good";
}

bool Grid::Lose()
{
    int Nb_empty = 0;

    // Compile le nombre de case vide
    for (int i = 0; i < *GridSize * *GridSize; i++)
    {
        if (grid[(int)floor(i / *GridSize)][i % *GridSize] == 0)
        {
            Nb_empty++;
        }
    }

    // Si il n'y a pas de case vide vérifier si il est possible de joindre des case
    if (Nb_empty == 0)
    {
        int x = 0, y = 0, z = 0;

        bool droit = false;
        for (y = 0; y < *GridSize; y++)
        {
            for (x = *GridSize - 1; x >= 0; x--)
            {
                if (grid[y][x] != 0)
                {
                    for (z = x - 1; z >= 0; z--)
                    {
                        if (grid[y][z] != 0)
                        {
                            if (grid[y][x] == grid[y][z])
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
        for (y = 0; y < *GridSize; y++)
        {
            for (x = 0; x < *GridSize; x++)
            {
                if (grid[y][x] != 0)
                {
                    for (z = x + 1; z < *GridSize; z++)
                    {
                        if (grid[y][z] != 0)
                        {
                            if (grid[y][x] == grid[y][z])
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
        for (x = 0; x < *GridSize; x++)
        {
            for (y = 0; y < *GridSize; y++)
            {
                if (grid[y][x] != 0)
                {
                    for (z = y + 1; z < *GridSize; z++)
                    {
                        if (grid[z][x] != 0)
                        {
                            if (grid[y][x] == grid[z][x])
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
        for (x = 0; x < *GridSize; x++)
        {
            for (y = *GridSize - 1; y >= 0; y--)
            {
                if (grid[y][x] != 0)
                {
                    for (z = y - 1; z >= 0; z--)
                    {
                        if (grid[z][x] != 0)
                        {
                            if (grid[y][x] == grid[z][x])
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
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool Grid::Win()
{
    if (GetMax() == 2048)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Grid::Get(int x, int y)
{
    return grid[x][y];
}

int Grid::GetScore()
{
    return score;
}

int Grid::GetNbMove()
{
    return NbMove;
}

int Grid::GetMax()
{
    int max = 0;

    for (int x = 0; x < *GridSize; x++)
    {
        for (int y = 0; y < *GridSize; y++)
        {
            if (grid[x][y] > max)
            {
                max = grid[x][y];
            }
        }
    }
    return max;
}