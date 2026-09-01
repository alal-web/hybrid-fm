#ifndef PLUGIN_WEBARCHIVER_H
#define PLUGIN_WEBARCHIVER_H

#include <hfm_kpart_plugin.h>

class PluginWebArchiver : public KonqParts::Plugin
{
    Q_OBJECT

public:
    PluginWebArchiver(QObject *parent, const QVariantList &args);
    ~PluginWebArchiver() override = default;

protected slots:
    void slotSaveToArchive();
};

#endif
