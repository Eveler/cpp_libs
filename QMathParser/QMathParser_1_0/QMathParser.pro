#-------------------------------------------------
#
# Project created by QtCreator 2010-09-25T12:53:49
#
#-------------------------------------------------

QT       += core gui

TARGET = QMathParser
TEMPLATE = app

greaterThan( QT_MAJOR_VERSION, 4 ) QT += widgets


SOURCES += main.cpp\
        qmathparser.cpp \
    muParser/muParserTokenReader.cpp \
    muParser/muParserTest.cpp \
    muParser/muParserInt.cpp \
    muParser/muParserError.cpp \
    muParser/muParserDLL.cpp \
    muParser/muParserComplex.cpp \
    muParser/muParserCallback.cpp \
    muParser/muParserBytecode.cpp \
    muParser/muParserBase.cpp \
    muParser/muParser.cpp

HEADERS  += qmathparser.h \
    muParser/muParserTokenReader.h \
    muParser/muParserToken.h \
    muParser/muParserTest.h \
    muParser/muParserStack.h \
    muParser/muParserInt.h \
    muParser/muParserFixes.h \
    muParser/muParserError.h \
    muParser/muParserDLL.h \
    muParser/muParserDef.h \
    muParser/muParserComplex.h \
    muParser/muParserCallback.h \
    muParser/muParserBytecode.h \
    muParser/muParserBase.h \
    muParser/muParser.h

FORMS    += qmathparser.ui

RESOURCES += \
    qmathparser.qrc
