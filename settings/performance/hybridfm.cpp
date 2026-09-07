#include "hybridfm.h"

#include <kconfig.h>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QCheckBox>
#include <KLocalizedString>
#include <KConfigGroup>

namespace KCMPerformance
{

HybridFM::HybridFM(QWidget *parent_P)
    : HybridFM_ui(parent_P)
{
    cb_preload_on_startup->setToolTip(
        i18n("<p>If enabled, an instance of HybridFM will be preloaded after the ordinary Plasma "
             "startup sequence.</p>"
             "<p>This will make the first HybridFM window open faster, but "
             "at the expense of longer Plasma startup times (but you will be able to work "
             "while it is loading, so you may not even notice that it is taking longer).</p>"));
    cb_always_have_preloaded->setToolTip(
        i18n("<p>If enabled, HybridFM will always try to have one preloaded instance ready; "
             "preloading a new instance in the background whenever there is not one available, "
             "so that windows will always open quickly.</p>"
             "<p><b>Warning:</b> In some cases, it is actually possible that this will "
             "reduce perceived performance.</p>"));
    connect(cb_preload_on_startup, &QAbstractButton::toggled, this, &HybridFM::changed);
    connect(cb_always_have_preloaded, &QAbstractButton::toggled, this, &HybridFM::changed);
    defaults();
}

void HybridFM::load()
{
    KConfig _cfg(QStringLiteral("hybrid-fmrc"));
    KConfigGroup cfg(&_cfg, "Reusing");
    cb_preload_on_startup->setChecked(cfg.readEntry("PreloadOnStartup", false));
    cb_always_have_preloaded->setChecked(cfg.readEntry("AlwaysHavePreloaded", true));
}

void HybridFM::save()
{
    KConfig _cfg(QStringLiteral("hybrid-fmrc"));
    KConfigGroup cfg(&_cfg, "Reusing");
    cfg.writeEntry("PreloadOnStartup", cb_preload_on_startup->isChecked());
    cfg.writeEntry("AlwaysHavePreloaded", cb_always_have_preloaded->isChecked());
    cfg.sync();
    QDBusMessage message =
        QDBusMessage::createSignal(QStringLiteral("/KonqMain"), QStringLiteral("org.kde.Konqueror.Main"), QStringLiteral("reparseConfiguration"));
    QDBusConnection::sessionBus().send(message);
}

void HybridFM::defaults()
{
    cb_preload_on_startup->setChecked(false);
    cb_always_have_preloaded->setChecked(true);
}

} // namespace
