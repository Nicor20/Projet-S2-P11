#include "Record.h"

Record::Record(QWidget* parent) : QWidget(parent)
{
    fpga = new Fpga();

    //Layout
    {
        gLayout = new QGridLayout(this);
        vLayout = new QVBoxLayout(gLayout->widget());
        gLayout_Mid = new QGridLayout(vLayout->widget());
        
        
        setLayout(gLayout);
        gLayout->addLayout(vLayout,0,0,Qt::AlignCenter);

    }

	//Label
    {
        Label_Titre = Create_Label("Label Titre", "Enregistrement", 75, true);
        
        Label_Sub = Create_Label("Label Sub", "Phoneme", 30, true);
        Label_Sub->setStyleSheet("QLabel { background-color : rgba(255,255,255,0.2); }");

        Label_Choix = Create_Label("Label Choix", Tab[nbShow], 15, true);
        Label_Choix->setFrameStyle(QFrame::Box | QFrame::Plain);
        Label_Choix->setLineWidth(4);
        Label_Choix->setMidLineWidth(3);
        Label_Choix->setAutoFillBackground(true);
        Label_Choix->setStyleSheet("QLabel { background-color : rgb(255,255,255); }");


        Label_Pourcentage = Create_Label("Label Pourcentage", "0%", 20, true);
        Label_Pourcentage->setStyleSheet("QLabel { background-color : rgba(255,255,255,0.2); }");
        Label_Pourcentage->setFixedHeight(50);
    }
	
    //Bouton
    {
        Bouton_Moin = Create_Button("Bouton Moin", "<", 20, true);
        connect(Bouton_Moin, SIGNAL(clicked()), this, SLOT(Bouton_Moin_Clicked()));

        Bouton_Plus = Create_Button("Bouton Plus", ">", 20, true);
        connect(Bouton_Plus, SIGNAL(clicked()), this, SLOT(Bouton_Plus_Clicked()));

        Bouton_Quitter = Create_Button("Bouton Quitter", "Menu", 20, true);
        connect(Bouton_Quitter, SIGNAL(clicked()), parent, SLOT(Bouton_Record_Quitter_Clicked()));
    }
    
    //gLayout_Mid
    {
        gLayout_Mid->setVerticalSpacing(15);

        gLayout_Mid->addWidget(Label_Sub, 0, 0, 1, 3);
        gLayout_Mid->addWidget(Bouton_Moin, 1, 0);
        gLayout_Mid->addWidget(Label_Choix, 1, 1);
        gLayout_Mid->addWidget(Bouton_Plus, 1, 2);
        gLayout_Mid->addWidget(Label_Pourcentage, 2, 0, 1, 3);
        
        frame = new QFrame();
        frame->setObjectName("Frame");
        frame->setFrameStyle(QFrame::Box | QFrame::Plain);
        frame->setLineWidth(4);
        frame->setMidLineWidth(3);
        frame->setLayout(gLayout_Mid);
    }


    //vLayout
    vLayout->addWidget(Label_Titre);
    vLayout->addSpacerItem(new QSpacerItem(10, 40));
    vLayout->addWidget(frame);
    vLayout->addSpacerItem(new QSpacerItem(10, 40));
    vLayout->addWidget(Bouton_Quitter);
    
    //Timer
    {
        Timer = new QTimer(this);
        connect(Timer, SIGNAL(timeout()), this, SLOT(FPGA_Timer()));

        if (fpga->isConnected())
        {
            Timer->start(wait_Time);
        }
    }
}

Record::~Record()
{
    delete fpga;
}

