#include "jeu.h"
#include <iostream>

Jeu::Jeu(int size, bool load) : GridSize(size) , Loaded(load)
{
    if (load == true)
    {
        Setup_Loaded_Grid();
    }
    else
    {
        Setup_New_Grid();
    }
    
    Setup_FPGA();
}

Jeu::~Jeu()
{

}

#pragma region Jeu

QString Jeu::Bouge_Haut()
{
    if (SaveOn == false ||VerifOn == false)
    {
        QString Status = Move_Up();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else
        {
            return "Refresh";
        }
    }
    else
    {
        return "En lecture";
    }
}

QString Jeu::Bouge_Droit()
{
    if (SaveOn == false || VerifOn == false)
    {
        QString Status = Move_Right();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else
        {
            return "Refresh";
        }
    }
    else
    {
        return "En lecture";
    }
}

QString Jeu::Bouge_Bas()
{
    if (SaveOn == false || VerifOn == false)
    {
        QString Status = Move_Down();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else
        {
            return "Refresh";
        }
    }
    else
    {
        return "En lecture";
    }
}

QString Jeu::Bouge_Gauche()
{
    if (SaveOn == false || VerifOn == false)
    {
        QString Status = Move_Left();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else
        {
            return "Refresh";
        }
    }
    else
    {
        return "En lecture";
    }
}

#pragma endregion

#pragma region Grid

void Jeu::Setup_New_Grid()
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

    //Création du tableau adaptif selon la valeur de size
    grid = new int* [GridSize];
    for (int i = 0; i < GridSize; i++)
    {
        grid[i] = new int[GridSize];
    }

    // Remplis la grille de 0
    for (int i = 0; i < (GridSize * GridSize); i++)
    {
        grid[(int)floor(i / GridSize)][i % GridSize] = 0;
    }

    AddRandom();
    AddRandom();
}

void Jeu::Setup_Loaded_Grid()
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

    QFile file("Save.txt");

    if (file.exists())
    {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&file);
        QList temp = in.readLine().split("/");
        file.close();

        GridSize = temp[0].toInt();
        score = temp[1].toInt();
        NbMove = temp[2].toInt();
        grid = new int* [GridSize];
        for (int i = 0; i < GridSize; i++)
        {
            grid[i] = new int[GridSize];
        }

        for (int i = 0; i < GridSize * GridSize; i++)
        {
            grid[(int)floor(i / GridSize)][i % GridSize] = temp[i + 3].toInt();
        }
    }
}

void Jeu::AddRandom()
{
    // Remplis le vecteur avec la position des case vide du graphique
    QVector<int> vec;
    for (int i = 0; i < GridSize * GridSize; i++)
    {
        if (grid[(int)floor(i / GridSize)][i % GridSize] == 0)
        {
            vec.push_back(i);
        }
    }

    // Si il y a une case de vide déterminer une position aléatoire et insert 2 ou 4
    if (vec.size() > 0)
    {
        int pos = vec[random(vec.size())];
        grid[(int)floor(pos / GridSize)][pos % GridSize] = twoFour[random(ratio * 10)];
    }
}

int Jeu::random(int high)
{
    //retourne une valeur random entre 0 et high
    srand((int)time(0));
    return rand() % high;
}

