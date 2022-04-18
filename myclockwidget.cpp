#include "myclockwidget.h"
#include <QTimer>
#include <QDebug>
#include <QtMath>
#include <QDateTimeEdit>
#include "./ui_mainwindow.h"

myClockWidget::myClockWidget(QWidget *parent) : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);

    setWindowTitle("MyAnalogClock");
    resize(500, 500);
}

void myClockWidget::paintEvent(QPaintEvent*){

    QPainter painter(this);
    pen = painter.pen();

    painter.translate(width()/2, height()/2);

    drawClockFace(&painter);

    QDateTime datetime = QDateTime::currentDateTime();
            setDate(&painter, datetime.date().day(), datetime.date().month());
            QTime time = QTime::currentTime();
            setTime(&painter, time.hour(), time.minute(), time.second());

//    if(current==true){
//        QDateTime datetime = QDateTime::currentDateTime();
    //        setDate(&painter, datetime.date().day(), datetime.date().month());
    //        QTime time = QTime::currentTime();
    //        setTime(&painter, time.hour(), time.minute(), time.second());
//    }
//    if(current==false){
//        QTimeEdit* timeEdit = new QTimeEdit();
//        QTime CTime = timeEdit->time();
//        //QTime timeNow = QTime::currentTime();
//        int offset= QTime::currentTime().msecsTo(CTime)/1000;
//        QTime time= QTime::currentTime().addSecs(offset);
//        setTime(&painter, time.hour(), time.minute(), time.second());

//        QDateEdit* dateEdit = new QDateEdit();
//        QDate CDate = dateEdit->date();
//        setDate(&painter, CDate.day(), CDate.month());
//    }


    /*painter.drawLine(0,0, 0, minuteHand);
    painter.rotate(45);
    painter.drawLine(0,0, 0, minuteHand);*/
}

void myClockWidget::drawClockFace(QPainter* painter){
    pen.setColor(Qt::black);

    //Draw minute lines
    int angle = 360/60;
    pen.setWidth(2);
    painter->setPen(pen);
    painter->save();

    for( auto i = 0; i < 360; i+=angle){
        painter->drawLine(0,-height()/2, 0, (-height() * 95 / 200));
        painter->rotate(angle);
    }
    painter->restore();

    //Draw hour lines
    angle = 360/12;
    pen.setWidth(5);
    //pen.set
    painter->setPen(pen);
    painter->save();

    for( auto i = 0; i < 360; i+=angle){
        if(i % 90 == 0){
            //  Colors quarters red
            //pen.setColor(Qt::darkRed); //QColor("#722f37")
            //painter->setPen(pen);
            painter->drawLine(0,-height()/2, 0, (-height() * 8 / 20));
        }
        else {
            //pen.setColor(Qt::black);
            //painter->setPen(pen);
            painter->drawLine(0,-height()*115/200, 0, (-height() * 8 / 20));
        }
        painter->rotate(angle);
        qDebug() << i % 90;
    }
    painter->restore();

    // Draw the frame around the clock
    painter->drawRect(-height()/2,-height()/2,height(),height());
}

void myClockWidget::setTime(QPainter* painter, int hours, int minutes, int seconds){

    QPoint hourHand[2] = {
        QPoint(0,0),
        QPoint(0, -height() * 50 /200)
    };

    QPoint minuteHand[2] = {
        QPoint(0,0),
        QPoint(0, -height() * 70 / 200)
    };

    QPoint secondHand[2] = {
        QPoint(0,0),
        QPoint(0, -height()/2)
    };

    //Draw hourhand
    painter->save();
    pen.setColor(Qt::black);
    pen.setWidth(5);
    painter->setPen(pen);
    //painter->rotate(6 * minutes);
    painter->rotate(30 * (hours + minutes/60.0));
    painter->drawLine(hourHand[0], hourHand[1]);
    painter->restore();
    //qDebug() << "Hourhand moved to " << hours + minutes/60.0;

    //Draw minuteHand
    painter->save();
    pen.setColor(Qt::black);
    pen.setWidth(4);
    painter->setPen(pen);
    //painter->rotate(6 * minutes);
    painter->rotate(6 * minutes);
    painter->drawLine(minuteHand[0], minuteHand[1]);
    painter->restore();

    //Draw secondhand
    painter->save();
    pen.setColor(Qt::red);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->rotate(6 * seconds);
    painter->drawLine(secondHand[0], secondHand[1]);
    painter->restore();
    //qDebug() << "second hand moved to " << seconds;
}

void myClockWidget::setDate(QPainter *painter, int day, int month)
{
    // Draw the frame for the date and month
    const QRect rectangle(-50, 10, 100, 50);
    painter->drawRect(rectangle);
    QFont font = painter->font();
    font.setPixelSize(40);
    painter->setFont(font);
    QString dateString;
    if (day < 10 && month < 10){
        dateString = QString("0%1.0%2").arg(QString::number(day), QString::number(month));
    }else if(month < 10){
        dateString = QString("%1.0%2").arg(QString::number(day), QString::number(month));
    }else if (day < 10){
        dateString = QString("0%1.%2").arg(QString::number(day), QString::number(month));
    }else{
        dateString = QString("%1.%2").arg(QString::number(day), QString::number(month));
    }

    painter->drawText(rectangle, 0, dateString);
}

