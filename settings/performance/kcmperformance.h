#ifndef _KCM_PERFORMANCE_H
#define _KCM_PERFORMANCE_H

#include <kcmodule.h>

namespace KCMPerformance
{

class HybridFM;
class SystemWidget;

class Config
    : public KCModule
{
    Q_OBJECT
public:
    Config(QWidget *parent_P, const QVariantList &args);
    void load() override;
    void save() override;
    void defaults() override;
private:
    HybridFM *hybridfm_widget;
    SystemWidget *system_widget;
};

class HybridFMConfig
    : public KCModule
{
    Q_OBJECT
public:
    HybridFMConfig(QWidget *parent_P, const QVariantList &args);
    void load() override;
    void save() override;
    void defaults() override;
private:
    HybridFM *widget;
};

} // namespace

#endif
