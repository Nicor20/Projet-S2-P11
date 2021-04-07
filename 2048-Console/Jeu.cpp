/*
	Auteur : Nicolas Cantin
*/
#include "Jeu.h"

Jeu::Jeu()
{
	window_to_show = "Accueil";
	mode_lecture = 2;
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
		else if (window_to_show == "Mode")
		{
			Menu_Mode();
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
			window_to_show = "Mode";
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
				window_to_show = "Mode";
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


		if (mode_lecture == 'c')
		{
			bool Good = false;
			char input;
			while (Good == false)
			{
				input = _getch();
				Good = Touche_Jeu(input);
			}
		}
		else if (mode_lecture == 'v')
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

void Jeu::Menu_Mode()
{
	system("cls");

	cout << "Voulez-vous jouer avec la voix ou avec un clavier?" << endl;
	cout << endl;
	cout << "C = Clavier" << endl;
	cout << "V = Voix" << endl;
	cout << "Q = Quitter" << endl;

	// Lire la réponse
	bool Good = false;
	char input;

	while (Good == false)
	{
		input = _getch();

		if (input == 'C' || input == 'c')
		{
			mode_lecture = 'c';
			window_to_show = "Jeu";
			Good = true;
		}
		else if (input == 'V' || input == 'v')
		{
			Setup_FPGA();
			mode_lecture = 'v';
			window_to_show = "Jeu";
			Good = true;
		}
		else if (input == 'Q' || input == 'q')
		{
			window_to_show = "Accueil";
			Good = true;
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
	else
	{
		return false;
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


	statutport = port.ecrireRegistre(nreg_ecri_led, 0x00);          // envoyer valeur '1' sur led(0) du FPGA : signal pour passer en mode connecté
	if (!port.estOk())
	{
		cout << port.messageErreur() << endl;
	}

	cout << endl << dec << "Delai d'attente ajoute dans a boucle de lecture : " << delai_boucle << " ms" << endl;

	cout << setfill('0') << setw(4) << hex << showbase << internal << endl;
	cout << "   Stat_BTN,  SWT,  compt_t,      ch[0], ch[1], ch[2], ch[3]" << endl;

	//setup phoneme
	Phoneme temp;

	//Phoneme 'a'
	temp.val[0][0] = 60;		//min pot1
	temp.val[0][1] = 90;		//max pot1
	temp.val[1][0] = 520;		//min pot2
	temp.val[1][1] = 610;		//max pot2
	temp.val[2][0] = 20;		//min pot3
	temp.val[2][1] = 60;		//max pot3
	temp.val[3][0] = 90;		//min pot4
	temp.val[3][1] = 170;		//max pot4
	val_ref[0] = temp;

	//Phoneme 'e'
	temp.val[0][0] = 180;		//min pot1
	temp.val[0][1] = 270;		//max pot1
	temp.val[1][0] = 60;		//min pot2
	temp.val[1][1] = 100;		//max pot2
	temp.val[2][0] = 300;		//min pot3
	temp.val[2][1] = 530;		//max pot3
	temp.val[3][0] = 130;		//min pot4
	temp.val[3][1] = 240;		//max pot4
	val_ref[1] = temp;

	//Phoneme 'eu'
	temp.val[0][0] = 550;		//min pot1
	temp.val[0][1] = 830;		//max pot1
	temp.val[1][0] = 180;		//min pot2
	temp.val[1][1] = 280;		//max pot2
	temp.val[2][0] = 240;		//min pot3
	temp.val[2][1] = 390;		//max pot3
	temp.val[3][0] = 40;		//min pot4
	temp.val[3][1] = 110;		//max pot4
	val_ref[2] = temp;

	//Phoneme 'i'
	temp.val[0][0] = 500;		//min pot1
	temp.val[0][1] = 780;		//max pot1
	temp.val[1][0] = 0;			//min pot2
	temp.val[1][1] = 60;		//max pot2
	temp.val[2][0] = 430;		//min pot3
	temp.val[2][1] = 615;		//max pot3
	temp.val[3][0] = 585;		//min pot4
	temp.val[3][1] = 810;		//max pot4
	val_ref[3] = temp;

	/*	
	* Phoneme 'a'
	* pot1 = 0x16
	* pot2 = 0x8D
	* pot3 = 0x0A
	* pot4 = 0x20
	* 
	* Phoneme 'e'
	* pot1 = 0x38
	* pot2 = 0x14
	* pot3 = 0x68
	* pot4 = 0x2E
	* 
	* Phoneme 'eu'
	* pot1 = 0xAD
	* pot2 = 0x3A
	* pot3 = 0x4F
	* pot4 = 0x16
	* 
	* Phoneme 'i'
	* pot1 = 0xA0
	* pot2 = 0x08
	* pot3 = 0x83
	* pot4 = 0xAE
	*/
	
}

bool Jeu::Lecture_FPGA()
{
	bool move_bon = false;

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
		statutport = port.ecrireRegistre(nreg_ecri_led, swt);
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


	if (statutport)
	{
		//Ajuster les pot
		if (swt == 0x80)
		{//#1
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x01);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[0]);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		}
		else if (swt == 0x40)
		{//#2
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x02);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[1]);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		}
		else if (swt == 0x20)
		{//#3
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x03);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[2]);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		}
		else if (swt == 0x10)
		{//#4
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x04);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[3]);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		}
		else
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x00);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, 0x00);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x00);
		}

		if (stat_btn == 0x11 && swt == 0x00 && save_val == false)
		{
			save_val = true;
			nb_saved = 0;
		}

		if (save_val == true && nb_saved < nb_lecture_voulu-1)
		{
			val_verif[nb_saved][0] = Chanel[0];
			val_verif[nb_saved][1] = Chanel[1];
			val_verif[nb_saved][2] = Chanel[2];
			val_verif[nb_saved][3] = Chanel[3];
			//cout << "Lecture #" << to_string(nb_saved + 1) << endl;
			nb_saved++;
		}
		else if (save_val == true && nb_saved == nb_lecture_voulu-1)
		{
			val_verif[nb_saved][0] = Chanel[0];
			val_verif[nb_saved][1] = Chanel[1];
			val_verif[nb_saved][2] = Chanel[2];
			val_verif[nb_saved][3] = Chanel[3];
			
			//cout << "Lecture #" << to_string(nb_saved + 1) << endl;
			cout << "Start Verif" << endl;
			move_bon = Verification();
			Sleep(1000);
			save_val = false;
		}


		/*
		// Mémoire phonem 1
		if (swt == 0x82)
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x01);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, vref_1);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		}
		//Ajustement pot #1
		else if (swt == 0x80 || swt == 0x81)
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x01);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[0]);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);

			if (stat_btn == 0x11 && swt == 0x80 && Chanel[0] == vref_1)
			{	//Phoneme #1
				tab->Bouge_Gauche();
				return true;
			}
			else if (stat_btn == 0x11 && swt == 0x81)
			{	//Sauvegarde des valeurs pot 1
				vref_1 = Chanel[0];
				cout << "Sauvegarde val 1" << endl;
			}
		}
		// Mémoire phonem 2
		else if (swt == 0x42)
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x02);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, vref_2);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		}
		//Ajustement pot #2
		else if (swt == 0x40 || swt == 0x41)
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x02);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[1]);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);

			if (stat_btn == 0x11 && swt == 0x40 && Chanel[1] == vref_2)
			{	//Phoneme #2
				tab->Bouge_Haut();
				return true;
			}
			else if (stat_btn == 0x11 && swt == 0x41)
			{	//Sauvegarde des valeurs pot 2
				vref_2 = Chanel[1];
				cout << "Sauvegarde val 2" << endl;
			}
		}
		// Mémoire phonem 3
		else if (swt == 0x22)
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x03);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, vref_3);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		}
		//Ajustement pot #3
		else if (swt == 0x20 || swt == 0x21)
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x03);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[2]);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);

			if (stat_btn == 0x11 && swt == 0x20 && Chanel[2] == vref_3)
			{	//Phoneme #3
				tab->Bouge_Bas();
				return true;
			}
			else if (stat_btn == 0x11 && swt == 0x21)
			{	//Sauvegarde des valeurs pot 3
				vref_3 = Chanel[2];
				cout << "Sauvegarde val 3" << endl;
			}
		}
		// Mémoire phonem 4
		else if (swt == 0x12)
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x04);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, vref_4);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		}
		// Ajustement pot #4
		else if (swt == 0x10 || swt == 0x11)
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x04);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, Chanel[3]);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);

			if (stat_btn == 0x11 && swt == 0x10 && Chanel[3] == vref_4)
			{	//Phoneme #4
				tab->Bouge_Droit();
				return true;
			}
			else if (stat_btn == 0x11 && swt == 0x11)
			{	//Sauvegarde des valeurs pot 4
				vref_4 = Chanel[3];
				cout << "Sauvegarde val 4" << endl;
			}
		}
		else
		{
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x00);
			statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, 0x00);
			statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x00);
		}
		*/
	}

	Sleep(delai_boucle);
	return move_bon;
}

