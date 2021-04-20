/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 19/04/2021
* Nom de fichier : jeu.cpp
* Description : Permet de créer l'interface de jeu et de gérer son fonctionnement et ces intéractions
*/

#include "jeu.h"

Jeu::Jeu(QWidget* parent, int* size, bool load) : QWidget(parent), GridSize(size) , Loaded(load)
{
    //Permet de créer les éléments de l'interface d'accueil
    grid = new Grid(size, load);
    fpga = new Fpga();
    
    this->setObjectName("widget_Jeu");

    //Layout & frame
    {
        gLayout1 = new QGridLayout(this);
        gLayout1->setObjectName("gLayout1");
        this->setLayout(gLayout1);

        gLayout2 = new QGridLayout(gLayout1->widget());
        gLayout2->setObjectName("gLayout2");


        gLayout_Game = new QGridLayout(gLayout2->widget());
        gLayout_Game->setObjectName("gLayout_Game");

        gLayout_Button = new QGridLayout(gLayout2->widget());
        gLayout_Button->setObjectName("gLayout_Game");

        gLayout1->addLayout(gLayout2, 0, 0, Qt::AlignCenter);
    }
    
    //Label Grid
    {
        labelGrid = new QLabel * *[*size];
        for (int i = 0; i < *size; i++)
        {
            labelGrid[i] = new QLabel * [*size];
        }

        for (int x = 0; x < *size; x++)
        {
            for (int y = 0; y < *size; y++)
            {
                labelGrid[x][y] = Create_Game_Label("label" + QString::number((x * 4) + y), QString::number(grid->Get(x, y)), 15, true);
            }
        }
    }
    
    //Labels
    {
        label_Score = Create_Custom_Label("Label Score", "Score\n" + QString::number(grid->GetScore()), 15, true);

        label_NbMove = Create_Custom_Label("Label NbMove", "Nb Move\n" + QString::number(grid->GetNbMove()), 15, true);

        label_Max = Create_Custom_Label("Label Max", "Max\n" + QString::number(grid->GetMax()), 15, true);

        label_Status = Create_Label("Label Status", "", 20, true);
    }
    
    //Buttons
    {
        Bouton_Haut = Create_Button("Bouton Haut", "Haut (A)", 20, true);
        connect(Bouton_Haut, SIGNAL(clicked()), this, SLOT(Bouton_Haut_Clicked()));
        connect(Bouton_Haut, SIGNAL(pressed()), this, SLOT(Bouton_Pressed()));
        connect(Bouton_Haut, SIGNAL(released()), this, SLOT(Bouton_Released()));

        Bouton_Droit = Create_Button("Bouton Droit", "Droit (E)", 20, true);
        connect(Bouton_Droit, SIGNAL(clicked()), this, SLOT(Bouton_Droit_Clicked()));
        connect(Bouton_Droit, SIGNAL(pressed()), this, SLOT(Bouton_Pressed()));
        connect(Bouton_Droit, SIGNAL(released()), this, SLOT(Bouton_Released()));

        Bouton_Bas = Create_Button("Bouton Bas", "Bas (EU)", 20, true);
        connect(Bouton_Bas, SIGNAL(clicked()), this, SLOT(Bouton_Bas_Clicked()));
        connect(Bouton_Bas, SIGNAL(pressed()), this, SLOT(Bouton_Pressed()));
        connect(Bouton_Bas, SIGNAL(released()), this, SLOT(Bouton_Released()));

        Bouton_Gauche = Create_Button("Bouton Gauche", "Gauche (I)", 20, true);
        connect(Bouton_Gauche, SIGNAL(clicked()), this, SLOT(Bouton_Gauche_Clicked()));
        connect(Bouton_Gauche, SIGNAL(pressed()), this, SLOT(Bouton_Pressed()));
        connect(Bouton_Gauche, SIGNAL(released()), this, SLOT(Bouton_Released()));

        Bouton_Quitter = Create_Button("Bouton Quitter", "Menu", 20, true);
        connect(Bouton_Quitter, SIGNAL(clicked()), parent, SLOT(Bouton_Jeu_Quitter_Clicked()));
    }

    //gLayout_Game
    {
        for (int x = 0; x < *size; x++)
        {
            for (int y = 0; y < *size; y++)
            {
                gLayout_Game->addWidget(labelGrid[x][y],x, y);
            }
        }

        frame = new QFrame(this);
        frame->setFrameStyle(QFrame::Box | QFrame::Plain);
        frame->setLineWidth(5);
        frame->setLayout(gLayout_Game);

    }

    //gLayout_Button
    {
        gLayout_Button->addWidget(Bouton_Haut, 0, 1);
        gLayout_Button->addWidget(Bouton_Gauche,1, 0);
        gLayout_Button->addWidget(Bouton_Bas, 1,1);
        gLayout_Button->addWidget(Bouton_Droit,1,2);
    }
    
    //gLayout2
    {
        gLayout2->addWidget(label_Score, 0, 0);
        gLayout2->addWidget(label_NbMove,0, 1);
        gLayout2->addWidget(label_Max, 0, 2);
        gLayout2->addWidget(frame, 1, 0, 1, 3);
        gLayout2->addWidget(label_Status, 2, 0, 1, 3);
        gLayout2->addLayout(gLayout_Button, 3, 0, 1, 3);
        gLayout2->addWidget(Bouton_Quitter, 4, 0, 1, 3);

        gLayout2->setVerticalSpacing(10);
    }

    //Timer
    {
        Timer = new QTimer();
        connect(Timer, SIGNAL(timeout()), this, SLOT(FPGA_Timer()));

        if (fpga->isConnected())
        {
            Status("Fpga connecte");
            Timer->start(wait_Time);
        }
        else
        {
            Status("Fpga non connecte");
        }
    }
    
}

