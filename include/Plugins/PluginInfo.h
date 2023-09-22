#ifndef PLUGININFO_H
#define PLUGININFO_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief Holds the information (meta data) of a plugin. see \ref Datall::Plugin for more details.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include <QSharedPointer>

namespace Eagle
{
class Plugin;

/**
 * @brief Holds the information (meta data) of a plugin. see \ref Datall::Plugin for more details.
 */
struct PluginInfo
{
    /**
     *  @brief Creates a default \ref Datall::PluginInfo.
     */
    PluginInfo()
    {
    }

    /**
     *  @brief Creates a \ref Datall::PluginInfo with the provided args.
     *  @param path: Absolute path to the plugin library file.
     *  @param vendor: Vendor name of the plugin.
     *  @param name: Name of the plugin.
     *  @param version: Version number of the plugin.
     *  @param build: Build number of the plugin
     *  @param index: index of the plugin
     *  @param type: Type of the plugin
     *  @param description: Plugin description.
     *  @param plugin: A pointer to an instance of the loaded plugin.
     */
    PluginInfo(const QString &path, const QString &vendor, const QString &name, const double version, const int build, const int index, const QString &type,
               const QString &description, const QSharedPointer<Plugin> &plugin)
    {
        this->path        = path;
        this->vendor      = vendor;
        this->name        = name;
        this->version     = version;
        this->build       = build;
        this->index       = index;
        this->type        = type;
        this->description = description;
        this->plugin      = plugin;
    }

    /**
     * @brief Absolute path to the loaded dynamic library.
     */
    QString  path;

    /**
     * @brief type name.
     * There is 4 type declare here
     * Base --> The base and system plugin
     * Stacked_Base --> The Stacked Window based system plugins
     * Main_Base --> The Main Window based system plugins
     * Optional --> The optinal plugin
     */
    QString  type;

    /**
     * @brief Name of the plugin. May differ from library name.
     */
    QString  name;

    /**
     * @brief vendor name of the plugin
     */
    QString  vendor;

    /**
     * @brief Version number of the plugin.
     */
    double  version;

    /**
     * @brief Build Number of the plugin
     */
    int  build;

    /**
     * @brief Index of the plugin.
     * This is use to sort plugins to load and enabled
     */
    int  index;

    /**
     * @brief A descriptive information about this plugin.
     */
    QString  description;

    /**
     * @brief A pointer to an instance of the loaded plugin. Null if plugin is not loaded.
     */
    QSharedPointer<Plugin>  plugin;
};
}

#endif // PLUGININFO_H
