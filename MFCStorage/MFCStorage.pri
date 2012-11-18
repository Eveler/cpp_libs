#-------------------------------------------------
#
# Project created by QtCreator 2012-11-12T14:45:29
#
#-------------------------------------------------

DEPENDPATH  += $${PWD}

mytarget.target = .buildfile
mytarget.depends = MFCStorage
MFCStorage_lib.target = MFCStorage


QMAKE_EXTRA_TARGETS += mytarget MFCStorage_lib

CONFIG += link_prl #recursive

LIBS += -L$${PWD} -lMFCStorage

#PRE_TARGETDEPS += $${DESTDIR}/MFCStorage.a
