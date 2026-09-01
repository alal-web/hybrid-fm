#ifndef WEBENGNINE_FILTER_H
#define WEBENGNINE_FILTER_H

#include <QString>
#include <QRegExp>
#include <QVector>
#include <webenginepart.h>

class StringsMatcher;

namespace KDEPrivate
{
// This represents a set of filters that may match URLs.
// Currently it supports a subset of AddBlock Plus functionality.
class FilterSet {
public:
    FilterSet();
    ~FilterSet();

    // Parses and registers a filter. This will also strip @@ for exclusion rules, skip comments, etc.
    // The user does have to split black and white lists into separate sets, however
    void addFilter(const QString& filter);

    bool isUrlMatched(const QString& url);
    QString urlMatchedBy(const QString& url);

    void clear();

private:
    QVector<QRegExp> reFilters;
    StringsMatcher* stringFiltersMatcher;
};

}

#endif // WEBENGINE_FILTER_H

// kate: indent-width 4; replace-tabs on; tab-width 4; space-indent on;
