#ifndef EXITDIALOG_H
#define EXITDIALOG_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief ExitDialog class.Exit program dialog, and save workspace or discard it
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include <QDialog>

namespace Ui
{
class ExitDialog;
}

namespace Eagle
{
/**
 * @brief Dialog for handling application exit.
 *
 * The ExitDialog class is a QDialog subclass that provides a dialog for handling application exit. It allows the user
 * to choose whether to save or discard changes before exiting the application.
 */
class ExitDialog: public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructs an ExitDialog object with the given parent.
     * @param parent The parent widget of the dialog.
     */
    explicit ExitDialog(QWidget *parent = nullptr);

    /**
     * @brief Destructor for the ExitDialog.
     */
    ~ExitDialog();

    /**
     * @brief Configures the exit dialog.
     * This method is used to configure the exit dialog and set up its initial state.
     */
    void  configure();

    /**
     * @brief Sets the save and discard buttons for the exit dialog.
     * This method sets up the save and discard buttons in the exit dialog based on the current state.
     * @param flag Enable discard/save button if true.
     */
    void  setSaveDiscardButtons(bool flag);

    /**
     * @brief Saves the data before exiting.
     * The saveData() method is responsible for saving the data before exiting the application.
     * It performs the necessary operations to save any unsaved changes or data modifications.
     * @return True if the data was successfully saved, false otherwise.
     */
    bool  saveData();

private slots:
    /**
     * @brief Slot for the Ok button clicked event.
     * This slot is called when the Ok button is clicked in the exit dialog. It performs the necessary actions when the
     * user chooses to save changes and exit.
     */
    void  on_pbOkClicked();

    /**
     * @brief Slot for the Discard button clicked event.
     * This slot is called when the Discard button is clicked in the exit dialog. It performs the necessary actions when
     * the user chooses to discard changes and exit.
     */
    void  on_pbDiscardClicked();

    /**
     * @brief Slot for the Cancel button clicked event.
     * This slot is called when the Cancel button is clicked in the exit dialog. It performs the necessary actions when
     * the user cancels the exit operation.
     */
    void  on_pbCancelClicked();

private:
    /**
     * @brief ui: The UI object for the exit dialog.
     */
    Ui::ExitDialog *ui;
};
}

#endif // EXITDIALOG_H
