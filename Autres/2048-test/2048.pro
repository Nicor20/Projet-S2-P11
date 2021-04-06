TEMPLATE     = vcapp
TARGET       = 2048-test
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += Tableau.h CommunicationFPGA.h Jeu.h
SOURCES     += Tableau.cpp Jeu.cpp Main.cpp CommunicationFPGA-release.lib
INCLUDEPATH += C:/Users/canti/Desktop/Projet-S2-P11/2048-test
LIBS	    += C:/Users/canti/Desktop/Projet-S2-P11/2048-test/CommunicationFPGA-release.lib
QT 	    += widgets
