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
        label = new QLabel*[6];
        label[0] = Create_Label("label_Titre","Stats",50,true);
        label[1] = Create_Label("label_Status","Status",15,true);
        label[2] = Create_Label("label_Size","Size",15,true);
        label[3] = Create_Label("label_Points","Points",15,true);
        label[4] = Create_Label("label_Move","Nb Move",15,true);
        label[5] = Create_Label("label_Max","Max",15,true);

    }

    //Button
    {
        button = new QPushButton*[8];
        button[0] = Create_Button("button_Menu","Menu",15,true);        //button_GridMoin


        connect(button[0],SIGNAL(clicked()),this,SLOT(Menu_clicked()));

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
        Stats_gLayout->addWidget(label[1],0,0);
        Stats_gLayout->addWidget(label[2],0,1);
        Stats_gLayout->addWidget(label[3],0,2);
        Stats_gLayout->addWidget(label[4],0,3);
        Stats_gLayout->addWidget(label[5],0,4);

        QString filename = "Stats.txt";
        int i = 1;
        QFile file(filename);

        if (!file.exists())
        {
            qDebug()<<"Error. File not found";
        }
        else
        {
            qDebug()<<"File found";
        }

        QString line;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&file);
            while(!in.atEnd())
            {
                QList temp = in.readLine().split("/");
                for(int a = 0; a<5;a++)
                {
                    Stats_gLayout->addWidget(Create_Label("l"+QString::number(i)+QString::number(a),temp[a],15,false),i,a);
                }
                i++;
            }
        }

        file.close();
    }

    //vLayout
    {
        vLayout->addWidget(label[0]);
        vLayout->addSpacerItem(new QSpacerItem(40,20));
        vLayout->addLayout(Stats_gLayout);

        vLayout->addWidget(button[0]);
    }

    gLayout->addLayout(vLayout,0,0,Qt::AlignCenter);

    this->setCentralWidget(centralWidget);
}

Stats::~Stats()
{

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

void Stats::Menu_clicked()
{
    Accueil *w = new Accueil(GridSize,GameMode);
    w->showMaximized();
    this->close();
}
