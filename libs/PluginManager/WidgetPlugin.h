#ifndef WIDGETPLUGIN_H
#define WIDGETPLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The WidgetPlugin class is an abstract base class for widget plugins.
 *
 * @author Datall Co, Eagle_Ir
 * @date Jan 2023
 */

#include "Plugin.h"

#include <QWidget>

namespace Datall
{
namespace Gui
{
/**
 * @brief The WidgetPlugin class is an abstract base class for widget plugins.
 * It provides an interface for creating and managing widget components.
 */
class WidgetPlugin: public Plugin
{
public:
    /**
     * @brief QWidget of the plugin.
     */
    virtual QWidget* getWidget() const = 0;

    /**
     * @brief resetWidget: Clear and reset widget
     */
    virtual void     resetWidget() = 0;
};
}
}

#define WIDGETPLUGIN_IID "org.Datall.core.widgetplugin"
Q_DECLARE_INTERFACE(Datall::Gui::WidgetPlugin, WIDGETPLUGIN_IID)


#endif // WIDGETPLUGIN_H
