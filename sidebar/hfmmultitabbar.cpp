#include "hfmmultitabbar.h"
#include <QDragEnterEvent>
#include <QMimeData>

#include <KUrlMimeData>

KonqMultiTabBar::KonqMultiTabBar(QWidget *parent)
    : KMultiTabBar(KMultiTabBar::Left, parent)
{
    setAcceptDrops(true);
}

void KonqMultiTabBar::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->accept();
    }
}

void KonqMultiTabBar::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->accept();
    }
}

void KonqMultiTabBar::dropEvent(QDropEvent *event)
{
    const QList<QUrl> urls = KUrlMimeData::urlsFromMimeData(event->mimeData());
    emit urlsDropped(urls);
}
