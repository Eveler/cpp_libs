TEMPLATE = lib
CONFIG += qt warn_on
QT -= gui
!win32:VERSION = 1.0.0

DEFINES += QUAZIP_BUILD
CONFIG(staticlib): DEFINES += QUAZIP_STATIC

exists( ../../../install_path.pri ){
    include(../../../install_path.pri)
}

# Input
include(quazip.pri)

unix:!symbian {
    headers.path=$$PREFIX/include/quazip
    headers.files=$$HEADERS
    target.path=$$PREFIX/lib
    INSTALLS += headers target

	OBJECTS_DIR=.obj
	MOC_DIR=.moc
	
}

win32 {
#    headers.path=$$PREFIX/include/quazip
#    headers.files=$$HEADERS
#    target.path=$$PREFIX/lib
#    INSTALLS += headers target
    # workaround for qdatetime.h macro bug
    DEFINES += NOMINMAX
}

win32 {
    target.path = $$INSTALL_WIN_LIB
    INSTALLS += target
}

symbian {

    # Note, on Symbian you may run into troubles with LGPL.
    # The point is, if your application uses some version of QuaZip,
    # and a newer binary compatible version of QuaZip is released, then
    # the users of your application must be able to relink it with the
    # new QuaZip version. For example, to take advantage of some QuaZip
    # bug fixes.

    # This is probably best achieved by building QuaZip as a static
    # library and providing linkable object files of your application,
    # so users can relink it.

    CONFIG += staticlib
    CONFIG += debug_and_release

    LIBS += -lezip

    #Export headers to SDK Epoc32/include directory
    exportheaders.sources = $$HEADERS
    exportheaders.path = quazip
    for(header, exportheaders.sources) {
        BLD_INF_RULES.prj_exports += "$$header $$exportheaders.path/$$basename(header)"
    }
}

contains(QT_CONFIG, system-zlib) {
    if(unix|win32-g++*): LIBS_PRIVATE += -lz
    else:                LIBS += zdll.lib
} else {
    INCLUDEPATH += $$[QT_INSTALL_HEADERS/get]/QtZlib
}


greaterThan(QT_MAJOR_VERSION, 4) {
  INCLUDEPATH += \
      ../../../bin_qt5 \
      ../../../include
#  !win32-msvc*:LIBS += -lz
#  win32-msvc*:LIBS += zdll.lib

  DESTDIR = ../../../bin_qt5
  DLLDESTDIR = ../../../bin_qt5
}

lessThan(QT_MAJOR_VERSION, 5) {
  INCLUDEPATH += \
      ../../../bin \
      ../../../include
#      ../../../bin \
#      C:/Qt/4.8.4/src/3rdparty/freetype/src/gzip

  DESTDIR = ../../../bin
  DLLDESTDIR = ../../../bin
}

CONFIG(release, debug|release){
  OBJECTS_DIR = ../../../temp/$$TARGET/release
  MOC_DIR = ../../../temp/$$TARGET/release
  RCC_DIR = ../../../temp/$$TARGET/release
  UI_DIR = ../../../temp/$$TARGET/release
}
CONFIG(debug, debug|release){
  OBJECTS_DIR = ../../../temp/$$TARGET/debug
  MOC_DIR = ../../../temp/$$TARGET/debug
  RCC_DIR = ../../../temp/$$TARGET/debug
  UI_DIR = ../../../temp/$$TARGET/debug
}
