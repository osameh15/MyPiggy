#ifndef EVENT_SYSTEM_PLUGIN_H
#define EVENT_SYSTEM_PLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief EventSystemPlugin class. Event system plugin initialize. This plugin is based
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "Plugin.h"
#include "EventSystem.h"

namespace Eagle
{
/**
 * @brief The EventSystemPlugin class: Event system plugin class
 */
class EventSystemPlugin: public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "meta.json")
    Q_INTERFACES(Eagle::Plugin)

public:
    /**
     * @brief CorePlugin: Constructor
     */
    EventSystemPlugin();

    /**
     * @brief init: Core Plugin Initialize
     * @param manager: Plugin manager object
     * @return
     */
    bool  init(const PluginManager *manager);

private:
    Events::EventSystem *m_eventSystem;
};
}

#endif // EVENT_SYSTEM_PLUGIN_H
