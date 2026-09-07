#include <QtGlobal>

#include "hfmapplication.h"
#include "hfmsettings.h"
#include <hybrid-fm-version.h>
#include "hfmmainwindow.h"
#include "KonquerorAdaptor.h"
#include "hfmviewmanager.h"
#include "hfmurl.h"
#include "hfmsettingsxt.h"
#include "hfmsessionmanager.h"
#include "hfmclosedwindowsmanager.h"
#include "hfmdebug.h"
#include "hfmmainwindow.h"
#include "hfmmainwindowfactory.h"
#include "hfmmisc.h"

#include <QDBusConnection>
#include <QDBusMessage>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>
#include <QProcess>
#include <QDirIterator>
#include <QTextStream>

#include <KCrash>
#include <KLocalizedString>
#include <KSharedConfig>
#include <KDBusService>
#include <KStartupInfo>
#include <KWindowSystem>
#include <kwindowsystem_version.h>

#include <iostream>

HybridFMApplication::HybridFMApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    // enable high dpi support
    setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    new KonquerorAdaptor; // not really an adaptor
    const QString dbusInterface = QStringLiteral("org.kde.Konqueror.Main");
    QDBusConnection dbus = QDBusConnection::sessionBus();
    dbus.connect(QString(), KONQ_MAIN_PATH, dbusInterface, QStringLiteral("reparseConfiguration"), this, SLOT(slotReparseConfiguration()));
    dbus.connect(QString(), KONQ_MAIN_PATH, dbusInterface, QStringLiteral("addToCombo"), this,
                 SLOT(slotAddToCombo(QString,QDBusMessage)));
    dbus.connect(QString(), KONQ_MAIN_PATH, dbusInterface, QStringLiteral("removeFromCombo"), this,
                 SLOT(slotRemoveFromCombo(QString,QDBusMessage)));
    dbus.connect(QString(), KONQ_MAIN_PATH, dbusInterface, QStringLiteral("comboCleared"), this, SLOT(slotComboCleared(QDBusMessage)));

#ifdef WEBENGINEPART_DICTIONARY_DIR
    if (!qEnvironmentVariableIsSet("QTWEBENGINE_DICTIONARIES_PATH")) {
        qputenv("QTWEBENGINE_DICTIONARIES_PATH", WEBENGINEPART_DICTIONARY_DIR);
    }
#endif

    QByteArray flags = qgetenv("QTWEBENGINE_CHROMIUM_FLAGS");
    flags.append(" --enable-features=WebRTCPipeWireCapturer");
    qputenv("QTWEBENGINE_CHROMIUM_FLAGS", flags);

    KLocalizedString::setApplicationDomain("hybrid-fm");
}

void HybridFMApplication::slotReparseConfiguration()
{
    KSharedConfig::openConfig()->reparseConfiguration();
    KonqFMSettings::reparseConfiguration();

    QList<KonqMainWindow *> *mainWindows = KonqMainWindow::mainWindowList();
    if (mainWindows) {
        foreach (KonqMainWindow *window, *mainWindows) {
            window->reparseConfiguration();
        }
    }
}

void HybridFMApplication::slotAddToCombo(const QString &url, const QDBusMessage &msg)
{
    KonqMainWindow::comboAction(KonqMainWindow::ComboAdd, url, msg.service());
}

void HybridFMApplication::slotRemoveFromCombo(const QString &url, const QDBusMessage &msg)
{
    KonqMainWindow::comboAction(KonqMainWindow::ComboRemove, url, msg.service());
}

void HybridFMApplication::slotComboCleared(const QDBusMessage &msg)
{
    KonqMainWindow::comboAction(KonqMainWindow::ComboClear, QString(), msg.service());
}

void HybridFMApplication::setupAboutData()
{
    KAboutData m_aboutData("hybrid-fm", i18n("HybridFM"), HYBRIDFM_VERSION);
    m_aboutData.setShortDescription(i18n("Hybrid file manager and web browser."));
    m_aboutData.setHomepage("https://astralinux.ru/");

    KAboutData::setApplicationData(m_aboutData);
}

