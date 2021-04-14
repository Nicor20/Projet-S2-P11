#include "UI.h"

UI::UI()
{
    this->setObjectName("UI");

    Load_Accueil();

    //Background
    QPixmap bk("BG.png");
    bk = bk.scaled(qApp->primaryScreen()->size(), Qt::IgnoreAspectRatio);
    QPalette pa;
    pa.setBrush(QPalette::Window, bk);
    this->setPalette(pa);
}

UI::~UI()
{

}

#pragma region Accueil

void UI::Load_Accueil()
{
    accueil = new Accueil();

    QWidget* widget = new QWidget(this);
    widget->setObjectName("widget_Accueil");

    //Layout
    QGridLayout *gLayout = new QGridLayout(widget);
    gLayout->setObjectName("gLayout");

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setObjectName("vLayout");

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setObjectName("hLayout");
    
    //Label
    QLabel* label_Titre = Create_Label_Accueil("label_Titre", "Super 2048", 80, true);
    QLabel *label_Sub = Create_Label_Accueil("label_Sub", "Taille de la grille", 30, true);
    label_GridSize = Create_Label_Accueil("label_GridSize", QString::number(GridSize) + "x" + QString::number(GridSize), 25, true, true);

    //Button
    QPushButton* button_Moin = Create_Button_Accueil("button_Accueil_Moin", "<", 20, true, true);
    QPushButton* button_Plus = Create_Button_Accueil("button_Accueil_Plus", ">", 20, true, true);
    QPushButton* button_Jouer = Create_Button_Accueil("button_Accueil_Jouer", "Jouer", 20, true, false);
    QPushButton* button_Charger = Create_Button_Accueil("button_Accueil_Charger", "Charger", 20, true, false);
    QPushButton* button_Stats = Create_Button_Accueil("button_Accueil_Stats", "Stats", 20, true, false);
    QPushButton* button_Quitter = Create_Button_Accueil("button_Accueil_Quitter", "Quitter", 20, true, false);

    //hLayout1
    hLayout->addWidget(button_Moin);
    hLayout->addWidget(label_GridSize);
    hLayout->addWidget(button_Plus);

    //vLayout
    vLayout->addWidget(label_Titre);
    vLayout->addSpacerItem(new QSpacerItem(20, 20));
    vLayout->addWidget(label_Sub);
    vLayout->addLayout(hLayout);
    vLayout->addSpacerItem(new QSpacerItem(20, 20));
    vLayout->addWidget(button_Jouer);
    vLayout->addWidget(button_Charger);
    vLayout->addWidget(button_Stats);
    vLayout->addWidget(button_Quitter);

    gLayout->addLayout(vLayout, 0, 0, Qt::AlignCenter);
    this->setCentralWidget(widget);

    //Check Save
    button_Charger->setEnabled(accueil->CheckSave());

    //Check Stats
    button_Stats->setEnabled(accueil->CheckStats());
}

QPushButton* UI::Create_Button_Accueil(QString nom, QString text, int size, bool bold, bool custom)
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
        connect(button, &QPushButton::pressed, this, &UI::Button_Pressed);
        connect(button, &QPushButton::released, this, &UI::Button_Released);
    }
    connect(button, &QPushButton::clicked, this, &UI::Button_clicked);

    return button;
}

QLabel* UI::Create_Label_Accueil(QString nom, QString text, int size, bool bold, bool custom)
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

    if (custom == true)
    {
        //label->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
        //label->setLineWidth(4);
        //label->setMidLineWidth(3);
    }

    return label;
}

#pragma endregion

#pragma region Jeu

