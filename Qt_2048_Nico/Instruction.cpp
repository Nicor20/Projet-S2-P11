/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 19/04/2021
* Nom de fichier : instruction.cpp
* Description : Permet de créer l'interface d'instruction
*/
#include "Instruction.h"

Instruction::Instruction(QWidget* parent) : QWidget(parent)
{
	setObjectName("Instruction");

	//Layout
	{
		gLayout = new QGridLayout(this);
		gLayout->setObjectName("gLayout");

		vLayout = new QVBoxLayout(gLayout->widget());
		vLayout->setObjectName("vLayout");

		gLayout->addLayout(vLayout, 0, 0, Qt::AlignCenter);
	}

	//Label
	{
        label_Titre = new QLabel("Instruction");
        label_Titre->setObjectName("label Titre");
        label_Titre->setAlignment(Qt::AlignCenter);
        QFont font1 = label_Titre->font();
        font1.setPointSize(75);
        font1.setBold(true);
        label_Titre->setFont(font1);

        
        QString text;
        text += "1. Enregistrement de phoneme\n";
        text += "   - Cliquer sur le bouton Enregistrer de l'accueil\n";
        text += "   - Cliquez sur les fleche pour changer de phoneme\n";
        text += "   - Cliquez sur le bouton 0 de la carte Fpga pour demarer l'enregistrement\n";
        text += "   - Prononcer le phoneme chosi jusqu'a ce que la barre de progression indique 100%\n";
        text += "   - Choisissez si vous voulex conserver l'enregistrement \n";
        text += "   - Repeter la procedure pour les 4 phoneme\n";
        text += "   - Cliquer sur le bouton Menu pour revenir a l'accueil\n";
        text += "\n";
        text += "2. Jouer au jeu\n";
        text += "   - Cliquez sur les fleche pour changer la taille de la grille\n";
        text += "   - Cliquer sur le bouton Jouer pour lancer une nouvelle partie\n";
        text += "   - Cliquer sur le bouton Charger pour charger la derniere partie en sauvegarde\n";
        text += "\n";
        text += "3. Menu Classement";
        text += "   - Cliquez sur le bouton classement de l'accueil\n";
        text += "   - Affiche les 10 meilleurs parties termine en memoire\n";
        text += "   - Cliquer sur le bouton Menu pour revenir a l'accueil\n";
        text += "\n";
        text += "4. En cours de Jeu";
        text += "   - Cliquer sur une des touche de l'ecran pour demarer la partie\n";
        text += "   - Bouger les case avec les touches w a s d du clavier\n";
        text += "   - Bouger les case avec les touches a l'ecran\n";
        text += "   - Bouger les case avec la voix en cliquant sur le bouton 0 de la carte Fpga et en prononcant le phoneme voulu durant 2 seconde \n";
        text += "   - Cliquer sur le bouton Menu pour revenir a l'accueil\n";


        label_Info = new QLabel(text,this);
        label_Info->setObjectName("label Info");

        QFont font2 = label_Info->font();
        font2.setPointSize(15);
        font2.setBold(false);
        label_Info->setFont(font2);

        label_Info->setAutoFillBackground(true);
        label_Info->setStyleSheet("QLabel { background-color : rgba(255,255,255,0.75); }");
        label_Info->setFrameStyle(QFrame::Box | QFrame::Plain);
        label_Info->setLineWidth(4);
        label_Info->setMidLineWidth(3);
        label_Info->setMargin(15);
	}

	//Bouton
	{
        bouton_Quitter = Create_Button("bouton Quitter", "Menu", 20, true);
        connect(bouton_Quitter, SIGNAL(clicked()), parent, SLOT(Bouton_Instruction_Quitter_Clicked()));
	}

	//vLayout
	{
        vLayout->addWidget(label_Titre);
        vLayout->addSpacerItem(new QSpacerItem(10, 10));
        vLayout->addWidget(label_Info);
        vLayout->addSpacerItem(new QSpacerItem(10, 10));
        vLayout->addWidget(bouton_Quitter);
	}
}

QPushButton* Instruction::Create_Button(QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer des boutons pour la classe accueil
    QPushButton* button = new QPushButton(text);
    button->setObjectName(nom);
    button->setFixedHeight(50);
    button->setAutoFillBackground(true);
    button->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }");
    button->setCursor(Qt::PointingHandCursor);

    QFont font = button->font();
    font.setPointSize(size);
    font.setBold(bold);
    button->setFont(font);
    return button;
}

QLabel* Instruction::Create_Label(QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer des label pour la classe accueil
    QLabel* label = new QLabel(text);
    label->setObjectName(nom);
    label->setAlignment(Qt::AlignCenter);

    QFont font = label->font();
    font.setPointSize(size);
    font.setBold(bold);
    label->setFont(font);

    return label;
}