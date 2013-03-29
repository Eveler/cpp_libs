QT       += gui

TARGET = Address
CONFIG(debug, debug|release): TARGET = $${TARGET}d
#CONFIG += create_prl

TEMPLATE = lib

DEFINES += ADDRESS_LIBRARY

INCLUDEPATH += ./ \
    ../bin/ \
    ../include/ \
    ../Abstraction/AbstractSimpleObject/ \
    ../Abstraction/AbstractSimpleStorage/ \
    ./Address/ \
    ./AddressesStorage/ \
    ./Address/Country/CountriesStorage/ \
    ./Address/Subject/Subject/ \
    ./Address/Subject/SubjectsStorage/ \
    ./Address/Region/Region/ \
    ./Address/Region/RegionsStorage/ \
    ./Address/Area/Area/ \
    ./Address/Area/AreasStorage/ \
    ./Address/City/City/ \
    ./Address/City/CitiesStorage/ \
    ./Address/InnerCity/InnerCity/ \
    ./Address/InnerCity/InnerCitiesStorage/ \
    ./Address/Township/Township/ \
    ./Address/Township/TownshipsStorage/ \
    ./Address/Street/Street/ \
    ./Address/Street/StreetsStorage/ \
    ./Address/Subaddress/Subaddress/ \
    ./Address/Subaddress/SubaddressesStorage/ \
    ./Address/Slaveaddress/SlaveaddressesStorage/ \
    ./Address/Abbreviation/Abbreviation/ \
    ./Address/Abbreviation/AbbreviationsStorage/ \
    ./Address/CenterStatus/CenterStatusesStorage/ \
    ./Address/StructureStatus/StructureStatus/ \
    ./Address/StructureStatus/StructureStatusesStorage/ \
    ./Address/Postcode/PostcodesStorage/

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE279790D
    TARGET.CAPABILITY =
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Address.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

DESTDIR = ../bin
DLLDESTDIR = ../bin
CONFIG(release, debug|release){
  OBJECTS_DIR = ../temp/$$TARGET/release
  MOC_DIR = ../temp/$$TARGET/release
  RCC_DIR = ../temp/$$TARGET/release
  UI_DIR = ../temp/$$TARGET/release
}
CONFIG(debug, debug|release){
  OBJECTS_DIR = ../temp/$$TARGET/debug
  MOC_DIR = ../temp/$$TARGET/debug
  RCC_DIR = ../temp/$$TARGET/debug
  UI_DIR = ../temp/$$TARGET/debug
}

LIBS += -L../bin/ \
    -lMFCStorage \
    -lAMSLogger \
    -lMFCCore

SOURCES += \
    ../Abstraction/AbstractSimpleObject/abstractsimpleobject.cpp \
    ../Abstraction/AbstractSimpleStorage/abstractsimplestorage.cpp \
    Address/address.cpp \
    AddressesStorage/addressesstorage.cpp \
    Address/Country/CountriesStorage/countriesstorage.cpp \
    Address/Subject/Subject/subject.cpp \
    Address/Subject/SubjectsStorage/subjectsstorage.cpp \
    Address/Region/Region/region.cpp \
    Address/Region/RegionsStorage/regionsstorage.cpp \
    Address/Area/Area/area.cpp \
    Address/Area/AreasStorage/areasstorage.cpp \
    Address/City/City/city.cpp \
    Address/City/CitiesStorage/citiesstorage.cpp \
    Address/InnerCity/InnerCity/innercity.cpp \
    Address/InnerCity/InnerCitiesStorage/innercitiesstorage.cpp \
    Address/Township/Township/township.cpp \
    Address/Township/TownshipsStorage/townshipsstorage.cpp \
    Address/Street/Street/street.cpp \
    Address/Street/StreetsStorage/streetsstorage.cpp \
    Address/Subaddress/Subaddress/subaddress.cpp \
    Address/Subaddress/SubaddressesStorage/subaddressesstorage.cpp \
    Address/Slaveaddress/SlaveaddressesStorage/slaveaddressesstorage.cpp \
    Address/Abbreviation/Abbreviation/abbreviation.cpp \
    Address/Abbreviation/AbbreviationsStorage/abbreviationsstorage.cpp \
    Address/CenterStatus/CenterStatusesStorage/centerstatusesstorage.cpp \
    Address/StructureStatus/StructureStatus/structurestatus.cpp \
    Address/StructureStatus/StructureStatusesStorage/structurestatusesstorage.cpp \
    Address/Postcode/PostcodesStorage/postcodesstorage.cpp

HEADERS += \
    ../include/abstractsimpleobject.h \
    ../include/abstractsimplestorage.h \
    ../include/address.h \
    ../include/addressesstorage.h \
    ../include/countriesstorage.h \
    ../include/subject.h \
    ../include/subjectsstorage.h \
    ../include/region.h \
    ../include/regionsstorage.h \
    ../include/area.h \
    ../include/areasstorage.h \
    ../include/city.h \
    ../include/citiesstorage.h \
    ../include/innercity.h \
    ../include/innercitiesstorage.h \
    ../include/township.h \
    ../include/townshipsstorage.h \
    ../include/street.h \
    ../include/streetsstorage.h \
    ../include/subaddress.h \
    ../include/subaddressesstorage.h \
    ../include/slaveaddressesstorage.h \
    ../include/abbreviation.h \
    ../include/abbreviationsstorage.h \
    ../include/centerstatusesstorage.h \
    ../include/structurestatus.h \
    ../include/structurestatusesstorage.h \
    ../include/postcodesstorage.h


