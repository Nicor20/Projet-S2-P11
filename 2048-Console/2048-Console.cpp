/*
    Auteur : Nicolas Cantin
*/

#include <iostream>
#include <conio.h>
#include "Tableau.h"

//Le menu de base vas ici
int main()
{
    Tableau* tableau;
    tableau = new Tableau();

    int Menu = 0;
    bool continuer;

    char input;

    while (true)
    {
        if (Menu == 0)
        {
            // Menu Accueil

            // Efface le contenu de la console
            system("cls");

            continuer = false;

            // Composant du menu accueil
            cout << "SUPER 2048 version console equipe P11" << endl << endl;
            cout << "Choisir le mode de jeu :" << endl << endl;
            cout << "3 = Mode 3x3" << endl;
            cout << "4 = Mode 4x4" << endl;
            cout << "5 = Mode 5x5" << endl;
            cout << "6 = Mode 6x6" << endl;
            cout << "7 = Mode 7x7" << endl;
            cout << "8 = Mode 8x8" << endl << endl;
            cout << "S = Stats" << endl << endl; 
            cout << "Q = quitter" << endl;

            // Lis la touche cliquer sans avoir besoin de cliquer sur enter
            input = _getch();
            if (input == '3' || input == '4' || input == '5' || input == '6' || input == '7' || input == '8')
            {
                //Efface le tableau existant
                delete tableau;
                //Crée un nouveau tableau pour le mode sélectionner (3-4-5-6-7-8)
                tableau = new Tableau(input - '0');
                //Dirige vers le menu Jeu
                Menu = 1;
            }
            else if (input == 's' || input == 'S')
            {
                //Dirige vers le menu statistique
                Menu = 3;
            }
            else if (input == 'q' || input == 'Q')
            {
                //Arrete le jeu
                break;
            }
        }
        else if (Menu == 1)
        {
            // Menu Jeu

            // Composant du menu jeu
            tableau->Afficher();

            cout << "W ou fleche haut = haut" << endl;
            cout << "A ou fleche gauche = gauche" << endl;
            cout << "S ou fleche bas = bas" << endl;
            cout << "D ou fleche droit = droit" << endl;
            cout << "Q = Menu principale" << endl;

            // Lis la touche cliquer sans avoir besoin de cliquer sur enter
            input = _getch();

            if (input == 'w' || input == 'W' || input == 72)
            {
                //Bouge les cases du tableau vers le haut
                tableau->Bouge_Haut();
            }
            else if (input == 's' || input == 'S' || input == 80)
            {
                //Bouge les cases du tableau vers le bas
                tableau->Bouge_Bas();
            }
            else if (input == 'd' || input == 'D' || input == 77)
            {
                //Bouge les cases du tableau vers la droite
                tableau->Bouge_Droit();
            }
            else if (input == 'a' || input == 'A' || input == 75)
            {
                //Bouge les cases du tableau vers la gauche
                tableau->Bouge_Gauche();
            }
            else if (input == 'q' || input == 'Q')
            {   
                //Sauvegarde le tableau
                tableau->Save();

                // Efface le contenu de la console
                system("cls");

                cout << "Fin" << endl;

                //Dirige vers le menu accueil
                Menu = 0;
            }
            
            if (tableau->Move_Possible() == false)
            {
                tableau->Save();

                // Efface le contenu de la console
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
                // Efface le contenu de la console
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
            // Menu Continuer (apparet selement si le joueur gagne)

            // Efface le contenu de la console
            system("cls");

            cout << "Vouler vous continuer la Partie" << endl;
            cout << "Y = Oui" << endl;
            cout << "N = Non" << endl;

            // Lis la touche cliquer sans avoir besoin de cliquer sur enter
            input = _getch();

            if (input == 'y' || input == 'Y')
            {   
                //Redirige vers le menu jeu pour continuer la partie
                Menu = 1;
                continuer = true;
            }
            else if (input == 'N' || input == 'n')
            {
                //Sauvegarde la partie
                tableau->Save();
                //Redirige vers le menu accueil
                Menu = 0;
            }
        }
        else if (Menu == 3)
        {
            //Menu Statistique de jeu

            // Efface le contenu de la console
            system("cls");

            cout << "Q = Quitter" << endl << endl;
            cout << "Stats : " << endl;

            //Lis les infos du fichier .txt et les affiche
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
                //Redirige vers le menu accueil
                Menu = 0;
            }
        }
    }
}
