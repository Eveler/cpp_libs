# List of header files that should be compiled with the ODB compiler.
#
##ODB_FILES += employee.hxx
isEmpty(ODB_FILES):error("Need to specify ODB_FILES!")

# ODB compiler flags.
#
##ODB_FLAGS = --database pgsql --profile qt --generate-schema --generate-query --generate-session
#ODB_FLAGS += -I$$PWD/include
#ODB_FLAGS += -I$$PWD/odb-2.3.0-i686-windows/etc
isEmpty(ODB_FLAGS):error("Need to specify ODB_FLAGS!")

# Select the database we are going to use.
#
#DEFINES += DATABASE_PGSQL
#DEFINES += DATABASE_SQLITE

# Suppress unknown pragmas GCC warnings.
#
QMAKE_CXXFLAGS_WARN_ON = $$QMAKE_CXXFLAGS_WARN_ON -Wno-unknown-pragmas

# Link to the ODB runtime libraries.
#
LIBS += -L$$PWD/lib
##LIBS += -lodb-pgsql
LIBS += -lodb-qt
LIBS += -lodb

INCLUDEPATH += $$PWD/include

# ODB compilation rules. Normally you don't need to change anything here.
#

# Add the Qt headers directory to the ODB include directory list.
#
ODB_FLAGS += -I$$[QT_INSTALL_HEADERS]

# Newer versions of QtCreator do builds in a separate directory. As a
# result, we need to append the source directory to ODB files.
#
for(dir, ODB_FILES) {
  ODB_PWD_FILES += $$PWD/$${dir}
}

##!build_pass:message( $$ODB_PWD_FILES )
ODB_EXE = $$PWD/odb-2.3.0-i686-windows/bin/odb.exe
#odb.name = odb ${QMAKE_FILE_IN}
odb.name = $$ODB_EXE ${QMAKE_FILE_IN}
#odb.input = ODB_PWD_FILES
odb.input = ODB_FILES
odb.output = ${QMAKE_FILE_BASE}-odb.cxx
#odb.commands = odb $$ODB_FLAGS ${QMAKE_FILE_IN}
odb.commands = $$ODB_EXE $$ODB_FLAGS ${QMAKE_FILE_IN}
#odb.depends = $$ODB_PWD_FILES
odb.depends = $$ODB_FILES
odb.variable_out = SOURCES
odb.clean = ${QMAKE_FILE_BASE}-odb.cxx ${QMAKE_FILE_BASE}-odb.hxx ${QMAKE_FILE_BASE}-odb.ixx ${QMAKE_FILE_BASE}.sql
QMAKE_EXTRA_COMPILERS += odb

#odbh.name = odb ${QMAKE_FILE_IN}
odbh.name = $$ODB_EXE ${QMAKE_FILE_IN}
#odbh.input = ODB_PWD_FILES
odbh.input = ODB_FILES
odbh.output = ${QMAKE_FILE_BASE}-odb.hxx
#odbh.commands = @true
odbh.commands = @echo
odbh.CONFIG = no_link
odbh.depends = ${QMAKE_FILE_BASE}-odb.cxx
QMAKE_EXTRA_COMPILERS += odbh