Jeu::~Jeu()
{
    delete fpga;
    delete grid;
}

void Jeu::CheckMove(QString s)
{
    //Vérifie le résultat du mouvement et traite la réponse
    Status(s);
    if (s == "Gagne")
    {
        GameState = "Gagne";
        Refresh_Grid();
        SaveStats(s);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Super 2048");

        QFont font = msgBox.font();
        font.setPointSize(15);
        font.setBold(false);
        msgBox.setFont(font);

        msgBox.setText("Vous avez gagné!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        
        msgBox.exec();

        Bouton_Quitter->animateClick();
    }
    else if (s == "Perdu")
    {
        GameState = "Perdu";
        Refresh_Grid();
        SaveStats(s);
        QMessageBox msgBox;
        msgBox.setWindowTitle("Super 2048");

        QFont font = msgBox.font();
        font.setPointSize(15);
        font.setBold(false);
        msgBox.setFont(font);

        msgBox.setText("Vous avez Perdu!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);

        msgBox.exec();

        Bouton_Quitter->animateClick();
    }
    else if (s == "Actualisation")
    {
        GameState = "Refresh";
        Refresh_Grid();
    }
    else if (s == "Mouvement Impossible")
    {
        //Rien faire
    }
    else if (s == "Traitement FPGA")
    {
        //Rien faire
    }
    else
    {
        //Erreur
    }
}

QString Jeu::Menu()
{
    //Détermine l'action a faire lorsqu'il est nécessaire de passer de l'interface jeu à l'interface accueil

    if (GameState == "Gagne" || GameState == "Perdu")
    {
        ClearFile();
        return "Fin";
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Super 2048");

        QFont font = msgBox.font();
        font.setPointSize(15);
        font.setBold(false);
        msgBox.setFont(font);

        msgBox.setText("Voulez vous vraiment quitter?");
        QPushButton* boutonOui = msgBox.addButton("Oui", QMessageBox::YesRole);
        QPushButton* boutonNon = msgBox.addButton("Non", QMessageBox::NoRole);
        msgBox.setDefaultButton(boutonNon);
        msgBox.exec();

        if (msgBox.clickedButton() == boutonOui)
        {
            if (Loaded == true)
            {
                if (grid->ChangeMade() == true)
                {
                    msgBox.setText("Voulez vous sauvegarder la partie en cours?");
                    msgBox.setInformativeText("La derniere version de cette partie sera remplacée!");
                }
                else
                {
                    return "Exit";
                }
            }
            else if (grid->GetMax() >= 8)
            {
                msgBox.setText("Voulez vous sauvegarder la partie en cours?");
                
                QFile file("Game.2048");

                if (file.exists())
                {
                    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QTextStream in(&file);
                        if (in.readLine().length() > 5)
                        {
                            msgBox.setInformativeText("La sauvegarde d'une partie différente sera ecrasée!");
                        }
                        file.close();
                    }
                    else
                    {
                        msgBox.setInformativeText("La sauvegarde d'une partie différente sera peut-etre ecrasée!");
                    }
                }
            }
            else
            {
                return "Exit";
            }

            msgBox.setDefaultButton(boutonOui);
            msgBox.exec();

            if (msgBox.clickedButton() == boutonOui)
            {
                SaveGame();
            }
            return "Exit";
        }
        else
        {
            return "Cancel Exit";
        }
    }
}

void Jeu::Refresh_Grid()
{
    //Rafréchie la grille de jeu et les informations à l'écran
    for (int x = 0; x < *GridSize; x++)
    {
        for (int y = 0; y < *GridSize; y++)
        {
            labelGrid[x][y]->setText(QString::number(grid->Get(x, y)));
            Customize_Label(labelGrid[x][y]);
        }
    }

    label_Score->setText("Score\n" + QString::number(grid->GetScore()));
    label_NbMove->setText("Nb Move\n" + QString::number(grid->GetNbMove()));
    label_Max->setText("Max\n" + QString::number(grid->GetMax()));
}

void Jeu::Status(QString s)
{
    label_Status->setText("Status (" + s + ")");
}

void Jeu::Clear_Status()
{
    label_Status->setText("");
    qDebug() << "Status clearded\n";
}

#pragma region Event

void Jeu::resizeEvent(QResizeEvent* event)
{
   
}

void Jeu::keyPressEvent(QKeyEvent* event)
{
    //traite les touche de clavier cliquer et leurs interactions
    if (event->isAutoRepeat() == false)
    {
        if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up)
        {
            Bouton_Haut->animateClick();
        }
        else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right)
        {
            Bouton_Droit->animateClick();
        }
        else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down)
        {
            Bouton_Bas->animateClick();
        }
        else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left)
        {
            Bouton_Gauche->animateClick();
        }
    }
}

