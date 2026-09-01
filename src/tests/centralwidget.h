#ifndef CENTRALWIDGET_H
#define CENTRALWIDGET_H

#include <QMainWindow>

// SCW == Switch (or Set) Central Widget
class SCWMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    SCWMainWindow(QWidget *parent = nullptr);

private slots:
    void slotSwitchCentralWidget();
};

#endif