void UI::Load_Jeu(bool load)
{
    jeu = new Jeu(GridSize, load);

    QWidget *widget = new QWidget(this);
    widget->setObjectName("widget_Jeu");

    //Layout
    QGridLayout *gLayout = new QGridLayout(widget);
    gLayout->setObjectName("gLayout");

    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setObjectName("vLayout");

    QGridLayout* Game_gLayout = new QGridLayout();
    Game_gLayout->setObjectName("Game_gLayout");

    QGridLayout* Button_gLayout = new QGridLayout();
    Button_gLayout->setObjectName("Button_gLayout");

    QGridLayout* Stats_gLayout = new QGridLayout();
    Stats_gLayout->setObjectName("Stats_gLayout");

    //Label Grid
    labelGrid = new QLabel **[GridSize];
    for (int i = 0; i < GridSize; i++)
    {
        labelGrid[i] = new QLabel * [GridSize];
    }

    for (int x = 0; x < GridSize; x++)
    {
        for (int y = 0; y < GridSize; y++)
        {
            labelGrid[x][y] = Create_Label_Jeu("label" + QString::number((x * 4) + y), QString::number(jeu->Get(x, y)), 15, true, false, true);
        }
    }

    //Labels
    label_Score = Create_Label_Jeu("label_Score", "Score\n" + QString::number(jeu->GetScore()), 15, true,true,false);
    label_NbMove = Create_Label_Jeu("label_NbMove", "Nb Move\n" + QString::number(jeu->GetNbMove()), 15, true, true, false);
    label_Max = Create_Label_Jeu("label_Max", "Max\n" + QString::number(jeu->GetMax()), 15, true, true, false);

    //Buttons
    QPushButton* button_Haut = Create_Button_Jeu("button_Jeu_Up", "Haut", 20, true, true);
    QPushButton* button_Gauche = Create_Button_Jeu("button_Jeu_Left", "Gauche", 20, true, true);
    QPushButton* button_Bas = Create_Button_Jeu("button_Jeu_Down", "Bas", 20, true, true);
    QPushButton* button_Droit = Create_Button_Jeu("button_Jeu_Right", "Droit", 20, true, true);
    QPushButton* button_Menu = Create_Button_Jeu("button_Jeu_Accueil", "Menu", 20, true, false);
    

    //Game_gLayout
    for (int x = 0; x < GridSize; x++)
    {
        for (int y = 0; y < GridSize; y++)
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
    QFrame *frame = new QFrame();
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
    vLayout->addWidget(button_Menu);

    //Fill gridLayout
    gLayout->addLayout(vLayout, 0, 0, Qt::AlignCenter);

    this->setCentralWidget(widget);

    //Timer
    {
        Timer = new QTimer();
        connect(Timer, &QTimer::timeout, this, &UI::FPGA_Timer);

        if (jeu->isConnected())
        {
            Timer->start(jeu->waitTime());
        }
    }
}

void UI::FPGA_Timer()
{
    QString text = jeu->Read();

    if (text == "LecStart")
    {
        Timer->setInterval(jeu->readTime());
        cout << "Debut de lecture" << endl;
    }
    else if (text == "Lec")
    {
        cout << "Lecture" << endl;
    }
    else if (text == "LecStop")
    {
        Timer->setInterval(jeu->waitTime());
        cout << "Fin de lecture" << endl;
    }
    else if (text == "Haut")
    {
        CheckMove(jeu->Bouge_Haut());
        cout << "Haut" << endl;
    }
    else if (text == "Droit")
    {
        CheckMove(jeu->Bouge_Droit());
        cout << "Droit" << endl;
    }
    else if (text == "Bas")
    {
        CheckMove(jeu->Bouge_Bas());
        cout << "Bas" << endl;
    }
    else if (text == "Gauche")
    {
        CheckMove(jeu->Bouge_Gauche());
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

void UI::Refresh_Grid()
{
    for (int x = 0; x < GridSize; x++)
    {
        for (int y = 0; y < GridSize; y++)
        {
            labelGrid[x][y]->setText(QString::number(jeu->Get(x, y)));
            CustomLabel(labelGrid[x][y]);
        }
    }

    label_Score->setText("Score\n" + QString::number(jeu->GetScore()));
    label_NbMove->setText("Nb Move\n" + QString::number(jeu->GetNbMove()));
    label_Max->setText("Max\n" + QString::number(jeu->GetMax()));
}

void UI::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W)
    {
        CheckMove(jeu->Bouge_Haut());
    }
    else if (event->key() == Qt::Key_D)
    {
        CheckMove(jeu->Bouge_Droit());
    }
    else if (event->key() == Qt::Key_S)
    {
        CheckMove(jeu->Bouge_Bas());
    }
    else if (event->key() == Qt::Key_A)
    {
        CheckMove(jeu->Bouge_Gauche());
    }
}

void UI::CheckMove(QString s)
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

void UI::CustomLabel(QLabel* label)
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

QPushButton* UI::Create_Button_Jeu(QString nom, QString text, int size, bool bold, bool custom)
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
        connect(button, &QPushButton::pressed, this, &UI::Button_Pressed);
        connect(button, &QPushButton::released, this, &UI::Button_Released);
    }
    connect(button, &QPushButton::clicked, this, &UI::Button_clicked);

    return button;
}