#pragma endregion

#pragma region Sauvegarde

void Jeu::SaveGame()
{
    //Sauvegarde la partie en cours dans le dans le fichier Game.2048
    QFile file("Game.2048");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        in << QString::number(*GridSize) + "/";
        in << QString::number(grid->GetScore()) + "/";
        in << QString::number(grid->GetNbMove()) + "/";
        for (int x = 0; x < *GridSize; x++)
        {
            for (int y = 0; y < *GridSize; y++)
            {
                if (x == *GridSize - 1 && y == *GridSize - 1)
                {
                    in << QString::number(grid->Get(x, y));
                }
                else
                {
                    in << QString::number(grid->Get(x, y)) + "/";
                }

            }
        }
    }
    file.close();
}

void Jeu::SaveStats(QString s)
{
    //Sauvegarde les statistique de la partie en cours dans le dans le fichier Stats.2048
    QFile file("Stats.2048");

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream in(&file);
        in << s + "/";
        in << QString::number(*GridSize) + "x" + QString::number(*GridSize) + "/";
        in << QString::number(grid->GetScore()) + "/";
        in << QString::number(grid->GetNbMove()) + "/";
        in << QString::number(grid->GetMax()) + "\n";
    }
    file.close();

    if (Loaded == true)
    {
        ClearFile();
    }
}

void Jeu::ClearFile()
{
    //Vide le fichier Game.2048
    QFile file("Game.2048");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in << "";
    }
    file.close();
}

