#ifndef DLLPRO_GLOBAL_H
#define DLLPRO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLLPRO_LIBRARY)
#  define DLLPROSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DLLPROSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLPRO_GLOBAL_H
