#ifndef WEBENGINEURLREQUESTINTERCEPTOR
#define WEBENGINEURLREQUESTINTERCEPTOR

#include <QWebEngineUrlRequestInfo>
#include <QWebEngineUrlRequestInterceptor>

class WebEngineUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor
{
public:
    WebEngineUrlRequestInterceptor(QObject* parent = nullptr);
    void interceptRequest(QWebEngineUrlRequestInfo &info) override;
};

#endif // WEBENGINEURLREQUESTINTERCEPTOR
