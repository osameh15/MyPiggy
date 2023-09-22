#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QIcon>
#include <QPointer>
#include "PluginManager.h"
#include "Registry.h"
#include "BuildInfo.h"
#include "Definitions.h"

int main(int argc, char* argv[])
{
    //! Set plugins directory to system path
    QString  sysPath = qgetenv("PATH");

    sysPath.append(";plugins");
    qputenv("PATH", sysPath.toLocal8Bit());

    //!

    int  return_from_event_loop_code;

#ifdef __linux
    putenv((char *)"MESA_GL_VERSION_OVERRIDE=3.3");
#endif //LINUX

    QSettings::setDefaultFormat(QSettings::IniFormat);
    QCoreApplication::setOrganizationName(ORG_NAME);
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setApplicationVersion(BuildInfo::getVersion());

    QPointer<QApplication>  app;
    qputenv("QT_ASSUME_STDERR_HAS_CONSOLE", "1");

    app = new QApplication(argc, argv);
    app->setWindowIcon(QIcon(":/Logo/logo.ico"));

    Eagle::Registry::instance();
    Eagle::PluginManager::getInstance().loadPlugins(PLUGINS_DIR);

    return_from_event_loop_code = app->exec();

    Eagle::PluginManager::getInstance().unloadPlugins();

    delete app;

    return return_from_event_loop_code;
}
