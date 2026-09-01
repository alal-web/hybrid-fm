#ifndef PLACES_MODULE_H
#define PLACES_MODULE_H

#include <hfmsidebarplugin.h>

#include <kfileplacesview.h>


class KonqSideBarPlacesModule : public KonqSidebarModule
{
    Q_OBJECT

public:
    KonqSideBarPlacesModule(QWidget *parent,
                            const KConfigGroup &configGroup);
    ~KonqSideBarPlacesModule() override = default;

    QWidget *getWidget() override;

private slots:
    void slotPlaceUrlChanged(const QUrl &url);

private:
    KFilePlacesView *m_placesView;
};

#endif
