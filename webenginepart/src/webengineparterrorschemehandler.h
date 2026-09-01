#ifndef WEBENGINEPARTERRORSCHEMEHANDLER_H
#define WEBENGINEPARTERRORSCHEMEHANDLER_H

#include <QWebEngineUrlSchemeHandler>
#include <QUrl>
#include <QString>

class QBuffer;

class WebEnginePartErrorSchemeHandler : public QWebEngineUrlSchemeHandler{
    
    Q_OBJECT
    
public:
    
    WebEnginePartErrorSchemeHandler(QObject *parent = nullptr);
    
    ~WebEnginePartErrorSchemeHandler() override {}
    
    void requestStarted(QWebEngineUrlRequestJob * job) override;
    
private:
    
    struct ErrorInfo{
        int code;
        QString text;
        QUrl requestUrl;
    };
    
    ErrorInfo parseErrorUrl(const QUrl& url);
    
    void writeErrorPage(QBuffer *buf, const ErrorInfo &info);
    
    QString readWarningIconData() const;
    
    const QString m_warningIconData;
};

#endif //WEBENGINEPARTERRORSCHEMEHANDLER_H
