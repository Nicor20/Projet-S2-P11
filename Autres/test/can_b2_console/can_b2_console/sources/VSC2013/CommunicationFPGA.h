/*
*   CommunicationFPGA est une classe d'interface à la pour la communication
*   avec la carte FPGA de la session S2. Pour les details de l'utilisation
*   de cette classe, consultez le guide d'utilisation.
*   
*   $Author: bruc2001 $
*   $Date: 2011-03-01 15:47:25 -0500 (mar., 01 mars 2011) $
*   $Revision: 57 $
*   $Id: CommunicationFPGA.h 57 2011-03-01 20:47:25Z bruc2001 $
*
*   Copyright 2011 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/

#ifndef COMMUNICATIONFPGA_H
#define COMMUNICATIONFPGA_H

#include <windows.h>

using namespace std;

enum Registre {SW=8, BTN=9, LD=10, AN0=11, AN1=12, AN2=13, AN3=14};

class CommunicationFPGA {
public:
    CommunicationFPGA();
	~CommunicationFPGA();

	bool lireRegistre(int registre, int &valeur);
	bool ecrireRegistre(int registre, int valeur);

	bool estOk();
	const char * messageErreur();
private:
	bool erreur;
    char msgErreur[1024];
	unsigned long hif;
};

#endif