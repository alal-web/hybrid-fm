#ifndef KONQ_HISTORY_H
#define KONQ_HISTORY_H

#include <QtGlobal>

namespace KonqHistory
{

enum ExtraData {
    TypeRole = Qt::UserRole + 0xaaff00,
    DetailedToolTipRole,
    UrlRole,
    LastVisitedRole
};

enum EntryType {
    HistoryType = 1,
    GroupType = 2
};

}

#endif // KONQ_HISTORY_H
