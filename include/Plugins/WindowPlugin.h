#ifndef WINDOWPLUGIN_H
#define WINDOWPLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The WindowPlugin class is an abstract base class for window plugins.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "Plugin.h"
#include "Definitions.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

namespace Eagle
{
namespace Gui
{
/**
 * @brief The WindowPlugin class is an abstract base class for window plugins.
 * It provides an interface for creating and managing window components.
 */
class WindowPlugin: public Plugin
{
public:
    /**
     * @brief mainWindow: Return Stacked window object
     * @return
     */
    virtual QMainWindow* stackedWindow() = 0;

    /**
     * @brief registerWidget: Add dynamically widgets to stack and register it
     * @param widget: Plugin widget
     * @param widgetType: Plugin widget type
     */
    virtual void         registerWidget(QWidget *widget, Stacked::StackedWidgets widgetType) = 0;

    /**
     * @brief setStackedWidgetIndex: Change current widget index of stacked
     * @param index: Index of current widget
     */
    virtual void         setStackedWidgetIndex(Stacked::StackedWidgets index) const = 0;
};
}
}

#define WINDOWPLUGIN_IID "org.Datall.core.windowplugin"
Q_DECLARE_INTERFACE(Eagle::Gui::WindowPlugin, WINDOWPLUGIN_IID)


#endif // WINDOWPLUGIN_H
