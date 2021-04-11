#ifndef MYLAYOUTGRID_H
#define MYLAYOUTGRID_H



#include <QGraphicsLayoutItem>
class MyLayoutGrid : public QGraphicsLayoutItem
{
public:
	MyLayoutGrid();//faut lui envoyer comme parent de la vue qui le contient
	
	virtual void setGeometry();
	virtual void updateGeometry();

private:

protected:
	virtual QGraphicsLayoutItem sizeHint();

};
#endif // MYLAYOUTGRID_H