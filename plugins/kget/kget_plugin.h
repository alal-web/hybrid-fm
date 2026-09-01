#ifndef KGETPLUGIN_H
#define KGETPLUGIN_H

#include <hfm_kpart_plugin.h>
#include <QPointer>

class KToggleAction;

class KGetPlugin : public KonqParts::Plugin
{
    Q_OBJECT
public:
    KGetPlugin(QObject *parent, const QVariantList &);
    ~KGetPlugin() override;

private Q_SLOTS:
    void slotShowDrop();
    void slotShowLinks();
    void slotShowSelectedLinks();
    void slotImportLinks();
    void showPopup();

private:
    void getLinks(bool selectedOnly = false);

    QStringList m_linkList;
    KToggleAction *m_dropTargetAction;
};

#endif
