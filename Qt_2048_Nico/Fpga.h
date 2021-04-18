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

const int nbToRead = 100;
const int nbToRecord = 100;


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
    //  minimum - moyenne - maximum - pourcentage
    QString SBA[4];
    QString SBB[4];
    QString SBC[4];
    QString SBD[4];

    QString toString()
    {
        QString text = "SBA :\n";
        text += "Minumum : " + SBA[0] + "\n";
        text += "Moyenne : " + SBA[1] + "\n";
        text += "Maximum : " + SBA[2] + "\n";
        text += "Pourcentage : " + SBA[3] + "\n\n";
        text += "SBB :\n";
        text += "Minumum : " + SBB[0] + "\n";
        text += "Moyenne : " + SBB[1] + "\n";
        text += "Maximum : " + SBB[2] + "\n";
        text += "Pourcentage : " + SBB[3] + "\n\n";
        text += "SBC :\n";
        text += "Minumum : " + SBC[0] + "\n";
        text += "Moyenne : " + SBC[1] + "\n";
        text += "Maximum : " + SBC[2] + "\n";
        text += "Pourcentage : " + SBC[3] + "\n\n";
        text += "SBD :\n";
        text += "Minumum : " + SBD[0] + "\n";
        text += "Moyenne : " + SBD[1] + "\n";
        text += "Maximum : " + SBD[2] + "\n";
        text += "Pourcentage : " + SBD[3];
        return text;
    }
};

class Fpga
{
public:
    Fpga();
    ~Fpga();

    bool isConnected();
    QString Read();
    QString Verification();

    QString LectureRecord();
    QString AnalyzeRecord();

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
    
    Lecture ListLecture[nbToRead];

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

