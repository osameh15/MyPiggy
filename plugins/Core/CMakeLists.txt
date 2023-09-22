cmake_minimum_required(VERSION 3.1)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

#======================= Variables =======================#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${DIST_PLUGINS_PATH})
if (WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIST_PLUGINS_PATH})
endif()

#======================= Definitions =======================#
add_definitions(-DCORE_EXPORTS)

#======================= INCLUSION OF Qt =======================#
find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Widgets
)

#=================== INCLUSION OF Project Files ====================#
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

#=================== SETUP LIBRARY ====================#
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_JSONS} ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HDRS})

#=======================  Target includes =======================#
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${Qt6Core_INCLUDE_DIRS}
)

#===================== LINKING LIBRARIES =======================#
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    ${BASE_LINKS}
    QtOSDNotification
)
