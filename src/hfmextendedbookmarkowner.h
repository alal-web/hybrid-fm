#ifndef KONQEXTENDEDBOOKMARKOWNER_H
#define KONQEXTENDEDBOOKMARKOWNER_H

#include <hfmbookmarkmenu.h>
#include <kbookmarkowner.h>

class KonqExtendedBookmarkOwner : public KBookmarkOwner
{
public:
    KonqExtendedBookmarkOwner(KonqMainWindow *);
    QString currentTitle() const override;
    QUrl currentUrl() const override;
    bool supportsTabs() const override;
    QList<FutureBookmark> currentBookmarkList() const override;
    void openBookmark(const KBookmark &bm, Qt::MouseButtons mb, Qt::KeyboardModifiers km) override;
    void openInNewTab(const KBookmark &bm) override;
    void openInNewWindow(const KBookmark &bm) override;
    void openFolderinTabs(const KBookmarkGroup &grp) override;

private:
    KonqMainWindow *m_pKonqMainWindow;
};

#endif
