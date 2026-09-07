#ifndef _KCM_PERF_HYBRIDFM_H
#define _KCM_PERF_HYBRIDFM_H

#include "ui_hybridfm_ui.h"

namespace KCMPerformance
{

class HybridFM_ui : public QWidget, public Ui::HybridFM_ui
{
public:
    HybridFM_ui(QWidget *parent) : QWidget(parent)
    {
        setupUi(this);
        layout()->setContentsMargins(0, 0, 0, 0);
    }
};

class HybridFM
    : public HybridFM_ui
{
    Q_OBJECT
public:
    HybridFM(QWidget *parent_P = nullptr);
    void load();
    void save();
    void defaults();
Q_SIGNALS:
    void changed();
};

}  // namespace

#endif