QString Jeu::Move_Up()
{
    bool move = false;
    int x = 0, y = 0, z = 0;

    // Passe à travers chaque colone du tableau de la gauche vers la droite
    for (x = 0; x < GridSize; x++)
    {
        // Du haut vers le bas
        for (y = 0; y < GridSize; y++)
        {
            // Si la case n'est pas vide
            if (grid[y][x] != 0)
            {
                // Vérifie chacune des case en bas de celle-ci
                for (z = y + 1; z < GridSize; z++)
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
        for (y = 0; y < GridSize; y++)
        {
            // Si la case est vide
            if (grid[y][x] == 0)
            {
                // Vérifie chacune des case en bas de celle-ci
                for (z = y + 1; z < GridSize; z++)
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

QString Jeu::Move_Right()
{
    bool move = false;
    int x = 0, y = 0, z = 0;

    // Passe à travers chaque rangé du tableau du haut vers le bas
    for (y = 0; y < GridSize; y++)
    {
        // De la droie vers la gauche
        for (x = GridSize - 1; x >= 0; x--)
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
        for (x = GridSize - 1; x >= 0; x--)
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

QString Jeu::Move_Down()
{
    bool move = false;
    int x = 0, y = 0, z = 0;

    // Passe à travers chaque colone du tableau de la gauche vers la droite
    for (x = 0; x < GridSize; x++)
    {
        // Du bas vers le haut
        for (y = GridSize - 1; y >= 0; y--)
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
        for (y = GridSize - 1; y >= 0; y--)
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

QString Jeu::Move_Left()
{
    bool move = false;
    int x = 0, y = 0, z = 0;

    // Passe à travers chaque rangé du tableau du haut vers le bas
    for (y = 0; y < GridSize; y++)
    {
        // De la gauche vers la droite
        for (x = 0; x < GridSize; x++)
        {
            // Si la case n'est pas vide
            if (grid[y][x] != 0)
            {
                // Vérifie chacune des case à la droite de celle-ci
                for (z = x + 1; z < GridSize; z++)
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
        for (x = 0; x < GridSize; x++)
        {
            // Si la case est vide
            if (grid[y][x] == 0)
            {
                // Vérifie chacune des case à la droite de celle-ci
                for (z = x + 1; z < GridSize; z++)
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

bool Jeu::Lose()
{
    int Nb_empty = 0;

    // Compile le nombre de case vide
    for (int i = 0; i < GridSize * GridSize; i++)
    {
        if (grid[(int)floor(i / GridSize)][i % GridSize] == 0)
        {
            Nb_empty++;
        }
    }

    // Si il n'y a pas de case vide vérifier si il est possible de joindre des case
    if (Nb_empty == 0)
    {
        int x = 0, y = 0, z = 0;

        bool droit = false;
        for (y = 0; y < GridSize; y++)
        {
            for (x = GridSize - 1; x >= 0; x--)
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
        for (y = 0; y < GridSize; y++)
        {
            for (x = 0; x < GridSize; x++)
            {
                if (grid[y][x] != 0)
                {
                    for (z = x + 1; z < GridSize; z++)
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
        for (x = 0; x < GridSize; x++)
        {
            for (y = 0; y < GridSize; y++)
            {
                if (grid[y][x] != 0)
                {
                    for (z = y + 1; z < GridSize; z++)
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
        for (x = 0; x < GridSize; x++)
        {
            for (y = GridSize - 1; y >= 0; y--)
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

bool Jeu::Win()
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

int Jeu::Get(int x, int y)
{
    return grid[x][y];
}

int Jeu::GetScore()
{
    return score;
}

int Jeu::GetNbMove()
{
    return NbMove;
}

int Jeu::GetMax()
{
    int max = 0;

    for (int x = 0; x < GridSize; x++)
    {
        for (int y = 0; y < GridSize; y++)
        {
            if (grid[x][y] > max)
            {
                max = grid[x][y];
            }
        }
    }
    return max;
}

int Jeu::GetSize()
{
    return GridSize;
}

#pragma endregion

#pragma region FPGA

void Jeu::Setup_FPGA()
{
    port = new CommunicationFPGA();

    if (!port->estOk())
    {
        cout << port->messageErreur() << endl;
    }
    else
    {
        cout << "Statut initial du port de communication = " << port->estOk() << endl << endl;
    }

    int statut_circuit = 0;
    statutport = port->lireRegistre(nreg_lect_stat_btn, statut_circuit);

    //Phoneme 'a'
    {
        valPhoneme[0].val[0][0] = 60;		//min pot1
        valPhoneme[0].val[0][1] = 90;		//max pot1
        valPhoneme[0].val[1][0] = 520;		//min pot2
        valPhoneme[0].val[1][1] = 610;		//max pot2
        valPhoneme[0].val[2][0] = 20;		//min pot3
        valPhoneme[0].val[2][1] = 60;		//max pot3
        valPhoneme[0].val[3][0] = 90;		//min pot4
        valPhoneme[0].val[3][1] = 170;		//max pot4
    }

    //Phoneme 'e'
    {
        valPhoneme[1].val[0][0] = 180;		//min pot1
        valPhoneme[1].val[0][1] = 270;		//max pot1
        valPhoneme[1].val[1][0] = 60;		//min pot2
        valPhoneme[1].val[1][1] = 100;		//max pot2
        valPhoneme[1].val[2][0] = 300;		//min pot3
        valPhoneme[1].val[2][1] = 530;		//max pot3
        valPhoneme[1].val[3][0] = 130;		//min pot4
        valPhoneme[1].val[3][1] = 240;		//max pot4
    }

    //Phoneme 'eu'
    {
        valPhoneme[2].val[0][0] = 550;		//min pot1
        valPhoneme[2].val[0][1] = 830;		//max pot1
        valPhoneme[2].val[1][0] = 180;		//min pot2
        valPhoneme[2].val[1][1] = 280;		//max pot2
        valPhoneme[2].val[2][0] = 240;		//min pot3
        valPhoneme[2].val[2][1] = 390;		//max pot3
        valPhoneme[2].val[3][0] = 40;		//min pot4
        valPhoneme[2].val[3][1] = 110;		//max pot4
    }

    //Phoneme 'i'
    {
        valPhoneme[3].val[0][0] = 500;		//min pot1
        valPhoneme[3].val[0][1] = 780;		//max pot1
        valPhoneme[3].val[1][0] = 0;		//min pot2
        valPhoneme[3].val[1][1] = 60;		//max pot2
        valPhoneme[3].val[2][0] = 430;		//min pot3
        valPhoneme[3].val[2][1] = 615;		//max pot3
        valPhoneme[3].val[3][0] = 585;		//min pot4
        valPhoneme[3].val[3][1] = 810;		//max pot4
    }


    //Phoneme 'a' = ( 0x16 - 0x8D - 0x0A - 0x20 )

    //Phoneme 'e' = ( 0x38 - 0x14 - 0x68 - 0x2E )

    //Phoneme 'eu' = ( 0xAD - 0x3A - 0x4F - 0x16 )

    //Phoneme 'i' = ( 0xA0 - 0x08 - 0x83 - 0xAE )
}

bool Jeu::isConnected()
{
    return statutport;
}

QString Jeu::Read()
{
    // lecture statut et BTN
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_stat_btn, stat_btn);
    }
    else
    {
        return "Erreur";
    }

    // lecture swt
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_swt, swt);
        statutport = port->ecrireRegistre(nreg_ecri_led, swt);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 0
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can0, Chanel[0]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 1
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can1, Chanel[1]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 2
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can2, Chanel[2]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 3
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can3, Chanel[3]);
    }
    else
    {
        return "Erreur";
    }

    if (statutport)
    {
        //Ajuster les pot
        if (swt == 0x80)	//#1
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x01);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[0]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x40)	//#2
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x02);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[1]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x20)	//#3
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x03);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[2]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x10)	//#4
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x04);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[3]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x00);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, 0x00);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x00);
        }

        if (stat_btn == 0x11 && swt == 0x00 && SaveOn == false && VerifOn == false)	//Lance la lecture
        {
            SaveOn = true;
            return "LecStart";
        }
        else if (SaveOn == true && nbSaved < nbLecture && VerifOn == false)	//Enregistre les lectures
        {
            for (int i = 0; i < 4; i++)
                ListLecture[nbSaved].pot[i] = Chanel[i];

            nbSaved++;
            return "Lec";
        }
        else if (SaveOn == true && nbSaved == nbLecture && VerifOn == false)	//Arrête la lecture
        {
            SaveOn = false;
            VerifOn = true;
            return "LecStop";
        }
        else if (SaveOn == false && VerifOn == true)	//Vérifie la correspondance
        {
            QString rep = Verification();
            VerifOn = false;
            nbSaved = 0;
            return rep;
        }

        return "Rien";
    }
    else
    {
        return "Erreur";
    }
}

QString Jeu::Verification()
{
    int pointage[4] = { 0 };
    int lecture;
    for (int a = 0; a < nbLecture; a++) // lecture #1 a #10
    {
        for (int b = 0; b < 4; b++)// pot #1 a #4
        {
            for (int c = 0; c < 4; c++) //Phonème #1 a #4
            {
                lecture = ListLecture[a].pot[b] * 4;

                if (lecture >= valPhoneme[c].val[b][0] && lecture <= valPhoneme[c].val[b][1])
                {
                    //cout << dec << "l=" << to_string(a + 1) << " P=" << to_string(b + 1) << " h=" << to_string(c + 1) << " val=";
                    //cout << hex << to_string(ListLecture[a].pot[b]) << endl;
                    pointage[c]++;
                }
            }
        }
    }

    //Trouver le correspondant
    int max = 0;
    int num = 0;
    int seuil = floor((4.0 * nbLecture) * 0.8);
    for (int i = 0; i < 4; i++)
    {
        if (pointage[i] >= max)
        {
            num = i + 1;
            max = pointage[i];
        }
    }

    cout << "Nombre de bon = " << to_string(max) << "\nNum : " << to_string(num) << endl;
    if (num == 1 && max >= seuil)
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, num);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        return "Haut";
    }
    else if (num == 2 && max >= seuil)
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, num);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        return "Droit";
    }
    else if (num == 3 && max >= seuil)
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, num);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        return "Bas";
    }
    else if (num == 4 && max >= seuil)
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, num);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        return "Gauche";
    }
    else
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x0E);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, 0xE0);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0);
        return "Aucun";
    }
}

