#ifndef SPLASHSCREENPLUGIN_PLUGIN_H
#define SPLASHSCREENPLUGIN_PLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief SplashScreenPlugin class. Splash screen plugin initialize. This plugin is based
 * Splash image screen will be displayed for 2 sec
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "Plugin.h"

#include <QSplashScreen>

namespace Eagle
{
/**
 * @brief The SplashScreenPlugin class: Splash screen plugin class to show logo splash for 2 sec
 */
class SplashScreenPlugin: public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID PLUGIN_IID FILE "meta.json")
    Q_INTERFACES(Eagle::Plugin)

public:
    /**
     * @brief SplashScreenPlugin: Constructor
     */
    SplashScreenPlugin();

    /**
     * @brief init: Splash Screen Plugin Initialize
     * @param manager: Plugin manager object
     * @return
     */
    bool  init(const PluginManager *manager);

public slots:
    void done();
private:
    /**
     * @brief Pointer to the QSplashScreen object.
     * This pointer is used to manage the application splash screen.
     */
    QSplashScreen *m_splashScreen = nullptr;
};
}

#endif // SPLASHSCREENPLUGIN_PLUGIN_H
