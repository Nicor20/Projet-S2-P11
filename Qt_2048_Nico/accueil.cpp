/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 19/04/2021
* Nom de fichier : accueil.cpp
* Description : Permet de créer l'interface de l'accueil et de gérer son fonctionnement et ces intéractions
*/
#include "accueil.h"


Accueil::Accueil(QWidget* parent, int* size) : QWidget(parent) , GridSize(size)
{
    //Permet de créer les éléments de l'interface d'accueil
    setObjectName("widget_Accueil");

    //Layout
    {
        gLayout1 = new QGridLayout(this);
        gLayout1->setObjectName("gLayout1");
        
        gLayout2 = new QGridLayout(gLayout1->widget());
        gLayout2->setObjectName("gLayout2");
        gLayout2->setVerticalSpacing(15);

        gLayout1->addLayout(gLayout2, 0, 0, Qt::AlignCenter);
    }
    
    //Label
    {
        label_Titre = Create_Label(gLayout2->widget(), "label_Titre", "Super 2048", 80, true);

        label_Sub = Create_Label(gLayout2->widget(), "label_Sub", "Taille de la grille", 30, true);

        label_GridSize = Create_Label(gLayout2->widget(), "label_GridSize", QString::number(*GridSize) + " x " + QString::number(*GridSize), 25, true);
        label_GridSize->setAutoFillBackground(true);
        label_GridSize->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }");
        label_GridSize->setFrameStyle(QFrame::Box | QFrame::Plain);
        label_GridSize->setLineWidth(4);
        label_GridSize->setMidLineWidth(3);
    }
    
    //Button
    {
        Bouton_Moin = Create_Button(gLayout2->widget(), "Bouton Moin", "<", 20, true);
        connect(Bouton_Moin, SIGNAL(clicked()), this, SLOT(Bouton_Moin_Clicked()));
        connect(Bouton_Moin, SIGNAL(pressed()), this, SLOT(Bouton_Pressed()));
        connect(Bouton_Moin, SIGNAL(released()), this, SLOT(Bouton_Released()));

        Bouton_Plus = Create_Button(gLayout2->widget(), "Bouton Plus", ">", 20, true);
        connect(Bouton_Plus, SIGNAL(clicked()), this, SLOT(Bouton_Plus_Clicked()));
        connect(Bouton_Plus, SIGNAL(pressed()), this, SLOT(Bouton_Pressed()));
        connect(Bouton_Plus, SIGNAL(released()), this, SLOT(Bouton_Released()));

        Bouton_Jouer = Create_Button(gLayout2->widget(), "Bouton Jouer", "&Jouer", 20, true);
        connect(Bouton_Jouer, SIGNAL(clicked()), parent, SLOT(Bouton_Accueil_Jouer_Clicked()));

        Bouton_Charger = Create_Button(gLayout2->widget(), "Bouton Charger", "&Charger", 20, true);
        connect(Bouton_Charger, SIGNAL(clicked()), parent, SLOT(Bouton_Accueil_Charger_Clicked()));

        Bouton_Classement = Create_Button(gLayout2->widget(), "Bouton Classement", "&Classement", 20, true);
        connect(Bouton_Classement, SIGNAL(clicked()), parent, SLOT(Bouton_Accueil_Classement_Clicked()));

        Bouton_Instruction = Create_Button(gLayout2->widget(), "Bouton Instruction", "&Instruction", 20, true);
        connect(Bouton_Instruction, SIGNAL(clicked()), parent, SLOT(Bouton_Accueil_Instruction_Clicked()));

        Bouton_Record = Create_Button(gLayout2->widget(), "Bouton Record", "&Enregistrement", 20, true);
        connect(Bouton_Record, SIGNAL(clicked()), parent, SLOT(Bouton_Accueil_Record_Clicked()));

        Bouton_Quitter = Create_Button(gLayout2->widget(), "Bouton Quitter", "&Quitter", 20, true);
        connect(Bouton_Quitter, SIGNAL(clicked()), parent, SLOT(Bouton_Accueil_Quitter_Clicked()));
    }
    
    //gLayout2
    {
        gLayout2->addWidget(label_Titre, 0, 0, 1, 3);
        gLayout2->addWidget(label_Sub, 1, 0, 1, 3);
        gLayout2->addWidget(Bouton_Moin, 2, 0);
        gLayout2->addWidget(label_GridSize, 2, 1);
        gLayout2->addWidget(Bouton_Plus, 2, 2);

        gLayout2->addWidget(Bouton_Jouer, 3, 0, 1, 3);
        gLayout2->addWidget(Bouton_Charger, 4, 0, 1, 3);
        gLayout2->addWidget(Bouton_Classement, 5, 0, 1, 3);
        gLayout2->addWidget(Bouton_Instruction, 6, 0, 1, 3);
        gLayout2->addWidget(Bouton_Record, 7, 0, 1, 3);
        gLayout2->addWidget(Bouton_Quitter, 8, 0, 1, 3);
    }

    CheckFiles();
}

