#ifndef WEBENGINEPARTCERTIFICATEERRORDLG_H
#define WEBENGINEPARTCERTIFICATEERRORDLG_H

#include "webenginepage.h"

#include <QDialog>
#include <QWebEngineCertificateError>

class QAbstractButton;

namespace Ui
{
class WebEnginePartCertificateErrorDlg;
}

namespace KonqWebEnginePart {

    /**
    * @brief Dialog which asks the user whether to ignore a SSL certificate error or not.
    *
    * The user can choose to ignore the error only once, forever or to not ignore it
    */
    class WebEnginePartCertificateErrorDlg : public QDialog
    {
        Q_OBJECT

    public:

        /**
        * @brief Constructor
        * @param error the certificate error the dialog is about
        * @param parent the parent widget
        */
        WebEnginePartCertificateErrorDlg(const QWebEngineCertificateError& error, WebEnginePage* page, QWidget* parent);

        /**
        * @brief Destructor
        */
        ~WebEnginePartCertificateErrorDlg();

        /**
        * @brief Enum which describes the possible user choices
        */
        enum class UserChoice{DontIgnoreError, IgnoreErrorOnce, IgnoreErrorForever};

        /**
        * @brief The choice made by the user
        * @return the choice made by the user
        * @warning This method should only be called *after* the user closed the dialog
        * using one of the three buttons. In all other situations, the returned value is
        * undefined.
        */
        UserChoice userChoice() const;

        /**
        * @return The certificate error the dialog is about
        */
        QWebEngineCertificateError certificateError() const;

    private slots:
        /**
        * @brief Displays information about a certificate in the certificate chain
        * @param idx the index of the certificate in the certificate chain
        */
        void displayCertificate(int idx);


        /**
        * @brief Sets the variable containing the user's choice when he presses one of the dialog buttons
        *
        * @param btn the button pressed by the user
        */
        void updateUserChoice(QAbstractButton *btn);

    private:

        /**
        * @brief The Ui object
        */
        Ui::WebEnginePartCertificateErrorDlg *m_ui;

        /**
        * @brief The error the dialog is about
        */
        QWebEngineCertificateError m_error;

        /**
        * @brief The choice made by the user
        *
        * @warning The value contained in this variable is undefined until the user closed the dialog
        * using one of the three buttons
        */
        UserChoice m_choice;
    };
}

#endif // WEBENGINEPARTCERTIFICATEERRORDLG_H
