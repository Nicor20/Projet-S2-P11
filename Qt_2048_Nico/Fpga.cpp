/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 15/04/2021
* Nom de fichier : Fpga.cpp
* Description : Permet de gérer la lecture de la carte Fpga
*/
#include "Fpga.h"

Fpga::Fpga()
{
    //Instancie la connection avec la carte fpga et les valeurs de référence pour chaque phonème
    port = new CommunicationFPGA();

    if (!port->estOk())
    {
        cout << port->messageErreur() << endl;
    }
    else
    {
        cout << "Statut initial du port de communication = " << port->estOk() << endl << endl;
    }

    int statut_circuit = 0;
    statutport = port->lireRegistre(nreg_lect_stat_btn, statut_circuit);

    //Phoneme 'a'
    {
        valPhoneme[0].val[0][0] = 60;		//min pot1
        valPhoneme[0].val[0][1] = 90;		//max pot1
        valPhoneme[0].val[1][0] = 520;		//min pot2
        valPhoneme[0].val[1][1] = 610;		//max pot2
        valPhoneme[0].val[2][0] = 20;		//min pot3
        valPhoneme[0].val[2][1] = 60;		//max pot3
        valPhoneme[0].val[3][0] = 90;		//min pot4
        valPhoneme[0].val[3][1] = 170;		//max pot4
    }

    //Phoneme 'e'
    {
        valPhoneme[1].val[0][0] = 180;		//min pot1
        valPhoneme[1].val[0][1] = 270;		//max pot1
        valPhoneme[1].val[1][0] = 60;		//min pot2
        valPhoneme[1].val[1][1] = 100;		//max pot2
        valPhoneme[1].val[2][0] = 300;		//min pot3
        valPhoneme[1].val[2][1] = 530;		//max pot3
        valPhoneme[1].val[3][0] = 130;		//min pot4
        valPhoneme[1].val[3][1] = 240;		//max pot4
    }

    //Phoneme 'eu'
    {
        valPhoneme[2].val[0][0] = 550;		//min pot1
        valPhoneme[2].val[0][1] = 830;		//max pot1
        valPhoneme[2].val[1][0] = 180;		//min pot2
        valPhoneme[2].val[1][1] = 280;		//max pot2
        valPhoneme[2].val[2][0] = 240;		//min pot3
        valPhoneme[2].val[2][1] = 390;		//max pot3
        valPhoneme[2].val[3][0] = 40;		//min pot4
        valPhoneme[2].val[3][1] = 110;		//max pot4
    }

    //Phoneme 'i'
    {
        valPhoneme[3].val[0][0] = 500;		//min pot1
        valPhoneme[3].val[0][1] = 780;		//max pot1
        valPhoneme[3].val[1][0] = 0;		//min pot2
        valPhoneme[3].val[1][1] = 60;		//max pot2
        valPhoneme[3].val[2][0] = 430;		//min pot3
        valPhoneme[3].val[2][1] = 615;		//max pot3
        valPhoneme[3].val[3][0] = 585;		//min pot4
        valPhoneme[3].val[3][1] = 810;		//max pot4
    }


    //Phoneme 'a' = ( 0x16 - 0x8D - 0x0A - 0x20 )

    //Phoneme 'e' = ( 0x38 - 0x14 - 0x68 - 0x2E )

    //Phoneme 'eu' = ( 0xAD - 0x3A - 0x4F - 0x16 )

    //Phoneme 'i' = ( 0xA0 - 0x08 - 0x83 - 0xAE )

}

Fpga::~Fpga()
{

}

bool Fpga::isConnected()
{
    //Vérifie si la connection est ok
    return statutport;
}

