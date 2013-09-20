#-------------------------------------------------
#
# Project created by QtCreator 2010-09-25T12:53:49
#
#-------------------------------------------------

QT       += core gui

TARGET = muCalculator
TEMPLATE = lib

greaterThan( QT_MAJOR_VERSION, 4 ) QT += widgets

DEFINES += EXPORT_LIB_MUCALCULATOR


INCLUDEPATH += ./ \
    ../bin/ \
    ../bin_qt5/ \
    ../include/ \
    ./QMathParser_1_0/ \
    ./QMathParser_1_0/muParser/

INSTALL_TO_TICKETCHOICE = E:/devel/Tests/bin
INSTALL_WIN_LIB = $$INSTALL_TO_TICKETCHOICE

unix:!symbian {

    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32 {
    target.path = $$INSTALL_WIN_LIB
    INSTALLS += target
}

greaterThan( QT_MAJOR_VERSION, 4 ) {
  DESTDIR = ../bin_qt5
  DLLDESTDIR = ../bin_qt5
}
lessThan( QT_MAJOR_VERSION, 5 ) {
  DESTDIR = ../bin
  DLLDESTDIR = ../bin
}

CONFIG(release, debug|release){
  OBJECTS_DIR = ../temp/$$TARGET/release
  MOC_DIR = ../temp/$$TARGET/release
  RCC_DIR = ../temp/$$TARGET/release
  UI_DIR = ../temp/$$TARGET/release
}
CONFIG(debug, debug|release){
  OBJECTS_DIR = ../temp/$$TARGET/debug
  MOC_DIR = ../temp/$$TARGET/debug
  RCC_DIR = ../temp/$$TARGET/debug
  UI_DIR = ../temp/$$TARGET/debug
}


SOURCES += \
    QMathParser_1_0/muParser/muParserTokenReader.cpp \
    QMathParser_1_0/muParser/muParserTest.cpp \
    QMathParser_1_0/muParser/muParserInt.cpp \
    QMathParser_1_0/muParser/muParserError.cpp \
    QMathParser_1_0/muParser/muParserDLL.cpp \
    QMathParser_1_0/muParser/muParserComplex.cpp \
    QMathParser_1_0/muParser/muParserCallback.cpp \
    QMathParser_1_0/muParser/muParserBytecode.cpp \
    QMathParser_1_0/muParser/muParserBase.cpp \
    QMathParser_1_0/muParser/muParser.cpp \
    mucalculator.cpp

HEADERS  += \
    ../include/export/mucalculator_export_lib.h \
    QMathParser_1_0/muParser/muParserTokenReader.h \
    QMathParser_1_0/muParser/muParserToken.h \
    QMathParser_1_0/muParser/muParserTest.h \
    QMathParser_1_0/muParser/muParserStack.h \
    QMathParser_1_0/muParser/muParserInt.h \
    QMathParser_1_0/muParser/muParserFixes.h \
    QMathParser_1_0/muParser/muParserError.h \
    QMathParser_1_0/muParser/muParserDLL.h \
    QMathParser_1_0/muParser/muParserDef.h \
    QMathParser_1_0/muParser/muParserComplex.h \
    QMathParser_1_0/muParser/muParserCallback.h \
    QMathParser_1_0/muParser/muParserBytecode.h \
    QMathParser_1_0/muParser/muParserBase.h \
    QMathParser_1_0/muParser/muParser.h \
    ../include/mucalculator.h
