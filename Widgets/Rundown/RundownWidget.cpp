#include "RundownWidget.h"
#include "RundownTreeWidget.h"

#include "EventManager.h"

#include <QtGui/QApplication>
#include <QtGui/QIcon>
#include <QtGui/QToolButton>

RundownWidget::RundownWidget(QWidget* parent)
    : QWidget(parent),
      tabCount(1)
{
    setupUi(this);

    setupMenus();

    QToolButton* toolButtonRundownDropdown = new QToolButton(this);
    toolButtonRundownDropdown->setObjectName("toolButtonRundownDropdown");
    toolButtonRundownDropdown->setMenu(this->contextMenuRundownDropdown);
    toolButtonRundownDropdown->setPopupMode(QToolButton::InstantPopup);
    this->tabWidgetRundown->setCornerWidget(toolButtonRundownDropdown);
    this->tabWidgetRundown->setTabIcon(0, QIcon(":/Graphics/Images/TabSplitter.png"));

    if (this->tabWidgetRundown->count() == 0)
        EventManager::getInstance().fireNewRundownEvent();

    qApp->installEventFilter(this);
}

void RundownWidget::setupMenus()
{
    this->contextMenuRundownDropdown = new QMenu(this);
    this->contextMenuRundownDropdown->setTitle("Rundown Dropdown");
    this->contextMenuRundownDropdown->addAction(/*QIcon(":/Graphics/Images/NewRundown.png"),*/ "Add rundown", this, SLOT(addNewRundown()));
}

bool RundownWidget::eventFilter(QObject* target, QEvent* event)
{
    if (event->type() == static_cast<QEvent::Type>(Enum::EventType::NewRundown))
    {
        RundownTreeWidget* widget = new RundownTreeWidget(this);
        widget->setActive(true);

        int index = this->tabWidgetRundown->addTab(widget, QIcon(":/Graphics/Images/TabSplitter.png"), QString("Rundown %1").arg(this->tabCount++));
        this->tabWidgetRundown->setCurrentIndex(index);

        return true;
    }

    return QObject::eventFilter(target, event);
}

void RundownWidget::addNewRundown()
{
    EventManager::getInstance().fireNewRundownEvent();
}

void RundownWidget::tabCloseRequested(int index)
{
    if (this->tabWidgetRundown->count() > 1)
        this->tabWidgetRundown->removeTab(index);
}

void RundownWidget::currentChanged(int index)
{
    for (int i = 0; i < this->tabWidgetRundown->count(); i++)
        dynamic_cast<RundownTreeWidget*>(this->tabWidgetRundown->widget(i))->setActive(false);

    dynamic_cast<RundownTreeWidget*>(this->tabWidgetRundown->widget(index))->setActive(true);
}
