#include "jeu.h"

Jeu::Jeu(int* size, bool load) : GridSize(size) , Loaded(load)
{
    grid = new Grid(size, load);
    fpga = new Fpga();
    
    this->setObjectName("widget_Jeu");

    //Layout
    QGridLayout* gLayout = new QGridLayout(this);
    gLayout->setObjectName("gLayout");

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setObjectName("vLayout");

    QGridLayout* Game_gLayout = new QGridLayout();
    Game_gLayout->setObjectName("Game_gLayout");

    QGridLayout* Button_gLayout = new QGridLayout();
    Button_gLayout->setObjectName("Button_gLayout");

    QGridLayout* Stats_gLayout = new QGridLayout();
    Stats_gLayout->setObjectName("Stats_gLayout");

    //Label Grid
    labelGrid = new QLabel * *[*size];
    for (int i = 0; i < *size; i++)
    {
        labelGrid[i] = new QLabel * [*size];
    }

    for (int x = 0; x < *size; x++)
    {
        for (int y = 0; y < *size; y++)
        {
            labelGrid[x][y] = Create_Label_Jeu("label" + QString::number((x * 4) + y), QString::number(grid->Get(x, y)), 15, true, false, true);
        }
    }

    //Labels
    label_Score = Create_Label_Jeu("label_Score", "Score\n" + QString::number(grid->GetScore()), 15, true, true, false);
    label_NbMove = Create_Label_Jeu("label_NbMove", "Nb Move\n" + QString::number(grid->GetNbMove()), 15, true, true, false);
    label_Max = Create_Label_Jeu("label_Max", "Max\n" + QString::number(grid->GetMax()), 15, true, true, false);

    //Buttons
    QPushButton* button_Haut = Create_Button_Jeu("button_Jeu_Up", "Haut", 20, true, true);
    QPushButton* button_Gauche = Create_Button_Jeu("button_Jeu_Left", "Gauche", 20, true, true);
    QPushButton* button_Bas = Create_Button_Jeu("button_Jeu_Down", "Bas", 20, true, true);
    QPushButton* button_Droit = Create_Button_Jeu("button_Jeu_Right", "Droit", 20, true, true);
    button_Accueil = Create_Button_Jeu("button_Jeu_Accueil", "Menu", 20, true, false);


    //Game_gLayout
    for (int x = 0; x < *size; x++)
    {
        for (int y = 0; y < *size; y++)
        {
            Game_gLayout->addWidget(labelGrid[x][y], x, y);
        }
    }

    //Button_gLayout
    Button_gLayout->addWidget(button_Haut, 0, 1);
    Button_gLayout->addWidget(button_Gauche, 1, 0);
    Button_gLayout->addWidget(button_Bas, 1, 1);
    Button_gLayout->addWidget(button_Droit, 1, 2);

    //Stats_gLayout
    Stats_gLayout->addWidget(label_Score, 0, 0);
    Stats_gLayout->addWidget(label_NbMove, 0, 1);
    Stats_gLayout->addWidget(label_Max, 0, 2);

    //Frame
    QFrame* frame = new QFrame();
    frame->setObjectName("Frame");
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    frame->setLineWidth(4);
    frame->setMidLineWidth(3);
    frame->setLayout(Game_gLayout);

    //vLayout
    vLayout->addLayout(Stats_gLayout);
    vLayout->addSpacerItem(new QSpacerItem(40, 20));
    vLayout->addWidget(frame);
    vLayout->addSpacerItem(new QSpacerItem(40, 20));
    vLayout->addLayout(Button_gLayout);
    vLayout->addSpacerItem(new QSpacerItem(40, 20));
    vLayout->addWidget(button_Accueil);

    //Fill gridLayout
    gLayout->addLayout(vLayout, 0, 0, Qt::AlignCenter);

    //Timer
    {
        Timer = new QTimer();
        connect(Timer, &QTimer::timeout, this, &Jeu::FPGA_Timer);

        if (fpga->isConnected())
        {
            Timer->start(wait_Time);
        }
    }
}

