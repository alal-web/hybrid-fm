#ifndef KCM_BOOKMARKS_H
#define KCM_BOOKMARKS_H

// KDE
#include <kcmodule.h>

// Local
#include "ui_bookmarks.h"

class BookmarksConfigModule : public KCModule
{
    Q_OBJECT

public:
    BookmarksConfigModule(QWidget *parent, const QVariantList &args);
    ~BookmarksConfigModule() override;

    void load() override;
    void save() override;
    void defaults() override;
    QString quickHelp() const override;

private Q_SLOTS:
    void clearCache();
    void configChanged();

private:
    Ui::BookmarksConfigUI ui;
};

#endif // KCM_BOOKMARKS_H

