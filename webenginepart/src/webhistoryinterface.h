#ifndef WEBHISTORYINTERFACE_H
#define WEBHISTORYINTERFACE_H

#include <QObject>


class WebHistoryInterface
{
public:
    WebHistoryInterface(QObject* parent = nullptr);
    void addHistoryEntry (const QString & url);
    bool historyContains (const QString & url) const;
};

#endif //WEBHISTORYINTERFACE_H
