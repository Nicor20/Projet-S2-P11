#include "accueil.h"

Accueil::Accueil(int size,int mode) : GridSize(size) , GameMode(mode)
{
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

        hLayout1 = new QHBoxLayout(centralWidget);
        hLayout1->setObjectName("hLayout1");

        hLayout2 = new QHBoxLayout(centralWidget);
        hLayout2->setObjectName("hLayout2");
    }

    //Labels
    {
        label = new QLabel*[5];

        label[0] = Create_Label("label_Titre","Super 2048",50,true);
        label[1] = Create_Label("label_Sub1","Taille de la grille",20,true);
        label[2] = Create_Label("label_GridSize",QString::number(GridSize) + "x" + QString::number(GridSize),15,false);
        label[3] = Create_Label("label_Sub2","Taille de la grille",20,true);
        label[4] = Create_Label("label_GameMode","Interface",15,false);
    }

    //Buttons
    {
        button = new QPushButton*[8];

        button[0] = Create_Button("button_SizeMoin","<",15,true);
        button[1] = Create_Button("button_SizePlus",">",15,true);
        button[2] = Create_Button("button_ModeMoin","<",15,true);
        button[3] = Create_Button("button_ModePlus",">",15,true);
        button[4] = Create_Button("button_Jouer","Jouer",15,true);
        button[5] = Create_Button("button_Charger","Charger",15,true);
        button[6] = Create_Button("button_Stats","Stats",15,true);
        button[7] = Create_Button("button_Quitter","Quitter",15,true);

        connect(button[0],SIGNAL(clicked()),this,SLOT(SizeMoin_clicked()));
        connect(button[1],SIGNAL(clicked()),this,SLOT(SizePlus_clicked()));
        connect(button[2],SIGNAL(clicked()),this,SLOT(ModeMoin_clicked()));
        connect(button[3],SIGNAL(clicked()),this,SLOT(ModePlus_clicked()));

        connect(button[4],SIGNAL(clicked()),this,SLOT(Jouer_clicked()));
        connect(button[5],SIGNAL(clicked()),this,SLOT(Charger_clicked()));
        connect(button[6],SIGNAL(clicked()),this,SLOT(Stats_clicked()));
        connect(button[7],SIGNAL(clicked()),this,SLOT(Quitter_clicked()));
    }

    //hLayout1
    {
        hLayout1->addWidget(button[0]);
        hLayout1->addWidget(label[2]);
        hLayout1->addWidget(button[1]);
    }

    //hLayout2
    {
        hLayout2->addWidget(button[2]);
        hLayout2->addWidget(label[4]);
        hLayout2->addWidget(button[3]);
    }

    //vLayout
    {
        vLayout->addWidget(label[0]);
        vLayout->addSpacerItem(new QSpacerItem(20,20));
        vLayout->addWidget(label[1]);
        vLayout->addLayout(hLayout1);
        vLayout->addSpacerItem(new QSpacerItem(20,20));
        vLayout->addWidget(label[3]);
        vLayout->addLayout(hLayout2);
        vLayout->addSpacerItem(new QSpacerItem(20,20));
        vLayout->addWidget(button[4]);
        vLayout->addWidget(button[5]);
        vLayout->addWidget(button[6]);
        vLayout->addWidget(button[7]);
    }

    gLayout->addLayout(vLayout,0,0,Qt::AlignCenter);

    this->setCentralWidget(centralWidget);

    CheckSave();
    CheckStats();


}

Accueil::~Accueil()
{

}

QPushButton* Accueil::Create_Button(QString nom, QString text,int size, bool bold)
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

QLabel* Accueil::Create_Label(QString nom, QString text,int size, bool bold)
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

void Accueil::CheckSave()
{
    QFile file("Save.txt");

    if(!file.exists())
    {
       button[5]->setEnabled(false);
    }
    else
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            if(in.readLine().length()>5)
            {
                button[5]->setEnabled(true);
            }
            else
            {
                button[5]->setEnabled(false);
            }
            file.close();
        }
        else
        {
            button[5]->setEnabled(false);
        }
    }
}

void Accueil::CheckStats()
{
    QFile file("Stats.txt");

    if(!file.exists())
    {
       button[6]->setEnabled(false);
    }
    else
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            if(in.readLine().length()>5)
            {
                button[6]->setEnabled(true);
            }
            else
            {
                button[6]->setEnabled(false);
            }
            file.close();
        }
        else
        {
            button[6]->setEnabled(false);
        }
    }

}

void Accueil::SizePlus_clicked()
{
    if(GridSize<8)
    {
        GridSize++;
    }
    else
    {
        GridSize = 3;
    }

    label[2]->setText(QString::number(GridSize) + "x" + QString::number(GridSize));
}

void Accueil::SizeMoin_clicked()
{
    if(GridSize>3)
    {
        GridSize--;
    }
    else
    {
        GridSize = 8;
    }

    label[2]->setText(QString::number(GridSize) + "x" + QString::number(GridSize));
}

void Accueil::ModePlus_clicked()
{
    if(GameMode < 3)
    {
        GameMode++;
    }
    else
    {
        GameMode = 1;
    }

    if(GameMode == 1)
    {
        label[4]->setText("Interface");
    }
    else if(GameMode == 2)
    {
        label[4]->setText("Clavier");
    }
    else if(GameMode == 3)
    {
        label[4]->setText("Voix");
    }
}

void Accueil::ModeMoin_clicked()
{
    if(GameMode > 1)
    {
        GameMode--;
    }
    else
    {
        GameMode = 3;
    }

    if(GameMode == 1)
    {
        label[4]->setText("Interface");
    }
    else if(GameMode == 2)
    {
        label[4]->setText("Clavier");
    }
    else if(GameMode == 3)
    {
        label[4]->setText("Voix");
    }
}

void Accueil::Jouer_clicked()
{
    Jeu *w = new Jeu(GridSize,GameMode,false);
    w->showMaximized();
    this->close();
}

void Accueil::Charger_clicked()
{
    Jeu *w = new Jeu(GridSize,GameMode,true);
    w->showMaximized();
    this->close();
}

void Accueil::Stats_clicked()
{
    Stats *w = new Stats(GridSize,GameMode);
    w->showMaximized();
    this->close();
}

void Accueil::Quitter_clicked()
{
    this->close();
}

