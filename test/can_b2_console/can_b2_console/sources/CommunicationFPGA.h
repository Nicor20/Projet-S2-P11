/*
*   CommunicationFPGA est une classe d'interface à la pour la communication
*   avec la carte FPGA de la session S2. Pour les details de l'utilisation
*   de cette classe, consultez le guide d'utilisation.
*   
*   $Author: bruc2001 $
*   $Date: 2018-02-13 08:54:36 -0500 (mar., 13 févr. 2018) $
*   $Revision: 108 $
*   $Id: CommunicationFPGA.h 108 2018-02-13 13:54:36Z bruc2001 $
*
*   Copyright 2013 Département de génie électrique et génie informatique
*                  Université de Sherbrooke  
*/

#ifndef COMMUNICATIONFPGA_H
#define COMMUNICATIONFPGA_H

#include <windows.h>

using namespace std;

class CommunicationFPGA {
public:
    CommunicationFPGA();
	~CommunicationFPGA();

	bool lireRegistre(int registre, int &valeur);
	bool ecrireRegistre(int registre, int valeur);
	void sleep(unsigned int millisecondes = 10);

	bool estOk();
	const char * messageErreur();
private:
	bool erreur;
    char msgErreur[1024];
	unsigned long hif;
};

#endif
