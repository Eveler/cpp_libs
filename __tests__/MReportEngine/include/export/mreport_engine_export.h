#ifndef MREPORT_ENGINE_EXPORT_H
#define MREPORT_ENGINE_EXPORT_H

#ifdef NOTUSE_LIB_MREPORTENGINE
#define EXPORT_MREPORTENGINE
#else
#ifdef EXPORT_LIB_MREPORTENGINE
#define EXPORT_MREPORTENGINE Q_DECL_EXPORT
#else
#define EXPORT_MREPORTENGINE Q_DECL_IMPORT
#endif
#endif

#endif // MREPORT_ENGINE_EXPORT_H
