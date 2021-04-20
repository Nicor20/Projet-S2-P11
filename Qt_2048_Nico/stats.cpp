/*
* Nom des cr�ateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de cr�ation : 05/04/2021 � 19/04/2021
* Nom de fichier : stats.cpp
* Description : Permet de cr�er l'interface de classement et de g�rer son fonctionnement et ces int�ractions
*/

#include "stats.h"

Stats::Stats(QWidget* parent) : QWidget(parent)
{
    //Permet de cr�er les �l�ments de l'interface de classement
    this->setObjectName("widget_Stats");

    //Label
    QLabel* label_Titre = Create_Label_Stats("label_Titre", "Classement", 75, true, false, false);
    QLabel* label_Position = Create_Label_Stats("label_Position", "Position", 20, true, true, false);
    QLabel* label_Status = Create_Label_Stats("label_Status", "Status", 20, true, true, false);
    QLabel* label_Size = Create_Label_Stats("label_Size", "Size", 20, true, true, false);
    QLabel* label_Score = Create_Label_Stats("label_Score", "Score", 20, true, true, false);
    QLabel* label_NbMove = Create_Label_Stats("label_NbMove", "Nb Move", 20, true, true, false);
    QLabel* label_Max = Create_Label_Stats("label_Max", "Max", 20, true, true, false);

    //Button
    Bouton_Quitter = Create_Button_Stats("button_Stats_Accueil", "Menu", 20, true);
    connect(Bouton_Quitter, SIGNAL(clicked()), parent, SLOT(Bouton_Stats_Quitter_Clicked()));

    Bouton_Effacer = Create_Button_Stats("button_Stats_Effacer", "Effacer", 20, true);
    connect(Bouton_Effacer, SIGNAL(clicked()), this, SLOT(Bouton_Effacer_Clicked()));

    //Layout
    QGridLayout* gLayout = new QGridLayout(this);
    gLayout->setObjectName("gLayout");

    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->setObjectName("vLayout");

    QGridLayout* Stats_gLayout = new QGridLayout();
    Stats_gLayout->setObjectName("Stats_gLayout");


    Read();
    Sort();

    //Stats_gLayout
    {
        Stats_gLayout->addWidget(label_Position, 0, 0);
        Stats_gLayout->addWidget(label_Status, 0, 1);
        Stats_gLayout->addWidget(label_Size, 0, 2);
        Stats_gLayout->addWidget(label_Score, 0, 3);
        Stats_gLayout->addWidget(label_NbMove, 0, 4);
        Stats_gLayout->addWidget(label_Max, 0, 5);

        QLabel* temp;

        int nb = (ListGame.size() > NbToShow ? NbToShow : ListGame.size());
        for (int i = 0; i < nb; i++)
        {
            temp = Create_Label_Stats("label_Position" + QString::number(i + 1), "#" + QString::number(i + 1), 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 0);

            temp = Create_Label_Stats("label_Status" + QString::number(i + 1), ListGame[i].Status, 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 1);

            temp = Create_Label_Stats("label_Size" + QString::number(i + 1), ListGame[i].Size, 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 2);

            temp = Create_Label_Stats("label_Score" + QString::number(i + 1), QString::number(ListGame[i].Score), 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 3);

            temp = Create_Label_Stats("label_NbMove" + QString::number(i + 1), QString::number(ListGame[i].NbMove), 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 4);

            temp = Create_Label_Stats("label_Max" + QString::number(i + 1), QString::number(ListGame[i].Max), 15, false, false, true, i);
            Stats_gLayout->addWidget(temp, i + 1, 5);
        }
    }

    //Frame
    QFrame* frame = new QFrame();
    frame->setObjectName("Frame");
    frame->setFrameStyle(QFrame::Box | QFrame::Plain);
    frame->setLineWidth(4);
    frame->setMidLineWidth(3);
    frame->setLayout(Stats_gLayout);
    frame->setAutoFillBackground(true);
    frame->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");

    //vLayout
    vLayout->addWidget(label_Titre);
    vLayout->addSpacerItem(new QSpacerItem(40, 20));
    vLayout->addWidget(Bouton_Effacer);
    vLayout->addSpacerItem(new QSpacerItem(40, 20));
    vLayout->addWidget(frame);
    vLayout->addSpacerItem(new QSpacerItem(40, 20));
    vLayout->addWidget(Bouton_Quitter);
    

    gLayout->addLayout(vLayout, 0, 0, Qt::AlignCenter);
}

Stats::~Stats()
{

}

void Stats::Read()
{
    //Lis les �l�ments du fichier Stats.2048 et les insert dans une liste de structure Game
    int i = 1;
    QFile file("Stats.2048");

    if (file.exists())
    {
        QString line;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while (!in.atEnd())
            {
                line = in.readLine();
                Game g;
                g.Status = line.split("/")[0];
                g.Size = line.split("/")[1];
                g.Score = line.split("/")[2].toInt();
                g.NbMove = line.split("/")[3].toInt();
                g.Max = line.split("/")[4].toInt();
                ListGame.append(g);
            }
        }
        file.close();
    }
    else
    {
        qDebug() << "Error. File not found";
    }
}

void Stats::Sort()
{
    //Tris les �l�ments de la Liste
    //Overall = (Max + (score/Move))/size

    for (int i = 0; i < ListGame.size(); i++)
    {
        ListGame[i].Overall = ListGame[i].Max;
        ListGame[i].Overall += ListGame[i].Score / ListGame[i].NbMove;
        ListGame[i].Overall /= ListGame[i].Size.split("x")[0].toInt();
    }

    QList<Game> temp;
    while (ListGame.size() != 0)
    {
        int pos = 0;
        for (int i = 0; i < ListGame.size(); i++)
        {
            if (ListGame[i].Overall >= ListGame[pos].Overall)
            {
                pos = i;
            }
        }
        temp.append(ListGame[pos]);
        ListGame.removeAt(pos);
    }
    ListGame = temp;
}

QPushButton* Stats::Create_Button_Stats(QString nom, QString text, int size, bool bold)
{   
    //Fonction pour cr�er des boutons pour la classe Stats
    QFont font;
    QPushButton* button = new QPushButton();
    button->setObjectName(nom);
    button->setText("&"+text);
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

QLabel* Stats::Create_Label_Stats(QString nom, QString text, int size, bool bold, bool info, bool stats, int num)
{
    //Fonction pour cr�er les Labels pour la classe Stats
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
        label->setFixedWidth(150);
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

void Stats::Bouton_Effacer_Clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Super 2048");

    QFont font = msgBox.font();
    font.setPointSize(15);
    font.setBold(false);
    msgBox.setFont(font);

    msgBox.setText("Voulez vous vraiment effacer les donnees du classement?");
    QPushButton* boutonOui = msgBox.addButton("Oui", QMessageBox::YesRole);
    QPushButton* boutonNon = msgBox.addButton("Non", QMessageBox::NoRole);
    msgBox.setDefaultButton(boutonNon);
    msgBox.exec();

    if (msgBox.clickedButton() == boutonOui)
    {
        QFile file("Stats.2048");

        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            in << "";
        }
        file.close();
        Bouton_Quitter->animateClick();
    }
}