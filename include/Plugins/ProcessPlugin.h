#ifndef PROCESSPLUGIN_H
#define PROCESSPLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The ProcessPlugin class is an abstract base class for process plugins.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "Plugin.h"

namespace Eagle
{
namespace Process
{
/**
 * @brief The ProcessPlugin class is an abstract base class for process plugins.
 * It provides an interface for creating and managing processes.
 */
class ProcessPlugin: public Plugin
{
public:
    /**
     * @brief QWidget of the plugin.
     */
    virtual QVariantList  process(QVector<QPoint> *, uint) const = 0;

    /**
     * @brief Reset.
     */
    virtual void          reset() const = 0;
};
}
}

#define PROCESSPLUGIN_IID "org.Eagle.core.processplugin"
Q_DECLARE_INTERFACE(Eagle::Process::ProcessPlugin, PROCESSPLUGIN_IID)


#endif // PROCESSPLUGIN_H
