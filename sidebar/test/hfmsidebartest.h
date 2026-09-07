#ifndef _konq_sidebar_test_h_
#define _konq_sidebar_test_h_
#include <hfmsidebarplugin.h>
#include <QLabel>
#include <QUrl>

class SidebarTest : public KonqSidebarModule
{
    Q_OBJECT
public:
    SidebarTest(QWidget *parent, const QString &desktopName, const KConfigGroup &configGroup)
        : KonqSidebarModule(parent, configGroup)
    {
        Q_UNUSED(desktopName);
        widget = new QLabel("Init Value", parent);
    }
    ~SidebarTest() override {}
    QWidget *getWidget() override
    {
        return widget;
    }
protected:
    QLabel *widget;
    void handleURL(const QUrl &url) override
    {
        widget->setText(url.url());
    }
};

#endif
