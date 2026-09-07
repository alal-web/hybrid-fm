#ifndef KONQMULTITABBAR_H
#define KONQMULTITABBAR_H

#include <QUrl>
#include <kmultitabbar.h>

class KonqMultiTabBar : public KMultiTabBar
{
    Q_OBJECT

public:
    explicit KonqMultiTabBar(QWidget *parent);

Q_SIGNALS:
    void urlsDropped(const QList<QUrl> &urls);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};

#endif /* KONQMULTITABBAR_H */

