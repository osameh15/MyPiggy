#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QObject>
#include <QPair>

static constexpr auto  ORG_NAME     = "Haya";
static constexpr auto  APP_NAME     = "My Piggy";
static constexpr auto  PLUGINS_DIR  = "plugins";
static constexpr auto  RESTART_CODE = 1998;

/// Status bar static strings
#define WELOCME "Welcome to My Piggy -v 0.9"
#define WELCOME_TIMEOUT 10000

/// Menu title bar static strings
#define HOME_MENU "Home"
#define TOOLS_MENU "Tools"
#define VIEW_MENU "View"
#define WINDOW_MENU "Window"
#define REPORTS_MENU "Reports"
#define HELP_MENU "Help"

namespace Eagle
{
namespace Styles
{
enum StyleType
{
    Default,
    NeonButtons,
    Light,
    Dark,
    BreezeLight,
    BreezeDark,
    MaterialDark,
    ElegantDark,
    Amoled,
    Indigo,
    MaterialBlue
};
}

namespace Notify
{
enum NotificationType : int
{
    Information = 0,
    Warning,
    Critical
};
}

namespace Stacked
{
enum class StackedWidgets
{
    Login = 0,
    Projects,
    TreeStructure,
    MainWindow
};
}

namespace Menu
{
enum class TitleBar
{
    Home = 0,
    View,
    Tools,
    Reports,
    Windows,
    Help
};
}
}

#endif // DEFINITIONS_H
