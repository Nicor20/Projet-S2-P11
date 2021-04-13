#include "jeu.h"
#include <iostream>

Jeu::Jeu(int size, bool load) : GridSize(size) , Loaded(load)
{
    grid = new Grid(size,load);
    GridSize = grid->GetSize();

    this->setObjectName("Accueil");

    //Widget
    {
        centralWidget = new QWidget(this);
        centralWidget->setObjectName("centralWidget");
    }

    //Layout
    {
        gLayout = new QGridLayout(centralWidget);
        gLayout->setObjectName("gLayout");

        vLayout = new QVBoxLayout(centralWidget);
        vLayout->setObjectName("vLayout");

        Game_gLayout = new QGridLayout(centralWidget);
        Game_gLayout->setObjectName("Game_gLayout");

        Button_gLayout = new QGridLayout(centralWidget);
        Button_gLayout->setObjectName("Button_gLayout");

        Stats_gLayout = new QGridLayout(centralWidget);
        Stats_gLayout->setObjectName("Stats_gLayout");
    }

    //Setup Label Grid
    {
        labelGrid = new QLabel**[GridSize];
        for(int i =0;i<GridSize;i++)
        {
            labelGrid[i] = new QLabel*[GridSize];
        }

        for(int x = 0;x<GridSize;x++)
        {
            for(int y = 0;y<GridSize;y++)
            {
                labelGrid[x][y] = Create_Label("label"+QString::number((x*4)+y),QString::number(grid->Get(x,y)),15,true);
                CustomLabel(labelGrid[x][y]);
            }
        }

    }

    //Labels
    {
        label_Score = Create_Label("label_Score","Score\n" + QString::number(grid->GetScore()),15,true);
        label_Score->setFrameStyle(QFrame::Box | QFrame::Plain);
        label_Score->setLineWidth(4);
        label_Score->setMidLineWidth(3);
        label_Score->setAutoFillBackground(true);
        label_Score->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");

        label_NbMove = Create_Label("label_NbMove","Nb Move\n" + QString::number(grid->GetNbMove()),15,true);
        label_NbMove->setFrameStyle(QFrame::Box | QFrame::Plain);
        label_NbMove->setLineWidth(4);
        label_NbMove->setMidLineWidth(3);
        label_NbMove->setAutoFillBackground(true);
        label_NbMove->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");

        label_Max = Create_Label("label_Max","Max\n" + QString::number(grid->GetMax()),15,true);
        label_Max->setFrameStyle(QFrame::Box | QFrame::Plain);
        label_Max->setLineWidth(4);
        label_Max->setMidLineWidth(3);
        label_Max->setAutoFillBackground(true);
        label_Max->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");
    }

    //Buttons
    {
        button_Haut = Create_Button("button_Haut","Haut",15,true);
        button_Gauche = Create_Button("button_Gauche","Gauche",15,true);
        button_Bas = Create_Button("button_Bas","Bas",15,true);
        button_Droit = Create_Button("button_Droit","Droit",15,true);
        button_Menu = Create_Button("button_Menu","Menu",15,true);
        
        connect(button_Haut, &QPushButton::clicked, this, &Jeu::Button_clicked);
        connect(button_Gauche, &QPushButton::clicked, this, &Jeu::Button_clicked);
        connect(button_Bas, &QPushButton::clicked, this, &Jeu::Button_clicked);
        connect(button_Droit, &QPushButton::clicked, this, &Jeu::Button_clicked);
        connect(button_Menu, &QPushButton::clicked, this, &Jeu::Button_clicked);
    }

    //Game_gLayout
    {
        for(int x = 0;x<GridSize;x++)
        {
            for(int y = 0;y<GridSize;y++)
            {
                Game_gLayout->addWidget(labelGrid[x][y],x,y);
            }
        }
    }

    //Button_gLayout
    {
        Button_gLayout->addWidget(button_Haut,0,1);
        Button_gLayout->addWidget(button_Gauche,1,0);
        Button_gLayout->addWidget(button_Bas,1,1);
        Button_gLayout->addWidget(button_Droit,1,2);
    }

    //Stats_gLayout
    {
        Stats_gLayout->addWidget(label_Score,0,0);
        Stats_gLayout->addWidget(label_NbMove,0,1);
        Stats_gLayout->addWidget(label_Max,0,2);
    }

    //Frame
    {
        frame = new QFrame(centralWidget);
        frame->setObjectName("Frame");
        frame->setFrameStyle(QFrame::Box | QFrame::Plain);
        frame->setLineWidth(4);
        frame->setMidLineWidth(3);
        frame->setLayout(Game_gLayout);
    }

    //vLayout
    {
        vLayout->addLayout(Stats_gLayout);
        vLayout->addSpacerItem(new QSpacerItem(40,20));
        //vLayout->addLayout(Game_gLayout);
        vLayout->addWidget(frame);
        vLayout->addSpacerItem(new QSpacerItem(40,20));
        vLayout->addLayout(Button_gLayout);
        
        vLayout->addSpacerItem(new QSpacerItem(40,20));
        vLayout->addWidget(button_Menu);
    }

    //Fill gridLayout
    gLayout->addLayout(vLayout,0,0,Qt::AlignCenter);

    this->setCentralWidget(centralWidget);

    //Timer
    {
        CarteFPGA = new FPGA();
        Timer = new QTimer(centralWidget);
        connect(Timer, &QTimer::timeout, this, &Jeu::FPGA_Timer);

        if (CarteFPGA->Connected())
        {
            Timer->start(interval_wait);
        }
    }

    //Background
    {
        QPixmap bk("BG.png");
        bk = bk.scaled(QSize(1920, 1080), Qt::IgnoreAspectRatio);
        QPalette pa;
        pa.setBrush(QPalette::Window, bk);
        this->setPalette(pa);
    }
}

