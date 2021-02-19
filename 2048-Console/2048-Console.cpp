#include <iostream>
#include<conio.h>
#include "Tableau.h"

using namespace std;

//Le menu de base vas ici
int main()
{
    Tableau tab = Tableau();
    char input;

    cout << "Choix du move :\nw = haut\na = gauche\ns = bas\nd = droit\nq = quitter" << endl;
    input = _getch();

    while (input != 'q' && tab.Next_Move_Possible == true && tab.Get_Highest()<2048)
    {
        //Switch case pour le jeu
        switch (input)
        {

        case 'w':
            cout << endl << "Up" << endl;//key up
            tab.Bouge_Haut();
            break;

        case 's':
            cout << endl << "Down" << endl;   // key down
            tab.Bouge_Bas();
            break;

        case 'd':
            cout << endl << "Right" << endl;  // key right
            tab.Bouge_Droit();
            break;

        case 'a':
            cout << endl << "Left" << endl;  // key left
            tab.Bouge_Gauche();
            break;
        }

        cout << "Choix du move :\nw = haut\na = gauche\ns = bas\nd = droit\nq = quitter" << endl;
        input = _getch();
    }
    
}
