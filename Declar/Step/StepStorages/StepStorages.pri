INCLUDEPATH *= $$PWD/ \
    $$PWD/../../../Abstraction/AbstractSimpleObject/ \
    $$PWD/Procedure/ \
    $$PWD/Destination/ \
    $$PWD/../../../Abstraction/AbstractSimpleStorage/ \
    $$PWD/ProceduresStorage/ \
    $$PWD/DestinationsStorage/ \
    $$PWD/../../../include/

LIBS *= -L$$PWD/../../../bin/ \
    -lMFCStorage \
    -lAMSLogger \
    -lMFCCore

HEADERS *= \
    $$PWD/../../../include/abstractsimpleobject.h \
    $$PWD/../../../include/procedure.h \
    $$PWD/../../../include/destination.h \
    $$PWD/../../../include/abstractsimplestorage.h \
    $$PWD/../../../include/proceduresstorage.h \
    $$PWD/../../../include/destinationsstorage.h

SOURCES *= \
    $$PWD/../../../Abstraction/AbstractSimpleObject/abstractsimpleobject.cpp \
    $$PWD/Procedure/procedure.cpp \
    $$PWD/Destination/destination.cpp \
    $$PWD/../../../Abstraction/AbstractSimpleStorage/abstractsimplestorage.cpp \
    $$PWD/ProceduresStorage/proceduresstorage.cpp \
    $$PWD/DestinationsStorage/destinationsstorage.cpp













