#ifndef STACKEDWINDOW_PLUGIN_H
#define STACKEDWINDOW_PLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The StackedWindowPlugin class represents a plugin for stacked windows in the GUI.This plugin is based
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "WindowPlugin.h"
#include "StackedWindow.h"

namespace Eagle
{
/**
 * @brief The StackedWindowPlugin class represents a plugin for stacked windows in the GUI.
 *
 * This class inherits from Gui::WindowPlugin and serves as a specific type of plugin for stacked
 * windows in the GUI. It extends the functionality provided by the WindowPlugin class to handle
 * stacked windows and associated operations within the application's graphical user interface.
 */
class StackedWindowPlugin: public Gui::WindowPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "meta.json")
    Q_INTERFACES(Eagle::Plugin)

public:
    /**
     * @brief StackedWindowPlugin: Constructor
     */
    StackedWindowPlugin();

    /**
     * @brief Destroys the StackedWindowPlugin object.
     */
    ~StackedWindowPlugin();

    /**
     * @brief init: Stacked Window Plugin Initialize
     * @param manager: Plugin manager object
     * @return
     */
    bool         init(const PluginManager *manager);

    /**
     * @brief mainWindow: Return Stacked window object
     * @return
     */
    QMainWindow* stackedWindow();

    /**
     * @brief registerWidget: Add dynamically widgets to stack and register it
     * @param widget: Plugin widget
     * @param widgetType: Plugin widget type
     */
    void         registerWidget(QWidget *widget, Stacked::StackedWidgets widgetType);

    /**
     * @brief setStackedWidgetIndex: Change current widget in stacked
     * @param index: Index of widget
     */
    void         setStackedWidgetIndex(Stacked::StackedWidgets index) const;

public slots:
    /**
     * @brief showMainWindow: Show maximized main window
     */
    void         showMainWindow();

private:
    /**
     * @brief m_stackWindow: Base window of application
     */
    Widgets::StackedWindow *m_stackWindow;
};
}

#endif // STACKEDWINDOW_PLUGIN_H
