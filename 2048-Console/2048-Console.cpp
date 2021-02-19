#include <iostream>
#include<conio.h>
#include "Tableau.h"


using namespace std;

//Le menu de base vas ici
int main()
{
    Tableau* tableau;
    tableau = new Tableau();

    int mode = 4;
    char input;
    bool Afficher_Menu = true;

    while (true)
    {
        if (Afficher_Menu == true)
        {
            delete tableau;
            system("cls");
            cout << "2048 version console equipe P11" << endl << endl;
            cout << "Choisir le mode de jeu :" << endl << endl;
            cout << "4 = Mode 4x4" << endl;
            cout << "5 = Mode 5x5" << endl;
            cout << "6 = Mode 6x6" << endl;
            cout << "7 = Mode 7x7" << endl;
            cout << "8 = Mode 8x8" << endl << endl;
            cout << "Q = quitter" << endl;
            input = _getch();

            if (input == '4')
            {
                mode = 4;
                tableau = new Tableau(4);
                Afficher_Menu = false;
            }
            else if (input == '5')
            {
                mode = 5;
                tableau = new Tableau(5);
                Afficher_Menu = false;
            }
            else if (input == '6')
            {
                mode = 6;
                tableau = new Tableau(6);
                Afficher_Menu = false;
            }
            else if (input == '7')
            {
                mode = 7;
                tableau = new Tableau(7);
                Afficher_Menu = false;
            }
            else if (input == '8')
            {
                mode = 8;
                tableau = new Tableau(8);
                Afficher_Menu = false;
            }
            else if (input == 'q' || input == 'Q')
            {
                break;
            }
            
        }
        else
        {
            if (mode == 4)
            {
                tableau->Afficher();

                cout << "W = haut" << endl;
                cout << "A = gauche" << endl;
                cout << "S = bas" << endl;
                cout << "D = droit" << endl;
                cout << "F = Fin de partie" << endl;

                input = _getch();

                if (input == 'w' || input == 'W')
                {
                    tableau->Bouge_Haut();
                    tableau->Afficher();
                }
                else if (input == 's' || input == 'S')
                {
                    tableau->Bouge_Bas();
                    tableau->Afficher();
                }
                else if (input == 'd' || input == 'D')
                {
                    tableau->Bouge_Droit();
                    tableau->Afficher();
                }
                else if (input == 'a' || input == 'A')
                {
                    tableau->Bouge_Gauche();
                    tableau->Afficher();
                }
                else if (input == 'f' || input == 'F')
                {
                    system("cls");
                    cout << "Fin" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Move_Possible() == false)
                {
                    system("cls");
                    cout << "Perdu" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Get_Highest() >= 2048)
                {
                    system("cls");
                    cout << "Gagner" << endl;
                    Afficher_Menu = true;
                }
            }
            else if (mode == 5)
            {
                tableau->Afficher();

                cout << "W = haut" << endl;
                cout << "A = gauche" << endl;
                cout << "S = bas" << endl;
                cout << "D = droit" << endl;
                cout << "F = Fin de partie" << endl;

                input = _getch();

                if (input == 'w' || input == 'W')
                {
                    tableau->Bouge_Haut();
                    tableau->Afficher();
                }
                else if (input == 's' || input == 'S')
                {
                    tableau->Bouge_Bas();
                    tableau->Afficher();
                }
                else if (input == 'd' || input == 'D')
                {
                    tableau->Bouge_Droit();
                    tableau->Afficher();
                }
                else if (input == 'a' || input == 'A')
                {
                    tableau->Bouge_Gauche();
                    tableau->Afficher();
                }
                else if (input == 'f' || input == 'F')
                {
                    system("cls");
                    cout << "Fin" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Move_Possible() == false)
                {
                    system("cls");
                    cout << "Perdu" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Get_Highest() >= 2048)
                {
                    system("cls");
                    cout << "Gagner" << endl;
                    Afficher_Menu = true;
                }
            }
            else if (mode == 6)
            {
                tableau->Afficher();

                cout << "W = haut" << endl;
                cout << "A = gauche" << endl;
                cout << "S = bas" << endl;
                cout << "D = droit" << endl;
                cout << "F = Fin de partie" << endl;

                input = _getch();

                if (input == 'w' || input == 'W')
                {
                    tableau->Bouge_Haut();
                    tableau->Afficher();
                }
                else if (input == 's' || input == 'S')
                {
                    tableau->Bouge_Bas();
                    tableau->Afficher();
                }
                else if (input == 'd' || input == 'D')
                {
                    tableau->Bouge_Droit();
                    tableau->Afficher();
                }
                else if (input == 'a' || input == 'A')
                {
                    tableau->Bouge_Gauche();
                    tableau->Afficher();
                }
                else if (input == 'f' || input == 'F')
                {
                    system("cls");
                    cout << "Fin" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Move_Possible() == false)
                {
                    system("cls");
                    cout << "Perdu" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Get_Highest() >= 2048)
                {
                    system("cls");
                    cout << "Gagner" << endl;
                    Afficher_Menu = true;
                }
            }
            else if (mode == 7)
            {
                tableau->Afficher();

                cout << "W = haut" << endl;
                cout << "A = gauche" << endl;
                cout << "S = bas" << endl;
                cout << "D = droit" << endl;
                cout << "F = Fin de partie" << endl;

                input = _getch();

                if (input == 'w' || input == 'W')
                {
                    tableau->Bouge_Haut();
                    tableau->Afficher();
                }
                else if (input == 's' || input == 'S')
                {
                    tableau->Bouge_Bas();
                    tableau->Afficher();
                }
                else if (input == 'd' || input == 'D')
                {
                    tableau->Bouge_Droit();
                    tableau->Afficher();
                }
                else if (input == 'a' || input == 'A')
                {
                    tableau->Bouge_Gauche();
                    tableau->Afficher();
                }
                else if (input == 'f' || input == 'F')
                {
                    system("cls");
                    cout << "Fin" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Move_Possible() == false)
                {
                    system("cls");
                    cout << "Perdu" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Get_Highest() >= 2048)
                {
                    system("cls");
                    cout << "Gagner" << endl;
                    Afficher_Menu = true;
                }
            }
            else if (mode == 8)
            {
                tableau->Afficher();

                cout << "W = haut" << endl;
                cout << "A = gauche" << endl;
                cout << "S = bas" << endl;
                cout << "D = droit" << endl;
                cout << "F = Fin de partie" << endl;

                input = _getch();

                if (input == 'w' || input == 'W')
                {
                    tableau->Bouge_Haut();
                    tableau->Afficher();
                }
                else if (input == 's' || input == 'S')
                {
                    tableau->Bouge_Bas();
                    tableau->Afficher();
                }
                else if (input == 'd' || input == 'D')
                {
                    tableau->Bouge_Droit();
                    tableau->Afficher();
                }
                else if (input == 'a' || input == 'A')
                {
                    tableau->Bouge_Gauche();
                    tableau->Afficher();
                }
                else if (input == 'f' || input == 'F')
                {
                    system("cls");
                    cout << "Fin" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Move_Possible() == false)
                {
                    system("cls");
                    cout << "Perdu" << endl;
                    Afficher_Menu = true;
                }
                else if (tableau->Get_Highest() >= 2048)
                {
                    system("cls");
                    cout << "Gagner" << endl;
                    Afficher_Menu = true;
                }
            }
        }
    }
}
