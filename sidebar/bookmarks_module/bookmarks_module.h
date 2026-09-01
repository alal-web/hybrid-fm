#ifndef BOOKMARKS_MODULE_H
#define BOOKMARKS_MODULE_H

#include <hfmsidebarplugin.h>
class QTreeView;
class QStandardItemModel;
class QItemSelection;

class KonqSideBarBookmarksModule : public KonqSidebarModule
{
    Q_OBJECT

public:
    KonqSideBarBookmarksModule(QWidget *parent,
                            const KConfigGroup &configGroup);
    ~KonqSideBarBookmarksModule() override;

    QWidget *getWidget() override;
    void handleURL(const QUrl &hand_url) override;
	
private slots:
    void slotSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void customEvent(QEvent *ev) override;

private:
    QTreeView *treeView;
    QStandardItemModel *model;
    QUrl m_lastURL;
    QUrl m_initURL;
};

#endif