QString Fpga::Read()
{
    // lecture statut et BTN
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_stat_btn, stat_btn);
    }
    else
    {
        return "Erreur";
    }

    // lecture swt
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_swt, swt);
        statutport = port->ecrireRegistre(nreg_ecri_led, swt);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 0
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can0, Chanel[0]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 1
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can1, Chanel[1]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 2
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can2, Chanel[2]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 3
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can3, Chanel[3]);
    }
    else
    {
        return "Erreur";
    }

    if (statutport)
    {
        //Ajuster les pot
        if (swt == 0x80)	//#1
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x01);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[0]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x40)	//#2
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x02);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[1]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x20)	//#3
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x03);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[2]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x10)	//#4
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x04);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[3]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x00);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, 0x00);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x00);
        }
        
        
        if (stat_btn == 0x11 && swt == 0x00 && SaveOn == false && VerifOn == false)	
        {
            //Lance la lecture
            SaveOn = true;
            return "LecStart";
        }
        else if (SaveOn == true && nbRead < nbToRead && VerifOn == false)	
        {
            //Enregistre les lectures
            for (int i = 0; i < 4; i++)
                ListLecture[nbRead].pot[i] = Chanel[i];

            nbRead++;
            return "Lec";
        }
        else if (SaveOn == true && nbRead == nbToRead && VerifOn == false)
        {
            //Arrête la lecture
            SaveOn = false;
            VerifOn = true;
            return "LecStop";
        }
        else if (SaveOn == false && VerifOn == true)	
        {
            //Vérifie la correspondance
            QString rep = Verification();
            VerifOn = false;
            nbRead = 0;
            return rep;
        }

        return "Rien";
    }
    else
    {
        return "Erreur";
    }
}

QString Fpga::Verification()
{
    //effectue la comparaison pour déterminer le phonème dit
    int pointage[4] = { 0 };
    int lecture;
    for (int a = 0; a < nbToRead; a++) // lecture #1 a #10
    {
        for (int b = 0; b < 4; b++)// pot #1 a #4
        {
            for (int c = 0; c < 4; c++) //Phonème #1 a #4
            {
                lecture = ListLecture[a].pot[b] * 4;

                if (lecture >= valPhoneme[c].val[b][0] && lecture <= valPhoneme[c].val[b][1])
                {
                    //cout << dec << "l=" << to_string(a + 1) << " P=" << to_string(b + 1) << " h=" << to_string(c + 1) << " val=";
                    //cout << hex << to_string(ListLecture[a].pot[b]) << endl;
                    pointage[c]++;
                }
            }
        }
    }

    //Trouver le correspondant
    int max = 0;
    int num = 0;
    int seuil = floor((4.0 * nbToRead) * 0.8);
    for (int i = 0; i < 4; i++)
    {
        if (pointage[i] >= max)
        {
            num = i + 1;
            max = pointage[i];
        }
    }

    cout << "Nombre de bon = " << to_string(max) << "\nNum : " << to_string(num) << endl;
    if (num == 1 && max >= seuil)
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, num);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        return "Haut";
    }
    else if (num == 2 && max >= seuil)
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, num);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        return "Droit";
    }
    else if (num == 3 && max >= seuil)
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, num);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        return "Bas";
    }
    else if (num == 4 && max >= seuil)
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, num);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, pointage[num - 1]);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        return "Gauche";
    }
    else
    {
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x0E);
        statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, 0xE0);
        statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0);
        return "Aucun";
    }
}

