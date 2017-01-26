/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */
#ifndef DIVISACTIONWIDGET_H
#define DIVISACTIONWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QStyleOption>

class DivisactionWidget : public QWidget
{
    Q_PROPERTY(QString class READ cssClass)
public:
    explicit DivisactionWidget(QWidget *parent = 0);
    virtual ~DivisactionWidget() { }

    virtual QString cssClass();

    void paintEvent(QPaintEvent *) override;
};

#endif // DIVISACTIONWIDGET_H
