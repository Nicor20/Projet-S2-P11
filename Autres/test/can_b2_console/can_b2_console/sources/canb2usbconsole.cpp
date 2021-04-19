/**
*   Programme "console" pour circuit can_b2
*   Echanges des données entre un système d'acquisition analogique-numerique
*   sur cartes FPGA Digilent BASYS2
*   programmee avec le circuit logique can_b2.bit avec USBconsole_Can_2b_v1.vhd
*
*   @file canb2usbconsole.cpp
*   @author D. Dalle
*   @date 2017/11/30
*   @version voir (CANB2USBCONSOLE_VERS)
*
*   Historique de révision
* 
*   V01.00a 2018/08/12 D. Dalle  validation Visual Studio 2017 x64
*   V01.00a 2017/11/20 D. Dalle  documentation
*   V01.00a 2017/11/20 D. Dalle  validation V01.00a canb2usbconsole
*   V01.00a 2017/10/16 D. Dalle  creation initiale
*
*   Reférences:
*  - Digilent Inc. http://www.digilentinc.com
*  - Librairie communicationFPGA, exemple de programmation Note technique, 
*    C. A. Brunet, Département de génie électrique et de génie informatique, 2011.
*  - Digilent Parallel Interface Model Reference Manual,
*    Revision: 08/10/2004
*  - Librairies du digilent.adept.sdk_v2.0.1
*  - Digilent Adept Device Access  Manager (DMGR) Programmer’s Reference Manual
*    Revision: September 2, 2010 Doc: 506-018
*  - Digilent Asynchronous Parallel Interface (DEPP)
*    Revision: September 2, 2010 Doc: 564-000
*  - Digilent Adept System Programmer’s Reference Manual
*    Revision: August 18, 2010 Doc: 506-020
*  - Digilent Adept Asynchronous Parallel Port Intterface (DEPP) Programmer’s Reference Manual
*    Revision: August 16, 2010 Doc: 506-022
*/

#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>
//#include <cmath>
using namespace std;

#include "CommunicationFPGA.h"
#include "canb2usbconsolehlp.h"


const string  CANB2USBCONSOLE_VERS = "V01.00a";


string ladate()
{
    string s;
    time_t t;             // strutures requises a la lecture
    // de la date et de l'heure systeme
    time(&t);
#ifdef WIN32
    char str[0x100];
    if (!ctime_s(str, 0x100, &t))
        s.assign(str);
    else
        s.assign("erreur ctime_s");
#endif
#ifdef UNIX
    s = ctime(&t);
#endif
    return s;
}

void affiche_aide() {         ///< Information de type "Aide"
    cout << endl << aide_canb2usbconsole << endl;
    return;
}


//============================================================================
// programme principal
//============================================================================
int main(int argc, char **argv, char **envp)

