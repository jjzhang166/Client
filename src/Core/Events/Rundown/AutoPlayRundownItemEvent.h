#pragma once

#include "../../Shared.h"

#include <QtCore/QEvent>
#include <QtCore/QSharedPointer>

#include <QtGui/QWidget>

class CORE_EXPORT AutoPlayRundownItemEvent : public QEvent
{
    public:
        explicit AutoPlayRundownItemEvent(QWidget* widget);

        QWidget* getSource() const;

    private:
        QWidget* widget;
};
