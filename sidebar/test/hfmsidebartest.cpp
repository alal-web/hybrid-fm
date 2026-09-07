#include "hfmsidebartest.h"

extern "C"
{
    Q_DECL_EXPORT void *create_konq_sidebartest(QWidget *parent, const QString &desktopname, const KConfigGroup &configGroup)
    {
        return new SidebarTest(parent, desktopname, configGroup);
    }
}
