cmake_minimum_required(VERSION 3.2)
project(QtOSDNotification)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Find QtCore module
find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS
    Core
)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set (${PROJECT_NAME}_SRCS
        qabstractosdnotification.cpp
        qosdnotification.cpp
        qosdnotificationclosebutton.cpp
        qosdnotificationmanager.cpp
        )

set (${PROJECT_NAME}_HDRS
        qabstractosdnotification_p.h
        qabstractosdnotification.h
        qosdnotification_global.h
        qosdnotification_p.h
        qosdnotification.h
        qosdnotificationclosebutton_p.h
        qosdnotificationclosebutton.h
        qosdnotificationmanager_p.h
        qosdnotificationmanager.h
        )

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HDRS})

target_link_libraries(${PROJECT_NAME}
    Qt6::Widgets
)


