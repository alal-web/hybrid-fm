#ifndef kshellcmdplugin_h
#define kshellcmdplugin_h

#include <hfm_kpart_plugin.h>

class KShellCmdPlugin : public KonqParts::Plugin
{
    Q_OBJECT
public:
    KShellCmdPlugin(QObject *parent, const QVariantList &);
    ~KShellCmdPlugin() override {}

public Q_SLOTS:
    void slotExecuteShellCommand();
};

#endif
