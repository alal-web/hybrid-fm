#include "hfmapplication.h"
#include "hfmmisc.h"
#include "hfmfactory.h"
#include "hfmmainwindow.h"
#include "hfmmainwindowfactory.h"
#include "hfmsessionmanager.h"
#include "hfmview.h"
#include "hfmsettingsxt.h"
#include "hfmurl.h"
#include "hfmclosedwindowsmanager.h"


#include <config-hybrid-fm.h>

#include "hfmdebug.h"
#include <QFile>
#include <QDir>
#include <QDirIterator>
#include <QStandardPaths>
#include <QProcess>

#include <KDBusService>
#include <KStartupInfo>
#include <KWindowSystem>
#include <kwindowsystem_version.h>

#include <KMessageBox>

extern "C" Q_DECL_EXPORT int kdemain(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts); // says QtWebEngine. Note: this must be set before creating the application
    HybridFMApplication app(argc, argv);
    return app.start();
}
