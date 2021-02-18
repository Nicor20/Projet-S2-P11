#include "accueil.h"
#include "ui_accueil.h"

Accueil::Accueil(QWidget *parent) : QMainWindow(parent), ui(new Ui::Accueil)
{
    ui->setupUi(this);
}

Accueil::~Accueil()
{
    delete ui;
}

void Accueil::on_Bouton_Jouer_clicked()
{

}

void Accueil::on_Bouton_Setting_clicked()
{

}

void Accueil::on_Bouton_Quitter_clicked()
{

}
