TEMPLATE     = vcapp
TARGET       = Qt_2048
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += accueil.h CommunicationFPGA.h jeu.h stats.h UI.h Grid.h Fpga.h needed.h
SOURCES     += accueil.cpp jeu.cpp main.cpp stats.cpp UI.cpp Grid.cpp Fpga.cpp
LIBS	    += CommunicationFPGA.lib
QT 	    += widgets
RESOURCES   += Resource.qrc
