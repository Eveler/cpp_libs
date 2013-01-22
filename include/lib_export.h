#ifndef LIB_EXPORT_H
#define LIB_EXPORT_H

#ifdef EXPORT_LIBRARY
#define EXPORT Q_DECL_EXPORT
#else
#define EXPORT Q_DECL_IMPORT
#endif

#endif // LIB_EXPORT_H
