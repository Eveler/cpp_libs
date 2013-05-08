QT *= network webkit xml

greaterThan(QT_MAJOR_VERSION, 4): QT *= webkitwidgets


INCLUDEPATH += $${PWD}/ \
    $${PWD}/MDateDialog/


LIB_LIST *= \
    -lMReportEngine \


SOURCES += $${PWD}/mreportviewer.cpp \
    $${PWD}/mreportviewer_p.cpp \
    $${PWD}/MDateDialog/mdatedialog.cpp

HEADERS  += ../include/mreportviewer.h \
    $${PWD}/mreportviewer_p.h \
    $${PWD}/MDateDialog/mdatedialog.h

FORMS    += $${PWD}/mreportviewer.ui \
    $${PWD}/MDateDialog/mdatedialog.ui

RESOURCES += \
    $${PWD}/MDateDialog/MDateDialog_Icons.qrc
