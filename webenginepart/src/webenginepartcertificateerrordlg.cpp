#include "webenginepartcertificateerrordlg.h"
#include "ui_webenginepartcertificateerrordlg.h"


#include <KSslCertificateBox>

#include <QAbstractButton>
#include <QPushButton>

using namespace KonqWebEnginePart;

WebEnginePartCertificateErrorDlg::WebEnginePartCertificateErrorDlg(const QWebEngineCertificateError &error, WebEnginePage *page, QWidget* parent):
    QDialog(parent),
    m_ui(new Ui::WebEnginePartCertificateErrorDlg), m_error(error), m_choice(UserChoice::DontIgnoreError)
{
    m_ui->setupUi(this);
    connect(m_ui->buttons, &QDialogButtonBox::clicked, this, &WebEnginePartCertificateErrorDlg::updateUserChoice);
    connect(m_ui->showDetails, &QCheckBox::toggled, m_ui->details, &QWidget::setVisible);
    connect(m_ui->certificateChain, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &WebEnginePartCertificateErrorDlg::displayCertificate);

    m_ui->buttons->button(QDialogButtonBox::No)->setDefault(true);
    m_ui->buttons->button(QDialogButtonBox::Yes)->setText(i18nc("Ignore the certificate error for this URL only for now", "Yes, &once"));
    m_ui->buttons->button(QDialogButtonBox::YesToAll)->setText(i18nc("Ignore the certificate error for this URL now and in the future", "Yes, &forever"));
    m_ui->details->hide();

    QString translatedDesc = i18n(m_error.errorDescription().toUtf8());
    QString text = i18n("<p>The server <tt>%1</tt> failed the authenticity check. The error is:</p><p><tt>%2</tt></p>Do you want to ignore this error?",
                        m_error.url().host(), translatedDesc);
    m_ui->label->setText(text);
    for (const QSslCertificate &cert : m_error.certificateChain()) {
        m_ui->certificateChain->addItem(cert.subjectDisplayName());
    }
    setWindowTitle(i18nc("title of a dialog asking what to do about a SSL certificate error", "Certificate error"));
}

WebEnginePartCertificateErrorDlg::~WebEnginePartCertificateErrorDlg()
{
}

QWebEngineCertificateError WebEnginePartCertificateErrorDlg::certificateError() const
{
    return m_error;
}

WebEnginePartCertificateErrorDlg::UserChoice WebEnginePartCertificateErrorDlg::userChoice() const
{
    return m_choice;
}

void WebEnginePartCertificateErrorDlg::displayCertificate(int idx)
{
    m_ui->subjectData->setCertificate(m_error.certificateChain().at(idx), KSslCertificateBox::Subject);;
    m_ui->issuerData->setCertificate(m_error.certificateChain().at(idx), KSslCertificateBox::Issuer);;
}

void WebEnginePartCertificateErrorDlg::updateUserChoice(QAbstractButton* btn)
{
    QDialogButtonBox::StandardButton code = m_ui->buttons->standardButton(btn);
    switch (code) {
        case QDialogButtonBox::Yes:
            m_choice = UserChoice::IgnoreErrorOnce;
            break;
        case QDialogButtonBox::YesToAll:
            m_choice = UserChoice::IgnoreErrorForever;
            break;
        default:
            m_choice = UserChoice::DontIgnoreError;
    }
}
