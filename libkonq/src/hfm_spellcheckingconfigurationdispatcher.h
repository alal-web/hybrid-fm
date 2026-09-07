#ifndef KONQ_SPELLCHECKINGCONFIGURATIONDISPATCHER_H
#define KONQ_SPELLCHECKINGCONFIGURATIONDISPATCHER_H

#include <QObject>

#include <libkonq_export.h>

class LIBKONQ_EXPORT KonqSpellCheckingConfigurationDispatcher : public QObject
{
    Q_OBJECT

public:
    static KonqSpellCheckingConfigurationDispatcher* self();

signals:
    void spellCheckingConfigurationChanged(bool enabled);

};

#endif // KONQ_SPELLCHECKINGCONFIGURATIONDISPATCHER_H
