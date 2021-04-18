#ifndef RECORD_H
#define RECORD_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include "Fpga.h"

class Record : public QWidget
{
	Q_OBJECT
public:
	Record(QWidget* parent);
	~Record();

	void DoneRecord();

	void Check();

	bool Menu();

	QPushButton* Create_Button(QString nom, QString text, int size, bool bold);
	QLabel* Create_Label(QString nom, QString text, int size, bool bold);

private slots:
	void FPGA_Timer();
	void Bouton_Moin_Clicked();
	void Bouton_Plus_Clicked();

private:
	QString Tab[4] = { "a","e","eu","i" };
	QString FileName[4] = { "PH1.2048","PH2.2048","PH3.2048","PH4.2048" };
	bool saved[4] = { false,false,false,false };

	int nbShow = 0;

	//GUI
	QGridLayout* gLayout;
	QVBoxLayout* vLayout;
	QGridLayout* gLayout_Mid;
	QFrame* frame;
	
	QLabel* Label_Titre;
	QLabel* Label_Sub;
	QLabel* Label_Choix;
	QLabel* Label_Pourcentage;

	QPushButton* Bouton_Plus;
	QPushButton* Bouton_Moin;
	QPushButton* Bouton_Quitter;



	//FPGA
	QTimer* Timer;
	Fpga* fpga;
	int read_Time = 10;
	int wait_Time = 100;
};





#endif // !RECORD_H



