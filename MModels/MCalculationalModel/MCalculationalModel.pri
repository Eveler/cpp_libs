INCLUDEPATH *= $$PWD/ \
    $$PWD/MCalculationalColumn/ \
    $$PWD/MCalculationalRow/ \
    $$PWD/CalculationAlgorithms/Abstract/ \
    $$PWD/CalculationAlgorithms/Column/ \
    $$PWD/CalculationAlgorithms/Row/

LIB_LIST *= \
    -lmuCalculator \
    -lAMSLogger

HEADERS *= \
    $$PWD/../../include/mcalculationalmodel.h \
    $$PWD/mcalculationalmodelprivate.h \
    $$PWD/../../include/mcalculationalcolumn.h \
    $$PWD/MCalculationalColumn/mcalculationalcolumnprivate.h \
    $$PWD/../../include/mcalculationalrow.h \
    $$PWD/MCalculationalRow/mcalculationalrowprivate.h \
    $$PWD/../../include/mabstractcolumncalculationalgorithm.h \
    $$PWD/CalculationAlgorithms/Abstract/mabstractcolumncalculationalgorithmprivate.h \
    $$PWD/../../include/mabstractrowcalculationalgorithm.h \
    $$PWD/CalculationAlgorithms/Abstract/mabstractrowcalculationalgorithmprivate.h \
    $$PWD/../../include/mrowcalculationalgorithm.h \
    $$PWD/CalculationAlgorithms/Row/mrowcalculationalgorithmprivate.h

SOURCES *= \
    $$PWD/mcalculationalmodel.cpp \
    $$PWD/mcalculationalmodelprivate.cpp \
    $$PWD/MCalculationalColumn/mcalculationalcolumn.cpp \
    $$PWD/MCalculationalColumn/mcalculationalcolumnprivate.cpp \
    $$PWD/MCalculationalRow/mcalculationalrow.cpp \
    $$PWD/MCalculationalRow/mcalculationalrowprivate.cpp \
    $$PWD/CalculationAlgorithms/Abstract/mabstractcolumncalculationalgorithm.cpp \
    $$PWD/CalculationAlgorithms/Abstract/mabstractcolumncalculationalgorithmprivate.cpp \
    $$PWD/CalculationAlgorithms/Abstract/mabstractrowcalculationalgorithm.cpp \
    $$PWD/CalculationAlgorithms/Abstract/mabstractrowcalculationalgorithmprivate.cpp \
    $$PWD/CalculationAlgorithms/Row/mrowcalculationalgorithm.cpp \
    $$PWD/CalculationAlgorithms/Row/mrowcalculationalgorithmprivate.cpp