{
    // ------------------------------------------------------------------------
    // Donnees du main
    // ------------------------------------------------------------------------

    BOOL statutport = false;            // statut du port de communication qui sera cree


    int compteur_temps = 0;
    int swt = 0;                         // donnee recue du FPGA
    int aff7sg_octet0 = 0;               // octet 0 (droite) pour afficheur 7 segments
    int aff7sg_octet1 = 0;               // octet 0 (droite) pour afficheur 7 segments
    int stat_btn      = 0;               // donnee recue du FPGA: statut et BTN
    int echconv[4];                      // donnee converties recues du FPGA
    int canal_a_afficher        = 0;     // donnee recue du FPGA
    int indice_canal_a_afficher = 0;

    const int nitermax  = 10000;         // Nbre d'itération max de la boucle de lecture d'acquisition (limite pour tests)
                                         // changer la condition de boucle sans cette limite selon le besoin de l'application
    const int delai_boucle = 10;         // delai d'attente ajouté dans la boucle de lecture en ms

	// numeros de registres correspondants pour les echanges FPGA <-> PC  ...
	unsigned const int nreg_lect_stat_btn = 0;  // fpga -> PC  Statut et BTN lus FPGA -> PC
	unsigned const int nreg_lect_swt = 1;       // fpga -> PC  SWT lus FPGA -> PC
	unsigned const int nreg_lect_cmpt_t = 2;    // fpga -> PC  compteur temps FPGA -> PC 
	unsigned const int nreg_lect_can0 = 3;      // fpga -> PC  canal 0 lus FPGA -> PC
	unsigned const int nreg_lect_can1 = 4;      // fpga -> PC  canal 1 lus FPGA -> PC
	unsigned const int nreg_lect_can2 = 5;      // fpga -> PC  canal 2 lus FPGA -> PC
	unsigned const int nreg_lect_can3 = 6;      // fpga -> PC  canal 3 lus FPGA -> PC
	unsigned const int nreg_ecri_aff7sg0 = 7;   // PC -> fpga (octet 0  aff.7 seg.)
	unsigned const int nreg_ecri_aff7sg1 = 8;   // PC -> fpga (octet 1  aff.7 seg.)
	unsigned const int nreg_ecri_aff7dot = 9;   // PC -> fpga (donnees dot-points)
	unsigned const int nreg_ecri_led = 10;      // PC -> fpga (donnees leds)


    // ------------------------------------------------------------------------
    // Initialisation du programme
    // ------------------------------------------------------------------------


    cout << "can_b2_console, " << CANB2USBCONSOLE_VERS << endl;
    cout << "Console de communication avec le circuit can_b2 sur FPGA" << endl;
    cout << "avec la gestion de port USB (Digilent Port Communication)" << endl;
    cout << "(circuits can_b2 et versions compatibles)" << endl;
    cout << "Date du test: " << ladate() << endl;

    cout << "programme     = " << argv[0] << endl;
    cout << "argc          = " << argc << endl;
    cout << "environnement = " << *envp << endl;

    // ------------------------------------------------------------------------
    // Gestion ligne de commande
    // ------------------------------------------------------------------------
    if (argc > 2)      // Analyse et validation de la ligne de commande
    {
        cout << "Ligne de commande non conforme (0 ou 1 fichier d'entree) \n";
        affiche_aide();   // Affiche la liste des commandes
        return 1;
    }

    if (argc >= 2)
    {
        string argv1 = argv[1];
        if ((argv1.compare(0, 2, "-h") == 0) | (argv1.compare("?") == 0))
        {
            affiche_aide();   // Affiche la liste des commandes
            return 1;
        }
    }

    // ------------------------------------------------------------------------
    // Ici, on pourrait placer l'ouverture et lecture fichier d'entree
    // eventuellement specifie par la ligne de commande
    // CETTE FONCTION NON IMPLÉMENTÉE DANS CETTE VERSION INITIALE ...
    // ------------------------------------------------------------------------

    if (argc == 2)      // si nom de fichier present dans la ligne de commande
    {
        cout << "Argument de la ligne de commande non reconnu " << argv[1] << endl;

        {
            affiche_aide();   // Affiche la liste des commandes
            return 1;
        }
    }


    CommunicationFPGA port;   // Instance du port de communication

    if (!port.estOk())
    {
        cout << port.messageErreur() << endl;
        return 1;
    }
    else
        cout << "Statut initial du port de communication = " << port.estOk() << endl << endl;
    
    int statut_circuit = 0;
 
	statutport = port.lireRegistre(nreg_lect_stat_btn, statut_circuit);

    cout << "Lecture du statut du circuit statut_circuit = " << (int)statut_circuit
         << ", statutport = " << statutport << endl;
    
     
    // code pour passer en mode connecté si BTN0 est appuyé
    cout << "Mode FPGA local - Attente de la commande BTN0 = " << endl;
    for (int niter = 0; ((niter < nitermax) && ((stat_btn & 1) == 0)); niter++)  // tant que nitermax non atteint et que BTN0 non 1
    {
        if (statutport) statutport = port.lireRegistre(nreg_lect_stat_btn, stat_btn);        // lecture BTN
        else { cout << "Erreur du port nreg_lect_stat_btn" << endl; exit(1); }
        Sleep(10); // attente 10 ms pour ne pas monopoliser le CPU dans cette boucle d'attente  ... 
    }
    cout << endl  << "Mode FPGA connecté - Attente de la commande BTN3 = " << endl;


    statutport = port.ecrireRegistre(nreg_ecri_led, 1);          // envoyer valeur '1' sur led(0) du FPGA : signal pour passer en mode connecté
    if (!port.estOk())
    {
        cout << port.messageErreur() << endl;
        return 1;
    }

    cout << endl << dec << "Delai d'attente ajoute dans a boucle de lecture : " << delai_boucle << " ms" << endl;

    cout << setfill('0') << setw(4) << hex << showbase << internal << endl;
    cout << "   Stat_BTN,  SWT,  compt_t,      ch[0], ch[1], ch[2], ch[3]" << endl;
    // ------------------------------------------------------------------------
    // Debut des echanges sur le port de communication
    // Digilent Adept Asynchronous Parallel Port Interface (DEPP)
    // ------------------------------------------------------------------------
    // Les echanges sont controles par le statut du circuit lu sur le registre BTN
    // ------------------------------------------------------------------------

	int value = 0;
    for (int niter = 0; ((niter < nitermax) && ((stat_btn & 8) == 0)); niter++)  // tant que nitermax non atteint et que btn3 non 1
    {
		
        if (statutport) statutport = port.lireRegistre(nreg_lect_stat_btn, stat_btn);     // lecture statut et BTN
        else { cout << "Erreur du port nreg_lect_stat_btn" << endl; exit(1); }
        if (statutport) statutport = port.lireRegistre(nreg_lect_swt, swt);               // lecture swt
        else { cout << "Erreur du port nreg_lect_swt" << endl; exit(1); }

        if (statutport) statutport = port.lireRegistre(nreg_lect_cmpt_t, compteur_temps);  // lecture compteur temps
        else { cout << "Erreur du port nreg_lect_cmpt_t" << endl; exit(1); }


        if (statutport) statutport = port.lireRegistre(nreg_lect_can0, echconv[0]);       // lecture canal 0
        else { cout << "Erreur du port nreg_lect_can0" << endl; exit(1); }

        if (statutport) statutport = port.lireRegistre(nreg_lect_can1, echconv[1]);       // lecture canal 1
        else { cout << "Erreur du port nreg_lect_can1" << endl; exit(1); }

        if (statutport) statutport = port.lireRegistre(nreg_lect_can2, echconv[2]);       // lecture canal 2
        else { cout << "Erreur du port nreg_lect_can2" << endl; exit(1); }

        if (statutport) statutport = port.lireRegistre(nreg_lect_can3, echconv[3]);       // lecture canal 3
        else { cout << "Erreur du port nreg_lect_can3" << endl; exit(1); }

        if (!statutport) {
            cout << "Erreur du port dans la boucle" << endl;
            exit(1);
        }
        if (statutport) statutport = port.ecrireRegistre(nreg_ecri_led, swt);                                    // re-envoyer lecture swt sur port LED
           else { cout << "Erreur du port nreg_ecri_led" << endl; exit(1); }
        // compose valeur pour affichage VV0N  
        canal_a_afficher = (swt & 0x3);
        indice_canal_a_afficher = (int)canal_a_afficher;
    

        if (statutport) statutport = port.ecrireRegistre(nreg_ecri_aff7sg0, canal_a_afficher);                    // envoyer numero canal_a_afficher afficheur 7 segments
           else { cout << "Erreur du port nreg_ecri_aff7sg0" << endl; exit(1); }
           if (statutport) statutport = port.ecrireRegistre(nreg_ecri_aff7sg1, echconv[indice_canal_a_afficher]); // envoyer valeur echconv[] afficheur 7 segments
           else { cout << "Erreur du port nreg_ecri_aff7sg1" << endl; exit(1); }
           if (statutport) statutport = port.ecrireRegistre(nreg_ecri_aff7dot, stat_btn & 0xFF);                  // envoyer vecteur  bouton (sans le statut)
           else { cout << "Erreur du port nreg_ecri_aff7dot" << endl; exit(1); }
        //
        //cout << "      " << (int)stat_btn << ",   " << (int)swt << ",     " << (int)compteur_temps;
        indice_canal_a_afficher = 0;

        for (indice_canal_a_afficher; indice_canal_a_afficher < 4; indice_canal_a_afficher++)
        {
            if ((int)echconv[indice_canal_a_afficher] == 0)
            {
                cout << ",      0x00";
            } 
            else
            {
                cout << ",      " << (int)echconv[indice_canal_a_afficher];
            }
        }
            
        cout << endl;
		

		//cout << value << endl;
		statutport = port.ecrireRegistre(nreg_ecri_aff7dot, (int)value);


		value++;
        Sleep(delai_boucle);                                                                                       // attente x ms sans occuper de CPU ... 
    }

    //cout << endl << "--------------------------------------------------" << endl;


    //cout << "--fin. " << endl;
    //return 0;  // fin normale
    system("pause");
}