bool Record::Menu()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Super 2048");

    QFont font = msgBox.font();
    font.setPointSize(15);
    font.setBold(false);
    msgBox.setFont(font);

    if (saved[0] == true && saved[1] == true && saved[2] == true && saved[3] == true)
    {
        msgBox.setText("Voulez vous vraiment retourner a l'accueil?");
    }
    else if (saved[0] == false && saved[1] == false && saved[2] == false && saved[3] == false)
    {
        return true;
    }
    else
    {
        msgBox.setText("Voulez vous vraiment retourner a l'accueil?");
        msgBox.setInformativeText("Vous n'avez pas enregistrer tout vos phonemes!");
    }

    QPushButton* boutonOui = msgBox.addButton("Oui", QMessageBox::YesRole);
    QPushButton* boutonNon = msgBox.addButton("Non", QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton() == boutonOui)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Record::FPGA_Timer()
{
    //Timer pour lire la carte fpga à chaque 250 millisecondes jusqu'a ce que le bouton 1 soit pesser
    //change l'intervale de lecture à 10 millisecondes et prend des mesures pendant 1 seconde et retourne a 250 ms après
    //traite le retour de la lecture

    QString text = fpga->LectureRecord();

    if (text == "LecStart")
    {
        Timer->setInterval(read_Time);

        Bouton_Moin->setEnabled(false);
        Bouton_Plus->setEnabled(false);

        cout << "Debut de lecture" << endl;
    }
    else if (text == "Lec")
    {
        Label_Pourcentage->setText(QString::number(fpga->nbRecord * 100 / fpga->GetNbToRecord()) + "%");
        Label_Pourcentage->setStyleSheet("QLabel { background-color : rgba(0, 230, 64,"+ QString::number((double)fpga->nbRecord/200.0) + "); }");
        //cout << "Lecture : "<< fpga->nbRecord << endl;
    }
    else if (text == "LecStop")
    {
        Timer->setInterval(wait_Time);
        cout << "Fin de lecture" << endl;
    }
    else if (text == "Done")
    {
        cout << "Fin de l'analyze" << endl;
        DoneRecord();
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

void Record::Bouton_Moin_Clicked()
{
    if (nbShow > 0)
    {
        nbShow--;
    }
    else
    {
        nbShow = 3;
    }

    Check();
    Label_Choix->setText(Tab[nbShow]);
}

void Record::Bouton_Plus_Clicked()
{
    Label_Pourcentage->setText("0%");
    Label_Pourcentage->setStyleSheet("QLabel { background-color : rgba(255,255,255,0.2); }");

    if (nbShow < 3)
    {
        nbShow++;
    }
    else
    {
        nbShow = 0;
    }

    Check();
    Label_Choix->setText(Tab[nbShow]);
}

void Record::Check()
{
    if (saved[nbShow] == true)
    {
        Label_Pourcentage->setText("100%");
        Label_Pourcentage->setStyleSheet("QLabel { background-color : rgb(0, 230, 64); }");
    }
    else
    {
        Label_Pourcentage->setText("0%");
        Label_Pourcentage->setStyleSheet("QLabel { background-color : rgba(255,255,255,0.2); }");
    }
}

void Record::DoneRecord()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Super 2048");

    QFont font = msgBox.font();
    font.setPointSize(15);
    font.setBold(false);
    msgBox.setFont(font);

    msgBox.setText("Voulez vous sauvegarder le phoneme?");
    msgBox.setInformativeText(fpga->RecordValue.toString());

    QPushButton* boutonOui = msgBox.addButton("Oui", QMessageBox::YesRole);
    QPushButton* boutonNon = msgBox.addButton("Non", QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton() == boutonOui)
    {
        fpga->SaveRecord(FileName[nbShow]);
        saved[nbShow] = true;
    }
    else
    {
        Check();
    }

    Bouton_Moin->setEnabled(true);
    Bouton_Plus->setEnabled(true);

    if (saved[nbShow] == true)
    {
        Bouton_Plus->animateClick();
    }
}

QPushButton* Record::Create_Button(QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer des boutons pour la classe accueil
    QFont font;
    QPushButton* button = new QPushButton(this);
    button->setObjectName(nom);
    button->setText("&" + text);
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

QLabel* Record::Create_Label(QString nom, QString text, int size, bool bold)
{
    //Fonction pour créer des label pour la classe accueil
    QFont font;
    QLabel* label = new QLabel(text,this);
    label->setObjectName(nom);
    label->setAlignment(Qt::AlignCenter);
    
    font = label->font();
    font.setPointSize(size);
    font.setBold(bold);
    label->setFont(font);

    return label;
}