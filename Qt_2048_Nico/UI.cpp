/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 15/04/2021
* Nom de fichier : UI.cpp
* Description : MainWindow qui permet d'afficher les différentes widget comme accueil, Jeu, et Classement
*/

#include "UI.h"

UI::UI()
{
    //Création du main window
    this->setWindowTitle("Super 2048");
    this->setObjectName("UI");

    Load_Accueil();
}

UI::~UI()
{

}

void UI::resizeEvent(QResizeEvent* event)
{
    QPixmap bk(":/Resources/BG.png");
    //QPixmap bk(":/Resources/LOGO_SUPER2048.jpg");
    bk = bk.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette pa;
    pa.setBrush(QPalette::Window, bk);
    this->setPalette(pa);
}

void UI::Load_Accueil()
{
    //Affiche l'accueil dans le main window
    accueil = new Accueil(this, &GridSize);
    setCentralWidget(accueil);
}

void UI::Load_Jeu(bool load)
{
    //Affiche le jeu dans le main window
    jeu = new Jeu(this, &GridSize, load);
    setCentralWidget(jeu);
}

void UI::Load_Stats()
{
    //Affiche le classement dans le main window
    stats = new Stats(this);
    setCentralWidget(stats);
}

void UI::Load_Record()
{
    record = new Record(this);
    setCentralWidget(record);
}

void UI::Load_Instruction()
{
    instruction = new Instruction(this);
    setCentralWidget(instruction);
}

void UI::Bouton_Accueil_Jouer_Clicked()
{
    Load_Jeu(false);
}

void UI::Bouton_Accueil_Charger_Clicked()
{
    Load_Jeu(true);
}

void UI::Bouton_Accueil_Classement_Clicked()
{
    Load_Stats();
}

void UI::Bouton_Accueil_Instruction_Clicked()
{
    Load_Instruction();
}

void UI::Bouton_Accueil_Record_Clicked()
{
    Load_Record();
}

void UI::Bouton_Accueil_Quitter_Clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Super 2048");

    QFont font = msgBox.font();
    font.setPointSize(15);
    font.setBold(false);
    msgBox.setFont(font);

    msgBox.setText("Voulez vous vraiment quitter l'application?");

    QPushButton* boutonOui = msgBox.addButton("Oui", QMessageBox::YesRole);
    QPushButton* boutonNon = msgBox.addButton("Non", QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton() == boutonOui)
    {
        this->close();
    }
}

void UI::Bouton_Jeu_Quitter_Clicked()
{
    QString rep = jeu->Menu();

    if (rep == "Fin" || rep == "Exit")
    {
        Load_Accueil();
    }
    else if (rep == "Cancel Exit")
    {
        //Cancel
    }
}

void UI::Bouton_Stats_Quitter_Clicked()
{
    Load_Accueil();
}

void UI::Bouton_Instruction_Quitter_Clicked()
{
    Load_Accueil();
}

void UI::Bouton_Record_Quitter_Clicked()
{
    if (record->Menu() == true)
    {
        Load_Accueil();
    }
}