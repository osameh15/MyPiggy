#include "CorePlugin.h"
#include "CoreService.h"

#include <iostream>

namespace Eagle
{
CorePlugin::CorePlugin()
{
}

bool  CorePlugin::init(const PluginManager *manager)
{
    bool  res = false;

    if (nullptr != manager)
    {
        std::cout << "Core plugin Initialized." << std::endl;

        connect(manager, SIGNAL(done()), this, SLOT(initCoreService()));

        res = true;
    }

    return res;
}

void CorePlugin::initCoreService()
{
    Core::CoreService::instance()->configure();
}
}
