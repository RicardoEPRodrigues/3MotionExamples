/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */
#ifndef HELPER_H
#define HELPER_H

#include <QWidget>
#include <QStyle>
#include <QLayout>

class QtHelper
{
private:
    QtHelper();
public:
    static void setProperty(QWidget* object, const char* name, const QVariant & value);
    static void clearLayout(QLayout* layout);
};

#endif // HELPER_H
