#ifndef WEBENGINEPARTCONTROLS_H
#define WEBENGINEPARTCONTROLS_H

#include <QObject>
#include <QWebEngineCertificateError>

class QWebEngineProfile;
class WebEnginePartCookieJar;
class SpellCheckerManager;
class WebEnginePartDownloadManager;
class WebEnginePage;

namespace KonqWebEnginePart {
    class CertificateErrorDialogManager;
}

class WebEnginePartControls : public QObject
{
    Q_OBJECT

public:

    static WebEnginePartControls *self();

    ~WebEnginePartControls();

    bool isReady() const;

    void setup(QWebEngineProfile *profile);

    SpellCheckerManager* spellCheckerManager() const;

    WebEnginePartDownloadManager* downloadManager() const;

    bool handleCertificateError(const QWebEngineCertificateError &ce, WebEnginePage *page);

private:

    WebEnginePartControls();

    QWebEngineProfile *m_profile;
    WebEnginePartCookieJar *m_cookieJar;
    SpellCheckerManager *m_spellCheckerManager;
    WebEnginePartDownloadManager *m_downloadManager;
    KonqWebEnginePart::CertificateErrorDialogManager *m_certificateErrorDialogManager;
};

#endif // WEBENGINEPARTCONTROLS_H
