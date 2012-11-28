INCLUDEPATH *= $$PWD/ \
    $$PWD/DestinationsStorage/ \
    $$PWD/ProceduresStorage/ \
    $$PWD/../../../include/

LIBS *= -L$$PWD/../../../bin/ \
    -lMFCStorage \
    -lAMSLogger \
    -lMFCCore

HEADERS *= \
    $$PWD/../../../include/proceduresstorage.h \
    $$PWD/../../../include/destinationsstorage.h

SOURCES *= \
    $$PWD/ProceduresStorage/proceduresstorage.cpp \
    $$PWD/DestinationsStorage/destinationsstorage.cpp