int Jeu::waitTime()
{
    return wait_Time;
}

int Jeu::readTime()
{
    return read_Time;
}


#pragma endregion

QString Jeu::Menu()
{
    if (Loaded == true)
    {
        SaveGame();
        return "Sauvegarde";
    }
    else if (GetMax() >= 16)
    {
        QFile file("Save.txt");

        if (file.exists())
        {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                if (in.readLine().length() > 5)
                {
                    //Demander si il faut écraser
                    return "Question";
                }
                else
                {
                    SaveGame();
                    return "Sauvegarde";
                }
                file.close();
            }
            else
            {
                return "Erreur ouverture";
            }
        }
        else
        {
            return "Fichier introuvable";
        }
    }
    else
    {
        return "Rien";
    }

    
}

void Jeu::SaveGame()
{
    QFile file("Save.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        in << QString::number(GridSize)+"/";
        in << QString::number(GetScore())+"/";
        in << QString::number(GetNbMove())+"/";
        for(int x = 0; x<GridSize;x++)
        {
            for(int y = 0;y<GridSize;y++)
            {
                if(x == GridSize-1 && y == GridSize-1)
                {
                    in << QString::number(grid[x][y]);
                }
                else
                {
                    in << QString::number(grid[x][y]) + "/";
                }

            }
        }
    }
    file.close();
}

void Jeu::SaveStats(QString s)
{
    QFile file("Stats.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream in(&file);
        in << s + "/";
        in << QString::number(GridSize)+ "x" + QString::number(GridSize) +"/";
        in << QString::number(GetScore())+"/";
        in << QString::number(GetNbMove())+"/";
        in << QString::number(GetMax())+"\n";
    }
    file.close();
}

void Jeu::ClearFile()
{
    QFile file("Save.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in << "";
    }
    file.close();
}
