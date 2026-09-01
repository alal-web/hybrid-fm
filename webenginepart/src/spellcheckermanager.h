#ifndef SPELLCHECKERMANAGER_H
#define SPELLCHECKERMANAGER_H

#include <QObject>
#include <QMap>
#include <QDateTime>

#include <Sonnet/Speller>

class QMenu;
class KActionCollection;
class QWidget;
class WebEnginePage;
class QWebEngineProfile;

class SpellCheckerManager : public QObject
{
    Q_OBJECT

public:
    SpellCheckerManager(QWebEngineProfile *profile, QObject *parent=nullptr);
    ~SpellCheckerManager();

    QMenu *spellCheckingMenu(const QStringList &suggestions, KActionCollection *coll, WebEnginePage *page);

public slots:
    void updateConfiguration(bool spellCheckingEnabled);

private:
    void removeLanguage(const QString &lang);
    void addLanguage(const QString &lang);
    void detectDictionaries();
    static QString dictionaryDir();

private slots:
    void spellCheckingToggled(bool on);

private:
    QString m_dictionaryDir;
    QMap<QString, QString> m_dicts;
    QStringList m_enabledDicts;
    Sonnet::Speller m_speller;
    QWebEngineProfile *m_profile;
};

#endif // SPELLCHECKERMANAGER_H
