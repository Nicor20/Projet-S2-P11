#include "UI.h"

UI::UI()
{
    this->setObjectName("UI");

    Load_Accueil();

    //Background
    QPixmap bk(":/Resources/BG.png");
    bk = bk.scaled(qApp->primaryScreen()->size(), Qt::IgnoreAspectRatio);
    QPalette pa;
    pa.setBrush(QPalette::Window, bk);
    this->setPalette(pa);
}

UI::~UI()
{

}

void UI::Load_Accueil()
{
    accueil = new Accueil(&GridSize);

    connect(accueil->button_Jouer, &QPushButton::clicked, this, &UI::Button_clicked);
    connect(accueil->button_Charger, &QPushButton::clicked, this, &UI::Button_clicked);
    connect(accueil->button_Stats, &QPushButton::clicked, this, &UI::Button_clicked);
    connect(accueil->button_Quitter, &QPushButton::clicked, this, &UI::Button_clicked);

    this->setCentralWidget(accueil);
}

void UI::Load_Jeu(bool load)
{
    jeu = new Jeu(&GridSize, load);
    connect(jeu->button_Accueil, &QPushButton::clicked, this, &UI::Button_clicked);
    this->setCentralWidget(jeu);
}

void UI::Load_Stats()
{
    stats = new Stats();
    connect(stats->button_Accueil, &QPushButton::clicked, this, &UI::Button_clicked);
    this->setCentralWidget(stats);
}

void UI::Button_clicked()
{
    QString name = qobject_cast<QPushButton*>(sender())->objectName();

    if (name == "button_Accueil_Jouer")    //Accueil
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
    else if (name == "button_Jeu_Accueil")
    {
        QString rep = jeu->Menu();

        if (rep == "Sauvegarde" || rep == "Rien")
        {
            Load_Accueil();
        }
        else if (rep == "Erreur ouverture")
        {
            cout << "Erreur ouverture" << endl;
            Load_Accueil();
        }
        else if (rep == "Fichier introuvable")
        {
            cout << "Fichier introuvable" << endl;
            Load_Accueil();
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