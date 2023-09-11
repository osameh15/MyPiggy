#ifndef CONNECTION_PLUGIN_H
#define CONNECTION_PLUGIN_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The ConnectionPlugin class is an abstract base class for connection plugins.
 *
 * @author Datall Co, Eagle_Ir
 * @date Jan 2023
 */

#include "Definitions.h"

#include <Plugin.h>

namespace Datall
{
/**
 * @brief The ConnectionPlugin class is an abstract base class for connection plugins.
 * It provides an interface for establishing and managing a connection to a remote system.
 */
class ConnectionPlugin: public Plugin
{
    Q_OBJECT

public:
    /**
     * @brief Establishes a connection to the remote system.
     */
    virtual void     connect() = 0;

    /**
     * @brief Disconnects from the remote system.
     */
    virtual void     disconnect() = 0;

    /**
     * @brief Returns the type of the connection.
     * @return The connection type.
     */
    virtual QString  connectionType() = 0;

    /**
     * @brief Sets the properties of the connection.
     * @param properties The properties to set.
     */
    virtual void     setProperty(QVariantMap properties) = 0;

    /**
     * @brief Sends a request to the remote system.
     * @param invoke The InvokeCall object for handling the response.
     * @param payload The payload of the request.
     */
    virtual void     request(InvokeCall invoke, QJsonObject payload) = 0;

    /**
     * @brief Subscribes to a specific event or data from the remote system.
     * @param invoke The InvokeCall object for handling the response.
     * @param payload The payload of the subscription request.
     */
    virtual void     subscribe(InvokeCall invoke, QJsonObject payload) = 0;

    /**
     * @brief Switch Mode between replay mode and live mode.
     * @param invoke The InvokeCall object for handling the response.
     * @param payload The payload of the switch mode request.
     */
    virtual void     switchMode(InvokeCall invoke, QJsonObject payload) = 0;

    /**
     * @brief Unsubscribes from a specific event or data from the remote system.
     * @param invoke The InvokeCall object for handling the response.
     * @param payload The payload of the unsubscription request.
     */
    virtual void     unsubscribe(InvokeCall invoke, QJsonObject payload) = 0;

signals:
    /**
     * @brief Signal emitted when the connection is successfully established.
     */
    void             connected();

    /**
     * @brief Signal emitted when the connection is disconnected.
     */
    void             disconnected();

    /**
     * @brief Signal emitted when an error occurs during the connection.
     * @param resp The response containing the error information.
     */
    void             errorOccured(QJsonObject resp);
};
}

#define CONNECTIONPLUGIN_IID "org.Datall.core.connectionplugin"
Q_DECLARE_INTERFACE(Datall::ConnectionPlugin, PLUGIN_IID)


#endif
