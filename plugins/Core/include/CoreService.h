#ifndef CORESERVICE_H
#define CORESERVICE_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief CoreService class. This class is maintenance application structure
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "WindowPlugin.h"
#include "AppSetting.h"
#include "UserSetting.h"

#include <mutex>
#include <QMap>
#include <QObject>
#include <QStandardItemModel>

class DaStandardItem;
class DaWidget;

#if defined (Q_OS_WIN)
#ifdef CORE_EXPORTS
#define CORE_API Q_DECL_EXPORT
#else
#define CORE_API Q_DECL_IMPORT
#endif
#elif defined (Q_OS_LINUX)
#define CORE_API
#endif
namespace Eagle
{
/**
 * @brief Typedef for a function pointer that creates an instance of a DaWidget.
 *
 * A DaWidgetPointer is a function pointer type that points to a function capable of creating an instance of a DaWidget.
 * It is used in conjunction with the registration and instantiation of DaWidgets in the DaWidget framework.
 */
typedef DaWidget * (*DaWidgetPointer)();

namespace Core
{
/**
 * @brief CoreService class is responsible for managing the connections with different DBMS and
 * providing a high-level API to work with the Database. It also provides access to the Workspace,
 * Windows, and other settings.
 */
class CORE_API CoreService: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief getInstance: Get singleton object of core service
     * @return
     */
    static CoreService* instance()
    {
        std::call_once(initInstanceFlag, &CoreService::createCoreServices);

        return m_instance;
    }

    /**
     * @brief configure: Initialize core service parameters
     * @param connections
     */
    void                           configure();

    /**
     * @brief configLocation: Return config location
     * @return
     */
    QString                        configLocation();

    /**
     * @brief setConfigLocation: Set config location
     * @param username: Username string
     */
    void                           setConfigLocation(QString username);

    /**
     * @brief setWindow: Set stacked window object
     * @param window: Stacked window object
     */
    void                           setWindow(Gui::WindowPlugin *window);

    /**
     * @brief window: Get stacked window object
     * @return
     */
    Gui::WindowPlugin*             window();

    /**
     * @brief appSetting: Return app setting data
     * @return
     */
    Settings::AppSetting*          appSetting();

    /**
     * @brief userSetting: Return user setting data
     * @return
     */
    Settings::UserSetting*         userSetting();

    /**
     * @brief Set the current user.
     * This function sets the current user to the specified user data.
     * @param currentUser The current user data to set.
     */
    void                           setCurrentUser(QVariantMap currentUser);

    /**
     * @brief setUsername sets the username associated with an entity.
     * This method sets the username associated with a particular entity or user. It allows for
     * updating or assigning a username to the entity, enabling proper user identification within
     * the application.
     * @param name The username to be set.
     */
    void                           setUsername(QString name);

    /**
     * @brief username retrieves the username associated with the entity.
     * This method retrieves the username associated with a particular entity or user. It allows
     * access to the username that has been set for the entity.
     * @return The username associated with the entity.
     */
    QString                        username();

    /**
     * @brief Get the current user.
     * This function returns the data of the current user.
     * @return The data of the current user.
     */
    QVariantMap                    currentUser();

    /**
     * @brief Registers an action with a specified type.
     * This function registers the given QAction object with the specified type. The action will be associated
     * with the specified type for further retrieval or processing.
     * @param type The type associated with the action.
     * @param act The QAction object to register.
     */
    void                           registerAction(QString type, QAction *act);

    /**
     * @brief Returns a QMultiMap of registered actions.
     * This function returns a QMultiMap of registered actions. The keys in the QMultiMap represent the types
     * associated with the actions, and the values are the QAction objects themselves. It provides a way to
     * retrieve the registered actions based on their associated types.
     * @return A QMultiMap<QString, QAction*> containing the registered actions.
     */
    QMultiMap<QString, QAction *>  actions() const;

    /**
     * @brief Registers a DaWidget factory function with a specified name.
     * @param name The name of the widget.
     * @param daWidget The Da Widget pointer.
     */
    void                           registerWidget(QString name, DaWidgetPointer daWidget);

    /**
     * @brief Retrieves the DaWidgetPointer associated with the specified widget name.
     * This function retrieves the DaWidgetPointer associated with the specified widget name.
     * The widget name is used as a unique identifier to look up and retrieve the corresponding DaWidgetPointer.
     * @param name The name of the widget to retrieve the DaWidgetPointer for.
     * @return The DaWidgetPointer associated with the specified widget name.
     */
    DaWidgetPointer                widgetPointer(QString name);

    /**
     * @brief Template function to create an instance of a DaWidget subclass.
     * @tparam T The subclass of DaWidget.
     * @return A new instance of the subclass.
     */
    template<typename T>
    static DaWidget*               createInstanceWidget()
    {
        return new T();
    }

private:
    /**
     * @brief CoreService: Default Constructor
     */
    CoreService();

    /**
     * @brief createCoreServices: Create Core Service Object
     */
    static void  createCoreServices()
    {
        m_instance = new CoreService;
    }

    /**
     * @brief initializeAppSetting: Initialize App settings when start application
     */
    void  initializeAppSetting();

    /**
     * @brief initializeUserSettings: Setting for specefic user
     * @param username: username string
     */
    void  initializeUserSettings(QString username);

    /**
     * @brief applicationThemeStylesheet: Set application theme style sheet after your application started
     * @param styles: Theme style sheet
     */
    void  applicationThemeStylesheet(Styles::StyleType styles);

private:
    /**
     * @brief Copy constructor is disabled.
     */
    Q_DISABLE_COPY(CoreService)

    /**
     * @brief m_instance: The singleton instance of the class.
     */
    static CoreService *m_instance;

    /**
     * @brief initInstanceFlag: The flag to ensure the singleton instance is initialized only once.
     */
    static std::once_flag  initInstanceFlag;

    /**
     * @brief m_windowWidget: The window widget used in the application.
     */
    Gui::WindowPlugin *m_windowWidget = nullptr;

    /**
     * @brief m_configLocation: The path to the configuration file.
     */
    QString  m_configLocation;

    /**
     * @brief The data of the current user.
     * This variable stores the data of the current user as a QVariantMap.
     * It provides access to various properties and information related to the current user.
     */
    QVariantMap  m_currentUser;

    /**
     * @brief m_username holds the username associated with an entity.
     * This member variable stores the username associated with a particular entity or user. It is
     * typically used to hold and manage the username, allowing for user identification and association
     * within the application. If no username is available, it is initialized as an empty string.
     */
    QString  m_username = "";

    /**
     * @brief m_appSetting: The application settings.
     */
    Settings::AppSetting *m_appSetting;

    /**
     * @brief m_userSetting: The user settings.
     */
    Settings::UserSetting *m_userSetting;

    /**
     * @brief m_actions: A QMultiMap to store the registered actions.
     */
    QMultiMap<QString, QAction *>  m_actions;

    /**
     * @brief m_registeredWidget:The map of registered widget names and their factory function pointers.
     */
    QMap<QString, DaWidgetPointer>  m_registeredWidget;
};
}
}

#endif // CORESERVICE_H
