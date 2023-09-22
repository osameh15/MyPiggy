#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QObject>
#include <QPair>

static constexpr auto  ORG_NAME               = "Haya";
static constexpr auto  APP_NAME               = "My Piggy";
static constexpr auto  PLUGINS_DIR            = "plugins";
static constexpr auto  RESTART_CODE = 1998;

/// Project and tree static string
#define ID_ROLE 998

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

/// Home menu static strings
#define LABEL_SOUND "Sound"
#define MUTE "Mute"
#define MUTE_TOOLTIP "Mute (Ctrl+M)"
#define LABEL_WORKSPACE "Workspace"
#define CURSOR "Cursor"
#define CURSOR_TOOLTIP "Cursor Mode"
#define DRAG "Drag"
#define DRAG_TOOLTIP "Drag Mode"
#define WORKSPACE_FIXED_SIZE 60
#define ADD_WORKSPACE "Add Workspace"
#define WORKSPACE_TOOLTIP "New Workspace (Ctrl+N)"
#define LABEL_VIEW_MODEL "View Model"
#define VIEW_2D "View 2D"
#define VIEW_2D_TOOLTIP "Model 2D"
#define VIEW_3D "View 3D"
#define VIEW_3D_TOOLTIP "Model 3D"
#define LABEL_CHARTS "Charts"
#define ONLINE_CHARTS "Online Charts"
#define ONLINE_CHARTS_TOOLTIP "Online Chart"
#define PV_CHARTS "PV Charts"
#define PV_CHARTS_TOOLTIP "PV Chart"
#define TREND_CHARTS "Trend Charts"
#define TREND_CHARTS_TOOLTIP "Trend Charts"
#define TREND_2D_CHARTS "2D Trend"
#define TREND_2D_CHARTS_TOOLTIP tr("2D Trend Data")
#define TREND_3D_CHARTS "3D Trend"
#define TREND_3D_CHARTS_TOOLTIP "3D Trend Data"
#define TREND_FIXED_SIZE 100
#define SET_THRESHOLDS "Set Thresholds"
#define SET_THRESHOLDS_TOOLTIP "Set Thresholds"
#define LABEL_GAUGE "Gauges"
#define GAUGE "Gauge"
#define GAUGE_TOOLTIP "Gauge"
#define LABEL_SNAPS "Snaps"
#define FREEZE "Freeze"
#define FREEZE_TOOLTIP "Freeze Snapshots"
#define COMPARE "Compare"
#define COMPARE_TOOLTIP "Compare Snapshots"
#define COMPARE_FIXED_SIZE 200
#define COMPARE_FULL "With Frozen Data"
#define COMPARE_IMPORT "Import Frozen Data"
#define COMPARE_SUMMARIES "With Minutely Summaries"
#define LABEL_LOGS "Logs"
#define LOG_VIEWER "Log Viewer"
#define LOG_VIEWER_TOOLTIP "Log Viewer"
#define LABEL_TEMPLATE "Template Label"
#define TEMPLATE "Template"
#define ADD_STATUS_BAR "Add To Status Bar"

/// Tools menu static strings
#define LABEL_SETTINGS "Settings"
#define UPDATE "Update"
#define UPDATE_TOOLTIP "Update Visage ..."
#define OPTIONS "Options"
#define OPTIONS_TOOLTIP "Visage Settings (Ctrl+,)"
#define LABEL_EVENTS "Events"
#define EVENTS_INFO "Events Info"
#define EVENTS_INFO_TOOLTIP "Display Auto Events"
#define EVENT_MANAGER "Event Manager"
#define EVENT_MANAGER_TOOLTIP "Display Manual Events"
#define SCHEDULER "Scheduler"
#define SCHEDULER_TOOLTIP "Scheduler Events"
#define LABEL_REPLAY "Replay"
#define RECORD "Record"
#define RECORD_TOOLTIP "Record"
#define AUTO_RECORD_TOOLTIP "Auto Record Is On"
#define STOP "Stop"
#define STOP_TOOLTIP "Stop"
#define REPLAY "Replay"
#define REPLAY_TOOLTIP "Replay"
#define LIVE_STATUS_WIDTH 90
#define REPLAY_STATUS_WIDTH 120
#define SESSION "Sessions"
#define SESSION_TOOLTIP "Sessions"
#define LABEL_SAMPLES "Samples"
#define EXPORT_SAMPLES "Export Samples"
#define EXPORT_SAMPLES_TOOLTIP "Export Samples Data"
#define LABEL_RULE_BUILDER "Rule Builder"
#define RULE_BUILDER "Rule Builder"

