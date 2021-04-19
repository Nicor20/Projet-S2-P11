/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 15/04/2021
* Nom de fichier : Fpga.h
* Description : Permet de gérer la lecture de la carte Fpga
*/
#ifndef FPGA_H
#define FPGA_H

#include "needed.h"
#include "CommunicationFPGA.h"

const int nbToRead = 200;
const int nbToRecord = 200;


struct Phoneme
{
    int val[4][2];
};

struct Lecture
{
    int pot[4];
};

struct RecordStruct
{
    QString moyenne[4];

    QString toString()
    {
        QString text;
        text += "Moyenne SBA : " + moyenne[0] + "\n";
        text += "Moyenne SBB : " + moyenne[1] + "\n";
        text += "Moyenne SBC : " + moyenne[2] + "\n";
        text += "Moyenne SBD : " + moyenne[3];

        return text;
    }
};

class Fpga
{
public:
    Fpga();
    ~Fpga();

    void CreatePhoneme();

    bool isConnected();
    QString Read();
    QString Verification();

    QString LectureRecord();
    QString AnalyzeRecord();

    int GetNbToRecord();

    void SaveRecord(QString file);

    bool SaveOn = false;
    bool VerifOn = false;
    int nbRead = 0;

    bool RecordOn = false;
    bool AnalyzeOn = false;
    int nbRecord = 0;
    RecordStruct RecordValue;


private:
    //Read
    int SBA_L[nbToRead];
    int SBB_L[nbToRead];
    int SBC_L[nbToRead];
    int SBD_L[nbToRead];

    Lecture ListLecture[nbToRead];

    RecordStruct ListPhoneme[4];


    //Record
    int SBA[nbToRecord];
    int SBB[nbToRecord];
    int SBC[nbToRecord];
    int SBD[nbToRecord];
    
    


    Phoneme valPhoneme[4];
    

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

    CommunicationFPGA* port;

};
#endif // FPGA_H

