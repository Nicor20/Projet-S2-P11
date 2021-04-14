#pragma once
#include "include.h"
#include "CommunicationFPGA.h"
#include <iostream>

struct Phoneme
{
	int val[4][2];
};

struct Lecture
{
	int pot[4];
};

class FPGA
{
public:
	FPGA();
	~FPGA();
	int Connected();
	QString Read();
	QString Verification();

private:
	//FPGA
	int nbLecture = 100;		//	Speed = 1 lecture par 10ms
	int nbSaved = 0;
	bool SaveOn = false;
	bool VerifOn = false;

	Phoneme valPhoneme[4];
	Lecture	*ListLecture = new Lecture[nbLecture];
	
	//QList<Lecture> ListLecture;
	//int val_verif[10][4];
	//int nb_save;
	

	BOOL statutport = false;

	int swt = 0;                            // donnee recue du FPGA
	int aff7sg_octet0 = 0;                  // octet 0 (droite) pour afficheur 7 segments
	int aff7sg_octet1 = 0;                  // octet 0 (droite) pour afficheur 7 segments
	int stat_btn = 0;                       // donnee recue du FPGA: statut et BTN
	int Chanel[4];                          // donnee converties recues du FPGA      
	const int delai_boucle = 10;            // delai d'attente ajouté dans la boucle de lecture en ms
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

	CommunicationFPGA *port;
};