#pragma endregion

#pragma region Slots

void Jeu::FPGA_Timer()
{
    //Timer pour lire la carte fpga à chaque 250 millisecondes jusqu'a ce que le bouton 1 soit pesser
    //change l'intervale de lecture à 10 millisecondes et prend des mesures pendant 1 seconde et retourne a 250 ms après
    //traite le retour de la lecture


    QString text = fpga->Read();

    if (text == "LecStart")
    {
        Timer->setInterval(read_Time);

        qDebug() << text << "\n";
        Status(text);
    }
    else if (text == "Lec")
    {
        Status("Lecture : " + QString::number(fpga->nbRead/2) + "%");
    }
    else if (text == "LecStop")
    {
        Timer->setInterval(wait_Time);

        qDebug() << text << "\n";
        Status(text);
    }
    else if (text == "Haut")
    {
        qDebug() << text << "\n";
        Status(text);
        Bouton_Haut->animateClick();
    }
    else if (text == "Droit")
    {
        qDebug() << text << "\n";
        Status(text);
        Bouton_Droit->animateClick();
    }
    else if (text == "Bas")
    {
        qDebug() << text << "\n";
        Status(text);
        Bouton_Bas->animateClick();
    }
    else if (text == "Gauche")
    {
        qDebug() << text << "\n";
        Status(text);
        Bouton_Gauche->animateClick();
    }
    else if (text == "Phonemes non enregistrees")
    {
        qDebug() << text << "\n";
        Status(text);
    }
    else if (text == "Aucun")
    {
        qDebug() << text << "\n";
        Status(text);
    }
    else if (text == "Rien")
    {
        //cout << "Rien" << endl;
    }
    else if (text == "Erreur")
    {
        Timer->stop();
        qDebug() << text << "\n";
        Status(text);
    }
    else
    {
        qDebug() << "Pas prevus!!!" << "\n";
        Status("Pas prevus!!!");
        Timer->stop();
    }
}

void Jeu::Bouton_Haut_Clicked()
{
    //Vérifie si il est possible de bouger vers le haut avec la classe Grid et Fpga
    QString State;
    if (fpga->SaveOn == false && fpga->VerifOn == false)
    {
        State = grid->Move_Up();
        cout << "Bouge Haut" << endl;
    }
    else
    {
        State = "Traitement FPGA";
    }
    CheckMove(State);
}

void Jeu::Bouton_Droit_Clicked()
{
    //Vérifie si il est possible de bouger vers la droite avec la classe Grid et Fpga
    QString State;
    if (fpga->SaveOn == false && fpga->VerifOn == false)
    {
        State = grid->Move_Right();
        cout << "Bouge Droit" << endl;
    }
    else
    {
        State = "Traitement FPGA";
    }
    CheckMove(State);
}

void Jeu::Bouton_Bas_Clicked()
{
    //Vérifie si il est possible de bouger vers le bas avec la classe Grid et Fpga
    QString State;
    if (fpga->SaveOn == false && fpga->VerifOn == false)
    {
        State = grid->Move_Down();
        cout << "Bouge Bas" << endl;
    }
    else
    {
        State = "Traitement FPGA";
    }
    CheckMove(State);
}

void Jeu::Bouton_Gauche_Clicked()
{
    //Vérifie si il est possible de bouger vers la gauche avec la classe Grid et Fpga
    QString State;
    if (fpga->SaveOn == false && fpga->VerifOn == false)
    {
        State = grid->Move_Left();
        cout << "Bouge Gauche" << endl;
    }
    else
    {
        State = "Traitement FPGA";
    }
    CheckMove(State);
}

void Jeu::Bouton_Pressed()
{
    //SLOT pour traite les actions a effectuer lorsque un des bouton de l'interface jeu est presser
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(211,211,211); }");   //Dark
}

void Jeu::Bouton_Released()
{
    //SLOT pour traite les actions a effectuer lorsque un des bouton de l'interface jeu est relacher
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }"); //light
}

#pragma endregion

