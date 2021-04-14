#include "jeu.h"

Jeu::Jeu(int size, int mode, bool load) : ModeJeu(mode) , Loaded(load)
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
        label = new QLabel*[3];

        label[0] = Create_Label("label_Score","Score\n" + QString::number(grid->GetScore()),15,true);
        label[0]->setFrameStyle(QFrame::Box | QFrame::Sunken);
        label[0]->setLineWidth(4);
        label[0]->setMidLineWidth(3);

        label[1] = Create_Label("label_NbMove","Nb Move\n" + QString::number(grid->GetNbMove()),15,true);
        label[1]->setFrameStyle(QFrame::Box | QFrame::Sunken);
        label[1]->setLineWidth(4);
        label[1]->setMidLineWidth(3);

        label[2] = Create_Label("label_Max","Max\n" + QString::number(grid->GetMax()),15,true);
        label[2]->setFrameStyle(QFrame::Box | QFrame::Sunken);
        label[2]->setLineWidth(4);
        label[2]->setMidLineWidth(3);
    }

    //Buttons
    {
        button = new QPushButton*[5];

        button[0] = Create_Button("button_Haut","Haut",15,true);
        button[1] = Create_Button("button_Gauche","Gauche",15,true);
        button[2] = Create_Button("button_Bas","Bas",15,true);
        button[3] = Create_Button("button_Droit","Droit",15,true);
        button[4] = Create_Button("button_Menu","Menu",15,true);

        connect(button[0],SIGNAL(clicked()),this,SLOT(Haut_clicked()));
        connect(button[1],SIGNAL(clicked()),this,SLOT(Gauche_clicked()));
        connect(button[2],SIGNAL(clicked()),this,SLOT(Bas_clicked()));
        connect(button[3],SIGNAL(clicked()),this,SLOT(Droit_clicked()));
        connect(button[4],SIGNAL(clicked()),this,SLOT(Menu_clicked()));
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
        Button_gLayout->addWidget(button[0],0,1);
        Button_gLayout->addWidget(button[1],1,0);
        Button_gLayout->addWidget(button[2],1,1);
        Button_gLayout->addWidget(button[3],1,2);
    }

    //Stats_gLayout
    {
        Stats_gLayout->addWidget(label[0],0,0);
        Stats_gLayout->addWidget(label[1],0,1);
        Stats_gLayout->addWidget(label[2],0,2);
    }

    //vLayout
    {
        vLayout->addLayout(Stats_gLayout);
        vLayout->addSpacerItem(new QSpacerItem(40,20));
        vLayout->addLayout(Game_gLayout);
        vLayout->addSpacerItem(new QSpacerItem(40,20));
        vLayout->addLayout(Button_gLayout);
        vLayout->addSpacerItem(new QSpacerItem(40,20));
        vLayout->addWidget(button[4]);
    }

    //Fill gridLayout
    gLayout->addLayout(vLayout,0,0,Qt::AlignCenter);

    this->setCentralWidget(centralWidget);
}

Jeu::~Jeu()
{

}

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

    label[0] ->setText("Score\n" + QString::number(grid->GetScore()));
    label[1] ->setText("Nb Move\n" + QString::number(grid->GetNbMove()));
    label[2] ->setText("Max\n" + QString::number(grid->GetMax()));
}

void Jeu::Haut_clicked()
{
    QString Status = grid->Haut();
    RefreshGrid();


    if(Status == "Perdu")
    {
        SaveStats(Status);
        ClearFile();
    }
    else if(Status == "Gagne")
    {
        SaveStats(Status);
        ClearFile();
    }
}

void Jeu::Bas_clicked()
{
    QString Status = grid->Bas();
    RefreshGrid();

    if(Status == "Perdu")
    {
        SaveStats(Status);
        ClearFile();
    }
    else if(Status == "Gagne")
    {
        SaveStats(Status);
        ClearFile();
    }
}

void Jeu::Droit_clicked()
{
    QString Status = grid->Droit();
    RefreshGrid();

    if(Status == "Perdu")
    {
        SaveStats(Status);
        ClearFile();
    }
    else if(Status == "Gagne")
    {
        SaveStats(Status);
        ClearFile();
    }
}

void Jeu::Gauche_clicked()
{
    QString Status = grid->Gauche();
    RefreshGrid();

    if(Status == "Perdu")
    {
        SaveStats(Status);
        ClearFile();
    }
    else if(Status == "Gagne")
    {
        SaveStats(Status);
        ClearFile();
    }
}

void Jeu::Menu_clicked()
{
    if(Loaded == true)
    {
        SaveGame();
    }
    else if(grid->GetMax() >= 32)
    {
        QMessageBox msgBox;
        msgBox.setText("Voulez vous sauvegarder la partie?");
        msgBox.setInformativeText("La dernière sauvegarde sera écraser");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int rep = msgBox.exec();

        if(rep == QMessageBox::Ok)
        {
            SaveGame();
        }
    }

    Accueil *w = new Accueil(GridSize,ModeJeu);
    w->showMaximized();
    this->close();
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
