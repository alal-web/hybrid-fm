#include <KParts/ReadOnlyPart>

#include "hfmbrowserinterface.h"
#include "hfmmainwindow.h"
#include "urlloader.h"
#include "hfmview.h"

KonqBrowserInterface::KonqBrowserInterface(KonqMainWindow *mainWindow, KParts::ReadOnlyPart *part):
    KParts::BrowserInterface(mainWindow), m_mainWindow(mainWindow), m_part(part)
{
}

void KonqBrowserInterface::toggleCompleteFullScreen(bool on)
{
    m_mainWindow->toggleCompleteFullScreen(on);
}

bool KonqBrowserInterface::isCorrectPartForLocalFile(KParts::ReadOnlyPart *part, const QString &path)
{
    return part->metaData().pluginId() == UrlLoader::partForLocalFile(path);
}
