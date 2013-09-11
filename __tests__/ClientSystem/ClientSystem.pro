QT += qml quick sql
TARGET = ClientSystemTest
qtHaveModule(widgets) {
    QT += widgets
}

INCLUDEPATH *= ./

CONFIG(release, debug|release){
  OBJECTS_DIR = ./temp/$$TARGET/release
  MOC_DIR = ./temp/$$TARGET/release
  RCC_DIR = ./temp/$$TARGET/release
  UI_DIR = ./temp/$$TARGET/release
}
CONFIG(debug, debug|release){
  OBJECTS_DIR = ./temp/$$TARGET/debug
  MOC_DIR = ./temp/$$TARGET/debug
  RCC_DIR = ./temp/$$TARGET/debug
  UI_DIR = ./temp/$$TARGET/debug
}

DESTDIR = ./bin
DLLDESTDIR = ./bin

SOURCES += \
    main.cpp

OTHER_FILES += \
    main.qml

RESOURCES += \
    qmls.qrc
