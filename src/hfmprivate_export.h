#ifndef KONQPRIVATE_EXPORT_H
#define KONQPRIVATE_EXPORT_H

#include "hybridfmprivate_export.h"

/* Classes from the application, which are exported only for unit tests */
#ifdef BUILD_TESTING
# ifndef KONQ_TESTS_EXPORT
#  define KONQ_TESTS_EXPORT HYBRIDFMPRIVATE_EXPORT
# endif
#else /* not compiling tests */
# define KONQ_TESTS_EXPORT
#endif

#endif
