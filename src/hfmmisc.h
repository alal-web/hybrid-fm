#ifndef _konq_misc_h
#define _konq_misc_h

#include "hfmprivate_export.h"

#include <QUrl>

#include <kparts/browserextension.h>

class KonqMainWindow;
class KonqView;

namespace KonqMisc
{
/**
 * Creates a new window from the history of a view, copies the history
 * @param view the History is copied from this view
 * @param steps Restore currentPos() + steps
 */
KonqMainWindow *newWindowFromHistory(KonqView *view, int steps);

/**
 * Applies the URI filters to @p url, and convert it to a QUrl.
 *
 * @p parent is used in case of a message box.
 * @p url to be filtered.
 * @p currentDirectory the directory to use, in case the url is relative.
 */
QUrl konqFilteredURL(KonqMainWindow *parent, const QString &url, const QUrl &currentDirectory = QUrl());

/**
* These are some helper functions to encode/decode session filenames. The
* problem here is that windows doesn't like files with ':' inside.
*/

QString encodeFilename(QString filename);

QString decodeFilename(QString filename);
}

#endif
