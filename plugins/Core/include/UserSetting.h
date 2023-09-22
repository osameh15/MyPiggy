#ifndef USERSETTING_H
#define USERSETTING_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief UserSetting class.  User settings like set event values
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include <QSettings>

#if defined (Q_OS_WIN)
#ifdef CORE_EXPORTS
#define  USERSETTING_API Q_DECL_EXPORT
#else
#define USERSETTING_API Q_DECL_IMPORT
#endif
#elif defined (Q_OS_LINUX)
#define USERSETTING_API
#endif


namespace Eagle
{
namespace Settings
{
/**
 * @brief The UserSetting class: user setting saved data for each user
 */
class USERSETTING_API UserSetting: public QSettings
{
public:
    /**
     * @brief UserSetting: Constructor
     * @param configLocation: User config location
     */
    explicit UserSetting(QString configLocation);

    /**
     * @brief getSettings: Get setting file
     * @return
     */
    QSettings* getSettings();

private:
    QSettings *m_settings;
};
}
}
#endif // USERSETTING_H
