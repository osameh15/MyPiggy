#ifndef STACKEDWINDOW_H
#define STACKEDWINDOW_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief StackedWindow class. Main class includes all main widgets like main window, tree or projects will be displayed first.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include "Definitions.h"

#include <QMainWindow>
#include <QStackedWidget>

#if defined (Q_OS_WIN)
#ifdef STACKEDWINDOW_EXPORTS
#define STACKEDWINDOW_API Q_DECL_EXPORT
#else
#define STACKEDWINDOW_API Q_DECL_IMPORT
#endif
#elif defined (Q_OS_LINUX)
#define STACKEDWINDOW_API
#endif

namespace Eagle
{
class ExitDialog;
namespace Widgets
{
/**
 * @brief The StackedWindow class: Stacked window class is main class to manage all main plugins
 */
class STACKEDWINDOW_API StackedWindow: public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief StackedWindow: Default Constructor
     */
    explicit StackedWindow();

    /**
     * @brief Destructor for the StackedWindow.
     */
    ~StackedWindow();

    /**
     * @brief configure: Config and initialize Stack window manager
     */
    void  configure();

    /**
     * @brief Sends a signal to indicate the need for a save and quit message.
     * This function is called to send a signal indicating that a save and quit message should
     * be displayed to the user. The signal is typically connected to a slot or handler that
     * handles the display of the message and performs the necessary actions based on the user's
     * response (e.g., saving data, discarding changes, canceling the quit operation).
     * @param flag Set exit dialog with discard button if true.
     * @note This function is typically invoked when the user initiates an action that triggers
     * the need for a save and quit message, such as clicking a "Quit" button or selecting an
     * exit option from a menu.
     * @see saveQuitMessage() signal in EventSystem class
     */
    void  saveQuitMessage(bool flag);

    /**
     * @brief registerWidget: Register and store widgets in private members
     * @param widgetType: Widget type
     */
    void  registerWidget(Stacked::StackedWidgets widgetType);

    /**
     * @brief addStackedWidget: Add Widget to Stacked
     * @param widget: Widget object
     */
    void  addStackedWidget(QWidget *widget);

    /**
     * @brief setCurrentIndex: Change Current widget in stacked
     * @param index: Index of widgets
     */
    void  setCurrentIndex(int index);

protected:
    /**
     * @brief Event handler for the close event of the widget.
     * This protected method is called when the widget is being closed. It allows custom handling of the close event.
     * @param event A pointer to the QCloseEvent object representing the close event.
     */
    void  closeEvent(QCloseEvent *event);

private slots:
    /**
     * @brief fullScreen: Show normal or fullscreen stacked window
     */
    void  fullScreen();

    /**
     * @brief Slot or handler for saving the project.
     * This slot or handler is called in response to the `saveProject()` signal. It is responsible for
     * performing the necessary actions to save the current project data.
     * @note The implementation of this slot should handle the saving process, such as updating the data
     * model, writing the data to a file, or sending the data to a server.
     * @see saveProject() signal in EventSystem class
     */
    void  saveProject();

private:
    /**
     * @brief Flag indicating whether a save and quit message should be displayed.
     * This flag is used to control the display of a save and quit message in the application.
     * When set to true, it indicates that a save and quit message should be shown to the user
     * before exiting the application. The flag is typically used to track whether there are any
     * unsaved changes or data that need to be saved before quitting.
     * @note The value of this flag should be updated as per the application logic and requirements.
     */
    bool  m_saveQuitMessage = false;

    /**
     * @brief Flag indicating whether the data has been saved.
     * The m_savedData variable is a boolean flag that indicates whether the data has been saved.
     * It is initially set to false and can be updated to true when the data is saved.
     */
    bool  m_savedData = false;

    /**
     * @brief Pointer to the stacked widget used for managing multiple widgets.
     */
    QStackedWidget *m_stackedWidget;
};
}
}

#endif // STACKEDWINDOW_H
