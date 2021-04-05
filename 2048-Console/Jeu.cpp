/*
    Auteur : Nicolas Cantin
*/
#include "Jeu.h"

Jeu::Jeu()
{
    window_to_show = "Accueil";
}

Jeu::~Jeu()
{

}

void Jeu::Run()
{
    while (run == true)
    {
        if (window_to_show == "Accueil")
        {
            Menu_Accueil();
        }
        else if (window_to_show == "Jeu")
        {
            Menu_Jeu();
        }
        else if (window_to_show == "Stats")
        {
            Menu_Stats();
        }
        else if (window_to_show == "Load")
        {
            Menu_Load();
        }
    }
}

void Jeu::Menu_Accueil()
{
    system("cls");

    // Composant du menu accueil
    cout << "SUPER 2048 version console equipe P11" << endl;
    cout << endl;
    cout << "Choisir le mode de jeu :" << endl;
    cout << endl;
    cout << "3 = Mode 3x3" << endl;
    cout << "4 = Mode 4x4" << endl;
    cout << "5 = Mode 5x5" << endl;
    cout << "6 = Mode 6x6" << endl;
    cout << "7 = Mode 7x7" << endl;
    cout << "8 = Mode 8x8" << endl;
    cout << endl;
    cout << "R = Reprendre la derniere partie" << endl;
    cout << endl;
    cout << "S = Stats" << endl;
    cout << endl;
    cout << "Q = quitter" << endl;
    
    // Lire la réponse
    bool Good = false;
    char input;

    while (Good == false)
    {
        input = _getch();
        cout << input << endl;
        
        if (input == '3' || input == '4' || input == '5' || input == '6' || input == '7' || input == '8')
        {
            Setup_Grid(input - '0');
            window_to_show = "Jeu";
            Good = true;
        }
        else if (input == 'R' || input == 'r')
        {
            window_to_show = "Load";
            Good = true;
        }
        else if (input == 's' || input == 'S')
        {
            window_to_show = "Stats";
            Good = true;
        }
        else if (input == 'q' || input == 'Q')
        {
            run = false;
            Good = true;
        }
    }
}

void Jeu::Menu_Load()
{
    system("cls");
    ifstream file("Save.txt");
    string info;
    getline(file, info);

    if (info.length() > 0)
    {
        vector<string> vec_temp;
        string temp = info;
        string delimiter = "/";
        size_t pos = 0;
        string token;

        while ((pos = temp.find(delimiter)) != string::npos)
        {
            token = temp.substr(0, pos);
            vec_temp.push_back(token);
            temp.erase(0, pos + delimiter.length());
        }
        vec_temp.push_back(temp);


        cout << "Mode " << vec_temp[0] << "x" << vec_temp[0] << endl;
        cout << "Score : " << vec_temp[1] << endl;
        cout << "Nb moves : " << vec_temp[2] << endl;
        cout << "Max : " << vec_temp[3] << endl;
        cout << endl;

        cout << "Voulez-vous charger cette partie?" << endl;
        cout << endl;
        cout << "O = oui" << endl;
        cout << "N = non" << endl;


        // Lire la réponse
        bool Good = false;
        char input;

        while (Good == false)
        {
            input = _getch();

            if (input == 'O' || input == 'o')
            {
                Load(info);
                window_to_show = "Jeu";
                Good = true;
            }
            else if (input == 'N' || input == 'n')
            {
                window_to_show = "Accueil";
                Good = true;
            }
        }
    }
    else
    {
        window_to_show = "Accueil";
    }



}

void Jeu::Load(string st)
{
    vector<string> vec;
    string delimiter = "/";

    size_t pos = 0;
    string token;
    while ((pos = st.find(delimiter)) != string::npos)
    {
        token = st.substr(0, pos);
        vec.push_back(token);
        cout << token << endl;
        st.erase(0, pos + delimiter.length());
    }
    vec.push_back(st);
    cout << st << endl;
    
    Setup_Grid(atoi(vec[0].c_str()));
    tab->Load_Grid(vec);
}

void Jeu::Menu_Jeu()
{
    bool show = true;
    while (show == true)
    {
        system("cls");
        //Afficher la grid
        tab->Afficher();
        cout << "W ou fleche haut = haut" << endl;
        cout << "A ou fleche gauche = gauche" << endl;
        cout << "S ou fleche bas = bas" << endl;
        cout << "D ou fleche droit = droit" << endl;
        cout << "Q = Menu principale" << endl;

        // Lire la réponse
        bool Good = false;
        char input;

        while (Good != true)
        {
            input = _getch();

            if (input == 'w' || input == 'W' || input == 72) //Bouge les cases du tableau vers le haut
            {
                tab->Bouge_Haut();
                Good = true;
            }
            else if (input == 's' || input == 'S' || input == 80)//Bouge les cases du tableau vers le bas
            {
                tab->Bouge_Bas();
                Good = true;

            }
            else if (input == 'd' || input == 'D' || input == 77) //Bouge les cases du tableau vers la droite
            {
                tab->Bouge_Droit();
                Good = true;
            }
            else if (input == 'a' || input == 'A' || input == 75) //Bouge les cases du tableau vers la gauche
            {
                tab->Bouge_Gauche();
                Good = true;
            }
            else if (input == 'q' || input == 'Q')
            {
                //Dirige vers le menu accueil
                Good = true;
                show = false;
                Menu_Sauvegarde();
            }
        }
    }
}

void Jeu::Menu_Sauvegarde()
{
    system("cls");

    cout << "Voulez-vous sauvegarder la partie en cours ?" << endl;
    cout << "Cela ecrasera la dernière sauvegarde" << endl;
    cout << endl;
    cout << "O = oui" << endl;
    cout << "N = non" << endl;

    // Lire la réponse
    bool Good = false;
    char input;

    while (Good == false)
    {
        input = _getch();

        if (input == 'O' || input == 'o')
        {
            //Code pour la sauvegarde
            tab->Save_Grid();

            window_to_show = "Accueil";
            Good = true;
        }
        else if (input == 'N' || input == 'n')
        {
            window_to_show = "Accueil";
            Good = true;
        }
    }
}

void Jeu::Menu_Stats()
{
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

    // Lire la réponse
    bool Good = false;
    char input;

    while (Good == false)
    {
        input = _getch();
        if (input == 'q' || input == 'Q')
        {
            Good = true;
            window_to_show = "Accueil";
        }
    }
}

void Jeu::Setup_Grid(int i)
{
    tab->~Tableau();
    tab = new Tableau(i);
}