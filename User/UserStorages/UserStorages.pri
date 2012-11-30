INCLUDEPATH *= $$PWD/ \
    $$PWD/../../Abstraction/AbstractSimpleObject/ \
    $$PWD/Post/ \
    $$PWD/Department/ \
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
    $$PWD/../../include/post.h \
    $$PWD/../../include/department.h \
    $$PWD/../../include/abstractsimplestorage.h \
    $$PWD/../../include/postsstorage.h \
    $$PWD/../../include/departmentsstorage.h

SOURCES *= \
    $$PWD/../../Abstraction/AbstractSimpleObject/abstractsimpleobject.cpp \
    $$PWD/Post/post.cpp \
    $$PWD/Department/department.cpp \
    $$PWD/../../Abstraction/AbstractSimpleStorage/abstractsimplestorage.cpp \
    $$PWD/PostsStorage/postsstorage.cpp \
    $$PWD/DepartmentsStorage/departmentsstorage.cpp













