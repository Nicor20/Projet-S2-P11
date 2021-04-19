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



