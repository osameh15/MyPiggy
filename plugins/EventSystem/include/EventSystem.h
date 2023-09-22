#ifndef EVENTSYSTEM_H
#define EVENTSYSTEM_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief EventSystem class. Management all signals and handle connections
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include <mutex>
#include <QMap>
#include <QObject>
#include <QJsonDocument>

#if defined (Q_OS_WIN)
#ifdef EVENTS_EXPORTS
#define EVENTS_API Q_DECL_EXPORT
#else
#define EVENTS_API Q_DECL_IMPORT
#endif
#elif defined (Q_OS_LINUX)
#define EVENTS_API
#endif

namespace Eagle
{
namespace Events
{
/**
 * @brief The EventSystem class handles event-related operations.
 * It provides a singleton instance and disables copying of the class.
 */
class EVENTS_API EventSystem: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Returns the singleton instance of EventSystem.
     * @return Pointer to the singleton instance.
     */
    static EventSystem* instance()
    {
        std::call_once(initInstanceFlag, &EventSystem::createEventSystem);

        return m_instance;
    }

private:
    /**
     * @brief CoreService: Default Constructor
     */
    EventSystem();

    /**
     * @brief createCoreServices: Create Core Service Object
     */
    static void  createEventSystem()
    {
        m_instance = new EventSystem;
    }

signals:
    /**
     * @brief fullScreen: emitted when clicked on fullscreen button in view menu
     */
    void  fullScreen();

private:
    /**
     * @brief Deleted copy constructor to disable copying of EventSystem.
     */
    Q_DISABLE_COPY(EventSystem)

    /**
     * @brief m_instance: Singleton instance of EventSystem.
     */
    static EventSystem *m_instance;

    /**
     * @brief initInstanceFlag: Flag for initializing the singleton instance.
     */
    static std::once_flag  initInstanceFlag;
};
}
}

#endif // EVENTSYSTEM_H