#pragma region Création

QPushButton* Jeu::Create_Button(QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer des boutons pour la classe Jeu
    QFont font;
    QPushButton* button = new QPushButton();
    button->setObjectName(nom);
    button->setText("&" + text);
    font = button->font();
    font.setPointSize(size);
    font.setBold(bold);
    button->setFont(font);
    button->setFixedHeight(50);
    button->setAutoFillBackground(true);
    button->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }");
    button->setCursor(Qt::PointingHandCursor);

    return button;
}

QLabel* Jeu::Create_Label(QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer les labels pour la classe Jeu
    QFont font;
    QLabel* label = new QLabel();
    label->setObjectName(nom);
    label->setText(text);
    //label->setAlignment(Qt::AlignCenter);
    font = label->font();
    font.setPointSize(size);
    font.setBold(bold);
    label->setFont(font);
    label->setMargin(10);

    label->setFrameStyle(QFrame::Box | QFrame::Plain);
    label->setLineWidth(4);
    label->setMidLineWidth(3);
    label->setAutoFillBackground(true);
    label->setStyleSheet("QLabel { background-color : rgba(255,255,255,0.5); }");

    return label;
}

QLabel* Jeu::Create_Custom_Label(QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer les labels pour la classe Jeu
    //Fonction pour créer les labels pour la classe Jeu
    QFont font;
    QLabel* label = new QLabel();
    label->setObjectName(nom);
    label->setText(text);
    label->setAlignment(Qt::AlignCenter);
    font = label->font();
    font.setPointSize(size);
    font.setBold(bold);
    label->setFont(font);
    label->setMargin(5);

    label->setFrameStyle(QFrame::Box | QFrame::Plain);
    label->setLineWidth(4);
    label->setMidLineWidth(3);
    label->setAutoFillBackground(true);
    label->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");

    return label;
}

QLabel* Jeu::Create_Game_Label(QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer les labels pour la classe Jeu
    QFont font;
    QLabel* label = new QLabel();
    label->setObjectName(nom);
    label->setText(text);
    label->setAlignment(Qt::AlignCenter);
    font = label->font();
    font.setPointSize(size);
    font.setBold(bold);
    label->setFont(font);

    label->setFixedSize(550 / *GridSize, 550 / *GridSize);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setLineWidth(6);
    label->setMidLineWidth(3);

    label->setAutoFillBackground(true);
    Customize_Label(label);

    return label;
}

void Jeu::Customize_Label(QLabel* label)
{
    //Modifie l'apparance des case du jeu pour s'adapter a leur valeurs

    //Text
    if (label->text() == "0")
    {
        label->setText("");
    }

    //color
    if (label->text() == "")
    {
        label->setStyleSheet("QLabel { background-color : rgba(236,236,236,0.3); }");
    }
    else if (label->text() == "2")
    {
        label->setStyleSheet("QLabel { background-color : rgb(238,228,218); }");
    }
    else if (label->text() == "4")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,224,200); }");
    }
    else if (label->text() == "8")
    {
        label->setStyleSheet("QLabel { background-color : rgb(242,177,121); }");
    }
    else if (label->text() == "16")
    {
        label->setStyleSheet("QLabel { background-color : rgb(245,149,99); }");
    }
    else if (label->text() == "32")
    {
        label->setStyleSheet("QLabel { background-color : rgb(246,124,95); }");
    }
    else if (label->text() == "64")
    {
        label->setStyleSheet("QLabel { background-color : rgb(246,94,59); }");
    }
    else if (label->text() == "128")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,207,114); }");
    }
    else if (label->text() == "256")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,204,97); }");
    }
    else if (label->text() == "512")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,200,80); }");
    }
    else if (label->text() == "1024")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,197,63); }");
    }
    else if (label->text() == "2048")
    {
        label->setStyleSheet("QLabel { background-color : rgb(0,255,0); }");
    }
    else
    {
        label->setStyleSheet("QLabel { background-color : rgb(51,255,255); }");
    }
}

#pragma endregion

