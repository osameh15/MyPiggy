#ifndef PLUGIN_H
#define PLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief Plugin class is the base class of all plugins. All plugins must inherit this class and implement the required functions.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include <QtPlugin>

namespace Eagle
{
class PluginManager;

/**
 * @brief Plugin class is the base class of all plugins. All plugins must inherit this class
 * and implement the required functions.
 */
class Plugin: public QObject
{
public slots:
    /**
     * @brief Initializes the plugin.
     */
    virtual bool  init(const PluginManager *manager) = 0;
};
}

#define PLUGIN_IID "org.Eagle.visage.plugin"
Q_DECLARE_INTERFACE(Eagle::Plugin, PLUGIN_IID)

#endif // PLUGIN_H
