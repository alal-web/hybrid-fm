#include "settings/webenginesettings.h"
#include "webengineurlrequestinterceptor.h"

WebEngineUrlRequestInterceptor::WebEngineUrlRequestInterceptor(QObject* parent) :
    QWebEngineUrlRequestInterceptor(parent)
{
}

void WebEngineUrlRequestInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    if (info.resourceType() == QWebEngineUrlRequestInfo::ResourceTypeImage) {
        info.block(WebEngineSettings::self()->isAdFiltered(info.requestUrl().url()));
    }
}
