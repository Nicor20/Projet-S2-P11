#include "accueil.h"

Accueil::Accueil(int* size) : GridSize(size)
{
    this->setObjectName("widget_Accueil");

    //Layout
    QGridLayout* gLayout = new QGridLayout(this);
    gLayout->setObjectName("gLayout");

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setObjectName("vLayout");

    QHBoxLayout* hLayout = new QHBoxLayout();
    hLayout->setObjectName("hLayout");

    //Label
    QLabel* label_Titre = Create_Label_Accueil("label_Titre", "Super 2048", 80, true);
    QLabel* label_Sub = Create_Label_Accueil("label_Sub", "Taille de la grille", 30, true);
    label_GridSize = Create_Label_Accueil("label_GridSize", QString::number(*GridSize) + "x" + QString::number(*GridSize), 25, true, true);

    //Button
    QPushButton* button_Moin = Create_Button_Accueil("button_Accueil_Moin", "<", 20, true, true);
    QPushButton* button_Plus = Create_Button_Accueil("button_Accueil_Plus", ">", 20, true, true);

    button_Jouer = Create_Button_Accueil("button_Accueil_Jouer", "Jouer", 20, true, false);
    button_Charger = Create_Button_Accueil("button_Accueil_Charger", "Charger", 20, true, false);
    button_Stats = Create_Button_Accueil("button_Accueil_Stats", "Stats", 20, true, false);
    button_Quitter = Create_Button_Accueil("button_Accueil_Quitter", "Quitter", 20, true, false);

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

    //Check Save
    button_Charger->setEnabled(CheckSave());

    //Check Stats
    button_Stats->setEnabled(CheckStats());
}

Accueil::~Accueil()
{

}

bool Accueil::CheckSave()
{
    QFile file("Game.2048");

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            if(in.readLine().length()>5)
            {
                return true;
            }
            else
            {
                return false;
            }
            file.close();
        }
        else
        {
            return false;
        }
    }
    else
    {
        CreateSave();
        return false;
    }
}

bool Accueil::CheckStats()
{
    QFile file("Stats.2048");

    if(file.exists())
    {
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            if(in.readLine().length()>5)
            {
                return true;
            }
            else
            {
                return false;
            }
            file.close();
        }
        else
        {
            return false;
        }
    }
    else
    {
        CreateStats();
        return false;
    }

}

void Accueil::CreateSave()
{
    QFile file("Game.2048");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream << "";
    file.close();
}

void Accueil::CreateStats()
{
    QFile file("Stats.2048");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream << "";
    file.close();
}


QPushButton* Accueil::Create_Button_Accueil(QString nom, QString text, int size, bool bold, bool custom)
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
        connect(button, &QPushButton::pressed, this, &Accueil::Button_Pressed);
        connect(button, &QPushButton::released, this, &Accueil::Button_Released);
        connect(button, &QPushButton::clicked, this, &Accueil::Button_clicked);
    }
    

    return button;
}

QLabel* Accueil::Create_Label_Accueil(QString nom, QString text, int size, bool bold, bool custom)
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

void Accueil::Button_clicked()
{
    QString name = qobject_cast<QPushButton*>(sender())->objectName();

    if (name == "button_Accueil_Moin")  //Accueil
    {
        if (*GridSize > 3)
        {
            *GridSize = *GridSize-1;
        }
        else
        {
            *GridSize = 8;
        }

        label_GridSize->setText(QString::number(*GridSize) + "x" + QString::number(*GridSize));
    }
    else if (name == "button_Accueil_Plus")     //Accueil
    {
        if (*GridSize < 8)
        {
            *GridSize = *GridSize + 1;
        }
        else
        {
            *GridSize = 3;
        }

        label_GridSize->setText(QString::number(*GridSize) + "x" + QString::number(*GridSize));
    }
}

void Accueil::Button_Pressed()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(211,211,211); }");   //Dark
}

void Accueil::Button_Released()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    button->setStyleSheet("QPushButton { background-color : rgb(255,255,255); }"); //light
}