#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The PluginManager class is responsible for loading plugins at runtime and managing them.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "PluginInfo.h"

#include <QMap>
#include <QSet>
#include <QSettings>
#include <QThread>
#include <mutex>

class QPluginLoader;

namespace Eagle
{
class Plugin;

/**
 * @brief The PluginManager class is responsible for loading plugins at runtime and managing them.
 * It provides methods to retrieve information about plugins and to get a singleton instance of the PluginManager.
 */
class PluginManager final: public QObject, public QEnableSharedFromThis<PluginManager>
{
    Q_OBJECT

public:
    using ProgressCallback = std::function<void (qint32 progress, const QString &message)>;

public:
    /**
     * @brief When asking for list of plugins, this mode is used to limit the results to an specific group.
     */
    enum QueryMode
    {
        /** All available plugins. */
        AllPlugins,

        /** Plugins that are enabled and loaded successfully. */
        LoadedPlugins,

        /** Plugins that are enabled but failed to load. */
        FailedPlugins,

        /** Plugins that are enabled (i.e., all plugins except exclusion list when loading plugins). */
        EnabledPlugins,

        /** Plugins that are disabled (i.e., exclusion list when loading plugins). */
        DisabledPlugins,
    };

    /**
     * @brief Retrieves the singleton instance of the PluginManager.
     * @return The singleton instance of the PluginManager.
     */
    static PluginManager& getInstance()
    {
        std::call_once(initInstanceFlag, &PluginManager::initSingleton);

        return *instance;
    }

    /**
     * @brief Gets a list of all plugins according to the condition provided by \p mode.
     * @param mode The search mode. Limits the result of search to specific plugins.
     * @return List of plugins asked for.
     */
    QList<PluginInfo>  getAllPlugins(QueryMode mode = QueryMode::AllPlugins) const
    {
        QList<PluginInfo>  res;

        switch (mode)
        {
        case PluginManager::AllPlugins:
        {
            res = m_allPlugins.values();
        }
        break;
        case PluginManager::LoadedPlugins:
        {
            res = m_loadedPlugins.values();
        }
        break;
        case PluginManager::FailedPlugins:
        {
            res = m_failedPlugins.values();
        }
        break;
        case PluginManager::EnabledPlugins:
        {
            res = m_enabledPlugins.values();
        }
        break;
        case PluginManager::DisabledPlugins:
        {
            res = m_disabledPlugins.values();
        }
        break;
        }

        return res;
    }

    /**
     * @brief Gets the information of a successfully loaded plugin.
     * @param name The name of plugin to search for.
     * @param info a pointer to a \ref Datall::PluginInfo that will hold the result. Can be null.
     * @return Success if plugin found.
     */
    bool  getPlugin(const QString &name, PluginInfo *info) const
    {
        bool  res          = false;
        auto  lodedPlugins = m_loadedPlugins.values();

        for (const auto &item : lodedPlugins)
        {
            if (name == item.name)
            {
                if (nullptr != info)
                {
                    *info = item;
                }

                res = true;

                break;
            }
        }

        return res;
    }

    /**
     * @brief Retrieves information about a plugin at the specified index.
     * @param index The index of the plugin.
     * @param info Pointer to a PluginInfo object to store the plugin information.
     * @return True if the plugin information was successfully retrieved, false otherwise.
     */
    bool  getPlugin(int index, PluginInfo *info) const
    {
        bool  res          = false;
        auto  lodedPlugins = m_loadedPlugins.values();

        for (const auto &item : lodedPlugins)
        {
            if (index == item.index)
            {
                if (nullptr != info)
                {
                    *info = item;
                }

                res = true;

                break;
            }
        }

        return res;
    }

    /**
     * @brief Loads all plugins in the \p directory.
     * @param directory The absolute or relative path of directory that holds the plugin files.
     * @param exclusion Files in exclusion set will not be loaded. One use case is to disable some plugins.
     * @return Number of plugins that have been successfully loaded.
     */
    quint32        loadPlugins(const QString &directory);

    /**
     * @brief Unloads all loaded plugins.
     */
    void           unloadPlugins();

    /**
     * @brief Saves the current plugin settings to file.
     */
    void           saveSettings();

    /**
     * @brief Gets the plugin exclusion list (i.e., disabled plugins).
     * @return A set of paths to disabled plugin files.
     */
    QSet<QString>  getExclusion() const;

    /**
     * @brief Sets the plugin exclusion list (i.e., disabled plugins). The exclusion will be applied after
     * calling \ref PluginManager::saveSettings and restarting the application.
     * @param exclusion A set of paths to disabled plugin files.
     */
    void           setExclusion(const QSet<QString> &exclusion);

signals:
    /**
     * @brief This signal is emitted while the plugin manager is loading plugins.
     * @param percent Total progress percentage [0, 100].
     * @param msg A message that shows the last state of loading progress.
     */
    void           progress(qint32 percent, const QString &msg);

    /**
     * @brief This signal is emitted when the plugin manager finishes loading plugins.
     */
    void           done();

private:
    Q_DISABLE_COPY(PluginManager)

    /**  Plugin manager instance*/
    static PluginManager    *instance;

    /** Plugin manager init instance flag*/
    static std::once_flag  initInstanceFlag;

    /**
     * @brief initSingleton: Create singleton class object
     */
    static void  initSingleton()
    {
        instance = new PluginManager;
    }

    /**
     * @brief Creates a plugin manager.
     */
    PluginManager(bool resetSettings = false);

    /**
     * @brief Loads plugin settings from file.
     */
    void  loadSettings();

private:
    /**
     * @brief Map of all plugins.
     * This map stores information about all available plugins, where the key is the plugin name and the value is the PluginInfo object.
     */
    QMap<QString, PluginInfo>  m_allPlugins;

    /**
     * @brief Map of loaded plugins.
     * This map stores information about the plugins that have been successfully loaded, where the key is the plugin name and the value is the PluginInfo object.
     */
    QMap<QString, PluginInfo>  m_loadedPlugins;

    /**
     * @brief Map of failed plugins.
     * This map stores information about the plugins that failed to load, where the key is the plugin name and the value is the PluginInfo object.
     */
    QMap<QString, PluginInfo>  m_failedPlugins;

    /**
     * @brief Map of enabled plugins.
     * This map stores information about the plugins that are currently enabled, where the key is the plugin name and the value is the PluginInfo object.
     */
    QMap<QString, PluginInfo>  m_enabledPlugins;

    /**
     * @brief Map of disabled plugins.
     * This map stores information about the plugins that are currently disabled, where the key is the plugin name and the value is the PluginInfo object.
     */
    QMap<QString, PluginInfo>  m_disabledPlugins;

    /**
     * @brief Set of excluded plugins.
     * This set stores the names of the plugins that are excluded from loading.
     */
    QSet<QString>  m_exclusion;

    /**
     * @brief Pointer to the QSettings object.
     * This pointer is used to access the settings for the PluginManager.
     */
    QScopedPointer<QSettings>  m_settings;

    /**
     * @brief Map of plugin instances and associated threads.
     * This map stores the plugin instances and the associated threads for concurrent execution.
     * The key is a QSharedPointer to the plugin instance, and the value is the corresponding QThread.
     */
    QMap<QSharedPointer<Plugin>, QThread *>  m_ThreadPool;
};
}

#endif
