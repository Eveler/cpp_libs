#ifndef QWIA_GLOBAL_H
#define QWIA_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QWIA_LIBRARY)
#  define QWIASHARED_EXPORT Q_DECL_EXPORT
#else
#  define QWIASHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // QWIA_GLOBAL_H
