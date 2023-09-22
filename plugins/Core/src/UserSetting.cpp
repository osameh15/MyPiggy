#include "UserSetting.h"

namespace Eagle
{
namespace Settings
{
UserSetting::UserSetting(QString configLocation):
    QSettings{configLocation}
{
    QString  fileName = configLocation + "/preferences.ini";

    m_settings = new QSettings(fileName, QSettings::IniFormat);
}

QSettings * UserSetting::getSettings()
{
    return m_settings;
}
}
}
