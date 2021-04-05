/**
*   Texte d'aide pour programme democanb2usbconsole
*   
*   @file democanb2usbconsolehlp.h.h
*   @author D. Dalle
*   @date 2017/10/16
*   @version V01.00a
*
*   Historique de révision
*   V01.00a 2017/10/16 D. Dalle  creation
*/
/*
*   (c) 2017 Département de génie électrique et génie informatique
*            Université de Sherbrooke, D. Dalle
*/
// Informations sur le fonctionnement du programme

string aide_canb2usbconsole =
"\n"
"---------------------------------------------------------------------------\n"
"Programme canb2usbconsole version V01.00a \n"
"Universite de Sherbrooke - Dept GEGI\n"
"Console de communication avec le circuit Can_b2 par le port USB.\n"
"\n"
"Configuration materielle requise :\n"
"  Carte Digilent BASYS-2 Branchee par le port USB.\n"
"  Configuration (exemple Can_b2.bit) programmee dans le FPGA avec le\n"
"  logiciel Digilent ADEPT\n"
"  ou reprogrammée depuis la mémoire ROM de la carte à la mise sous tension."
"\n"
"Utilisation :\n"
"  canb2usbconsole -h[elp] :  affiche ce message; \n"
"  canb2usbconsole         :  execute une (seule) operation de \n"
"  communication avec le FPGA.\n"
"  - Le programme lit le statut(3:0) et les boutons BTN(3:0). \n"
"  - Le programme lit les interrupteurs SW(7:0). \n"
"    Les bits SW(1:0) déterminent le numéro de la donnée à afficher. \n"
"  - Le programme transmet la donnée à afficher sur les afficheurs à 7 segments \n"
"    de la même manière qu'en mode local: le circuit affiche donc les données \n"
"    du canal sélectionné par les 2 bits inférieurs des interrupteurs SW: \n"
"    le numéro du canal et la valeur en hexadécimal sur les afficheurs: \n"
"    format VV0N  (valeur VV, numéro 0N). \n"
"  - Le programme retransmet les valeurs de SW(7:0) sur les LED(7:0). \n"
"  - Le programme retransmets les valeurs des bouton BTN(3:0) \n"
"    sur les points de l'afficheur. \n"
"---------------------------------------------------------------------------\n";
