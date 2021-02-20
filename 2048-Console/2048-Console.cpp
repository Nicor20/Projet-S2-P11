#include <iostream>
#include<conio.h>
#include "Tableau.h"

//Le menu de base vas ici
int main()
{
    Tableau* tableau;
    tableau = new Tableau();

    int Menu = 0;
    int Mode = 4;
    bool continuer;

    char input;

    while (true)
    {
        if (Menu == 0)
        {
            continuer = false;
            system("cls");
            cout << "2048 version console equipe P11" << endl << endl;
            cout << "Choisir le mode de jeu :" << endl << endl;
            cout << "3 = Mode 3x3" << endl;
            cout << "4 = Mode 4x4" << endl;
            cout << "5 = Mode 5x5" << endl;
            cout << "6 = Mode 6x6" << endl;
            cout << "7 = Mode 7x7" << endl;
            cout << "8 = Mode 8x8" << endl << endl;
            cout << "S = Stats" << endl << endl; 
            cout << "Q = quitter" << endl;
            input = _getch();

            if (input == '3' || input == '4' || input == '5' || input == '6' || input == '7' || input == '8')
            {
                delete tableau;
                tableau = new Tableau(input - '0');
                Menu = 1;
            }
            else if (input == 's' || input == 'S')
            {
                Menu = 3;
            }
            else if (input == 'q' || input == 'Q')
            {
                break;
            }
        }
        else if (Menu == 1)
        {
            tableau->Afficher();

            cout << "W = haut" << endl;
            cout << "A = gauche" << endl;
            cout << "S = bas" << endl;
            cout << "D = droit" << endl;
            cout << "Q = Menu principale" << endl;

            input = _getch();

            if (input == 'w' || input == 'W')
            {
                tableau->Bouge_Haut();
            }
            else if (input == 's' || input == 'S')
            {
                tableau->Bouge_Bas();
            }
            else if (input == 'd' || input == 'D')
            {
                tableau->Bouge_Droit();
            }
            else if (input == 'a' || input == 'A')
            {
                tableau->Bouge_Gauche();
            }
            else if (input == 'q' || input == 'Q')
            {   
                tableau->Save();
                system("cls");

                cout << "Fin" << endl;
                Menu = 0;
            }
            
            if (tableau->Move_Possible() == false)
            {
                tableau->Save();
                system("cls");

                cout << "Vous avez perdu la partie!" << endl << endl;
                cout << "Score : " << tableau->Get_Score() << endl;
                cout << "Max : " << tableau->Get_Max() << endl;
                cout << "Nombre de mouvement : " << tableau->Get_Move() << endl;
                cin.ignore();

                Menu = 0;
            }
            
            if (tableau->Get_Max() >= 2048 && continuer == false)
            {
                tableau->Save();
                system("cls");

                cout << "Vous avez gagner la partie!" << endl;
                cout << "Score : " << tableau->Get_Score() << endl;
                cout << "Nombre de mouvement : " << tableau->Get_Move() << endl;
                cin.ignore();

                Menu = 2;
            }
        }
        else if (Menu == 2)
        {
            system("cls");
            cout << "Vouler vous continuer la Partie" << endl;
            cout << "Y = Oui" << endl;
            cout << "N = Non" << endl;
            input = _getch();

            if (input == 'y' || input == 'Y')
            {
                Menu = 1;
                continuer = true;
            }
            else if (input == 'N' || input == 'n')
            {
                Menu = 0;
            }
        }
        else if (Menu == 3)
        {
            system("cls");
            cout << "Q = Quitter" << endl << endl;
            cout << "Stats : " << endl;

            string text;
            ifstream file("Stats.txt");
            while (getline(file, text))
            {
                cout << text << endl;
            }
            file.close();

            input = _getch();

            if (input == 'q' || input == 'Q')
            {
                Menu = 0;
            }
        }
    }
}
