#ifndef KONQEXTENSIONMANAGER_H
#define KONQEXTENSIONMANAGER_H

#include <QDialog>

class KonqExtensionManagerPrivate;
class KonqMainWindow;
namespace KParts
{
class ReadOnlyPart;
}

/**
 * Extension Manager for HybridFM. See KPluginSelector in kdelibs for
 * documentation.
 *
 * @author Martijn Klingens <klingens@kde.org>
 * @author Arend van Beelen jr. <arend@auton.nl>
 */
class KonqExtensionManager
    : public QDialog
{
    Q_OBJECT

public:
    KonqExtensionManager(QWidget *parent, KonqMainWindow *mainWindow, KParts::ReadOnlyPart *activePart);
    ~KonqExtensionManager() override;

    void apply();

public Q_SLOTS:
    void setChanged(bool c);
    void reparseConfiguration(const QByteArray &);
    void slotOk();
    void slotApply();
    void slotDefault();

protected:
    void showEvent(QShowEvent *event) override;

private:
    KonqExtensionManagerPrivate *d;
};

#endif // KONQEXTENSIONMANAGER_H
