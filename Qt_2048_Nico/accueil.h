/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 15/04/2021
* Nom de fichier : accueil.h
* Description : Permet de créer l'interface de l'accueil et de gérer son fonctionnement et ces intéractions
*/
#ifndef ACCUEIL_H
#define ACCUEIL_H

#include "needed.h"

class Accueil : public QWidget
{
    Q_OBJECT
public:
    Accueil(QWidget* parent, int* size);
    ~Accueil();

    void resizeEvent(QResizeEvent* event);
    
    void CheckFiles();

    QPushButton* Create_Button(QWidget* parent, QString nom, QString text, int size, bool bold);
    QLabel* Create_Label(QWidget* parent, QString nom, QString text, int size, bool bold);

private slots:
    void Bouton_Moin_Clicked();
    void Bouton_Plus_Clicked();
    void Bouton_Pressed();
    void Bouton_Released();

private:
    QGridLayout* gLayout1;
    QGridLayout* gLayout2;

    QLabel* label_Titre;
    QLabel* label_Sub;
    QLabel* label_GridSize;

    QPushButton* Bouton_Moin;
    QPushButton* Bouton_Plus;
    QPushButton* Bouton_Jouer;
    QPushButton* Bouton_Charger;
    QPushButton* Bouton_Classement;
    QPushButton* Bouton_Instruction;
    QPushButton* Bouton_Record;
    QPushButton* Bouton_Quitter;

    int* GridSize;
};

#endif // ACCUEIL_H
