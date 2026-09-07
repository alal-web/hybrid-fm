#ifndef KONQMAINWINDOWFACTORY_H
#define KONQMAINWINDOWFACTORY_H

#include "hfmopenurlrequest.h"
#include "hfmprivate_export.h"

class KonqMainWindow;
class QUrl;

namespace KonqMainWindowFactory
{

/**
 * Create a new empty window.
 * This layer on top of the KonqMainWindow constructor allows to reuse preloaded windows,
 * and offers restoring windows after a crash.
 * Note: the caller must call show()
 */
KonqMainWindow *createEmptyWindow();

KonqMainWindow *createPreloadWindow();

/**
 * Create a new window for @p url using @p args and @p req.
 * This layer on top of the KonqMainWindow constructor allows to reuse preloaded windows,
 * and offers restoring windows after a crash.
 * Note: the caller must call show()
 */
KONQ_TESTS_EXPORT KonqMainWindow *createNewWindow(const QUrl &url = QUrl(),
        const KonqOpenURLRequest &req = KonqOpenURLRequest());

KonqMainWindow *findPreloadedWindow();

};

#endif // KONQMAINWINDOWFACTORY_H
