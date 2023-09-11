#include "PluginManager.h"
#include "Plugin.h"

#include <QPluginLoader>
#include <QSettings>
#include <QDataStream>
#include <QDir>
#include <QSet>
#include <QQueue>
#include <QJsonArray>
#include <iostream>

namespace Datall
{
PluginManager  *PluginManager::instance = nullptr;
std::once_flag  PluginManager::initInstanceFlag;

static constexpr auto  SETTING_PLUGINS          = "Plugins";
static constexpr auto  PLUGIN_META              = "MetaData";
static constexpr auto  PLUGIN_META_VENDOR       = "vendor";
static constexpr auto  PLUGIN_META_NAME         = "name";
static constexpr auto  PLUGIN_META_VERSION      = "version";
static constexpr auto  PLUGIN_META_BUILD        = "build";
static constexpr auto  PLUGIN_META_INDEX        = "index";
static constexpr auto  PLUGIN_META_TYPE         = "type";
static constexpr auto  PLUGIN_META_DESC         = "description";
static constexpr auto  PLUGIN_META_DEPENDENCIES = "dependencies";

static bool  metaDataToPluginInfo(const QSharedPointer<QPluginLoader> &loader, PluginInfo *info)
{
    bool  res = false;

    if (nullptr != loader)
    {
        QJsonValue  json = loader->metaData()[PLUGIN_META];

        if (json.isObject())
        {
            const auto &metaData = json.toObject();

            // Checking meta data structure.
            if (metaData[PLUGIN_META_NAME].isString()
                && metaData[PLUGIN_META_VERSION].isDouble()
                && metaData[PLUGIN_META_TYPE].isString()
                && metaData[PLUGIN_META_DESC].isString())
            {
                const auto &vendor      = metaData[PLUGIN_META_VENDOR].toString();
                const auto &name        = metaData[PLUGIN_META_NAME].toString();
                const auto &version     = metaData[PLUGIN_META_VERSION].toDouble();
                const auto &build       = metaData[PLUGIN_META_BUILD].toInt();
                const auto &index       = metaData[PLUGIN_META_INDEX].toInt();
                const auto &type        = metaData[PLUGIN_META_TYPE].toString();
                const auto &description = metaData[PLUGIN_META_DESC].toString();

                if (nullptr != info)
                {
                    // We are just creating a "PluginInfo", the plugin is not actually loaded.
                    *info = PluginInfo(loader->fileName(), vendor, name, version, build, index, type, description, nullptr);
                }

                res = true;
            }
        }

        // Invalid meta data structure.
        if (!res)
        {
            if (nullptr != info)
            {
                *info = PluginInfo(loader->fileName(), QString(), QString(), 0, 0, 0,
                                   QString(), QStringLiteral("Invalid meta data structure."), nullptr);
            }
        }
    }

    return res;
}

bool  pluginSorter(const QSharedPointer<QPluginLoader> &p1, const QSharedPointer<QPluginLoader> &p2)
{
    PluginInfo  info1;
    PluginInfo  info2;

    metaDataToPluginInfo(p1, &info1);
    metaDataToPluginInfo(p2, &info2);

    return info1.index < info2.index;
}

static QString  createMsgStatus(const PluginInfo &info, bool success)
{
    return QStringLiteral("Plugin ") + info.name + QStringLiteral(" v") + QString::number(info.version)
           + (success ? QStringLiteral(" loaded.") : QStringLiteral(" failed."));
}

static QString  createMsgLoading(const PluginInfo &info)
{
    return QStringLiteral("Loading plugin ") + info.name + QStringLiteral(" v") + QString::number(info.version) + QStringLiteral(".");
}

PluginManager::PluginManager(bool resetSettings):
    m_settings(new QSettings())
{
    if (resetSettings)
    {
        saveSettings();
    }
    else
    {
        loadSettings();
    }
}

quint32  PluginManager::loadPlugins(const QString &directory)
{
    QDir  dirPlugins(directory);

        #if (__linux || __unix || __posix)
    dirPlugins.setNameFilters(QStringList("*.so"));
        #elif (_WIN64 || _WIN32)
    dirPlugins.setNameFilters(QStringList("*.dll"));
        #else
                #error This platform is not supported.
        #endif

    const auto                           &pluginFiles = dirPlugins.entryList(QDir::Files);
    QSet<QString>                         pluginNameSet;
    QList<QSharedPointer<QPluginLoader>>  pluginLoaders;
    QMap<QString, int>                    resolvedPlugins;

    // Phase 1: Checking meta data of all dynamic libraries.
    for (const auto &fileName : pluginFiles)
    {
        PluginInfo  info;
        const auto &filePath = dirPlugins.absoluteFilePath(fileName);
        const auto &loader   = QSharedPointer<QPluginLoader>::create(filePath);
        const auto &res      = metaDataToPluginInfo(loader, &info);

        if (res)
        {
            m_allPlugins.insert(filePath, info);

            if (!m_exclusion.contains(filePath))
            {
                m_enabledPlugins.insert(filePath, info);

                // All plugins are in failed state by default, they will be removed from this list when loaded successfully.
                m_failedPlugins.insert(filePath, info);

                const auto &lowerPluginName = info.name.toLower();

                if (!info.name.isEmpty() && !pluginNameSet.contains(lowerPluginName))
                {
                    pluginNameSet.insert(lowerPluginName);

                    pluginLoaders.push_back(loader);
                }
            }
            else
            {
                m_disabledPlugins.insert(filePath, info);
            }
        }
        else
        {
            if (!m_exclusion.contains(filePath))
            {
                std::cout << "Plugin failed : " << filePath.toStdString() << " : " << info.description.toStdString();
                m_failedPlugins.insert(filePath, info);
            }
            else
            {
                m_disabledPlugins.insert(filePath, info);
            }
        }
    }

    // Phase 2: Sort plugins in list.
    std::sort(pluginLoaders.begin(), pluginLoaders.end(), &pluginSorter);

    // Phase 3: Checking plugin dependencies and loading them.
    qint32        loadedPluginsCount = 0;
    const qreal   maxProgress        = pluginLoaders.size();
    const qint32  maxTries           = pluginLoaders.size() * pluginLoaders.size();

    for (qint32 tryNumber = 0; tryNumber < maxTries && 0 < pluginLoaders.size(); ++tryNumber)
    {
        const auto &loader = pluginLoaders.front();

        if (nullptr != loader)
        {
            const auto &metaData     = loader->metaData()[PLUGIN_META].toObject();
            const auto &dependencies = metaData[PLUGIN_META_DEPENDENCIES].toArray();
            bool        resolved     = true;

            // Ensuring that plugin's dependencies are resolved.
            for (const auto &d : dependencies)
            {
                const auto &depName = d.toString().toLower();

                if (resolvedPlugins.contains(depName))
                {
                    const auto &v = d.toObject()[PLUGIN_META_VERSION].toInt();
                    const int   pluginVersion(v);

                    if (resolvedPlugins[depName] < pluginVersion)
                    {
                        resolved = false;
                        break;
                    }
                }
                else
                {
                    resolved = false;
                    break;
                }
            }

            if (resolved)
            {
                PluginInfo  info;

                // TODO: It can be optimized by using PluginInfos that are loaded in phase 1.
                (void)metaDataToPluginInfo(loader, &info);

                QString                  message = createMsgStatus(info, false);
                emit                     progress(static_cast<qint32>(100 * (1.0 - pluginLoaders.size() / maxProgress)), createMsgLoading(info));
                QSharedPointer<QObject>  pluginInstance(loader->instance());
                bool                     failed = true;

                if (nullptr != pluginInstance)
                {
                    QSharedPointer<Plugin>  plugin = qobject_cast<Plugin *>(pluginInstance);

                    if (nullptr != plugin)
                    {
                        const auto &res = plugin->init(this);

                        failed = !res;

                        if (!failed)
                        {
                            if (info.type == "Process")
                            {
                                QThread *t = new QThread();

                                t->setObjectName(info.name);
                                plugin->moveToThread(t);
                                t->start();

                                m_ThreadPool.insert(plugin, t);
                            }

                            info.plugin = plugin;

                            // Updating the PluginInfo in "_enabledPlugins" and "_allPlugins" because the plugin pointer is updated.
                            m_allPlugins[info.name]     = info;
                            m_enabledPlugins[info.name] = info;
                            m_loadedPlugins.insert(info.path, info);
                            m_failedPlugins.remove(info.path);
                            resolvedPlugins.insert(info.name.toLower(), info.version);

                            ++loadedPluginsCount;

                            message = createMsgStatus(info, true);
                        }
                    }
                }

                if (failed)
                {
                    std::cout << "Plugin not loaded : " << loader->errorString().toStdString() << std::endl;
                    info.description           = loader->errorString();
                    m_failedPlugins[info.path] = info;
                }

                emit  progress(static_cast<qint32>(100 * (1.0 - pluginLoaders.size() / maxProgress)), message);

                pluginLoaders.pop_front();
            }
            else
            {
                if (pluginLoaders.size() > 1)
                {
                    pluginLoaders.move(0, pluginLoaders.size() - 1);
                }
            }
        }
    }

    emit  done();

    return loadedPluginsCount;
}

void  PluginManager::unloadPlugins()
{
    auto  threadPool = m_ThreadPool.values();

    m_ThreadPool.clear();

    for (auto t : threadPool)
    {
        t->quit();
        t->wait();
        std::cout << "Thread " << t->objectName().toStdString() << " stoped." << std::endl;
        delete t;
    }

    m_allPlugins.clear();
    m_loadedPlugins.clear();
    m_failedPlugins.clear();
    m_enabledPlugins.clear();
    m_disabledPlugins.clear();
    m_exclusion.clear();
}

void  PluginManager::saveSettings()
{
    QByteArray   buffer;
    QDataStream  ds(&buffer, QIODevice::WriteOnly);

    ds << m_exclusion;
    m_settings->setValue(SETTING_PLUGINS, buffer);
    m_settings->sync();
}

void  PluginManager::loadSettings()
{
    QByteArray   buffer = QSettings().value(SETTING_PLUGINS).toByteArray();
    QDataStream  ds(&buffer, QIODevice::ReadOnly);

    ds >> m_exclusion;
}

QSet<QString>  PluginManager::getExclusion() const
{
    return m_exclusion;
}

void  PluginManager::setExclusion(const QSet<QString> &exclusion)
{
    m_exclusion = exclusion;
}
}
