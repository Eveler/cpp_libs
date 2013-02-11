#-------------------------------------------------
#
# Project created by QtCreator 2010-09-25T12:53:49
#
#-------------------------------------------------

QT       += core gui

TARGET = QMathParser
TEMPLATE = lib

greaterThan( QT_MAJOR_VERSION, 4 ) QT += widgets

DEFINES += EXPORT_LIBRARY


INCLUDEPATH += ./ \
    ../bin/ \
    ../bin_qt5/ \
    ../include/ \
    ./QMathParser_1_0/


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
    QMathParser_1_0/muParser/muParser.cpp

HEADERS  += ../include/lib_export.h \
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
    QMathParser_1_0/muParser/muParser.h

