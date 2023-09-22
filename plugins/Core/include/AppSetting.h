#ifndef APPSETTING_H
#define APPSETTING_H

/**
 * Copyright (c) Gubras, Inc.
 *
 * @brief AppSetting class. Main app settings like change theme.
 *
 * @author Eagle_Ir
 * @date Sep 2023
 */

#include <QSettings>

#if defined (Q_OS_WIN)
#ifdef CORE_EXPORTS
#define APPSETTING_API Q_DECL_EXPORT
#else
#define APPSETTING_API Q_DECL_IMPORT
#endif
#elif defined (Q_OS_LINUX)
#define APPSETTING_API
#endif


namespace Eagle
{
namespace Settings
{
/**
 * @brief The AppSetting class: Main app setting
 */
class APPSETTING_API AppSetting: public QSettings
{
public:
    /**
     * @brief instance: Singleton object from application setting
     * @return
     */
    static AppSetting& instance();

private:
    /**
     * @brief AppSetting: Constructor
     * @param fileName: file name string
     */
    AppSetting(const QString &fileName);
};
}
}
#endif // APPSETTING_H