Jeu::~Jeu()
{

}

QString Jeu::Bouge_Haut()
{
    if (fpga->SaveOn == false || fpga->VerifOn == false)
    {
        QString Status = grid->Move_Up();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else
        {
            return "Refresh";
        }
    }
    else
    {
        return "En lecture";
    }
}

QString Jeu::Bouge_Droit()
{
    if (fpga->SaveOn == false || fpga->VerifOn == false)
    {
        QString Status = grid->Move_Right();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else
        {
            return "Refresh";
        }
    }
    else
    {
        return "En lecture";
    }
}

QString Jeu::Bouge_Bas()
{
    if (fpga->SaveOn == false || fpga->VerifOn == false)
    {
        QString Status = grid->Move_Down();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else
        {
            return "Refresh";
        }
    }
    else
    {
        return "En lecture";
    }
}

QString Jeu::Bouge_Gauche()
{
    if (fpga->SaveOn == false || fpga->VerifOn == false)
    {
        QString Status = grid->Move_Left();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            return Status;
        }
        else
        {
            return "Refresh";
        }
    }
    else
    {
        return "En lecture";
    }
}

QString Jeu::Menu()
{
    if (Loaded == true)
    {
        SaveGame();
        return "Sauvegarde";
    }
    else if (grid->GetMax() >= 16)
    {
        QFile file("Game.2048");

        if (file.exists())
        {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                if (in.readLine().length() > 5)
                {
                    //Demander si il faut écraser
                    return "Question";
                }
                else
                {
                    SaveGame();
                    return "Sauvegarde";
                }
                file.close();
            }
            else
            {
                return "Erreur ouverture";
            }
        }
        else
        {
            return "Fichier introuvable";
        }
    }
    else
    {
        return "Rien";
    }

    
}

void Jeu::SaveGame()
{
    QFile file("Game.2048");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        in << QString::number(*GridSize)+"/";
        in << QString::number(grid->GetScore())+"/";
        in << QString::number(grid->GetNbMove())+"/";
        for(int x = 0; x< *GridSize;x++)
        {
            for(int y = 0;y< *GridSize;y++)
            {
                if(x == *GridSize -1 && y == *GridSize -1)
                {
                    in << QString::number(grid->Get(x,y));
                }
                else
                {
                    in << QString::number(grid->Get(x,y)) + "/";
                }

            }
        }
    }
    file.close();
}

void Jeu::SaveStats(QString s)
{
    QFile file("Stats.2048");

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream in(&file);
        in << s + "/";
        in << QString::number(*GridSize)+ "x" + QString::number(*GridSize) +"/";
        in << QString::number(grid->GetScore())+"/";
        in << QString::number(grid->GetNbMove())+"/";
        in << QString::number(grid->GetMax())+"\n";
    }
    file.close();
}

void Jeu::ClearFile()
{
    QFile file("Game.2048");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in << "";
    }
    file.close();
}

void Jeu::FPGA_Timer()
{
    QString text = fpga->Read();

    if (text == "LecStart")
    {
        Timer->setInterval(read_Time);
        cout << "Debut de lecture" << endl;
    }
    else if (text == "Lec")
    {
        cout << "Lecture" << endl;
    }
    else if (text == "LecStop")
    {
        Timer->setInterval(wait_Time);
        cout << "Fin de lecture" << endl;
    }
    else if (text == "Haut")
    {
        CheckMove(Bouge_Haut());
        cout << "Haut" << endl;
    }
    else if (text == "Droit")
    {
        CheckMove(Bouge_Droit());
        cout << "Droit" << endl;
    }
    else if (text == "Bas")
    {
        CheckMove(Bouge_Bas());
        cout << "Bas" << endl;
    }
    else if (text == "Gauche")
    {
        CheckMove(Bouge_Gauche());
        cout << "Gauche" << endl;
    }
    else if (text == "Aucun")
    {
        cout << "Aucun" << endl;
    }
    else if (text == "Rien")
    {
        cout << "Rien" << endl;
    }
    else if (text == "Erreur")
    {
        Timer->stop();
        cout << "Erreur" << endl;
    }
    else
    {
        cout << "Pas prevus!!!" << endl;
        Timer->stop();
    }
}

