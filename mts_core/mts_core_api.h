#ifndef MTS_CORE_GLOBAL_H
#define MTS_CORE_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MTS_CORE_LIB
#define MTS_CORE_API Q_DECL_EXPORT
#else
#define MTS_CORE_API Q_DECL_IMPORT
#endif
#endif // MTS_CORE_GLOBAL_H