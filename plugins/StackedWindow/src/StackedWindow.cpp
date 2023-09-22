#include "StackedWindow.h"
//#include "CoreService.h"
//#include "EventSystem.h"
//#include "AppSetting.h"
#include "ExitDialog.h"

#include <QCloseEvent>
#include <QCoreApplication>

namespace Eagle
{
namespace Widgets
{
StackedWindow::StackedWindow()
{
    m_stackedWidget = new QStackedWidget;

    configure();

//    connect(Events::EventSystem::instance(), &Events::EventSystem::fullScreen, this, &StackedWindow::fullScreen);
//    connect(Events::EventSystem::instance(), &Events::EventSystem::saveQuitMessage, this, &StackedWindow::saveQuitMessage);
//    connect(Events::EventSystem::instance(), &Events::EventSystem::storeProject, this, &StackedWindow::saveProject);
//    connect(Core::CoreService::instance(), &Core::CoreService::saveSuccessfully, this,
//            [ =, this]
//            {
//                if (m_savedData)
//                {
//                    qApp->exit(0);
//                }
//            });

//    restoreGeometry(Settings::AppSetting::instance().value("StackedWindow/Geometry").toByteArray());
//    restoreState(Settings::AppSetting::instance().value("StackedWindow/State").toByteArray());
}

StackedWindow::~StackedWindow()
{
//    Settings::AppSetting::instance().setValue("StackedWindow/Geometry", saveGeometry());
//    Settings::AppSetting::instance().setValue("StackedWindow/State", saveState());

    delete m_stackedWidget;
}

void  StackedWindow::configure()
{
    m_stackedWidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(m_stackedWidget);
}

void  StackedWindow::saveQuitMessage(bool flag)
{
    m_saveQuitMessage = flag;
}

void  StackedWindow::addStackedWidget(QWidget *widget)
{
    m_stackedWidget->addWidget(widget);
}

void  StackedWindow::setCurrentIndex(int index)
{
    m_stackedWidget->setCurrentIndex(index);
}

void  StackedWindow::closeEvent(QCloseEvent *event)
{
    ExitDialog  exit(this);

    if (m_saveQuitMessage)
    {
        exit.setSaveDiscardButtons(true);
    }
    else
    {
        exit.setSaveDiscardButtons(false);
    }

    exit.exec();

    m_savedData = exit.saveData();

    if ((exit.result() == QDialog::Accepted) && !m_savedData)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void  StackedWindow::fullScreen()
{
    isFullScreen() ? showMaximized() : showFullScreen();
}

void  StackedWindow::saveProject()
{
//    Settings::AppSetting::instance().setValue("StackedWindow/Geometry", saveGeometry());
//    Settings::AppSetting::instance().setValue("StackedWindow/State", saveState());
}
}
}
