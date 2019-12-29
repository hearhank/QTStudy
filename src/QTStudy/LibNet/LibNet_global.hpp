#ifndef LIBNET_GLOBAL_HPP
#define LIBNET_GLOBAL_HPP

#include <QtCore/qglobal.h>

#if defined(LIBNET_LIBRARY)
#  define LIBNET_EXPORT Q_DECL_EXPORT
#else
#  define LIBNET_EXPORT Q_DECL_IMPORT
#endif

#endif // LIBNET_GLOBAL_HPP
