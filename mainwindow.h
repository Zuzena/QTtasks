#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "myclockwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
   void customDateTime();
   void reset();

private:
    Ui::MainWindow *ui;
    myClockWidget myClock;
};

#endif // MAINWINDOW_H
