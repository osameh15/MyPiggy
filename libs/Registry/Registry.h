#ifndef REGISTRY_H
#define REGISTRY_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The Registry class provides centralized management of application-wide resources.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include <QMap>
#include <QSet>
#include <QSettings>
#include <QThread>
#include <mutex>


#if defined (Q_OS_WIN)
#ifdef REGISTRY_EXPORTS
#define REGISTRY_API Q_DECL_EXPORT
#else
#define REGISTRY_API Q_DECL_IMPORT
#endif
#elif defined (Q_OS_LINUX)
#define REGISTRY_API
#endif

namespace Eagle
{
/**
 * @brief The Registry class provides centralized management of application-wide resources.
 *
 * The Registry class is designed to serve as a central component for managing application-wide
 * resources and services. It inherits from QObject and QEnableSharedFromThis to enable shared
 * ownership of Registry instances, making it suitable for use in a multi-component architecture.
 * Registry instances can store and provide access to various resources, configurations, or services
 * needed by different parts of the application.
 *
 * As a final class, Registry is designed to be a singleton, ensuring that only one instance exists
 * throughout the application's lifecycle. It can be accessed via shared pointers to provide a
 * consistent interface for resource management and access.
 */
class REGISTRY_API Registry final: public QObject, public QEnableSharedFromThis<Registry>
{
    Q_OBJECT

public:
    /**
     * @brief Retrieves the singleton instance of the Registry.
     * @return The singleton instance of the Registry.
     */
    static Registry& instance()
    {
        std::call_once(m_initInstanceFlag, &Registry::initSingleton);

        return *m_instance;
    }

    /**
     * @brief colorSchemeMode retrieves the current color scheme mode.
     * This method is used to retrieve and return the current color scheme mode of the application.
     * The color scheme mode typically represents the visual appearance or theme of the user interface,
     * such as "Light," "Dark," or other custom themes.
     * @return A QString containing the current color scheme mode.
     */
    QString  colorSchemeMode() const;

private:
    Q_DISABLE_COPY(Registry)

    /**  Registery instance*/
    static Registry    *m_instance;

    /** Registery init instance flag*/
    static std::once_flag  m_initInstanceFlag;

    /**
     * @brief initSingleton: Create singleton class object
     */
    static void  initSingleton()
    {
        m_instance = new Registry;
    }

    /**
     * @brief Creates a plugin manager.
     */
    Registry();

private:
    /**
     * @brief m_colorScheme stores the current color scheme mode.
     * This member variable holds a QString representing the current color scheme mode of the
     * application's user interface. The color scheme mode typically defines the visual appearance
     * or theme of the application, such as "Light," "Dark," or other custom themes. The value stored
     * in this variable indicates the active color scheme mode.
     */
    QString  m_colorScheme;
};
}

#endif