/// View menu static strings
#define LABEL_LAYOUTS "Layouts"
#define MACHINE_TREE "Machine Tree"
#define MACHINE_TREE_TOOLTIP "Show/Hide Machine Tree"
#define SYSTEM_LOGS "System Logs"
#define SYSTEM_LOGS_TOOLTIP "Show/Hide System Logs"
#define STATUS_BAR "Status Bar"
#define STATUS_BAR_TOOLTIP "Show/Hide Status Bar"
#define VIEW_FIXED_SIZE 100
#define LABEL_SCREENS "Screen"
#define RESET_LAYOUT "Reset Layout"
#define RESET_LAYOUT_TOOLTIP "Reset Visage Layout (F9)"
#define FULL_SCREEN "Full Screen"
#define FULL_SCREEN_TOOLTIP "Full Screen Mode (F10)"

/// Window menu static strings
#define LABEL_ARRANGEMENTS "Arrangement"
#define ARRANGE_VERTICALLY "Arrange Docks Vertically"
#define ARRANGE_VERTICALLY_TOOLTIP "Arrange Docks Vertically (F6)"
#define ARRANGE_HORIZONTALLY "Arrange Docks Horizontally"
#define ARRANGE_HORIZONTALLY_TOOLTIP "Arrange Docks Horizontally (F7)"
#define ARRANGE_GRID "Arrange Docks In Grid"
#define ARRANGE_GRID_TOOLTIP "Arrange Docks In Grid (F8)"
#define LABEL_MANAGEMENT "Management"
#define WINDOW_MANAGER "Workspace Manager"
#define WINDOW_MANAGER_TOOLTIP "Show/Hide/Delete Workspaces"

/// Reports menu static strings
#define LABEL_GENERATION "Generation"
#define REPORT_GENERATOR "Report Generator"
#define REPORT_GENERATOR_TOOLTIP "Generate Data Report"
#define LABEL_LOGS "Logs"
#define LOGBOOK "Logbook"
#define LOGBOOK_TOOLTIP "Logbook"
#define LABEL_ANALYSIS "Analysis"
#define ECONOMICAL_STATISTICS "Economical Statistics"
#define ECONOMICAL_STATISTICS_TOOLTIP "Economical Statistics"
#define DATA_ANALYSIS "Data Analysis"
#define DATA_ANALYSIS_TOOLTIP "Data Analysis"
#define OPERATIONAL_STATISTICS "Operational Statistics"
#define OPERATIONAL_STATISTICS_TOOLTIP "Operational Statistics"

/// Help menu static strings
#define LABEL_GUBRAS_PRODUCT "Gubras Product"
#define ABOUT "About"
#define ABOUT_TOOLTIP "About Visage"
#define HELP_TOPIC "Help Topics"
#define HELP_TOPIC_TOOLTIP "User Manual (F1)"

/// Preferences definitions. Preferences default value are define here.
/// Define limits and sizes
#define DEFAULT_HOST_IP                   "174.138.7.79:3003"
#define DEFAULT_THEME_STYLE               datall::appstyle::BaseStyle::Dark
#define DEFAULT_LOG_PAGING                true
#define DEFAULT_LOG_PAGE_SIZE             "10"
#define DEFAULT_MAXIMUM_LOG_SIZE          "200"
#define DEFAULT_NOTIF_EVENTS              false
#define DEFAULT_MAXIMUM_SCHEDULER_SIZE    "20"
#define DEFAULT_MAXIMUM_EVENT_SIZE        "200"

