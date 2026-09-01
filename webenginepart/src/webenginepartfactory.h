#ifndef WEBENGINEPARTFACTORY
#define WEBENGINEPARTFACTORY

#include <KPluginFactory>

#include <QHash>

class QWidget;

class WebEngineFactory : public KPluginFactory
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID KPluginFactory_iid FILE "webenginepart.json")
    Q_INTERFACES(KPluginFactory)
public:
    ~WebEngineFactory() override;
    QObject *create(const char* iface, QWidget *parentWidget, QObject *parent, const QVariantList& args, const QString &keyword) override;

private Q_SLOTS:
    void slotDestroyed(QObject* object);
    void slotSaveHistory(QObject* widget, const QByteArray&);

private:
    QHash<QObject*, QByteArray> m_historyBufContainer;
};

#endif // WEBENGINEPARTFACTORY
