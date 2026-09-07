#ifndef KONQ_HISTORYDIALOG_H
#define KONQ_HISTORYDIALOG_H

#include <QDialog>

#include "hfmhistorysettings.h"

class KonqMainWindow;
class KonqHistoryView;
class QModelIndex;
class QUrl;

class KonqHistoryDialog : public QDialog
{
    Q_OBJECT

public:
    KonqHistoryDialog(KonqMainWindow *parent = nullptr);
    ~KonqHistoryDialog() override;

    QSize sizeHint() const override;

private Q_SLOTS:
    void slotOpenWindow(const QUrl &url);
    void slotOpenTab(const QUrl &url);
    void slotOpenCurrentTab(const QUrl &url);
    void slotOpenCurrentOrNewTab(const QUrl &url);
    void slotOpenIndex(const QModelIndex &index);
    void reparseConfiguration();

private:

    KonqHistoryView *m_historyView;
    KonqMainWindow *m_mainWindow;

    KonqHistorySettings *m_settings;
    KonqHistorySettings::Action m_defaultAction;
};

#endif // KONQ_HISTORYDIALOG_H