void Jeu::Refresh_Grid()
{
    for (int x = 0; x < *GridSize; x++)
    {
        for (int y = 0; y < *GridSize; y++)
        {
            labelGrid[x][y]->setText(QString::number(grid->Get(x, y)));
            CustomLabel(labelGrid[x][y]);
        }
    }

    label_Score->setText("Score\n" + QString::number(grid->GetScore()));
    label_NbMove->setText("Nb Move\n" + QString::number(grid->GetNbMove()));
    label_Max->setText("Max\n" + QString::number(grid->GetMax()));
}

void Jeu::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W)
    {
        CheckMove(Bouge_Haut());
    }
    else if (event->key() == Qt::Key_D)
    {
        CheckMove(Bouge_Droit());
    }
    else if (event->key() == Qt::Key_S)
    {
        CheckMove(Bouge_Bas());
    }
    else if (event->key() == Qt::Key_A)
    {
        CheckMove(Bouge_Gauche());
    }
}

void Jeu::CheckMove(QString s)
{
    if (s == "Gagne")
    {
        //Ouvrir un truc pour indiquer que la partie est gagné
    }
    else if (s == "Perdu")
    {
        //Ouvrir un truc pour indiquer que la partie est perdu
    }
    else if (s == "Refresh")
    {
        Refresh_Grid();
    }
    else if (s == "En lecture")
    {
        //Inscrire que en lecture
    }
}

void Jeu::CustomLabel(QLabel* label)
{
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

QPushButton* Jeu::Create_Button_Jeu(QString nom, QString text, int size, bool bold, bool custom)
{
    QFont font;
    QPushButton* button = new QPushButton();
    button->setObjectName(nom);
    button->setText(text);
    font = button->font();
    font.setPointSize(size);
    font.setBold(bold);
    button->setFont(font);
    button->setFixedHeight(50);
    button->setAutoFillBackground(true);
    button->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }");

    if (custom == true)
    {
        connect(button, &QPushButton::pressed, this, &Jeu::Button_Pressed);
        connect(button, &QPushButton::released, this, &Jeu::Button_Released);
        connect(button, &QPushButton::clicked, this, &Jeu::Button_clicked);
    }
    

    return button;
}

QLabel* Jeu::Create_Label_Jeu(QString nom, QString text, int size, bool bold, bool info, bool custom)
{
    QFont font;
    QLabel* label = new QLabel();
    label->setObjectName(nom);
    label->setText(text);
    label->setAlignment(Qt::AlignCenter);
    font = label->font();
    font.setPointSize(size);
    font.setBold(bold);
    label->setFont(font);

    if (info == true && custom == false)
    {
        label->setFrameStyle(QFrame::Box | QFrame::Plain);
        label->setLineWidth(4);
        label->setMidLineWidth(3);
        label->setAutoFillBackground(true);
        label->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");
    }

    if (custom = true && info == false)
    {
        label->setFixedSize(550 / *GridSize, 550 / *GridSize);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setLineWidth(6);
        label->setMidLineWidth(3);

        label->setAutoFillBackground(true);
        CustomLabel(label);
    }

    return label;
}

void Jeu::Button_clicked()
{
    QString name = qobject_cast<QPushButton*>(sender())->objectName();

    if (name == "button_Jeu_Up")
    {
        CheckMove(Bouge_Haut());
    }
    else if (name == "button_Jeu_Right")
    {
        CheckMove(Bouge_Droit());
    }
    else if (name == "button_Jeu_Down")
    {
        CheckMove(Bouge_Bas());
    }
    else if (name == "button_Jeu_Left")
    {
        CheckMove(Bouge_Gauche());
    }
}

void Jeu::Button_Pressed()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(211,211,211); }");   //Dark
}

void Jeu::Button_Released()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }"); //light
}