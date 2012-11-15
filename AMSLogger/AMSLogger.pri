#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

QT       *= core network
#CONFIG += staticlib release
CONFIG += link_prl

QMAKE_PRO_INPUT = AMSLogger.pro
QMAKE_PRL_TARGET = AMSLogger

LIBS += -lAMSLogger

INCLUDEPATH += $${PWD}
