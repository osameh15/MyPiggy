cmake_minimum_required(VERSION 3.1)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIST_PLUGINS_PATH})
if (WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIST_PLUGINS_PATH})
endif()


# Find QtCore module
find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Widgets
)

set(resource_files
        resources/resource_splash.qrc
    )

add_library(SplashScreen-qrc OBJECT EXCLUDE_FROM_ALL ${resource_files})
set_target_properties(SplashScreen-qrc  PROPERTIES AUTORCC ON)

file(GLOB_RECURSE HFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE CppFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE JsonFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/*.json)

set(${PROJECT_NAME}_HDRS
  ${HFiles}
)

set(${PROJECT_NAME}_SRCS
  ${CppFiles}
)

set(${PROJECT_NAME}_JSONS
  ${JsonFiles}
)

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_JSONS} ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HDRS})
target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:SplashScreen-qrc>)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Qt6Core_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
    ${BASE_LINKS}
)

# Copying resources.
file(GLOB ${PROJECT_NAME}_RES resources/*)
file(COPY ${${PROJECT_NAME}_RES} DESTINATION ${DIST_RESOURCES_PATH}/${PROJECT_NAME})