void HybridFMApplication::setupParser()
{
    m_parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    m_aboutData.setupCommandLine(&m_parser);

    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("silent")}, i18n("Start without a default window, when called without URLs")));
    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("preload")}, i18n("Preload for later use. This mode does not support URLs on the command line")));
    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("profile")}, i18n("Profile to open (DEPRECATED, IGNORED)"), i18n("profile")));
    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("sessions")}, i18n("List available sessions")));
    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("open-session")}, i18n("Session to open"), i18n("session")));
    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("mimetype")}, i18n("Mimetype to use for this URL (e.g. text/html or inode/directory)"), i18n("mimetype")));
    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("part")}, i18n("Part to use (e.g. khtml or kwebkitpart)"), i18n("service")));
    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("select")}, i18n("For URLs that point to files, opens the directory and selects the file, instead of opening the actual file")));
    m_parser.addOption(QCommandLineOption(QStringList{QStringLiteral("tempfile")}, i18n("The files/URLs opened by the application will be deleted after use")));

    m_parser.addPositionalArgument(QStringLiteral("[URL]"), i18n("Location to open"));
}

static void fixOldStartUrl() {
    QUrl startUrl(HybridFMSettings::startURL());
    if (startUrl.scheme() == "about") {
        startUrl.setScheme(KonqUrl::scheme());
        HybridFMSettings::setStartURL(startUrl.url());
        HybridFMSettings::self()->save();
    }
}

int HybridFMApplication::startFirstInstance()
{
    fixOldStartUrl();

    if (isSessionRestored()) {
        restoreSession();
    } else {
        performStart(QDir::currentPath(), true);
    }

    QString programName = QApplication::applicationFilePath();

    //Ensure a session manager is created
    KonqSessionManager::self();

    const int ret = exec();

    bool alwaysPreload = HybridFMSettings::alwaysHavePreloaded();

    // Delete all KonqMainWindows, so that we don't have
    // any parts loaded when KLibLoader::cleanUp is called.
    // (and Qt doesn't delete WA_DeleteOnClose widgets on exit anyway :()
    while (KonqMainWindow::mainWindowList() != nullptr) {
        // the list will be deleted by last KonqMainWindow
        delete KonqMainWindow::mainWindowList()->first();
    }

    // Notify the session manager that the instance was closed without errors, and normally.
    KonqSessionManager::self()->disableAutosave();
    KonqSessionManager::self()->deleteOwnedSessions();

    KonqClosedWindowsManager::destroy();

    if (alwaysPreload) {
        QProcess::startDetached(programName, {"--preload"});
    }

    return ret;
}

int HybridFMApplication::start()
{
    setupAboutData();
    setupParser();

    KCrash::initialize();

    m_parser.process(*this);
    m_aboutData.processCommandLine(&m_parser);

    KDBusService dbusService(KDBusService::Unique);
    auto activateApp = [this](const QStringList &arguments, const QString &workingDirectory) {
        m_parser.parse(arguments);
        performStart(workingDirectory, false);
    };
    QObject::connect(&dbusService, &KDBusService::activateRequested, activateApp);

    return startFirstInstance();
}

int HybridFMApplication::performStart(const QString& workingDirectory, bool firstInstance)
{
    const QStringList args = m_parser.positionalArguments();

    if (m_parser.isSet("sessions")) {
        listSessions();
        return 0;
    } else if (m_parser.isSet("open-session")) {
        return openSession(m_parser.value("open-session"));
    }

    //We check for the --preload switch before attempting recovering session because we shouldn't
    //display windows when the user only asked to preload a window
    if (m_parser.isSet("preload")) {
        preloadWindow(args);
        return 0;
    }

    if (!m_sessionRecoveryAttempted) {
        // Ask the user to recover session if applicable
        KonqSessionManager::self()->askUserToRestoreAutosavedAbandonedSessions();
        m_sessionRecoveryAttempted = true;
    }

    WindowCreationResult result;
    if (args.isEmpty()) {
        result = createEmptyWindow(firstInstance);
    } else {
        result = createWindowsForUrlArguments(args, workingDirectory);
    }

    KonqMainWindow *mw = result.first;
    if (!firstInstance && mw) {
#if KWINDOWSYSTEM_VERSION >= QT_VERSION_CHECK(5,62,0)
        mw ->setAttribute(Qt::WA_NativeWindow, true);
        KStartupInfo::setNewStartupId(mw->windowHandle(), KStartupInfo::startupId());
#else
        KStartupInfo::setNewStartupId(mw, KStartupInfo::startupId());
#endif
        KWindowSystem::forceActiveWindow(mw->winId());
    }

    return result.second;
}

