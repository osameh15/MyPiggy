#include "StackedWindowPlugin.h"
#include "PluginManager.h"
#include "StackedWindow.h"
//#include "CoreService.h"
#include "Definitions.h"

#include <iostream>
#include <QTimer>

namespace Eagle
{
StackedWindowPlugin::StackedWindowPlugin()
{
    m_stackWindow = new Widgets::StackedWindow;
}

StackedWindowPlugin::~StackedWindowPlugin()
{
}

bool  StackedWindowPlugin::init(const PluginManager *manager)
{
    bool  res = false;

    if (nullptr != manager)
    {
        std::cout << "StackedWindow plugin load !" << std::endl;

        setStackedWidgetIndex(Stacked::StackedWidgets::Login);

//        Core::CoreService::instance()->setWindow(this);

        connect(manager, SIGNAL(done()), this, SLOT(showMainWindow()));

        res = true;
    }

    return res;
}

void  StackedWindowPlugin::showMainWindow()
{
    QTimer::singleShot(2500, this, [&]()
        {
            m_stackWindow->showMaximized();
        });
}

QMainWindow * StackedWindowPlugin::stackedWindow()
{
    return m_stackWindow;
}

void  StackedWindowPlugin::registerWidget(QWidget *widget, Stacked::StackedWidgets widgetType)
{
    m_stackWindow->addStackedWidget(widget);
}

void  StackedWindowPlugin::setStackedWidgetIndex(Stacked::StackedWidgets index) const
{
    m_stackWindow->setCurrentIndex((int)index);
}
}