QString Fpga::LectureRecord()
{
    // lecture statut et BTN
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_stat_btn, stat_btn);
    }
    else
    {
        return "Erreur";
    }

    // lecture swt
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_swt, swt);
        statutport = port->ecrireRegistre(nreg_ecri_led, swt);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 0
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can0, Chanel[0]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 1
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can1, Chanel[1]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 2
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can2, Chanel[2]);
    }
    else
    {
        return "Erreur";
    }

    // lecture canal 3
    if (statutport)
    {
        statutport = port->lireRegistre(nreg_lect_can3, Chanel[3]);
    }
    else
    {
        return "Erreur";
    }

    if (statutport)
    {
        //Ajuster les pot
        if (swt == 0x80)	//#1
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x01);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[0]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x40)	//#2
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x02);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[1]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x20)	//#3
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x03);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[2]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else if (swt == 0x10)	//#4
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x04);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, Chanel[3]);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x04);
        }
        else
        {
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg0, 0x00);
            statutport = port->ecrireRegistre(nreg_ecri_aff7sg1, 0x00);
            statutport = port->ecrireRegistre(nreg_ecri_aff7dot, 0x00);
        }


        if (stat_btn == 0x11 && swt == 0x00 && RecordOn == false && AnalyzeOn == false)
        {
            //Lance la lecture
            RecordOn = true;
            return "LecStart";
        }
        else if (RecordOn == true && nbRecord < nbToRecord && AnalyzeOn == false)
        {
            //Enregistre les lectures
            SBA[nbRecord] = Chanel[0];
            SBB[nbRecord] = Chanel[1];
            SBC[nbRecord] = Chanel[2];
            SBD[nbRecord] = Chanel[3];

            nbRecord++;
            return "Lec";
        }
        else if (RecordOn == true && nbRecord == nbToRecord && AnalyzeOn == false)
        {
            //Arrête la lecture
            RecordOn = false;
            AnalyzeOn = true;
            return "LecStop";
        }
        else if (RecordOn == false && AnalyzeOn == true)
        {
            //Vérifie la correspondance
            QString rep = AnalyzeRecord();
            AnalyzeOn = false;
            nbRecord = 0;
            return rep;
        }

        return "Rien";
    }
    else
    {
        return "Erreur";
    }
}

QString Fpga::AnalyzeRecord()
{
    //SBA
    {
        int minimum = 0, moyenne = 0, maximum = 0, pourcentage = 0;
        sort(std::begin(SBA),std::end(SBA));
        //Calculs


        //Inscription
        RecordValue.SBA[0] = QString::number(minimum);
        RecordValue.SBA[1] = QString::number(moyenne);
        RecordValue.SBA[2] = QString::number(maximum);
        RecordValue.SBA[3] = QString::number(pourcentage);
    }

    //SBB
    {
        int minimum = 0, moyenne = 0, maximum = 0, pourcentage = 0;
        sort(std::begin(SBB), std::end(SBB));
        //Calculs


        //Inscription
        RecordValue.SBB[0] = QString::number(minimum);
        RecordValue.SBB[1] = QString::number(moyenne);
        RecordValue.SBB[2] = QString::number(maximum);
        RecordValue.SBB[3] = QString::number(pourcentage);
    }

    //SBC
    {
        int minimum = 0, moyenne = 0, maximum = 0, pourcentage = 0;
        sort(std::begin(SBC), std::end(SBC));
        //Calculs


        //Inscription
        RecordValue.SBC[0] = QString::number(minimum);
        RecordValue.SBC[1] = QString::number(moyenne);
        RecordValue.SBC[2] = QString::number(maximum);
        RecordValue.SBC[3] = QString::number(pourcentage);
    }

    //SBD
    {
        int minimum = 0, moyenne = 0, maximum = 0, pourcentage = 0;
        sort(std::begin(SBD), std::end(SBD));
        //Calculs


        //Inscription
        RecordValue.SBD[0] = QString::number(minimum);
        RecordValue.SBD[1] = QString::number(moyenne);
        RecordValue.SBD[2] = QString::number(maximum);
        RecordValue.SBD[3] = QString::number(pourcentage);
    }

    return "Done";
}

void Fpga::SaveRecord(QString s)
{
    QFile file(s);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream in(&file);

    in << RecordValue.SBA[0] + "-" + RecordValue.SBA[1] + "-" + RecordValue.SBA[2] + "-" + RecordValue.SBA[3] + "\n";
    in << RecordValue.SBB[0] + "-" + RecordValue.SBB[1] + "-" + RecordValue.SBB[2] + "-" + RecordValue.SBB[3] + "\n";
    in << RecordValue.SBC[0] + "-" + RecordValue.SBC[1] + "-" + RecordValue.SBC[2] + "-" + RecordValue.SBC[3] + "\n";
    in << RecordValue.SBD[0] + "-" + RecordValue.SBD[1] + "-" + RecordValue.SBD[2] + "-" + RecordValue.SBD[3] + "\n";

    file.close();
}