Jeu::~Jeu()
{
    if (Timer->isActive())
    {
        Timer->stop();
    }
    
    delete CarteFPGA;
    this->destroy();
}

QWidget* Jeu::Get_Widget()
{
    return centralWidget;
}

void Jeu::RefreshGrid()
{
    for(int x = 0; x < GridSize; x++)
    {
        for(int y = 0; y < GridSize; y++)
        {
            labelGrid[x][y]->setText(QString::number(grid->Get(x,y)));
            CustomLabel(labelGrid[x][y]);
        }
    }

    label_Score ->setText("Score\n" + QString::number(grid->GetScore()));
    label_NbMove ->setText("Nb Move\n" + QString::number(grid->GetNbMove()));
    label_Max ->setText("Max\n" + QString::number(grid->GetMax()));
}

#pragma region Mouvement
void Jeu::Bouge_Haut()
{
    if (Lecture_FPGA == false)
    {
        QString Status = grid->Haut();
        RefreshGrid();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
    }
}

void Jeu::Bouge_Droit()
{
    if (Lecture_FPGA == false)
    {
        QString Status = grid->Droit();
        RefreshGrid();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
    }
}

void Jeu::Bouge_Bas()
{
    if (Lecture_FPGA == false)
    {
        QString Status = grid->Bas();
        RefreshGrid();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
    }
}

void Jeu::Bouge_Gauche()
{
    if (Lecture_FPGA == false)
    {
        QString Status = grid->Gauche();
        RefreshGrid();

        if (Status == "Perdu")
        {
            SaveStats(Status);
            ClearFile();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
        else if (Status == "Gagne")
        {
            SaveStats(Status);
            ClearFile();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
    }
}
#pragma endregion

#pragma region Slot
void Jeu::FPGA_Timer()
{
    QString text = CarteFPGA->Read();

    if (text == "LecStart")
    {
        Timer->setInterval(interval_read);
        Lecture_FPGA = true;
        cout << "Debut de lecture" << endl;
    }
    else if (text == "Lec")
    {
        cout << "Lecture" << endl;
    }
    else if (text == "LecStop")
    {
        Timer->setInterval(interval_wait);
        cout << "Fin de lecture" << endl;
    }
    else if (text == "Haut")
    {
        Lecture_FPGA = false;
        Bouge_Haut();
        cout << "Haut" << endl;
    }
    else if (text == "Droit")
    {
        Lecture_FPGA = false;
        Bouge_Droit();
        cout << "Droit" << endl;
    }
    else if (text == "Bas")
    {
        Lecture_FPGA = false;
        Bouge_Bas();
        cout << "Bas" << endl;
    }
    else if (text == "Gauche")
    {
        Lecture_FPGA = false;
        Bouge_Gauche();
        cout << "Gauche" << endl;
    }
    else if (text == "Aucun")
    {
        Lecture_FPGA = false;
        cout << "Aucun" << endl;
    }
    else if (text == "Rien")
    {
        cout << "Rien" << endl;
    }
    else if (text == "Erreur")
    {
        Lecture_FPGA = false;
        Timer->stop();
        cout << "Erreur" << endl;
    }
    else
    {
        Lecture_FPGA = false;
        cout << "Pas prevus!!!" << endl;
        Timer->stop();
    }
}

void Jeu::Button_clicked()
{
    QString name = qobject_cast<QPushButton*>(sender())->objectName();

    if (name == "button_Haut")
    {
        cout << "Bouton Haut" << endl;
        Bouge_Haut();
    }
    else if (name == "button_Droit")
    {
        cout << "Bouton Droit" << endl;
        Bouge_Droit();
    }
    else if (name == "button_Bas")
    {
        cout << "Bouton Bas" << endl;
        Bouge_Bas();
    }
    else if (name == "button_Gauche")
    {
        cout << "Bouton Gauche" << endl;
        Bouge_Gauche();
    }
    else if (name == "button_Menu")
    {
        cout << "Bouton Menu" << endl;
        Menu();
    }

    
}
#pragma endregion

#pragma region Creator
QPushButton* Jeu::Create_Button(QString nom, QString text,int size, bool bold)
{
    QFont font;
    QPushButton *temp = new QPushButton(centralWidget);
    temp ->setObjectName(nom);
    temp ->setText(text);
    font = temp->font();
    font.setPointSize(size);
    font.setBold(bold);
    temp->setFont(font);
    return temp;
}

QLabel* Jeu::Create_Label(QString nom, QString text,int size, bool bold)
{
    QFont font;
    QLabel *temp = new QLabel(centralWidget);
    temp ->setObjectName(nom);
    temp ->setText(text);
    temp ->setAlignment(Qt::AlignCenter);
    font = temp->font();
    font.setPointSize(size);
    font.setBold(bold);
    temp->setFont(font);
    return temp;
}

void Jeu::CustomLabel(QLabel *label)
{
    int width = 550;
    //Text
    if(label->text() == "0")
    {
        label->setText("");
    }

    //style
    label->setFixedSize(width/GridSize,width/GridSize);
    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    label->setLineWidth(6);
    label->setMidLineWidth(3);

    //color
    label->setAutoFillBackground(true);
    if(label->text() == "")
    {
        label->setStyleSheet("QLabel { background-color : rgba(236,236,236,0.3); }");
    }
    else if(label->text() == "2")
    {
        label->setStyleSheet("QLabel { background-color : rgb(238,228,218); }");
    }
    else if(label->text() == "4")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,224,200); }");
    }
    else if(label->text() == "8")
    {
        label->setStyleSheet("QLabel { background-color : rgb(242,177,121); }");
    }
    else if(label->text() == "16")
    {
        label->setStyleSheet("QLabel { background-color : rgb(245,149,99); }");
    }
    else if(label->text() == "32")
    {
        label->setStyleSheet("QLabel { background-color : rgb(246,124,95); }");
    }
    else if(label->text() == "64")
    {
        label->setStyleSheet("QLabel { background-color : rgb(246,94,59); }");
    }
    else if(label->text() == "128")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,207,114); }");
    }
    else if(label->text() == "256")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,204,97); }");
    }
    else if(label->text() == "512")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,200,80); }");
    }
    else if(label->text() == "1024")
    {
        label->setStyleSheet("QLabel { background-color : rgb(237,197,63); }");
    }
    else if(label->text() == "2048")
    {
        label->setStyleSheet("QLabel { background-color : rgb(0,255,0); }");
    }
    else
    {
        label->setStyleSheet("QLabel { background-color : rgb(51,255,255); }");
    }
}
#pragma endregion

