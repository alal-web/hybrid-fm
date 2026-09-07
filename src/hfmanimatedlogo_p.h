#ifndef KONQANIMATEDLOGO_P_H
#define KONQANIMATEDLOGO_P_H

#include <KAnimatedButton>

class QToolBar;

class KonqAnimatedLogo : public KAnimatedButton
{
    Q_OBJECT

public:
    /**
     * Creates an animated logo button which follows the toolbar icon size
     */
    KonqAnimatedLogo(QWidget *parent = nullptr);

protected:
    void changeEvent(QEvent *event) override;

private Q_SLOTS:
    void setAnimatedLogoSize(const QSize &);

private:
    void connectToToolBar(QToolBar *);
};

#endif // KONQANIMATEDLOGO_P_H
