/*
* Nom des cr�ateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de cr�ation : 05/04/2021 � 19/04/2021
* Nom de fichier : instruction.h
* Description : Permet de cr�er l'interface d'instruction
*/
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "needed.h"

class Instruction:public QWidget
{
public:
	Instruction(QWidget* parent);


	QPushButton* Create_Button(QString nom, QString text, int size, bool bold);
	QLabel* Create_Label(QString nom, QString text, int size, bool bold);

private:
	QGridLayout* gLayout;
	QVBoxLayout* vLayout;

	QLabel* label_Titre;
	QLabel* label_Info;

	QPushButton* bouton_Quitter;


};

#endif // !INSTRUCTION_H