#pragma region Event
void Jeu::closeEvent(QCloseEvent* event)
{
    Jeu::~Jeu();
}

void Jeu::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_W)
    {
        Bouge_Haut();
    }
    else if (event->key() == Qt::Key_D)
    {
        Bouge_Droit();
    }
    else if (event->key() == Qt::Key_S)
    {
        Bouge_Bas();
    }
    else if (event->key() == Qt::Key_A)
    {
        Bouge_Gauche();
    }
}
#pragma endregion

void Jeu::Menu()
{
    bool closeWithoutAsking = true;

    if(Loaded == true)
    {
        closeWithoutAsking = true;
        SaveGame();
    }
    else if(grid->GetMax() >= 16)
    {
        QFile file("Save.txt");

        if (!file.exists())
        {
            closeWithoutAsking = true;
        }
        else
        {
            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                if (in.readLine().length() > 5)
                {
                    closeWithoutAsking = false;
                }
                else
                {
                    closeWithoutAsking = true;
                }
                file.close();
            }
            else
            {
                closeWithoutAsking = true;
            }
        }
    }
    else
    {
        closeWithoutAsking = true;
    }

    if (closeWithoutAsking == true)
    {
        Accueil* w = new Accueil(GridSize);
        w->showMaximized();
        this->close();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Voulez vous sauvegarder la partie?");
        msgBox.setInformativeText("La dernière sauvegarde sera écraser");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int rep = msgBox.exec();

        if (rep == QMessageBox::Ok)
        {
            SaveGame();
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
        else
        {
            Accueil* w = new Accueil(GridSize);
            w->showMaximized();
            this->close();
        }
    }
}

void Jeu::SaveGame()
{
    QFile file("Save.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        in << QString::number(GridSize)+"/";
        in << QString::number(grid->GetScore())+"/";
        in << QString::number(grid->GetNbMove())+"/";
        //in << QString::number(grid->GetMax())+"/";
        for(int x = 0; x<GridSize;x++)
        {
            for(int y = 0;y<GridSize;y++)
            {
                if(x == GridSize-1 && y == GridSize-1)
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
    QFile file("Stats.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream in(&file);
        in << s + "/";
        in << QString::number(GridSize)+ "x" + QString::number(GridSize) +"/";
        in << QString::number(grid->GetScore())+"/";
        in << QString::number(grid->GetNbMove())+"/";
        in << QString::number(grid->GetMax())+"\n";
    }
    file.close();
}

void Jeu::ClearFile()
{
    QFile file("Save.txt");

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in << "";
    }
    file.close();
}
