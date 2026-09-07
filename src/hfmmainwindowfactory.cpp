#include "hfmmainwindowfactory.h"
#include "hfmmainwindow.h"
#include "hfmview.h"
#include "hfmsettingsxt.h"
#include "hfmdebug.h"
#include "hfmurl.h"

#include <KWindowInfo>
#include <KStartupInfo>
#include <QTimer>

// Terminates fullscreen-mode for any full-screen window on the current desktop
static void abortFullScreenMode()
{
    QList<KonqMainWindow *> *mainWindows = KonqMainWindow::mainWindowList();
    if (mainWindows) {
        foreach (KonqMainWindow *window, *mainWindows) {
            if (window->fullScreenMode()) {
                KWindowInfo info(window->winId(), NET::WMDesktop);
                if (info.valid() && info.isOnCurrentDesktop()) {
                    window->setWindowState(window->windowState() & ~Qt::WindowFullScreen);
                }
            }
        }
    }
}

// Prepare another preloaded window for next time
static void ensurePreloadedWindow()
{
    if (HybridFMSettings::alwaysHavePreloaded()) {
        QTimer::singleShot(500, nullptr, []() {return KonqMainWindowFactory::createPreloadWindow();});
    }
}

KonqMainWindow* KonqMainWindowFactory::findPreloadedWindow()
{
    QList<KonqMainWindow *> *mainWindowList = KonqMainWindow::mainWindowList();
    if (!mainWindowList) {
        return nullptr;
    }
    auto it = std::find_if(mainWindowList->constBegin(), mainWindowList->constEnd(), [](KonqMainWindow* w){return w->isPreloaded();});
    return it != mainWindowList->constEnd() ? *it : nullptr;
}

KonqMainWindow *KonqMainWindowFactory::createEmptyWindow()
{
    abortFullScreenMode();

    // Let's see if we can reuse a preloaded window
    KonqMainWindow *win = findPreloadedWindow();
    if (win) {
        qCDebug(KONQUEROR_LOG) << "Reusing preloaded window" << win;
        KStartupInfo::setWindowStartupId(win->winId(), KStartupInfo::startupId());
    } else {
        win = new KonqMainWindow(KonqUrl::url(KonqUrl::Type::Blank));
    }
    ensurePreloadedWindow();
    return win;
}

KonqMainWindow * KonqMainWindowFactory::createPreloadWindow()
{
    KonqMainWindow *mw = new KonqMainWindow(KonqUrl::url(KonqUrl::Type::Blank));
    return mw;
}

KonqMainWindow *KonqMainWindowFactory::createNewWindow(const QUrl &url,
                                          const KonqOpenURLRequest &req)
{
    KonqMainWindow *mainWindow = KonqMainWindowFactory::createEmptyWindow();
    if (!url.isEmpty()) {
        mainWindow->openUrl(nullptr, url, QString(), req);
        mainWindow->setInitialFrameName(req.browserArgs.frameName);
    } else {
        mainWindow->openUrl(nullptr, QUrl(HybridFMSettings::startURL()));
        mainWindow->focusLocationBar();
    }
    return mainWindow;
}
