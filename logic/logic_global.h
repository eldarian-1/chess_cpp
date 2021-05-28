#ifndef LOGIC_GLOBAL_H
#define LOGIC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LOGIC_LIBRARY)
#  define LOGIC_EXPORT Q_DECL_EXPORT
#else
#  define LOGIC_EXPORT Q_DECL_IMPORT
#endif

#endif // LOGIC_GLOBAL_H
