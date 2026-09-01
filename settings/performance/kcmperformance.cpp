// Own
#include "kcmperformance.h"

// Qt
#include <QTabWidget>

// KDE
#include <KLocalizedString>
// Local
#include "hybridfm.h"
#include "system.h"
#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON(KCMPerformanceConfigFactory, "kcmperformance.json", registerPlugin<KCMPerformance::HybridFMConfig>();)

namespace KCMPerformance
{

Config::Config(QWidget *parent_P, const QVariantList &)
    : KCModule(parent_P)
{
    setQuickHelp(i18n("<h1>KDE Performance</h1>"
                      " You can configure settings that improve KDE performance here."));

    QVBoxLayout *topLayout = new QVBoxLayout(this);
    QTabWidget *tabs = new QTabWidget(this);
    hybridfm_widget = new HybridFM;
    connect(hybridfm_widget, &HybridFM::changed, this, &Config::markAsChanged);
    tabs->addTab(hybridfm_widget, i18n("HybridFM"));
    system_widget = new SystemWidget;
    connect(system_widget, &SystemWidget::changed, this, &Config::markAsChanged);
    tabs->addTab(system_widget, i18n("System"));
    topLayout->addWidget(tabs);
}

void Config::load()
{
    hybridfm_widget->load();
    system_widget->load();
}

void Config::save()
{
    hybridfm_widget->save();
    system_widget->save();
}

void Config::defaults()
{
    hybridfm_widget->defaults();
    system_widget->defaults();
}

HybridFMConfig::HybridFMConfig(QWidget *parent_P, const QVariantList &)
    : KCModule(parent_P)
{
    setQuickHelp(i18n("<h1>HybridFM Performance</h1>"
                      " You can configure several settings that improve HybridFM performance here."
                      " These include options for reusing already running instances"
                      " and for keeping instances preloaded."));

    QVBoxLayout *topLayout = new QVBoxLayout(this);
    topLayout->setContentsMargins(0, 0, 0, 0);
    widget = new HybridFM(this);
    connect(widget, &HybridFM::changed, this, &HybridFMConfig::markAsChanged);
    topLayout->addWidget(widget);
}

void HybridFMConfig::load()
{
    widget->load();
}

void HybridFMConfig::save()
{
    widget->save();
}

void HybridFMConfig::defaults()
{
    widget->defaults();
}

} // namespace

#include "kcmperformance.moc"
