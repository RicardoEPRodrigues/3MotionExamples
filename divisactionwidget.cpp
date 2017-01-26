/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */
#include "divisactionwidget.h"

DivisactionWidget::DivisactionWidget(QWidget *parent) : QWidget(parent)
{

}


void DivisactionWidget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

QString DivisactionWidget::cssClass() {
    return QString(this->metaObject()->className());
}
