TEMPLATE     = vcapp
TARGET       = Super2048
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += Tableau.h Jeu.h Affichage.h Tuile.h Grille.h
SOURCES     += 2048-Console.cpp Tableau.cpp Jeu.cpp Affichage.cpp Tuile.cpp Grille.cpp
INCLUDEPATH += 
LIBS	    += 
QT += widgets
