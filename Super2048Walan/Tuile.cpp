
#include <QFileInfo>

#include "Tuile.h"



Tuile::Tuile()
{
	qDebug() << "Tuile basique creer";
}

Tuile::Tuile(int valeur)
{
	//crée la tuile
	setRect(0, 0, Size, Size);
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
	QBrush brush;
	//QRect rec = this->rect().toRect();


	if (Valeur == 2)
	{
		//qDebug() << "tuile 2";
		//setBrush(Qt::lightGray);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile2.png"));
		setBrush(brush);
		setOpacity(1);
		show();

	}
	else if (Valeur == 4)
	{
		//qDebug() << "tuile 4";
		//setBrush(Qt::gray);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile4.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
	else if (Valeur == 8)
	{
		//qDebug() << "tuile 8";
		//setBrush(Qt::cyan);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile8.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
	else if (Valeur == 16)
	{
		//qDebug() << "tuile 16";
		//setBrush(Qt::darkCyan);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile16.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
	else if (Valeur == 32)
	{
		//qDebug() << "tuile 32";
		//setBrush(Qt::blue);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile32.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
	else if (Valeur == 64)
	{
		//qDebug() << "tuile 64";
		//setBrush(Qt::darkBlue);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile64.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
	else if (Valeur == 128)
	{
		//qDebug() << "tuile 128";
		//setBrush(Qt::darkGreen);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile128.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
	else if (Valeur == 256)
	{
		//qDebug() << "tuile 256";
		//setBrush(Qt::red);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile256.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
	else if (Valeur == 512)
	{
		//qDebug() << "tuile 512";
		//setBrush(Qt::darkRed);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile512.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
	else if (Valeur == 1024)
	{
		//qDebug() << "tuile 1024";
		//setBrush(Qt::magenta);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile1024.png"));
		setBrush(brush);
		setOpacity(1);
		show();

	}
	else if (Valeur == 2048)
	{
		//qDebug() << "tuile 2048";
		//setBrush(Qt::darkMagenta);
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/Tuile2048.png"));
		setBrush(brush);
		setOpacity(1);
		show();

	}
	else
	{
		//qDebug() << "tuile blanche";
		//setBrush(Qt::white);
		
		brush.setTextureImage(QImage(":/Resource/Resource/60x60/TuileVide.png"));
		setBrush(brush);
		setOpacity(1);
		show();
	}
}

int Tuile::getExiste()
{
	return Existe;
}