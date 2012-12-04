INCLUDEPATH *= $$PWD/ \
    $$PWD/../../../Abstraction/AbstractSimpleObject/ \
    $$PWD/../../../Abstraction/AbstractSimpleStorage/ \
    $$PWD/ProceduresStorage/ \
    $$PWD/DestinationsStorage/ \
    $$PWD/CallsStorage/ \
    $$PWD/SmsStorage/ \
    $$PWD/../../../include/

LIBS *= -L$$PWD/../../../bin/ \
    -lMFCStorage \
    -lAMSLogger \
    -lMFCCore

HEADERS *= \
    $$PWD/../../../include/abstractsimpleobject.h \
    $$PWD/../../../include/abstractsimplestorage.h \
    $$PWD/../../../include/proceduresstorage.h \
    $$PWD/../../../include/destinationsstorage.h \
    $$PWD/../../../include/callsstorage.h \
    $$PWD/../../../include/smsstorage.h

SOURCES *= \
    $$PWD/../../../Abstraction/AbstractSimpleObject/abstractsimpleobject.cpp \
    $$PWD/../../../Abstraction/AbstractSimpleStorage/abstractsimplestorage.cpp \
    $$PWD/ProceduresStorage/proceduresstorage.cpp \
    $$PWD/DestinationsStorage/destinationsstorage.cpp \
    $$PWD/CallsStorage/callsstorage.cpp \
    $$PWD/SmsStorage/smsstorage.cpp













