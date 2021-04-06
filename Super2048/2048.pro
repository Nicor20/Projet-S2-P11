TEMPLATE     = vcapp
TARGET       = Super2048
CONFIG      += warn_on qt debug_and_release windows console
HEADERS     += super2048.h joueur.h tuile.h tableauTuile.h
SOURCES     += main.cpp joueur.cpp tuile.cpp tableauTuile.cpp
INCLUDEPATH += 
LIBS	    += 
QT += widgets