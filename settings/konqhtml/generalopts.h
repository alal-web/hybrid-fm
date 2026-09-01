#ifndef GENERALOPTS_H
#define GENERALOPTS_H

#include <QCheckBox>

#include <kcmodule.h>
#include <ksharedconfig.h>

class QComboBox;
class QLineEdit;
class Ui_advancedTabOptions;
class QVBoxLayout;
class KMessageWidget;

class KKonqGeneralOptions : public KCModule
{
    Q_OBJECT

public:
    KKonqGeneralOptions(QWidget *parent, const QVariantList &);
    ~KKonqGeneralOptions() override;
    void load() override;
    void save() override;
    void defaults() override;

private Q_SLOTS:
    void slotChanged();
    void displayEmpytStartPageWarningIfNeeded();

private:
    void addHomeUrlWidgets(QVBoxLayout *);

    KSharedConfig::Ptr m_pConfig;

    QComboBox *m_startCombo;
    QLineEdit *homeURL;
    QLineEdit *startURL;
    QComboBox *m_webEngineCombo;
    QComboBox *m_splitBehaviour;
    KMessageWidget *m_emptyStartUrlWarning;

    Ui_advancedTabOptions *tabOptions;
};

#endif // GENERALOPTS_H
