#ifndef KONQMOUSEEVENTFILTER_H
#define KONQMOUSEEVENTFILTER_H

#include <QObject>

class KonqMouseEventFilter : public QObject
{
    Q_OBJECT

public:
    static KonqMouseEventFilter *self();

    void reparseConfiguration();

protected:
    bool eventFilter(QObject *obj, QEvent *e) override;

private:
    explicit KonqMouseEventFilter();
    friend class KonqMouseEventFilterSingleton;

    bool m_bBackRightClick;
};

#endif /* KONQMOUSEEVENTFILTER_H */