HybridFMApplication::WindowCreationResult HybridFMApplication::createWindowsForUrlArguments(const QStringList& args, const QString &workingDirectory)
{
    QList<QUrl> urlList;
    urlList.reserve(args.length());

    auto urlFromArg = [workingDirectory](const QString &arg) {
        const QUrl url = QUrl::fromUserInput(arg, workingDirectory);
        // KonqMisc::konqFilteredURL doesn't cope with local files... A bit of hackery below
        if (url.isLocalFile() && QFile::exists(url.toLocalFile())) { // "konqueror index.html"
            return url;
        } else { // "konqueror slashdot.org"
            return KonqMisc::konqFilteredURL(nullptr, arg);
        }
    };

    for (const QString &arg : args) {
        urlList.append(urlFromArg(arg));
    };

    QList<QUrl> filesToSelect;
    if (m_parser.isSet("select")) {
        // Get all distinct directories from 'files' and open a tab
        // for each directory.
        QList<QUrl> dirs;
        for (const QUrl &url : urlList) {
            const QUrl dir(url.adjusted(QUrl::RemoveFilename));
            if (!dirs.contains(dir)) {
                dirs.append(dir);
            }
        }
        filesToSelect = urlList;
        urlList = dirs;
    }

    QUrl firstUrl = urlList.takeFirst();

    KParts::OpenUrlArguments urlargs;
    if (m_parser.isSet("mimetype")) {
        urlargs.setMimeType(m_parser.value("mimetype"));
    }

    KonqOpenURLRequest req;
    req.args = urlargs;
    req.filesToSelect = filesToSelect;
    req.tempFile = m_parser.isSet("tempfile");
    req.serviceName = m_parser.value("part");

    KonqMainWindow *mainwin = KonqMainWindowFactory::createNewWindow(firstUrl, req);
    if (!mainwin) {
        return qMakePair(nullptr, 1);
    }
    mainwin->show();
    if (!urlList.isEmpty()) {
        // Open the other urls as tabs in that window
        mainwin->openMultiURL(urlList);
    }
    return qMakePair(mainwin, 0);
}

void HybridFMApplication::preloadWindow(const QStringList &args)
{
    if (!args.isEmpty()) {
        QTextStream ts(stderr, QIODevice::WriteOnly);
        ts << i18n("You can't pass URLs when using the --preload switch. The URLs will be ignored\n");
    }
    KonqMainWindowFactory::createPreloadWindow();
}

HybridFMApplication::WindowCreationResult HybridFMApplication::createEmptyWindow(bool firstInstance)
{
    //Always create a new window except when called with the --silent switch or a session has been recovered (see #388333)
    if (m_parser.isSet("silent")) {
        return qMakePair(nullptr, 0);
    }

    if (firstInstance) { // If session recovery created some windows, no need for an empty window here.
        QList<KonqMainWindow *> *mainWindowList = KonqMainWindow::mainWindowList();
        if (mainWindowList && !mainWindowList->isEmpty()) {
            return qMakePair(mainWindowList->at(0), 0);
        }
    }

    KonqMainWindow *mainWin = KonqMainWindowFactory::createNewWindow();
    if (mainWin) {
        mainWin->show();
        return qMakePair(mainWin, 0);
    } else {
        return qMakePair(nullptr, 1);
    }
}

void HybridFMApplication::listSessions()
{
    const QString dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QLatin1Char('/') + "sessions/";
    QDirIterator it(dir, QDir::Readable | QDir::NoDotAndDotDot | QDir::Dirs);
    QTextStream ts(stdout, QIODevice::WriteOnly);
    while (it.hasNext()) {
        QFileInfo fileInfo(it.next());
        ts << fileInfo.baseName();
    }
}

int HybridFMApplication::openSession(const QString& session)
{
    QString sessionPath = session;
    if (!session.startsWith('/')) {
        sessionPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + QLatin1Char('/') + "sessions/" + session;
    }

    QDirIterator it(sessionPath, QDir::Readable | QDir::Files);
    if (!it.hasNext()) {
        qCWarning(KONQUEROR_LOG) << "session" << session << "not found or empty";
        return 1;
    }

    KonqSessionManager::self()->restoreSessions(sessionPath);

    QList<KonqMainWindow*> *mainWindows = KonqMainWindow::mainWindowList();
    return (mainWindows && !mainWindows->isEmpty()) ? 0 : 1;
}

void HybridFMApplication::restoreSession()
{
    KonqSessionManager::self()->restoreSessionSavedAtLogout();
}