QLabel* UI::Create_Label_Jeu(QString nom, QString text, int size, bool bold, bool info, bool custom)
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
        int width = 550;
        label->setFixedSize(width / GridSize, width / GridSize);
        label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
        label->setLineWidth(6);
        label->setMidLineWidth(3);

        label->setAutoFillBackground(true);
        CustomLabel(label);
    }

    return label;
}

#pragma endregion

#pragma region Stats

void UI::Load_Stats()
{
    stats = new Stats();

    QWidget* widget = new QWidget(this);
    widget->setObjectName("widget_Stats");

    //Label
    QLabel* label_Titre = Create_Label_Stats("label_Titre", "LeaderBoard", 75, true, false, false);
    QLabel* label_Position = Create_Label_Stats("label_Position", "Position", 15, true, true, false);
    QLabel* label_Status = Create_Label_Stats("label_Status", "Status", 15, true, true, false);
    QLabel* label_Size = Create_Label_Stats("label_Size", "Size", 15, true, true, false);
    QLabel* label_Score = Create_Label_Stats("label_Score", "Score", 15, true, true, false);
    QLabel* label_NbMove = Create_Label_Stats("label_NbMove", "Nb Move", 15, true, true, false);
    QLabel* label_Max = Create_Label_Stats("label_Max", "Max", 15, true, true, false);

    //Button
    QPushButton* button_Menu = Create_Button_Stats("button_Stats_Accueil", "Menu", 15, true, false);


    //Layout
    QGridLayout *gLayout = new QGridLayout(widget);
    gLayout->setObjectName("gLayout");

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setObjectName("vLayout");

    QGridLayout* Stats_gLayout = new QGridLayout();
    Stats_gLayout->setObjectName("Stats_gLayout");


    //Stats_gLayout
    {
        Stats_gLayout->addWidget(label_Position, 0, 0);
        Stats_gLayout->addWidget(label_Status, 0, 1);
        Stats_gLayout->addWidget(label_Size, 0, 2);
        Stats_gLayout->addWidget(label_Score, 0, 3);
        Stats_gLayout->addWidget(label_NbMove, 0, 4);
        Stats_gLayout->addWidget(label_Max, 0, 5);

        QLabel* temp;
        for (int i = 0; i < stats->GetNbToShow(); i++)
        {
            temp = Create_Label_Stats("label_Position" + QString::number(i + 1), "#" + QString::number(i + 1), 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 0);

            temp = Create_Label_Stats("label_Status" + QString::number(i + 1), stats->GetGameAt(i).Status, 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 1);

            temp = Create_Label_Stats("label_Size" + QString::number(i + 1), stats->GetGameAt(i).Size, 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 2);

            temp = Create_Label_Stats("label_Score" + QString::number(i + 1), QString::number(stats->GetGameAt(i).Score), 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 3);

            temp = Create_Label_Stats("label_NbMove" + QString::number(i + 1), QString::number(stats->GetGameAt(i).NbMove), 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 4);

            temp = Create_Label_Stats("label_Max" + QString::number(i + 1), QString::number(stats->GetGameAt(i).Max), 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 5);
        }
    }

    //Frame
    QFrame* frame = new QFrame();
    frame->setObjectName("Frame");
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    frame->setLineWidth(2);
    frame->setMidLineWidth(3);
    frame->setLayout(Stats_gLayout);
    frame->setAutoFillBackground(true);
    frame->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");

    //vLayout
    vLayout->addWidget(label_Titre);
    vLayout->addSpacerItem(new QSpacerItem(40, 20));
    vLayout->addWidget(frame);
    vLayout->addSpacerItem(new QSpacerItem(40, 20));
    vLayout->addWidget(button_Menu);

    gLayout->addLayout(vLayout, 0, 0, Qt::AlignCenter);

    this->setCentralWidget(widget);
}

