/*
* Nom des créateur : Nicolas Cantin, Anthony Denis, Walan Brousseau
* Date de création : 05/04/2021 à 19/04/2021
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
    statutport = port->lireRegistre(nreg_lect_swt, swt);
    statutport = port->ecrireRegistre(nreg_ecri_led, swt);

    CreatePhoneme();
}

Fpga::~Fpga()
{
    if (port->estOk())
    {
        delete port;
        //port->~CommunicationFPGA();
    }
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
            SBA_L[nbRead] = Chanel[0];
            SBB_L[nbRead] = Chanel[1];
            SBC_L[nbRead] = Chanel[2];
            SBD_L[nbRead] = Chanel[3];
            cout << "SBA(" << Chanel[0] << ") SBB(" << Chanel[1] << ") SBC(" << Chanel[2] << ") SBD(" << Chanel[3] << ")" << endl;

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
    
    for (int a = 0; a < 4; a++)
    {
        bool good[4] = { false,false,false,false };

        for (int b = 0; b < 4; b++)
        {
            if (ListPhoneme[a].moyenne[b].toInt() != 0)
            {
                good[b] = true;
            }
        }

        if (good[0] == false && good[1] == false && good[2] == false && good[3] == false)
        {
            return "Phonemes non enregistrees";
        }
    }







    int moyenne[4] = { 0,0,0,0 };

    //SBA_L
    {
        int count = 0;

        //Moyenne
        for (int i = 0; i < nbToRead; i++)
        {
            if (SBA_L[i] != 0)
            {
                moyenne[0] += SBA_L[i];
                count++;
            }
        }

        if (count > 0)
        {
            moyenne[0] = std::ceil(moyenne[0] / count);
        }
    }
    
    //SBB_L
    {
        int count = 0;

        //Moyenne
        for (int i = 0; i < nbToRead; i++)
        {
            if (SBB_L[i] != 0)
            {
                moyenne[1] += SBB_L[i];
                count++;
            }
        }

        if (count > 0)
        {
            moyenne[1] = std::ceil(moyenne[1] / count);
        }
    }
    
    //SBC_L
    {
        int count = 0;

        //Moyenne
        for (int i = 0; i < nbToRead; i++)
        {
            if (SBC_L[i] != 0)
            {
                moyenne[2] += SBC_L[i];
                count++;
            }
        }

        if (count > 0)
        {
            moyenne[2] = std::ceil(moyenne[2] / count);
        }
    }
    
    //SBD_L
    {
        int count = 0;

        //Moyenne
        for (int i = 0; i < nbToRead; i++)
        {
            if (SBD_L[i] != 0)
            {
                moyenne[3] += SBD_L[i];
                count++;
            }
        }

        if (count > 0)
        {
            moyenne[3] = std::ceil(moyenne[3] / count);
        }
    }
    

    //Différence à l'enregistrement
    int diff_Each[4][4] = { { 0,0,0,0 }, { 0,0,0,0 }, { 0,0,0,0 }, { 0,0,0,0 } };
    int diff_All[4] = { 0,0,0,0 };

    for (int a = 0; a < 4; a++)
    {
        for (int b = 0; b < 4; b++)
        {
            diff_Each[a][b] += std::abs(ListPhoneme[a].moyenne[b].toInt() - moyenne[b]);
            diff_All[a] += std::abs(ListPhoneme[a].moyenne[b].toInt() - moyenne[b]);
        }
    }


    //Plus petite différence
    int max = diff_All[0];
    int index = 0;

    for (int i = 1; i < 4; i++)
    {
        if (diff_All[i] <= max)
        {
            max = diff_All[i];
            index = i;
        }
    }

    //Affichge console
    if (index == 0)
    {
        cout << "Result A" << endl;
    }
    else if (index == 1)
    {
        cout << "Result E" << endl;
    }
    else if (index == 2)
    {
        cout << "Result EU" << endl;
    }
    else if (index == 3)
    {
        cout << "Result I" << endl;
    }
    cout << "Difference (" << diff_Each[index][0] << "-" << diff_Each[index][1] << "-" << diff_Each[index][2] << "-" << diff_Each[index][3] << ")" << endl;
    cout << "Moyenne (" << moyenne[0] << "-" << moyenne[1] << "-" << moyenne[2] << "-" << moyenne[3] << ")" << endl;


    int good_SBA = 30;
    int good_SBB = 30;
    int good_SBC = 30;
    int good_SBD = 30;

    //Choix du phoneme
    if (index == 0 && diff_Each[index][0] <= good_SBA && diff_Each[index][1] <= good_SBB && diff_Each[index][2] <= good_SBC && diff_Each[index][3] <= good_SBD)
    {
        //A
        return "Haut";
    }
    else if (index == 1 && diff_Each[index][0] <= good_SBA && diff_Each[index][1] <= good_SBB && diff_Each[index][2] <= good_SBC && diff_Each[index][3] <= good_SBD)
    {
        //E
        return "Droit";
    }
    else if (index == 2 && diff_Each[index][0] <= good_SBA && diff_Each[index][1] <= good_SBB && diff_Each[index][2] <= good_SBC && diff_Each[index][3] <= good_SBD)
    {
        //EU
        return "Bas";
    }
    else if (index == 3 && diff_Each[index][0] <= good_SBA && diff_Each[index][1] <= good_SBB && diff_Each[index][2] <= good_SBC && diff_Each[index][3] <= good_SBD)
    {
        //I
        return "Gauche";
    }
    else
    {
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

            cout << "SBA(" << Chanel[0] << ") SBB(" << Chanel[1] << ") SBC(" << Chanel[2] << ") SBD(" << Chanel[3] << ")" << endl;

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
    RecordValue.moyenne[0] = 0;
    RecordValue.moyenne[1] = 0;
    RecordValue.moyenne[2] = 0;
    RecordValue.moyenne[3] = 0;
    
    //SBA
    {
        int count = 0;
        int moyenne = 0;
        
        //Moyenne
        for (int i = 0; i < nbToRecord; i++)
        {
            if (SBA[i] != 0)
            {
                moyenne += SBA[i];
                count++;
            }
        }

        if (count > 0)
        {
            moyenne = std::ceil(moyenne/ count);
        }

        //Inscription
        RecordValue.moyenne[0] = QString::number(moyenne);
    }

    //SBB
    {
        int count = 0;
        int moyenne = 0;
        //Moyenne
        for (int i = 0; i < nbToRecord; i++)
        {
            if (SBB[i] != 0)
            {
                moyenne += SBB[i];
                count++;
            }
        }

        if (count > 0)
        {
            moyenne = std::ceil(moyenne / count);
        }
        
        //Inscription
        RecordValue.moyenne[1] = QString::number(moyenne);
    }

    //SBC
    {
        int count = 0;
        int moyenne = 0;

        //Moyenne
        for (int i = 0; i < nbToRecord; i++)
        {
            if (SBC[i] != 0)
            {
                moyenne += SBC[i];
                count++;
            }
        }

        if (count > 0)
        {
            moyenne = std::ceil(moyenne / count);
        }

        //Inscription
        RecordValue.moyenne[2] = QString::number(moyenne);
    }

    //SBD
    {
        int count = 0;
        int moyenne = 0;

        //Moyenne
        for (int i = 0; i < nbToRecord; i++)
        {
            if (SBD[i] != 0)
            {
                moyenne += SBD[i];
                count++;
            }
        }

        
        if (count > 0)
        {
            moyenne  = std::ceil(moyenne / count);
        }
        
        //Inscription
        RecordValue.moyenne[3] = QString::number(moyenne);
    }
    return "Done";
}

void Fpga::SaveRecord(QString s)
{
    QFile file(s);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream in(&file);

    in << RecordValue.moyenne[0] + "-" + RecordValue.moyenne[1] + "-" + RecordValue.moyenne[2] + "-" + RecordValue.moyenne[3] + "\n";

    file.close();
}

void Fpga::CreatePhoneme()
{
    QString FileName[4] = { "PH_A.2048","PH_E.2048","PH_EU.2048","PH_I.2048" };


    for (int i = 0; i < 4; i++)
    {
        QFile file(FileName[i]);

        if (file.exists())
        {
            file.open(QIODevice::ReadOnly | QIODevice::Text);

            QTextStream in(&file);

            QString line = in.readLine();

            qDebug() << FileName[i] << " (" << line << ")";

            ListPhoneme[i].moyenne[0] = line.split("-")[0];
            ListPhoneme[i].moyenne[1] = line.split("-")[1];
            ListPhoneme[i].moyenne[2] = line.split("-")[2];
            ListPhoneme[i].moyenne[3] = line.split("-")[3];

            file.close();
        }
    }
}

int Fpga::GetNbToRecord()
{
    return nbToRecord;
}