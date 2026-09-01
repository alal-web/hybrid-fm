#ifndef CREDENTIALSDETAILSWIDGET_H
#define CREDENTIALSDETAILSWIDGET_H

#include <QWidget>
#include <QScopedPointer>

#include "ui_credentialsdetailswidget.h"
#include "webenginewallet.h"

class WebFieldsDataModel;

class CredentialsDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    CredentialsDetailsWidget(QWidget* parent);
    ~CredentialsDetailsWidget() override;

    void setForms(const WebEngineWallet::WebFormList &forms);
    void clear();

private:
    QScopedPointer<Ui::CredentialsDetailsWidget> m_ui;
    WebFieldsDataModel *m_model;
};

#endif // CREDENTIALSDETAILSWIDGET_H
