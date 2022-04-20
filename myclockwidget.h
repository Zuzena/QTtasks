#ifndef MYCLOCKWIDGET_H
#define MYCLOCKWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QDebug>
class myClockWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myClockWidget(QWidget *parent = nullptr);

    void drawClockFace(QPainter*);
    void setTime(QPainter*, int, int, int);
    void setDate(QPainter*, int, int);
    void drawHand(QPainter*, int);
    void toggleMode(bool isTimeCurrent){current=isTimeCurrent; qDebug()<<current;}

    bool current=true;
signals:

public slots:
    void paintEvent(QPaintEvent*);


private:
    QPen pen;

};

#endif // MYCLOCKWIDGET_H
