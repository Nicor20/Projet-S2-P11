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
    }

    //Labels
    {
        label_Titre = Create_Label("label_Titre","Super 2048",50,true);
        label_Sub = Create_Label("label_Sub1","Taille de la grille",20,true);
        label_GridSize = Create_Label("label_GridSize",QString::number(GridSize) + "x" + QString::number(GridSize),15,false);
    }

    //Buttons
    {
        button_Moin = Create_Button("button_Moin","<",15,true);
        connect(button_Moin, &QPushButton::clicked, this, &Accueil::Button_clicked);

        button_Plus = Create_Button("button_Plus",">",15,true);
        connect(button_Plus, &QPushButton::clicked, this, &Accueil::Button_clicked);

        button_Jouer = Create_Button("button_Jouer","Jouer",15,true);
        connect(button_Jouer, &QPushButton::clicked, this, &Accueil::Button_clicked);

        button_Charger = Create_Button("button_Charger","Charger",15,true);
        connect(button_Charger, &QPushButton::clicked, this, &Accueil::Button_clicked);

        button_Stats = Create_Button("button_Stats","Stats",15,true);
        connect(button_Stats, &QPushButton::clicked, this, &Accueil::Button_clicked);

        button_Quitter = Create_Button("button_Quitter","Quitter",15,true);
        connect(button_Quitter,&QPushButton::clicked, this, &Accueil::Button_clicked);
    }

    //hLayout1
    {
        hLayout1->addWidget(button_Moin);
        hLayout1->addWidget(label_GridSize);
        hLayout1->addWidget(button_Plus);
    }

    //vLayout
    {
        vLayout->addWidget(label_Titre);
        vLayout->addSpacerItem(new QSpacerItem(20,20));
        vLayout->addWidget(label_Sub);
        vLayout->addLayout(hLayout1);
        vLayout->addSpacerItem(new QSpacerItem(20,20));
        vLayout->addWidget(button_Jouer);
        vLayout->addWidget(button_Charger);
        vLayout->addWidget(button_Stats);
        vLayout->addWidget(button_Quitter);
    }

    gLayout->addLayout(vLayout,0,0,Qt::AlignCenter);

    this->setCentralWidget(centralWidget);

    CheckSave();
    CheckStats();
}

Accueil::~Accueil()
{

}

void Accueil::Button_clicked()
{
    QString name = qobject_cast<QPushButton*>(sender())->objectName();

    if (name == "button_Moin")
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
    else if (name == "button_Plus")
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
    else if (name == "button_Jouer")
    {
        Jeu* w = new Jeu(GridSize, GameMode, false);
        w->showMaximized();
        this->close();
    }
    else if (name == "button_Charger")
    {
        Jeu* w = new Jeu(GridSize, GameMode, true);
        w->showMaximized();
        this->close();
    }
    else if (name == "button_Stats")
    {
        Stats* w = new Stats(GridSize, GameMode);
        w->showMaximized();
        this->close();
    }
    else if (name == "button_Quitter")
    {
        this->close();
    }

}

void Accueil::CheckSave()
{
    QFile file("Save.txt");

    if(!file.exists())
    {
       button_Charger->setEnabled(false);
    }
    else
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            if(in.readLine().length()>5)
            {
                button_Charger->setEnabled(true);
            }
            else
            {
                button_Charger->setEnabled(false);
            }
            file.close();
        }
        else
        {
            button_Charger->setEnabled(false);
        }
    }
}

void Accueil::CheckStats()
{
    QFile file("Stats.txt");

    if(!file.exists())
    {
       button_Stats->setEnabled(false);
    }
    else
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            if(in.readLine().length()>5)
            {
                button_Stats->setEnabled(true);
            }
            else
            {
                button_Stats->setEnabled(false);
            }
            file.close();
        }
        else
        {
            button_Stats->setEnabled(false);
        }
    }

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
