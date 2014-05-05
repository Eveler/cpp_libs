#-------------------------------------------------
#
# Project created by QtCreator 2011-04-18T18:17:45
#
#-------------------------------------------------

AMSLogger_lib.target = AMSLogger
AMSLogger_lib.commands += @$(QMAKE) -o MakeFile.$${AMSLogger_lib.target} $${PWD}/$${AMSLogger_lib.target}.pro
#mytarget.target = release
mytarget.commands += $(MAKE) -f MakeFile.$${AMSLogger_lib.target}
mytarget.commands += $(MAKE) -f $(MAKEFILE).Release
mytarget.depends = AMSLogger_lib
mytarget.recurse = AMSLogger_lib
mytarget.recurse_target = AMSLogger
#SUBDIRS.file += $${PWD}/AMSLogger.pro
#SUBDIRS.depends += AMSLogger.pro
#SUBDIRS.target += mytarget

QMAKE_EXTRA_TARGETS = AMSLogger_lib mytarget
#PRE_TARGETDEPS += AMSLogger
#REQUIRES += AMSLogger

QT       *= core network
#CONFIG += staticlib release
CONFIG += link_prl recursive

greaterThan(QT_MAJOR_VERSION, 4) {
  QMAKE_PRL_BUILD_DIR = $${PWD}/../bin_qt5
  LIBS += -L$${PWD}/../bin_qt5
}
lessThan(QT_MAJOR_VERSION, 5) {
  QMAKE_PRL_BUILD_DIR = $${PWD}/../bin
  LIBS += -L$${PWD}/../bin
}
QMAKE_PRO_INPUT = AMSLogger.pro
QMAKE_PRL_TARGET = AMSLogger

LIBS += -lAMSLogger

INCLUDEPATH += $${PWD}
DEPENDPATH  += $${PWD}
