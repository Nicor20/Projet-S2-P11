#include "stats.h"

Stats::Stats(int size, int mode) : GridSize(size) , GameMode(mode)
{
    this->setObjectName("Stats");

    //Widget
    {
        centralWidget = new QWidget(this);
        centralWidget->setObjectName("centralWidget");
    }


    


    //Label
    {
        int style = QFrame::WinPanel | QFrame::Raised;
        int line = 4;
        int midLine = 3;

        label_Titre = Create_Label("label_Titre", "LeaderBoard", 50, true);

        label_Position = Create_Label("label_Position", "Position", 15, true);
        Frame_Label(label_Position, style, line, midLine);
        Color_Label(label_Position, 0, "1");

        label_Status = Create_Label("label_Status","Status",15,true);
        Frame_Label(label_Status, style, line, midLine);
        Color_Label(label_Status, 0, "1");

        label_Size = Create_Label("label_Size","Size",15,true);
        Frame_Label(label_Size, style, line, midLine);
        Color_Label(label_Size, 0, "1");

        label_Score = Create_Label("label_Score","Score",15,true);
        Frame_Label(label_Score, style, line, midLine);
        Color_Label(label_Score, 0, "1");

        label_NbMove = Create_Label("label_NbMove","Nb Move",15,true);
        Frame_Label(label_NbMove, style, line, midLine);
        Color_Label(label_NbMove, 0, "1");

        label_Max = Create_Label("label_Max","Max",15,true);
        Frame_Label(label_Max, style, line, midLine);
        Color_Label(label_Max, 0, "1");
    }

    //Button
    {
        button_Menu = Create_Button("button_Menu","Menu",15,true);
        connect(button_Menu,&QPushButton::clicked,this,&Stats::Button_clicked);
    }

    //Layout
    {
        gLayout = new QGridLayout(centralWidget);
        gLayout->setObjectName("gLayout");

        vLayout = new QVBoxLayout(centralWidget);
        vLayout->setObjectName("vLayout");

        Stats_gLayout = new QGridLayout(centralWidget);
        Stats_gLayout->setObjectName("Stats_gLayout");
    }

    //Stats_gLayout
    {
        Stats_gLayout->addWidget(label_Position, 0, 0);
        Stats_gLayout->addWidget(label_Status, 0, 1);
        Stats_gLayout->addWidget(label_Size, 0, 2);
        Stats_gLayout->addWidget(label_Score, 0, 3);
        Stats_gLayout->addWidget(label_NbMove, 0, 4);
        Stats_gLayout->addWidget(label_Max, 0, 5);

        Stats_gLayout->setColumnMinimumWidth(0, 120);
        Stats_gLayout->setColumnMinimumWidth(1, 120);
        Stats_gLayout->setColumnMinimumWidth(2, 120);
        Stats_gLayout->setColumnMinimumWidth(3, 120);
        Stats_gLayout->setColumnMinimumWidth(4, 120);
        Stats_gLayout->setColumnMinimumWidth(5, 120);

        Read();
        Sort();

        Shown = (ListGame.size() > Shown ? Shown: ListGame.size());
        
        QLabel* temp;
        for (int i = 0; i < Shown; i++)
        {
            temp = Create_Label("label_Position" + QString::number(i + 1), "#" + QString::number(i + 1), 15, false);
            Color_Label(temp, i, "2/3/4");
            Stats_gLayout->addWidget(temp, i + 1, 0);

            temp = Create_Label("label_Status" + QString::number(i + 1), ListGame[i].Status, 15, false);
            Color_Label(temp, i, "2/3/4");
            Stats_gLayout->addWidget(temp,i+1,1);

            temp = Create_Label("label_Size" + QString::number(i + 1), ListGame[i].Size, 15, false);
            Color_Label(temp, i, "2/3/4");
            Stats_gLayout->addWidget(temp, i + 1, 2);

            temp = Create_Label("label_Score" + QString::number(i + 1), QString::number(ListGame[i].Score), 15, false);
            Color_Label(temp, i, "2/3/4");
            Stats_gLayout->addWidget(temp, i + 1, 3);

            temp = Create_Label("label_NbMove" + QString::number(i + 1), QString::number(ListGame[i].NbMove), 15, false);
            Color_Label(temp, i, "2/3/4");
            Stats_gLayout->addWidget(temp, i + 1, 4);

            temp = Create_Label("label_Max" + QString::number(i + 1), QString::number(ListGame[i].Max), 15, false);
            Color_Label(temp, i, "2/3/4");
            Stats_gLayout->addWidget(temp, i + 1, 5);
        }
    }

    //Frame
    {
        frame = new QFrame(centralWidget);
        frame->setObjectName("Frame");
        frame->setFrameStyle(QFrame::Box | QFrame::Plain);
        frame->setLineWidth(2);
        frame->setMidLineWidth(3);
        frame->setLayout(Stats_gLayout);
    }


    //vLayout
    {
        vLayout->addWidget(label_Titre);
        vLayout->addSpacerItem(new QSpacerItem(40, 20));
        vLayout->addWidget(frame);
        //vLayout->addLayout(Stats_gLayout);
        vLayout->addSpacerItem(new QSpacerItem(40, 20));
        vLayout->addWidget(button_Menu);
    }

    
    gLayout->addLayout(vLayout,0,0,Qt::AlignCenter);

    this->setCentralWidget(centralWidget);
}

Stats::~Stats()
{

}

void Stats::Button_clicked()
{
    QString name = qobject_cast<QPushButton*>(sender())->objectName();

    if (name == "button_Menu")
    {
        Accueil* w = new Accueil(GridSize, GameMode);
        w->showMaximized();
        this->close();
    }
}

void Stats::Read()
{
    int i = 1;
    QFile file("Stats.txt");

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

QPushButton* Stats::Create_Button(QString nom, QString text,int size, bool bold)
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

QLabel* Stats::Create_Label(QString nom, QString text,int size, bool bold)
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

void Stats::Color_Label(QLabel* label, int num, QString rule)
{
    label->setAutoFillBackground(true);
    int Cval;
    if (rule.contains("/") == true)
    {
        QList<QString> tab = rule.split("/");
        int pos = num % (tab.size());
        Cval = tab[pos].toInt();
    }
    else
    {
        Cval = rule.toInt();
        
    }


    if (Cval == 1)
    {
        label->setStyleSheet("QLabel { background-color : rgb(193, 225, 236); }");
    }
    else if (Cval == 2)
    {
        label->setStyleSheet("QLabel { background-color : rgb(212,235,242); }");
    }
    else if (Cval == 3)
    {
        label->setStyleSheet("QLabel { background-color : rgb(232,244,248); }");
    }
    else if (Cval == 4)
    {

    }
}

void Stats::Frame_Label(QLabel* label, int style, int l1, int l2)
{
    label->setFrameStyle(style);
    label->setLineWidth(l1);
    label->setMidLineWidth(l2);
}
