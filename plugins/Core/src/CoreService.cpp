#include "CoreService.h"
#include "DaWidget.h"

#include <QStandardPaths>
#include <QCoreApplication>
#include <QVersionNumber>
#include <QApplication>
#include <QDir>
#include <QMenu>

namespace Eagle
{
namespace Core
{
CoreService *CoreService::m_instance = nullptr;

std::once_flag  CoreService::initInstanceFlag;

CoreService::CoreService()

{
}

void  CoreService::initializeAppSetting()
{
    m_appSetting = &Settings::AppSetting::instance();

    QString  configLocation     = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QString  preferencesVersion = m_appSetting->value("applicationVersion", QString()).toString();

    if (preferencesVersion.isEmpty())
    {
        preferencesVersion = qApp->applicationVersion();

        m_appSetting->setValue("applicationVersion", qApp->applicationVersion());
    }

    QVersionNumber  prevVersion    = QVersionNumber::fromString(preferencesVersion);
    QVersionNumber  currentVersion = QVersionNumber::fromString(qApp->applicationVersion());

    if (prevVersion < currentVersion)
    {
        qDebug() << "upgrade preference version to " << qApp->applicationVersion();

        m_appSetting->setValue("applicationVersion", qApp->applicationVersion());
    }
    else if (prevVersion > currentVersion)
    {
        qDebug() << "applicationVersion is older than preference version";
    }

    m_appSetting->setValue("preferencesLocation", configLocation);

    qDebug() << "Preferences status:" << m_appSetting->status();
    qDebug() << "Preferences Location:" << configLocation;

    QString  styleType = m_appSetting->value("styleType", QString()).toString();

    if (styleType.isEmpty())
    {
        m_appSetting->setValue("styleType", 0);
    }

    applicationThemeStylesheet(static_cast<Styles::StyleType>(styleType.toInt()));

    m_appSetting->sync();
}

void  CoreService::initializeUserSettings(QString username)
{
    QString  cfgLocation = configLocation();

    qDebug() << "Required configLocation:" << cfgLocation;

    QDir  dir(cfgLocation);

    if (dir.exists())
    {
        qDebug() << "ConfigLocation exists.";
    }
    else
    {
        qDebug() << "ConfigLocation does not exists.";

        if (dir.mkpath(cfgLocation))
        {
            qDebug() << "ConfigLocation was made.";
        }
        else
        {
            qDebug() << "ConfigLocation could not be made.";
        }
    }

    m_userSetting = new Settings::UserSetting(cfgLocation);

    auto     setting  = m_userSetting->getSettings();
    QString  userName = setting->value("username", QString()).toString();

    if (userName.isEmpty())
    {
        setting->setValue("username", username);
    }

    qDebug() << "username:" << setting->value("username").toString();

    QString  profileImage = setting->value("profileImage", QString()).toString();

    if (profileImage.isEmpty())
    {
        setting->setValue("profileImage", ":/Main/user-info.svg");
    }

    qDebug() << "Profile Image:" << setting->value("profileImage").toString();

    setting->sync();
}

void  CoreService::applicationThemeStylesheet(Styles::StyleType styles)
{
    QFile  themeFile;

    switch (styles)
    {
    case 0:
        themeFile.setFileName(":/Theme/Themes/Default.qss");
        break;

    case 1:
        themeFile.setFileName(":/Theme/Themes/NeonButtons.qss");
        break;

    default:
        themeFile.setFileName(":/Theme/Themes/Default.qss");
        break;
    }

    if (!themeFile.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        themeFile.open(QFile::ReadOnly | QFile::Text);

        QTextStream  themeStream(&themeFile);

        qApp->setStyleSheet(themeStream.readAll());
    }
}

QMultiMap<QString, QAction *>  CoreService::actions() const
{
    return m_actions;
}

void  CoreService::registerWidget(QString name, DaWidgetPointer daWidget)
{
    if (!m_registeredWidget.contains(name))
    {
        m_registeredWidget.insert(name, daWidget);
    }
}

DaWidgetPointer  CoreService::widgetPointer(QString name)
{
    return m_registeredWidget.value(name, nullptr);
}

void  CoreService::configure()
{
    initializeAppSetting();
}

QString  CoreService::configLocation()
{
    return m_configLocation;
}

void  CoreService::setConfigLocation(QString username)
{
    QString  m_username;

    if (username.isEmpty())
    {
        m_username = "Unknown";
    }
    else
    {
        m_username = username;
    }

    setUsername(m_username);

    QString  configLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);

    m_configLocation = configLocation + "/" + m_username;

    initializeUserSettings(m_username);
}

void  CoreService::setWindow(Gui::WindowPlugin *window)
{
    m_windowWidget = window;
}

Gui::WindowPlugin * CoreService::window()
{
    return m_windowWidget;
}

Settings::AppSetting * CoreService::appSetting()
{
    return m_appSetting;
}

Settings::UserSetting * CoreService::userSetting()
{
    return m_userSetting;
}

void  CoreService::setCurrentUser(QVariantMap currentUser)
{
    m_currentUser = currentUser;
}

void  CoreService::setUsername(QString name)
{
    m_username = name;
}

QString  CoreService::username()
{
    return m_username;
}

QVariantMap  CoreService::currentUser()
{
    return m_currentUser;
}

void  CoreService::registerAction(QString type, QAction *act)
{
    m_actions.insert(type, act);
}
}
}
