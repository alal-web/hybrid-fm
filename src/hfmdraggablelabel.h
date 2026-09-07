#ifndef KONQDRAGGABLELABEL_H
#define KONQDRAGGABLELABEL_H

#include <QUrl>
#include <QLabel>
class KonqMainWindow;

class KonqDraggableLabel : public QLabel
{
    Q_OBJECT
public:
    KonqDraggableLabel(KonqMainWindow *mw, const QString &text);

protected:
    void mousePressEvent(QMouseEvent *ev) override;
    void mouseMoveEvent(QMouseEvent *ev) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void dragEnterEvent(QDragEnterEvent *ev) override;
    void dropEvent(QDropEvent *ev) override;

private Q_SLOTS:
    void delayedOpenURL();

private:
    QPoint startDragPos;
    bool validDrag;
    KonqMainWindow *m_mw;
    QList<QUrl> _savedLst;
};
#endif
