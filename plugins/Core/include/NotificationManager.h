#ifndef NOTIFICATION_MANAGER_H
#define NOTIFICATION_MANAGER_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief The NotificationManager class represents for managing notifications.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "Definitions.h"

#include <QObject>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
#include <mutex>

#if defined (Q_OS_WIN)
#ifdef CORE_EXPORTS
#define NOTIFICATION_API Q_DECL_EXPORT
#else
#define NOTIFICATION_API Q_DECL_IMPORT
#endif
#elif defined (Q_OS_LINUX)
#define NOTIFICATION_API
#endif

class QOSDNotificationManager;
class QWaitingSpinner;

namespace Eagle
{
namespace Notify
{
/**
 * @brief The NotificationManager class represents for managing notifications.
 * This class serves for managing notifications within an application.
 * It provides functionality for displaying and managing various types of notifications,
 * such as OSD (On-Screen Display) notifications, pop-up notifications, and others.
 */
class NOTIFICATION_API NotificationManager: public QObject
{
    Q_OBJECT

public:
    /**
     * @brief getInstance: Get singleton object of project manager
     * @return
     */
    static NotificationManager* instance()
    {
        std::call_once(initInstanceFlag, &NotificationManager::createNotificationContainer);

        return m_instance;
    }

public slots:
    /**
     * @brief Shows and returns a QWaitingSpinner for the specified parent widget.
     * This function shows a QWaitingSpinner for the specified parent widget and returns a pointer
     * to the created QWaitingSpinner object.
     * @param parent The parent widget for which the progress bar should be shown.
     * @return A pointer to the QWaitingSpinner object representing the progress bar.
     */
    QWaitingSpinner*          showProgressBar(QWidget *parent);

    /**
     * @brief Stops the progress bar associated with the specified parent widget.
     * This function stops the progress bar that is associated with the specified parent widget.
     * @param parent The parent widget for which the progress bar should be stopped.
     */
    void                      stopProgressBar(QWidget *parent);

    /**
     * @brief showStatusBarMessage: Set message to status bar to display
     * @param msg: Message text
     * @param timeout: Display time. Default is 5 sec
     */
    void                      showStatusBarMessage(QString msg, int timeout = 5000);

    /**
     * @brief showOSDNotify: Show OSD notification in bottom right side
     * @param title: Title of notification
     * @param description: Description text of notification
     * @param type: Notification type, default is 0
     * 0: Information, 1: Warning, 2: Critical
     * @param duration: mili second timer, default is 5 sec
     */
    void                      showOSDNotify(QString title, QString description, int type = Notify::Information, int duration = 5000);

    /**
     * @brief showInputDialog: Show Input dialog box with custom values
     * @param parent: The parent widget object
     * @param title: Title of input dialog
     * @param label: Description of input dialog
     * @param text: Text in input line, default is @code QString() = null @endcode
     * @param echo: Line edit echo mode, default is @code QLineEdit::Normal @endcode
     * @param flags: Windows flag variable, default is @code Qt::WindowType::WindowMinMaxButtonsHint @endcode
     * @param inputMethodHints: Input method hints variable, default is @code Qt::ImhNone @endcode
     * @return
     */
    std::pair<bool, QString>  showInputDialog(QWidget *parent, const QString &title, const QString &label,
                                              const QString &text                   = QString(),
                                              QLineEdit::EchoMode echo              = QLineEdit::Normal,
                                              Qt::WindowFlags flags                 = Qt::WindowType::WindowMinMaxButtonsHint,
                                              Qt::InputMethodHints inputMethodHints = Qt::ImhNone);

    /**
     * @brief showMessageBox: Show Message box with custom values
     * @param title: Title of message box
     * @param text: Description of message box
     * @param icon: Icon of message box
     * @param parent: The parent widget object, default is nullptr
     * @param buttons: Add buttons to message box, default is @code QMessageBox::NoButton @endcode
     * @param flags: Windows flag variable, default is @code Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint @endcode
     * @return
     */
    QMessageBox* showMessageBox(const QString &title, const QString &text, QMessageBox::Icon icon,
                                QWidget *parent                      = nullptr,
                                QMessageBox::StandardButtons buttons = QMessageBox::NoButton,
                                Qt::WindowFlags flags                = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

signals:
    /**
     * @brief Signal emitted to display a message on the status bar.
     * @param msg The message to display.
     * @param timeout The duration in milliseconds for which the message should be displayed. Default is 5000 milliseconds.
     */
    void  statusBarDisplay(QString msg, int timeout = 5000);

private:
    /**
     * @brief Constructs a new NotificationManager object.
     */
    NotificationManager();

    /**
     * @brief createNotificationContainer: Create notification manager Object
     */
    static void  createNotificationContainer()
    {
        m_instance = new NotificationManager;
    }

private:
    /**
     * @brief Copy constructor is disabled.
     */
    Q_DISABLE_COPY(NotificationManager)

    /**
     * @brief m_instance: Static pointer to the single instance of NotificationManager.
     */
    static NotificationManager *m_instance;

    /**
     * @brief initInstanceFlag: Flag to ensure that the instance of NotificationManager is created only once.
     */
    static std::once_flag  initInstanceFlag;

    /**
     * @brief Pointer to the OSD (On-Screen Display) notification manager.
     */
    QOSDNotificationManager *m_OSDManager = nullptr;

    /**
     * @brief Pointer to the waiting spinner widget.
     */
    QWaitingSpinner *m_spinner = nullptr;
};
}
}
#endif // NOTIFICATION_MANAGER_H