bool Jeu::Verification()
{
	int pointage[4] = { 0 };

	for (int a = 0; a < nb_lecture_voulu; a++) // lecture #1 a #10
	{
		for (int b = 0; b < 4; b++)// pot #1 a #4
		{
			for (int c = 0; c < 4; c++) //Phonème #1 a #4
			{
				if ((val_verif[a][b]*4) >= val_ref[c].val[b][0] && (val_verif[a][b]*4) <= val_ref[c].val[b][1])
				{
					//cout << dec << "l=" << to_string(a + 1) << " P=" << to_string(b + 1) << " h=" << to_string(c + 1) << " val=";
					//cout << hex << to_string(val_verif[a][b]) << endl;
					pointage[c]++;
				}
			}
		}
	}


	//Trouver le correspondant
	int max = 0;
	int num = 0;
	int seuil = floor((4.0 * nb_lecture_voulu) * 0.8);
	for (int i = 0; i < 4; i++)
	{
		if (pointage[i] >= max)
		{
			num = i+1;
			max = pointage[i];
		}
	}
	
	cout << "Nombre de bon = " << to_string(max) << endl;
	if (num == 1 && max >= seuil)
	{
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, num);
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, pointage[num-1]);
		statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		tab->Bouge_Haut();
		return true;
	}
	else if (num == 2 && max >= seuil)
	{
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, num);
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
		statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		tab->Bouge_Droit();
		return true;
	}
	else if (num == 3 && max >= seuil)
	{
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, num);
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
		statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		tab->Bouge_Bas();
		return true;
	}
	else if (num == 4 && max >= seuil)
	{
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, num);
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
		statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0x04);
		tab->Bouge_Gauche();
		return true;
	}
	else
	{
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, 0x0E);
		statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, 0xE0);
		statutport = port.ecrireRegistre(nreg_ecri_aff7dot, 0);
		cout << "Erreur de lecture" << endl;
		return false;
	}
}