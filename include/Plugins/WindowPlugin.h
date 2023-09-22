#ifndef WINDOWPLUGIN_H
#define WINDOWPLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The WindowPlugin class is an abstract base class for window plugins.
 *
 * @author Datall Co, Eagle_Ir
 * @date Jan 2023
 */

#include "Plugin.h"
#include "Definitions.h"

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

namespace Datall
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

    /**
     * @brief resetWidget: Reset all items in widget
     * @param widgetType: Plugin widget type
     */
    virtual void         resetWidget(Stacked::StackedWidgets widgetType) const = 0;

    /**
     * @brief A pure virtual function that refreshes a specific widget
     * @param widgetType The type of widget to refresh
     */
    virtual void         refreshWidget(Stacked::StackedWidgets widgetType) const = 0;
};
}
}

#define WINDOWPLUGIN_IID "org.Datall.core.windowplugin"
Q_DECLARE_INTERFACE(Datall::Gui::WindowPlugin, WINDOWPLUGIN_IID)


#endif // WINDOWPLUGIN_H
