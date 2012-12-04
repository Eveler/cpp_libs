INCLUDEPATH *= $$PWD/ \
    $$PWD/../../include/

include(./StepStorages/StepStorages.pri)

LIBS *= -L$$PWD/../../bin/ \
    -lUser

HEADERS *= \
    $$PWD/../../include/step.h

SOURCES *= \
    $$PWD/step.cpp