Accueil::~Accueil()
{

}

void Accueil::CheckFiles()
{
    QString FileName[6] = { "Game.2048","Stats.2048","PH_A.2048","PH_E.2048","PH_EU.2048","PH_I.2048" };
    bool Good[6] = { false,false,false,false,false,false };

    //Check
    for (int i = 0; i < 6; i++)
    {
        QFile file(FileName[i]);

        if (file.exists())
        {
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            
            QTextStream in(&file);
            if (in.readLine().length() > 5)
            {
                Good[i] = true;
            }
            file.close();
        }
        else
        {
            QFile file(FileName[i]);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream stream(&file);
            if (i == 0 || i == 1)
            {
                stream << "";
            }
            else
            {
                stream << "0-0-0-0";
            }
            
            file.close();
        }
    }

    //Bouton Charger
    if (Good[0] == true)
    {
        Bouton_Charger->setEnabled(true);
    }
    else
    {
        Bouton_Charger->setEnabled(false);
    }

    //Bouton Classement
    if (Good[1] == true)
    {
        Bouton_Classement->setEnabled(true);
    }
    else
    {
        Bouton_Classement->setEnabled(false);
    }
}

void Accueil::resizeEvent(QResizeEvent* event)
{
    //label_Titre->setText("(" + QString::number(this->width()) + " , " + QString::number(this->height()) + ")");
}

#pragma region Slots

void Accueil::Bouton_Moin_Clicked()
{
    if (*GridSize > 3)
    {
        *GridSize = *GridSize - 1;
    }
    else
    {
        *GridSize = 8;
    }

    label_GridSize->setText(QString::number(*GridSize) + " x " + QString::number(*GridSize));
}

void Accueil::Bouton_Plus_Clicked()
{
    if (*GridSize < 8)
    {
        *GridSize = *GridSize + 1;
    }
    else
    {
        *GridSize = 3;
    }

    label_GridSize->setText(QString::number(*GridSize) + " x " + QString::number(*GridSize));
}

void Accueil::Bouton_Pressed()
{
    //SLOT pour quand certains boutons de l'accueil sont presser
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(211,211,211); }");   //Dark
}

void Accueil::Bouton_Released()
{
    //SLOT pour quand certains boutons de l'accueil sont relacher
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }"); //light
}

#pragma endregion

QPushButton* Accueil::Create_Button(QWidget* parent, QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer des boutons pour la classe accueil
    QPushButton* button = new QPushButton(text, parent);
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

QLabel* Accueil::Create_Label(QWidget* parent, QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer des label pour la classe accueil
    QLabel* label = new QLabel(text,parent);
    label->setObjectName(nom);
    label->setAlignment(Qt::AlignCenter);

    QFont font = label->font();
    font.setPointSize(size);
    font.setBold(bold);
    label->setFont(font);

    return label;
}

