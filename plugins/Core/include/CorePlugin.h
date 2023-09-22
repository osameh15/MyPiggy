#ifndef CORE_PLUGIN_H
#define CORE_PLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief CorePlugin class.  Core Plugin Initialize. This plugin is based
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "Plugin.h"
#include "PluginManager.h"

namespace Eagle
{
/**
 * @brief The CorePlugin class: Core main plugin class
 */
class CorePlugin: public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "meta.json")
    Q_INTERFACES(Eagle::Plugin)

public:
    /**
     * @brief CorePlugin: Constructor
     */
    CorePlugin();

    /**
     * @brief init: Core Plugin Initialize
     * @param manager: Plugin manager object
     * @return
     */
    bool  init(const PluginManager *manager);

private slots:
    void initCoreService();
};
}

#endif // CORE_PLUGIN_H
