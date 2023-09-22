#include "AppSetting.h"

#include <QStandardPaths>

namespace Eagle
{
namespace Settings
{
AppSetting& AppSetting::instance()
{
    QString            configLocation = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QString            name           = configLocation + "/setting.ini";
    static AppSetting  appSetting(name);

    return appSetting;
}

AppSetting::AppSetting(const QString &fileName):
    QSettings(fileName, QSettings::IniFormat)
{
}
}
}
