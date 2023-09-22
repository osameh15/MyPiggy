#include "ExitDialog.h"
#include "ui_ExitDialog.h"
//#include "EventSystem.h"

namespace Eagle
{
ExitDialog::ExitDialog(QWidget *parent):
    QDialog(parent),
    ui(new Ui::ExitDialog)
{
    ui->setupUi(this);

    connect(ui->pbOk, &QPushButton::clicked, this, &ExitDialog::on_pbOkClicked);
    connect(ui->pbDiscard, &QPushButton::clicked, this, &ExitDialog::on_pbDiscardClicked);
    connect(ui->pbCancel, &QPushButton::clicked, this, &ExitDialog::on_pbCancelClicked);

    configure();
}

ExitDialog::~ExitDialog()
{
    delete ui;
}

void  ExitDialog::configure()
{
    ui->pbDiscard->setVisible(false);
}

void  ExitDialog::setSaveDiscardButtons(bool flag)
{
    if (flag)
    {
        setWindowTitle("Save And Exit");

        ui->pbDiscard->setVisible(true);
        ui->pbOk->setText("&Save");
        ui->lExitText->setText("Do you want to save last project and leave the Visage?");
    }
    else
    {
        setWindowTitle("Exit");

        ui->pbDiscard->setVisible(false);
        ui->pbOk->setText("&Yes");
        ui->lExitText->setText("Are you sure you want to exit the Visage?");
    }
}

bool  ExitDialog::saveData()
{
    if (ui->pbOk->text() == "&Save")
    {
        return true;
    }

    return false;
}

void  ExitDialog::on_pbOkClicked()
{
    if (ui->pbOk->text() == "&Save")
    {
//        emit  Events::EventSystem::instance()->saveProject();
    }

    accept();
}

void  ExitDialog::on_pbDiscardClicked()
{
    qApp->exit(0);
}

void  ExitDialog::on_pbCancelClicked()
{
    reject();
}
}
