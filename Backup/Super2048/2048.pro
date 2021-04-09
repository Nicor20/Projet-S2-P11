TEMPLATE     = vcapp
TARGET       = Super2048
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += super2048.h joueur.h tuile.h tableauTuile.h Tableau.h Jeu.h Affichage.h
SOURCES     += main.cpp joueur.cpp tuile.cpp tableauTuile.cpp Tableau.cpp Jeu.cpp Affichage.cpp
INCLUDEPATH += 
LIBS	    += 
QT += widgets