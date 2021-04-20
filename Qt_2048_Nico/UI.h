/*
* Nom des cr�ateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de cr�ation : 05/04/2021 � 19/04/2021
* Nom de fichier : UI.h
* Description : MainWindow qui permet d'afficher les diff�rentes widget comme accueil, Jeu, et Classement
*/

#ifndef UI_H
#define UI_H

#include "needed.h"
#include "accueil.h"
#include "jeu.h"
#include "stats.h"
#include "Record.h"
#include "Instruction.h"

class UI : public QMainWindow
{
    Q_OBJECT
public:
    UI();
    ~UI();

    void resizeEvent(QResizeEvent* event);

    void Load_Accueil();
    void Load_Jeu(bool load);
    void Load_Stats();
    void Load_Record();
    void Load_Instruction();

private slots:
    void Bouton_Accueil_Jouer_Clicked();
    void Bouton_Accueil_Charger_Clicked();
    void Bouton_Accueil_Classement_Clicked();
    void Bouton_Accueil_Instruction_Clicked();
    void Bouton_Accueil_Record_Clicked();
    void Bouton_Accueil_Quitter_Clicked();
    void Bouton_Jeu_Quitter_Clicked();
    void Bouton_Stats_Quitter_Clicked();
    void Bouton_Instruction_Quitter_Clicked();
    void Bouton_Record_Quitter_Clicked();

private:
    Accueil* accueil;
    Jeu* jeu;
    Stats* stats;
    Record* record;
    Instruction* instruction;

    int current;

    int GridSize = 4;
};

#endif // UI_H

