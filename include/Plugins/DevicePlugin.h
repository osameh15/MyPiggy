#ifndef DEVICEPLUGIN_H
#define DEVICEPLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The DevicePlugin class is an abstract base class for device plugins.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "Plugin.h"

#include <QVariantMap>

namespace Eagle
{
namespace Device
{
/**
 * @brief The DevicePlugin class is an abstract base class for device plugins.
 * It provides an interface for accessing device information, managing device status, and controlling device operations.
 */
class DevicePlugin: public Plugin
{
public:
    /**
     * @brief Retrieves the information of the device.
     * @return The device information as a QVariantMap.
     */
    virtual QVariantMap  deviceInfo() = 0;

    /**
     * @brief Retrieves the status of the device.
     * @return The device status as a QVariantMap.
     */
    virtual QVariantMap  deviceStatus() = 0;

    /**
     * @brief Starts the device.
     */
    virtual void         startDevice() = 0;

    /**
     * @brief Stops the device.
     */
    virtual void         stopDevice() = 0;

    /**
     * @brief Resets the device.
     */
    virtual void         reset() = 0;

    /**
     * @brief Retrieves the type of the device.
     * @return The device type as a QString.
     */
    virtual QString      type() = 0;
};
}
}

Q_DECLARE_INTERFACE(Eagle::Device::DevicePlugin, PLUGIN_IID)


#endif // DEVICEPLUGIN_H
