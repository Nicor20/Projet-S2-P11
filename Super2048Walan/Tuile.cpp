
#include <QFileInfo>

#include "Tuile.h"



Tuile::Tuile()
{
	qDebug() << "Tuile basique creer";
}

Tuile::Tuile(int valeur)
{
	//crée la tuile
	setRect(0,0, Size, Size);
	Valeur = valeur;
	//qDebug() << Valeur;

	setValeur(valeur);
}

Tuile::~Tuile()
{
	qDebug() << "Tuile Detruite";
}

int Tuile::getSize()
{
	return Size;
}

void Tuile::setSize(int NouvSize)
{
	Size = NouvSize;
}

int Tuile::getValeur()
{
	return Valeur;
}

void Tuile::setValeur(int NouvValeur)
{
	Valeur = NouvValeur;

	if (Valeur == 2)
	{
		//qDebug() << "tuile 2";
		setBrush(Qt::lightGray);
		//setPixmap(QPixmap(":/Assets/Tuile2.png"));

	}
	else if (Valeur == 4)
	{
		//qDebug() << "tuile 4";
		setBrush(Qt::gray);
		//setPixmap(QPixmap(":/Tuile4.png"));
	}
	else if (Valeur == 8)
	{
		//qDebug() << "tuile 8";
		setBrush(Qt::cyan);
		//setPixmap(QPixmap(":/Tuile8.png"));
	}
	else if (Valeur == 16)
	{
		//qDebug() << "tuile 16";
		setBrush(Qt::darkCyan);
		//setPixmap(QPixmap(":/Tuile16.png"));
	}
	else if (Valeur == 32)
	{
		//qDebug() << "tuile 32";
		setBrush(Qt::blue);
		//setPixmap(QPixmap(":/Tuile32.png"));
	}
	else if (Valeur == 64)
	{
		//qDebug() << "tuile 64";
		setBrush(Qt::darkBlue);
		//setPixmap(QPixmap(":/Tuile64.png"));
	}
	else if (Valeur == 128)
	{
		//qDebug() << "tuile 128";
		setBrush(Qt::darkGreen);
		//setPixmap(QPixmap(":/Tuile128.png"));
	}
	else if (Valeur == 256)
	{
		//qDebug() << "tuile 256";
		setBrush(Qt::red);
		//setPixmap(QPixmap(":/Tuile256.png"));
	}
	else if (Valeur == 512)
	{
		//qDebug() << "tuile 512";
		setBrush(Qt::darkRed);
		//setPixmap(QPixmap(":/Tuile512.png"));
	}
	else if (Valeur == 1024)
	{
		//qDebug() << "tuile 1024";
		setBrush(Qt::magenta);
		//setPixmap(QPixmap(":/Ressources/Assets/Tuile1024.png"));

	}
	else if (Valeur == 2048)
	{
		//qDebug() << "tuile 2048";
		setBrush(Qt::darkMagenta);
		//setPixmap(QPixmap(":/Ressources/Assets/Tuile2048.png"));
	}
	else
	{
		//qDebug() << "tuile blanche";
		setBrush(Qt::white);
		//qDebug() << "File exists -" << QFileInfo("Ressources/Assets/TuileVide.png").exists() << " " << QFileInfo("Ressources/Assets/TuileVide.png").absoluteFilePath();
		//setPixmap(QPixmap(":/Ressources/Assets/TuileVide.png"));
		//show();
	}
}

int Tuile::getExiste()
{
	return Existe;
}