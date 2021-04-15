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

    //Ajoute le Background
    QPixmap bk(":/Resources/BG.png");
    bk = bk.scaled(qApp->primaryScreen()->size(), Qt::IgnoreAspectRatio);
    QPalette pa;
    pa.setBrush(QPalette::Window, bk);
    this->setPalette(pa);
}

UI::~UI()
{

}

void UI::Load_Accueil()
{
    //Affiche l'accueil dans le main window
    accueil = new Accueil(&GridSize);
    connect(accueil->button_Jouer, &QPushButton::clicked, this, &UI::Button_clicked);
    connect(accueil->button_Charger, &QPushButton::clicked, this, &UI::Button_clicked);
    connect(accueil->button_Stats, &QPushButton::clicked, this, &UI::Button_clicked);
    connect(accueil->button_Quitter, &QPushButton::clicked, this, &UI::Button_clicked);
    this->setCentralWidget(accueil);
}

void UI::Load_Jeu(bool load)
{
    //Affiche le jeu dans le main window
    jeu = new Jeu(&GridSize, load);
    connect(jeu->button_Accueil, &QPushButton::clicked, this, &UI::Button_clicked);
    this->setCentralWidget(jeu);
}

void UI::Load_Stats()
{
    //Affiche le classement dans le main window
    stats = new Stats();
    connect(stats->button_Accueil, &QPushButton::clicked, this, &UI::Button_clicked);
    this->setCentralWidget(stats);
}

void UI::Button_clicked()
{
    //Détermine l'action a effectuer pour chaque boutons
    QString name = qobject_cast<QPushButton*>(sender())->objectName();

    if (name == "button_Accueil_Jouer")    //Accueil
    {
        Load_Jeu(false);
    }
    else if (name == "button_Accueil_Charger")  //Accueil
    {
        Load_Jeu(true);
    }
    else if (name == "button_Accueil_Stats")    //Accueil
    {
        Load_Stats();
    }
    else if (name == "button_Accueil_Quitter")  //Accueil
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
    else if (name == "button_Jeu_Accueil")
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
    else if (name == "button_Stats_Accueil")
    {
        Load_Accueil();
    }

}