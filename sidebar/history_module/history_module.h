#ifndef HISTORY_MODULE_H
#define HISTORY_MODULE_H

#include <hfmsidebarplugin.h>
#include "hfmhistorysettings.h"

class QModelIndex;
class KonqHistoryView;

class KonqSidebarHistoryModule : public KonqSidebarModule
{
    Q_OBJECT
public:
    KonqSidebarHistoryModule(QWidget *parent, const KConfigGroup &configGroup);
    ~KonqSidebarHistoryModule() override;
    QWidget *getWidget() override;

public Q_SLOTS:
    void slotCurViewUrlChanged(const QUrl& url) override;

private Q_SLOTS:
    void slotActivated(const QModelIndex &index);
    void slotPressed(const QModelIndex &index);
    void slotClicked(const QModelIndex &index);
    void slotOpenWindow(const QUrl &url);
    void slotOpenTab(const QUrl &url);
    void reparseConfiguration();

private:
    KonqHistoryView *m_historyView;
    Qt::MouseButtons m_lastPressedButtons;
    KonqHistorySettings *m_settings;
    KonqHistorySettings::Action m_defaultAction;
    QUrl m_currentUrl;
};

#endif // HISTORY_MODULE_H
