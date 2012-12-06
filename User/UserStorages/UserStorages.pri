INCLUDEPATH *= $$PWD/ \
    $$PWD/../../Abstraction/AbstractSimpleObject/ \
    $$PWD/../../Abstraction/AbstractSimpleStorage/ \
    $$PWD/PostsStorage/ \
    $$PWD/DepartmentsStorage/ \
    $$PWD/../../include/

LIBS *= -L$$PWD/../../bin/ \
    -lMFCStorage \
    -lAMSLogger \
    -lMFCCore

HEADERS *= \
    $$PWD/../../include/abstractsimpleobject.h \
    $$PWD/../../include/abstractsimplestorage.h \
    $$PWD/../../include/postsstorage.h \
    $$PWD/../../include/departmentsstorage.h

SOURCES *= \
    $$PWD/../../Abstraction/AbstractSimpleObject/abstractsimpleobject.cpp \
    $$PWD/../../Abstraction/AbstractSimpleStorage/abstractsimplestorage.cpp \
    $$PWD/PostsStorage/postsstorage.cpp \
    $$PWD/DepartmentsStorage/departmentsstorage.cpp














