/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 15/04/2021
* Nom de fichier : jeu.h
* Description : Permet de créer l'interface de jeu et de gérer son fonctionnement et ces intéractions
*/

#ifndef JEU_H
#define JEU_H

#include "needed.h"
#include "Fpga.h"
#include "Grid.h"

class Jeu : public QWidget
{
    Q_OBJECT
public:
    Jeu(QWidget* parent, int* size, bool load = false);
    ~Jeu();

    //Jeu
    void Refresh_Grid();

    void keyPressEvent(QKeyEvent* event);
    void resizeEvent(QResizeEvent* event);

    void CheckMove(QString s);
    void SaveGame();
    void SaveStats(QString s);
    void ClearFile();
    QString Menu();
    
    
    QPushButton* Create_Button(QString nom, QString text, int size, bool bold);
    QLabel* Create_Label(QString nom, QString text, int size, bool bold);
    QLabel* Create_Custom_Label(QString nom, QString text, int size, bool bold);
    void Customize_Label(QLabel* label);

private slots:
    void FPGA_Timer();

    void Bouton_Haut_Clicked();
    void Bouton_Droit_Clicked();
    void Bouton_Bas_Clicked();
    void Bouton_Gauche_Clicked();

    void Bouton_Pressed();
    void Bouton_Released();

private:
    QGridLayout* gLayout1;
    QGridLayout* gLayout2;
    QFrame* frame;

    QLabel* label_Titre;
    QLabel* label_Score;
    QLabel* label_NbMove;
    QLabel* label_Max;
    QLabel*** labelGrid;

    QPushButton* Bouton_Haut;
    QPushButton* Bouton_Droit;
    QPushButton* Bouton_Bas;
    QPushButton* Bouton_Gauche;
    QPushButton* Bouton_Quitter;

    //Jeu
    QTimer* Timer;
    bool Loaded;
    int read_Time = 10;
    int wait_Time = 250;
    
    int* GridSize;
    QString GameState;

    Grid* grid;
    Fpga* fpga;
};

#endif // JEU_H