/// System Logs definitions.
//////Define limits and sizes
 #define MAXIMUM_LOG_SIZE          200

/// Threshold definitions
#define CONSTANT            1
#define SEGMENTED           18

#define KEY_CRITICAL_LOWER  "cl"
#define KEY_CRITICAL_UPPPER "cu"
#define KEY_WARNING_LOWER   "wl"
#define KEY_WARNING_UPPER   "wu"

#define KEY_CRITICAL_LOWER_NAME  "Critical Lower"
#define KEY_CRITICAL_UPPPER_NAME "Critical Upper"
#define KEY_WARNING_LOWER_NAME   "Warning Lower"
#define KEY_WARNING_UPPER_NAME   "Warning Upper"

/// User manual
const qreal zoomMultiplier = qSqrt(1.5);
const qreal  zoomInit = 1;

namespace Datall
{
enum DataMode
{
    Online,
    Offline
};

enum RecordStatus
{
    NoRecording = 0,
    Manual,
    Auto
};

namespace Dashboard
{
enum class NetworkStatus
{
    Connected = 0,
    Disconnected,
    Unknown
};

enum class SensorActivity
{
    Active = 0,
    Deactive,
    Unknown
};

enum class StreamMode
{
    Online = 0,
    Only,
    Full,
    Default
};
}

namespace Replay
{
enum ReplayStatus
{
    Live = 0,
    Replay
};

enum ReplayMode
{
    Only = 1,
    Full = 2
};

enum ReplayProgressStatus
{
    Started = 0,
    Playing,
    Finished,
    Pause,
    Resume
};
}

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

namespace Product
{
enum class Zoom
{
    FitPage = 0,
    FitWidth,
    Custom
};
}

typedef QPair<QString, QObject *> InvokeCall;

namespace Connection
{
enum class ConnectionColumnType
{
    Name = 0,
    Type,
    Protocol,
    Address,
    Port
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

enum class HomeMenuBar
{
    Mute = 0,
    Cursor,
    Drag,
    AddWorkspace,
    _3DModel,
    _2DModel,
    OnlineCharts,
    TrendCharts2D,
    TrendCharts3D,
    PvCharts,
    SetThresholds,
    Gauge,
    Freeze,
    Compare,
    LogViewer,
    Template
};

enum class ToolsMenuBar
{
    Update = 20,
    Options,
    AddComponent,
    EditComponent,
    EventsInfo,
    EventManager,
    Scheduler,
    Record,
    Reply,
    Session,
    ExportSamples,
    RuleBuilder
};

enum class ViewMenuBar
{
    MachineTree = 30,
    SystemLogs,
    StatusBar,
    ResetLayout,
    FullScreen
};

enum class WindowsMenuBar
{
    ArrangeDocksVertically = 40,
    ArrangeDocksHorizontally,
    ArrangeDocksGrid,
    WindowManager
};

enum class ReportsMenuBar
{
    ReportGenerator = 50,
    LogBook,
    EconomicalStatistics,
    DataAnalysis,
    OperationalStatistics
};

enum class HelpMenuBar
{
    About = 60,
    HelpTopic
};
}
namespace Preference
{
enum class TabItem
{
    General = 0,
    SystemLog,
    Events
};
}

namespace Logs
{
enum class LogFilterMode
{
    Message  = 0x0001,
    Alert    = 0x0002,
    Error    = 0x0004,
    Network  = 0x0008,
    NoFilter = 0x0016
};

enum class ColumnType
{
    Id = 0,
    TimeStamp,
    LogType,
    Message,
    Source
};

enum class LogType
{
    Healthy = 0,
    Warning,
    Critical,
    Network
};
}
namespace Events
{
enum class BoardStatus
{
    BoardDisables                      = 0,
    BoardConnected                     = 1,
    BoardWarningNotSetParameter        = 2,
    BoardErrorSignalOverRange          = 4,
    BoardErrorSignalUnderRange         = 8,
    BoardErrorBreakInSensorLine        = 16,
    BoardErrorShortCircuitInSensorLine = 32,
    BoardErrorUnknown                  = 4096,
    BoardUnknown
};

enum class AlertIndex
{
    AlertSystem = 0,
    AlertEvent,
    AlertSession
};

enum class AlertSeverity
{
    AlertNeutral = 0,
    AlertWarning,
    AlertCritical
};

enum AlertSystemType
{
    AlertServerDown = 0,
    AlertServerUp,
};

enum class LogType
{
    LogEvent = 0,
    LogSession,
    LogSystem,
    LogMonitoring
};

enum class SessionLogType
{
    Insert = 0,
    Remove,
    Update,
    Patch,
};

enum class SystemLogType
{
    WrongHID = 0,
    Gap
};

/** Events Type */
enum class EventType
{
    MeasurementThresholdZone = 0,
    PerformanceParameterThresholdZone,
    SensorSignalQuality,
    UserAction,
    ModelChanges,
    PredefinedTime,
    Duration,
    CycleCount,
    Maintenance,
    EquipmentStart,
    EquipmentShutdown,
    SensorAvailability,
    BoardAvailability,
    UserRequest
};

/** Events Thresholds */
enum class ThresholdsZone
{
    Healthy = 0,
    Warning,
    Critical,
};

/** Events Sensor Status */
enum class SensorStatus
{
    Ok           = 0,
    Idle         = 1,
    Disconnected = 2,
    Unknown      = 4
};

/** Events Sensor qualities */
enum class Qualities
{
    Zero = 0,
    One,
    Two,
};

/** Events User role */
enum class UserRole
{
    Admin = 0,
    Designer,
    Monitor,
    Tester,
    Guest,
};

/** User Actions*/
enum class UserAction
{
    Login = 0,
    Logout
};

/** Event recurring type */
enum class RecurringType
{
    Days = 0,
    Weeks,
    Months
};

/** Event Predefined time*/
enum class PredefinedTimeType
{
    Recurring = 0,
    Single
};

/** Event Cycle Count*/
enum class CycleCountType
{
    Single = 0,
    Recurring
};

/** Event Actions*/
enum class Actions
{
    NoAction = 0,
    Sampling,
    Snapshot,
    SummaryCalculation,
    ExportSampling
};

enum class ModelChangesType
{
    TreeCreated = 0,
    TreeDeleted,
    ComponentAdded,
    ComponentDeleted,
    MeasurementAdded,
    MeasurementRemoved,
    PerformanceParameterAdded,
    PerformanceParameterRemoved,
    PropertyValueChange,
    CallibrationParameterChange,
    ThresholdChange
};

enum class FilterMode
{
    MeasurementThresholdZone = 0,
    PerformanceParameterThresholdZone,
    SensorSignalQuality,
    UserAction,
    ModelChanges,
    PredefinedTime,
    Duration,
    CycleCount,
    Maintenance,
    EquipmentStart,
    EquipmentShutdown,
    NoFilter
};

enum class SchedulerColumnType
{
    TriggerType = 0,
    Condition,
    Action,
    LastPerformed,
    Delete
};

enum class EventManagerColumnType
{
    Type = 0,
    Timestamp,
    Characteristic,
    Message,
    Action
};

enum class AutoEventsColumnType
{
    TriggerType = 0,
    Condition,
    Action
};
}
namespace Reports
{
enum class ReportTemplateType
{
    Trend = 0,
    Model,
    EventLog,
    ScreenShot
};

enum class DateType
{
    LastDay = 0,
    LastWeek,
    LastMonth
};

enum class ReportTemplateColumnType
{
    Id = 0,
    ItemType,
    Detail,
    Delete
};
}

namespace Compare
{
enum class CompareMode
{
    Snapshots = 0,
    Summaries
};
}
}

#endif // DEFINITIONS_H
