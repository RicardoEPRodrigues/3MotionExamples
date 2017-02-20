/*
 * Copyright (C) ricardo 2016 - All Rights Reserved
 */
#include "qthelper.h"

void QtHelper::setProperty(QWidget* object, const char* name, const QVariant & value) {
    object->setProperty(name, value);
    object->style()->unpolish(object);
    object->style()->polish(object);
}

void QtHelper::clearLayout(QLayout *layout) {
    if ( layout->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = layout->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
    }
}
