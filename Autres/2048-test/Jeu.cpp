/*
    Auteur : Nicolas Cantin
*/
#include "Jeu.h"

Jeu::Jeu()
{
    window_to_show = "Accueil";
    mode_lecture = 1;
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
    if (mode_lecture == 1)
    {
        cout << "L = Changer lecture pour (FPGA)" << endl;
    }
    else if(mode_lecture == 2)
    {
        cout << "L = Changer lecture pour (Clavier)" << endl;
    }
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
            Setup_FPGA();
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
        else if (input == 'L' || input == 'l')
        {
            if (mode_lecture == 1)
            {
                mode_lecture = 2;
            }
            else if (mode_lecture == 2)
            {
                mode_lecture = 1;
            }
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
                Setup_FPGA();
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
    Show_jeu = true;
    while (Show_jeu == true)
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
        

        if (mode_lecture == 1)
        {
            bool Good = false;
            char input;
            while (Good == false)
            {
                input = _getch();

                Good = Touche_Jeu(input);
            }
        }
        else if (mode_lecture == 2)
        {
            bool Good = false;
            while (Good == false)
            {
                Good = Lecture_FPGA();
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

bool Jeu::Touche_Jeu(char input)
{
    if (input == 'w' || input == 'W' || input == 72) //Bouge les cases du tableau vers le haut
    {
        tab->Bouge_Haut();
        return true;
    }
    else if (input == 's' || input == 'S' || input == 80)//Bouge les cases du tableau vers le bas
    {
        tab->Bouge_Bas();
        return true;

    }
    else if (input == 'd' || input == 'D' || input == 77) //Bouge les cases du tableau vers la droite
    {
        tab->Bouge_Droit();
        return true;
    }
    else if (input == 'a' || input == 'A' || input == 75) //Bouge les cases du tableau vers la gauche
    {
        tab->Bouge_Gauche();
        return true;
    }
    else if (input == 'q' || input == 'Q')
    {
        //Dirige vers le menu accueil
        return true;
        Show_jeu = false;
        Menu_Sauvegarde();
    }
}

void Jeu::Setup_FPGA()
{
    if (!port.estOk())
    {
        cout << port.messageErreur() << endl;
    }
    else
    {
        cout << "Statut initial du port de communication = " << port.estOk() << endl << endl;
    }

    int statut_circuit = 0;

    statutport = port.lireRegistre(nreg_lect_stat_btn, statut_circuit);

    cout << "Lecture du statut du circuit statut_circuit = " << (int)statut_circuit << ", statutport = " << statutport << endl;


    statutport = port.ecrireRegistre(nreg_ecri_led, 1);          // envoyer valeur '1' sur led(0) du FPGA : signal pour passer en mode connecté
    if (!port.estOk())
    {
        cout << port.messageErreur() << endl;
    }

    cout << endl << dec << "Delai d'attente ajoute dans a boucle de lecture : " << delai_boucle << " ms" << endl;

    cout << setfill('0') << setw(4) << hex << showbase << internal << endl;
    cout << "   Stat_BTN,  SWT,  compt_t,      ch[0], ch[1], ch[2], ch[3]" << endl;

}

bool Jeu::Lecture_FPGA()
{
    // lecture statut et BTN
    if (statutport)
    {
        statutport = port.lireRegistre(nreg_lect_stat_btn, stat_btn);
    }
    else
    {
        cout << "Erreur du port nreg_lect_stat_btn" << endl; exit(1);
    }

    // lecture swt
    if (statutport)
    {
        statutport = port.lireRegistre(nreg_lect_swt, swt);
    }
    else
    {
        cout << "Erreur du port nreg_lect_swt" << endl; exit(1);
    }

    // lecture canal 0
    if (statutport)
    {
        statutport = port.lireRegistre(nreg_lect_can0, Chanel[0]);
    }
    else
    {
        cout << "Erreur du port nreg_lect_can0" << endl; exit(1);
    }

    // lecture canal 1
    if (statutport)
    {
        statutport = port.lireRegistre(nreg_lect_can1, Chanel[1]);
    }
    else
    {
        cout << "Erreur du port nreg_lect_can1" << endl; exit(1);
    }

    // lecture canal 2
    if (statutport)
    {
        statutport = port.lireRegistre(nreg_lect_can2, Chanel[2]);
    }
    else
    {
        cout << "Erreur du port nreg_lect_can2" << endl; exit(1);
    }

    // lecture canal 3
    if (statutport)
    {
        statutport = port.lireRegistre(nreg_lect_can3, Chanel[3]);
    }
    else
    {
        cout << "Erreur du port nreg_lect_can3" << endl; exit(1);
    }

    if (!statutport) {
        cout << "Erreur du port dans la boucle" << endl;
        exit(1);
    }

    // re-envoyer lecture swt sur port LED
    if (statutport)
    {
        statutport = port.ecrireRegistre(nreg_ecri_led, swt);
    }
    else
    {
        cout << "Erreur du port nreg_ecri_led" << endl; exit(1);
    }


    //Ajustement pot #1
    if (swt == 0x80 && statutport)
    {
        statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x01);
        statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[0]);
        statutport = port.ecrireRegistre(nreg_ecri_aff7dot, stat_btn & 0xFF);
    }

    //Ajustement pot #2
    if (swt == 0x40 && statutport)
    {
        statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x02);
        statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[1]);
        statutport = port.ecrireRegistre(nreg_ecri_aff7dot, stat_btn & 0xFF);
    }

    //Ajustement pot #3
    if (swt == 0x20 && statutport)
    {
        statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x03);
        statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[2]);
        statutport = port.ecrireRegistre(nreg_ecri_aff7dot, stat_btn & 0xFF);
    }

    //Ajustement pot #4
    if (swt == 0x10 && statutport)
    {
        statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x04);
        statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[3]);
        statutport = port.ecrireRegistre(nreg_ecri_aff7dot, stat_btn & 0xFF);
    }

    //Sauvegarde des valeurs pot 1
    if (swt == 0x03 && stat_btn == 0x08 && statutport)
    {
        vref_1 = Chanel[0];
    }

    //Sauvegarde des valeurs pot 2
    if (swt == 0x03 && stat_btn == 0x04 && statutport)
    {
        vref_2 = Chanel[1];
    }

    //Sauvegarde des valeurs pot 3
    if (swt == 0x03 && stat_btn == 0x02 && statutport)
    {
        vref_3 = Chanel[2];
    }

    //Sauvegarde des valeurs pot 4
    if (swt == 0x03 && stat_btn == 0x01 && statutport)
    {
        vref_4 = Chanel[3];
    }

    //Phoneme #1
    if (stat_btn == 0x08 && statutport)
    {
        if (Chanel[0] == vref_1)
        {
            tab->Bouge_Gauche();
            return true;
        }
    }

    //Phoneme #2
    if (stat_btn == 0x04 && statutport)
    {
        if (Chanel[1] == vref_2)
        {
            tab->Bouge_Haut();
            return true;
        }
    }

    //Phoneme #3
    if (stat_btn == 0x02 && statutport)
    {
        if (Chanel[2] == vref_3)
        {
            tab->Bouge_Bas();
            return true;
        }
    }

    //Phoneme #4
    if (stat_btn == 0x01 && statutport)
    {
        if (Chanel[3] == vref_4)
        {
            tab->Bouge_Droit();
            return true;
        }
    }

    Sleep(delai_boucle);
}