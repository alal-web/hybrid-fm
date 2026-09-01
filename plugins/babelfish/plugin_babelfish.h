#ifndef __plugin_babelfish_h
#define __plugin_babelfish_h

#include <hfm_kpart_plugin.h>
#include <kactionmenu.h>
#include <QActionGroup>

class PluginBabelFish : public KonqParts::Plugin
{
    Q_OBJECT
public:
    explicit PluginBabelFish(QObject *parent,
                             const QVariantList &);
    ~PluginBabelFish() override;

private slots:
    void translateURL(QAction *);
    void slotAboutToShow();
    void slotEnableMenu();

private:
    void addTopLevelAction(const QString &name, const QString &text);

private:
    QActionGroup m_actionGroup;
    KActionMenu *m_menu;
};

#endif
