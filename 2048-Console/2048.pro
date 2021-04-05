TEMPLATE     = vcapp
TARGET       = 2048-test
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += Tableau.h CommunicationFPGA.h
SOURCES     += Tableau.cpp canb2usbconsole.cpp
INCLUDEPATH += C:/Users/canti/Desktop/Projet-S2-P11/2048-test
LIBS	    += C:/Users/canti/Desktop/Projet-S2-P11/2048-test/CommunicationFpga-release.lib
QT 	    += widgets
