#ifndef KSHELLCMDDIALOG_H
#define KSHELLCMDDIALOG_H

#include <qdialog.h>

class KShellCommandExecutor;
class QPushButton;

class KShellCommandDialog: public QDialog
{
    Q_OBJECT
public:
    KShellCommandDialog(const QString &title, const QString &command, QWidget *parent = nullptr, bool modal = false);
    ~KShellCommandDialog() override;
    //blocking
    int executeCommand();
protected:

    KShellCommandExecutor *m_shell;
    QPushButton *cancelButton;
    QPushButton *closeButton;
protected Q_SLOTS:
    void disableStopButton();
    void slotClose();
};

#endif // KSHELLCMDDIALOG_H
