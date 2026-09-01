#include "centralwidget.h"

#include <QApplication>
#include <QLabel>
#include <QTimer>

SCWMainWindow::SCWMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QLabel *widget1 = new QLabel(QStringLiteral("widget1"));
    setCentralWidget(widget1);
    QTimer::singleShot(10, this, SLOT(slotSwitchCentralWidget()));
}

void SCWMainWindow::slotSwitchCentralWidget()
{
    QLabel *widget2 = new QLabel(QStringLiteral("widget2"));
    delete centralWidget(); // ## workaround for the crash
    setCentralWidget(widget2);
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    SCWMainWindow *mw = new SCWMainWindow;
    mw->show();

    return app.exec();
}

