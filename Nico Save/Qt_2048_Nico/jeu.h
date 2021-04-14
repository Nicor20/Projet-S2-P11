#ifndef JEU_H
#define JEU_H

#include <QString>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include "CommunicationFPGA.h"

struct Phoneme
{
    int val[4][2];
};

struct Lecture
{
    int pot[4];
};

class Jeu
{
public:
    Jeu(int size = 1, bool load = false);
    ~Jeu();

    //Jeu
    QString Bouge_Haut();
    QString Bouge_Droit();
    QString Bouge_Bas();
    QString Bouge_Gauche();

    //Grid
    int Get(int row, int column);
    int GetScore();
    int GetNbMove();
    int GetMax();
    int GetSize();

    //FPGA
    bool isConnected();
    QString Read();
    int waitTime();
    int readTime();

    //?????
    void SaveGame();
    void SaveStats(QString s);
    void ClearFile();
    QString Menu();

private:
    //Jeu
    int read_Time = 10;
    int wait_Time = 250;
    //bool Lecture_FPGA = false;
    bool Loaded;

    //Grid
    void Setup_New_Grid();
    void Setup_Loaded_Grid();
    QString Move_Up();
    QString Move_Right();
    QString Move_Down();
    QString Move_Left();
    void AddRandom();
    int random(int high);
    bool Lose();
    bool Win();

    int** grid;
    int ratio = 5;
    int GridSize;
    int score = 0;
    int NbMove = 0;
    QVector<int> twoFour;

    //FPGA
    void Setup_FPGA();
    QString Verification();

    int nbLecture = 100;		//	Speed = 1 lecture par 10ms
    int nbSaved = 0;
    bool SaveOn = false;
    bool VerifOn = false;

    Phoneme valPhoneme[4];
    Lecture* ListLecture = new Lecture[nbLecture];

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

#endif // JEU_H
