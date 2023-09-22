#include "EventSystemPlugin.h"
#include "PluginManager.h"

#include <iostream>

namespace Eagle
{
EventSystemPlugin::EventSystemPlugin()
{
}

bool  EventSystemPlugin::init(const PluginManager *manager)
{
    bool  res = false;

    if (nullptr != manager)
    {
        std::cout << "Event System plugin Initialized." << std::endl;

        m_eventSystem->instance();

        res = true;
    }

    return res;
}
}
