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
    CreatePhoneme();

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
            SBA_L[nbRead] = Chanel[0];
            SBB_L[nbRead] = Chanel[1];
            SBC_L[nbRead] = Chanel[2];
            SBD_L[nbRead] = Chanel[3];
            cout << "SBA(" << Chanel[0] << ") SBB(" << Chanel[1] << ") SBC(" << Chanel[2] << ") SBD(" << Chanel[3] << ")" << endl;


            //for (int i = 0; i < 4; i++)
            //    ListLecture[nbRead].pot[i] = Chanel[i];

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
    int moyenne[4] = { 0,0,0,0 };

    //SBA_L
    QList<int> Temp_SBA;
    std::sort(std::begin(SBA_L), std::end(SBA_L));

    //Remove zero
    for (int i = 0; i < nbToRead; i++)
    {
        if (SBA_L[i] != 0)
        {
            Temp_SBA.append(SBA_L[i]);
        }
    }

    //Moyenne
    if (Temp_SBA.length() > 0)
    {
        for (int i = 0; i < Temp_SBA.length(); i++)
        {
            moyenne[0] += Temp_SBA.at(i);
        }

        
        moyenne[0] = std::ceil(moyenne[0] / Temp_SBA.length());
    }

    
    
    //SBB_L
    QList<int> Temp_SBB;
    std::sort(std::begin(SBB_L), std::end(SBB_L));

    //Remove zero
    for (int i = 0; i < nbToRead; i++)
    {
        if (SBB_L[i] != 0)
        {
            Temp_SBB.append(SBB_L[i]);
        }
    }

    //Moyenne
    if (Temp_SBB.length() > 0)
    {
        for (int i = 0; i < Temp_SBB.length(); i++)
        {
            moyenne[1] += Temp_SBB.at(i);
        }
        moyenne[1] = std::ceil(moyenne[1] / Temp_SBB.length());
    }

    
    
    //SBC_L
    QList<int> Temp_SBC;
    std::sort(std::begin(SBC_L), std::end(SBC_L));

    //Remove zero
    for (int i = 0; i < nbToRead; i++)
    {
        if (SBC_L[i] != 0)
        {
            Temp_SBC.append(SBC_L[i]);
        }
    }

    //Moyenne
    if (Temp_SBC.length() > 0)
    {
        for (int i = 0; i < Temp_SBC.length(); i++)
        {
            moyenne[2] += Temp_SBC.at(i);
        }
        moyenne[2] = std::ceil(moyenne[2] / Temp_SBC.length());
    }

    
    
    //SBD_L
    QList<int> Temp_SBD;
    std::sort(std::begin(SBD_L), std::end(SBD_L));

    //Remove zero
    for (int i = 0; i < nbToRead; i++)
    {
        if (SBD_L[i] != 0)
        {
            Temp_SBD.append(SBD_L[i]);
        }
    }

    //Moyenne
    if (Temp_SBD.length() > 0)
    {
        for (int i = 0; i < Temp_SBD.length(); i++)
        {
            moyenne[3] += Temp_SBD.at(i);
        }
        moyenne[3] = std::ceil(moyenne[3] / Temp_SBD.length());
    }


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







    int good_SBA = 30;
    int good_SBB = 30;
    int good_SBC = 30;
    int good_SBD = 30;

    if (index == 0)
    {
        //A
        cout << "Result A" << endl;
        cout << "Difference (" << diff_Each[index][0] << "-" << diff_Each[index][1] << "-" << diff_Each[index][2] << "-" << diff_Each[index][3] << ")" << endl;
        cout << "Moyenne (" << moyenne[0] << "-" << moyenne[1] << "-" << moyenne[2] << "-" << moyenne[3] << ")" << endl;

        if (diff_Each[index][0] <= good_SBA && diff_Each[index][1] <= good_SBB && diff_Each[index][2] <= good_SBC && diff_Each[index][3] <= good_SBD)
        {
            return "Haut";
        }
        else
        {
            return "Aucun";
        }
    }
    else if (index == 1)
    {
        //E
        cout << "Result E" << endl;
        cout << "Difference (" << diff_Each[index][0] << "-" << diff_Each[index][1] << "-" << diff_Each[index][2] << "-" << diff_Each[index][3] << ")" << endl;
        cout << "Moyenne (" << moyenne[0] << "-" << moyenne[1] << "-" << moyenne[2] << "-" << moyenne[3] << ")" << endl;

        if (diff_Each[index][0] <= good_SBA && diff_Each[index][1] <= good_SBB && diff_Each[index][2] <= good_SBC && diff_Each[index][3] <= good_SBD)
        {
            return "Droit";
        }
        else
        {
            return "Aucun";
        }
    }
    else if (index == 2)
    {
        //EU
        cout << "Result EU" << endl;
        cout << "Difference (" << diff_Each[index][0] << "-" << diff_Each[index][1] << "-" << diff_Each[index][2] << "-" << diff_Each[index][3] << ")" << endl;
        cout << "Moyenne (" << moyenne[0] << "-" << moyenne[1] << "-" << moyenne[2] << "-" << moyenne[3] << ")" << endl;

        if (diff_Each[index][0] <= good_SBA && diff_Each[index][1] <= good_SBB && diff_Each[index][2] <= good_SBC && diff_Each[index][3] <= good_SBD)
        {
            return "Bas";
        }
        else
        {
            return "Aucun";
        }
    }
    else if (index == 3)
    {
        //I
        cout << "Result I" << endl;
        cout << "Difference (" << diff_Each[index][0] << "-" << diff_Each[index][1] << "-" << diff_Each[index][2] << "-" << diff_Each[index][3] << ")" << endl;
        cout << "Moyenne (" << moyenne[0] << "-" << moyenne[1] << "-" << moyenne[2] << "-" << moyenne[3] << ")" << endl;

        if (diff_Each[index][0] <= good_SBA && diff_Each[index][1] <= good_SBB && diff_Each[index][2] <= good_SBC && diff_Each[index][3] <= good_SBD)
        {
            return "Gauche";
        }
        else
        {
            return "Aucun";
        }
    }
    else
    {
        return "Aucun";
    }


    /*
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
    */
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
        QList<int> Temp;
        int moyenne = 0;

        std::sort(std::begin(SBA), std::end(SBA));
        
        //Remove zero
        for (int i = 0; i < nbToRecord; i++)
        {
            if (SBA[i] != 0)
            {
                Temp.append(SBA[i]);
            }
        }

        //Moyenne
        if (Temp.length() > 0)
        {
            for (int i = 0; i < Temp.length(); i++)
            {
                moyenne += Temp.at(i);
            }
            moyenne = std::ceil(moyenne/Temp.length());
        }

        //Show
        //if (Temp.length() > 0)
        //{
        //    for (int i = 0; i < Temp.length(); i++)
        //    {
        //        cout << "SBA : " << Temp.at(i) << endl;
        //    }
        //}

        //Inscription
        RecordValue.moyenne[0] = QString::number(moyenne);
    }

    //SBB
    {
        QList<int> Temp;
        int moyenne = 0;

        std::sort(std::begin(SBB), std::end(SBB));


        //Remove zero
        for (int i = 0; i < nbToRecord; i++)
        {
            if (SBB[i] != 0)
            {
                Temp.append(SBB[i]);
            }
        }

        //Moyenne
        if (Temp.length() > 0)
        {
            for (int i = 0; i < Temp.length(); i++)
            {
                moyenne += Temp.at(i);
            }
            moyenne = std::ceil(moyenne / Temp.length());
        }
        

        //Inscription
        RecordValue.moyenne[1] = QString::number(moyenne);
    }

    //SBC
    {
        QList<int> Temp;
        int moyenne = 0;

        std::sort(std::begin(SBC), std::end(SBC));
        

        //Remove zero
        for (int i = 0; i < nbToRecord; i++)
        {
            if (SBC[i] != 0)
            {
                Temp.append(SBC[i]);
            }
        }

        //Moyenne
        if (Temp.length() > 0)
        {
            for (int i = 0; i < Temp.length(); i++)
            {
                moyenne += Temp.at(i);
            }
            moyenne = std::ceil(moyenne / Temp.length());
        }

        //Inscription
        RecordValue.moyenne[2] = QString::number(moyenne);
    }

    //SBD
    {
        QList<int> Temp;
        int moyenne = 0;

        std::sort(std::begin(SBD), std::end(SBD));

        //Remove zero
        for (int i = 0; i < nbToRecord; i++)
        {
            if (SBD[i] != 0)
            {
                Temp.append(SBD[i]);
            }
        }

        //Moyenne
        if (Temp.length() > 0)
        {
            for (int i = 0; i < Temp.length(); i++)
            {
                moyenne += Temp.at(i);
            }
            moyenne  = std::ceil(moyenne / Temp.length());
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

            qDebug() << FileName[i] << " (" << line << ")\n";

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