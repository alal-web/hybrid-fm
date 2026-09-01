#include "webhistoryinterface.h"

#include <KParts/HistoryProvider>


WebHistoryInterface::WebHistoryInterface(QObject* parent)
{
}

void WebHistoryInterface::addHistoryEntry(const QString& url)
{
    KParts::HistoryProvider::self()->insert(url);
}

bool WebHistoryInterface::historyContains(const QString& url) const
{
    return KParts::HistoryProvider::self()->contains(url);
}
