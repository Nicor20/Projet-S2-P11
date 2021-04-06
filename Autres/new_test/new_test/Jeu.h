
/*
	Auteur : Nicolas Cantin
*/
#include <stdlib.h>

#include <conio.h>
#include <iomanip>

#include <ctime>
#include "Tableau.h"
#include "CommunicationFPGA.h"

//using namespace std;

class Jeu
{
public:
	Jeu();
	~Jeu();

	void Run();

	void Menu_Accueil();

	void Menu_Jeu();

	void Menu_Load();

	void Load(string st);

	void Menu_Sauvegarde();

	void Menu_Stats();

	void Menu_Mode();

	void Setup_Grid(int nb);

	bool Touche_Jeu(char ch);

	void Setup_FPGA();
	bool Lecture_FPGA();


private:
	//Grille de jeu
	Tableau* tab = new Tableau(3);

	//Boucle pour Run
	bool run = true;

	bool Show_jeu = true;

	string window_to_show;

	char mode_lecture;


	//FPGA

	int vref_1 = 0x00;
	int vref_2 = 0x00;
	int vref_3 = 0x00;
	int vref_4 = 0x00;

	BOOL statutport = false;

	int swt = 0;                            // donnee recue du FPGA
	int aff7sg_octet0 = 0;                  // octet 0 (droite) pour afficheur 7 segments
	int aff7sg_octet1 = 0;                  // octet 0 (droite) pour afficheur 7 segments
	int stat_btn = 0;                       // donnee recue du FPGA: statut et BTN
	int Chanel[4];                          // donnee converties recues du FPGA      
	const int delai_boucle = 100;            // delai d'attente ajouté dans la boucle de lecture en ms
	int canal_a_afficher = 0;               // donnee recue du FPGA
	int indice_canal_a_afficher = 0;

	unsigned const int nreg_lect_stat_btn = 0;  // fpga -> PC  Statut et BTN lus FPGA -> PC
	unsigned const int nreg_lect_swt = 1;       // fpga -> PC  SWT lus FPGA -> PC
	unsigned const int nreg_lect_can0 = 3;      // fpga -> PC  canal 0 lus FPGA -> PC
	unsigned const int nreg_lect_can1 = 4;      // fpga -> PC  canal 1 lus FPGA -> PC
	unsigned const int nreg_lect_can2 = 5;      // fpga -> PC  canal 2 lus FPGA -> PC
	unsigned const int nreg_lect_can3 = 6;      // fpga -> PC  canal 3 lus FPGA -> PC
	unsigned const int nreg_ecri_aff7sg0 = 7;   // PC -> fpga (octet 0  aff.7 seg.)
	unsigned const int nreg_ecri_aff7sg1 = 8;   // PC -> fpga (octet 1  aff.7 seg.)
	unsigned const int nreg_ecri_aff7dot = 9;   // PC -> fpga (donnees dot-points)
	unsigned const int nreg_ecri_led = 10;      // PC -> fpga (donnees leds)

	CommunicationFPGA port;
};