QPushButton* UI::Create_Button_Stats(QString nom, QString text, int size, bool bold, bool custom)
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
        connect(button, &QPushButton::pressed, this, &UI::Button_Pressed);
        connect(button, &QPushButton::released, this, &UI::Button_Released);
    }
    connect(button, &QPushButton::clicked, this, &UI::Button_clicked);

    return button;
}

QLabel* UI::Create_Label_Stats(QString nom, QString text, int size, bool bold, bool info, bool stats, int num)
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

    if (info == true)
    {
        label->setFixedWidth(110);
        label->setFrameStyle(QFrame::WinPanel | QFrame::Raised);
        label->setLineWidth(4);
        label->setMidLineWidth(3);
        label->setAutoFillBackground(true);
        label->setStyleSheet("QLabel { background-color : rgb(193, 225, 236); }");
    }

    if (stats == true)
    {
        label->setAutoFillBackground(true);
        if (num % 2 == 0)
        {
            label->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");
        }
        else
        {
            label->setStyleSheet("QLabel { background-color : rgb(220, 220, 220); }");
        }
        
    }

    return label;
}

#pragma endregion

#pragma region All

void UI::Button_clicked()
{
    QString name = qobject_cast<QPushButton*>(sender())->objectName();

    if (name == "button_Accueil_Moin")  //Accueil
    {
        if (GridSize > 3)
        {
            GridSize--;
        }
        else
        {
            GridSize = 8;
        }

        label_GridSize->setText(QString::number(GridSize) + "x" + QString::number(GridSize));
    }
    else if (name == "button_Accueil_Plus")     //Accueil
    {
        if (GridSize < 8)
        {
            GridSize++;
        }
        else
        {
            GridSize = 3;
        }

        label_GridSize->setText(QString::number(GridSize) + "x" + QString::number(GridSize));
    }
    else if (name == "button_Accueil_Jouer")    //Accueil
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
        this->close();
    }
    else if (name == "button_Jeu_Up")
    {
        CheckMove(jeu->Bouge_Haut());
    }
    else if (name == "button_Jeu_Right")
    {
        CheckMove(jeu->Bouge_Droit());
    }
    else if (name == "button_Jeu_Down")
    {
        CheckMove(jeu->Bouge_Bas());
    }
    else if (name == "button_Jeu_Left")
    {
        CheckMove(jeu->Bouge_Gauche());
    }
    else if (name == "button_Jeu_Accueil")
    {
        QString rep = jeu->Menu();

        if (rep == "Sauvegarde" || rep == "Rien")
        {
            Load_Accueil();
        }
        else if (rep == "Erreur ouverture")
        {

        }
        else if (rep == "Fichier introuvable")
        {

        }
        else if (rep == "Question")
        {
            QMessageBox msgBox;
            msgBox.setText("Voulez vous sauvegarder la partie?");
            msgBox.setInformativeText("La derniere sauvegarde sera ecraser");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.setGeometry(960, 510, 800, 550);
            int rep = msgBox.exec();

            if (rep == QMessageBox::Ok)
            {
                jeu->SaveGame();
                Load_Accueil();
            }
            else
            {
                Load_Accueil();
            }
        }
    }
    else if (name == "button_Stats_Accueil")
    {
        Load_Accueil();
    }

}

void UI::Button_Pressed()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(211,211,211); }");   //Dark
}

void UI::Button_Released()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }"); //light
}

#pragma endregion