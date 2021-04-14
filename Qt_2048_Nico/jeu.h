#ifndef JEU_H
#define JEU_H

#include "needed.h"
#include "Fpga.h"
#include "Grid.h"

class Jeu : public QWidget
{
public:
    Jeu(int* size, bool load = false);
    ~Jeu();

    //Jeu
    QString Bouge_Haut();
    QString Bouge_Droit();
    QString Bouge_Bas();
    QString Bouge_Gauche();
    void CustomLabel(QLabel* label);
    QPushButton* Create_Button_Jeu(QString nom, QString text, int size, bool bold, bool custom);
    QLabel* Create_Label_Jeu(QString nom, QString text, int size, bool bold, bool info, bool custom);
    void Refresh_Grid();

    void keyPressEvent(QKeyEvent* event);

    void CheckMove(QString s);
    void SaveGame();
    void SaveStats(QString s);
    void ClearFile();
    QString Menu();

    QPushButton* button_Accueil;

private slots:
    void FPGA_Timer();
    void Button_clicked();
    void Button_Pressed();
    void Button_Released();

private:
    //Jeu
    QTimer* Timer;
    bool Loaded;
    int read_Time = 10;
    int wait_Time = 250;
    QLabel*** labelGrid;
    QLabel* label_Score;
    QLabel* label_NbMove;
    QLabel* label_Max;

    int* GridSize;

    Grid* grid;
    Fpga* fpga;
};

#endif // JEU_H
