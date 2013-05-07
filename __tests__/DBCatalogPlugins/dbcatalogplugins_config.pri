DBC_INTERFACES =

greaterThan(QT_MAJOR_VERSION, 4): DBC_LIBS_BIN = ../../bin_qt5/
lessThan(QT_MAJOR_VERSION, 5): DBC_LIBS_BIN = ../../bin/
DBC_LIBS_INCLUDE = ../../include/

DBC_DEST_DIR = plugins/
DBC_PLUGINS_DIR = $${DBC_DEST_DIR}
