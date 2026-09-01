#ifndef _AKREGATORPLUGIN_H_
#define _AKREGATORPLUGIN_H_

#include <kabstractfileitemactionplugin.h>

class KFileItem;
class KFileItemListProperties;

namespace Akregator
{

class AkregatorMenu : public KAbstractFileItemActionPlugin
{
    Q_OBJECT

public:
    AkregatorMenu(QObject *parent, const QVariantList &args);
    ~AkregatorMenu() override = default;

    QList<QAction *> actions(const KFileItemListProperties &fileItemInfos, QWidget *parent) override;

public slots:
    void slotAddFeed();

private:
    bool isFeedUrl(const KFileItem &item) const;

private:
    QStringList m_feedMimeTypes;
};

}

#endif
