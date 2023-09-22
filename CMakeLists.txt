cmake_minimum_required(VERSION 3.14)
set (CMAKE_CXX_STANDARD 20)

project(MyPiggy LANGUAGES CXX VERSION 0.9.0)

#======================= Options =======================#
option(OPTIMIZE_MODE "Compile with optimize flags" OFF)
option (EAGLE_BUILD_DOCS "Build documentation using Doxygen." OFF)

if (OPTIMIZE_MODE)
  set( CMAKE_CXX_FLAGS "-Wall -m64 -Ofast -mavx2 -march=native" )
  add_definitions(-DOPTIMIZE_MODE)
endif()

#======================= Variables =======================#
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH $ENV{QTDIR})
set(CMAKE_CXX_FLAGS "-fPIC")
set(EAGLE_VERSION ${CMAKE_PROJECT_VERSION})
set(DIST_PATH ${PROJECT_BINARY_DIR}/dist)
set(DIST_PLUGINS_PATH ${DIST_PATH}/plugins)
set(DIST_RESOURCES_PATH ${DIST_PATH}/res)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${DIST_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_CONFIGURATION_TYPES "Release;RelWithDebInfo" CACHE STRING "" FORCE)

#======================= Definitions =======================#
add_definitions(-DQT_QML_DEBUG)

#======================= INCLUSION OF Qt =======================#
find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

#======================= Versioning =======================#
include(GetGitRevisionDescription)
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
string(TIMESTAMP BUILD_TIME "%Y%m%d%H%M%S")
message ("BUILD TIME: ${BUILD_TIME}")
message ("GIT SHA1: ${GIT_SHA1}")
message ("Version: ${EAGLE_VERSION}")
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/BuildInfo.cpp.in" "${CMAKE_CURRENT_BINARY_DIR}/src/BuildInfo.cpp" @ONLY)

#======================= Git =======================#
if(NOT DEFINED  GIT_BRANCH)
execute_process(
  COMMAND git rev-parse --abbrev-ref HEAD
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_BRANCH
  OUTPUT_STRIP_TRAILING_WHITESPACE
)
endif()

# Git branch
message("This is '${GIT_BRANCH}' branch.")

if(${GIT_BRANCH} MATCHES "release/*")
    set(BINARY_REVISION "Edge")
elseif(${GIT_BRANCH} MATCHES "develop")
    set(BINARY_REVISION "Edge")
elseif(${GIT_BRANCH} MATCHES "master")
    set(BINARY_REVISION "Stable")
else()
    set(BINARY_REVISION "Unstable")
endif()

message("This is a ${BINARY_REVISION} binary revision.")

#=================== Thirdparties ====================#
add_subdirectory(thirdparties)
add_subdirectory(libs)
set(BASE_LINKS Utility PluginManager Registry)

#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_SOURCE_DIR}/forms")

file(GLOB_RECURSE HFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Plugins/*.h
)
file(GLOB_RECURSE CppFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_BINARY_DIR}/src/BuildInfo.cpp
    )
file(GLOB_RECURSE UiFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/forms/*.ui
    )

set(${PROJECT_NAME}_HDRS
  ${HFiles}
)

set(${PROJECT_NAME}_SRCS
  ${CppFiles}
  uncrustify.cfg
)

set(${PROJECT_NAME}_UIS
  ${UiFiles}
)

#=======================  Resources Library =======================#
set(RESOURCES_DIR
        res/res.qrc
    )

add_library(MyPiggy-qrc OBJECT EXCLUDE_FROM_ALL ${RESOURCES_DIR})
set_target_properties(MyPiggy-qrc  PROPERTIES AUTORCC ON)

# Copying resources.
file(GLOB ${PROJECT_NAME}_RES resources/*)
file(COPY ${${PROJECT_NAME}_RES} DESTINATION ${DIST_RESOURCES_PATH})

#=================== SETUP EXECTUABLE ====================#
# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

# Enable debug logging on RELWITHDEBINFO configuration
set_property(DIRECTORY APPEND PROPERTY COMPILE_DEFINITIONS
    $<$<CONFIG:RELWITHDEBINFO>:QT_MESSAGELOGCONTEXT>
)

if (WIN32) 
    add_executable(${PROJECT_NAME} WIN32 ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HDRS} ${${PROJECT_NAME}_UIS})
elseif(UNIX)
    add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HDRS} ${${PROJECT_NAME}_UIS})
endif()
target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:MyPiggy-qrc>)

#=======================  Target includes =======================#
include_directories(
    include
    include/Plugins
    include/Utility
    libs/PluginManager
    libs/Registry
    libs/Utility/include
    thirdparties/Qt-Advanced-Docking-System
    thirdparties/Qt-OSD-Notification
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${Qt6Core_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${FORMS_DIR})

#===================== LINKING LIBRARIES =======================#
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    PluginManager
    Registry
)

#======================= Plugins =======================#
function(DefinePlugin pluginName)
  message("Defining plugin: ${pluginName}")
  string(TOUPPER ${pluginName} upperName)
  option (PLUGIN_${upperName} "Use ${pluginName}" OFF)

  if (PLUGIN_${upperName})
    add_subdirectory(plugins/${pluginName})
    target_include_directories(${pluginName} PRIVATE
        ${Qt6Core_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/include/Plugins
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/Utility/include
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/PluginManager
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/Registry
        ${CMAKE_CURRENT_SOURCE_DIR}/libs/Utility/include)
    include_directories(
     plugins/${pluginName}/include)
    add_definitions(-DPLUGIN_${upperName})
  endif ()
endfunction()

macro(SUBDIRLIST result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

SUBDIRLIST(PLUGINS ${CMAKE_CURRENT_SOURCE_DIR}/plugins)

foreach(p ${PLUGINS})
  DefinePlugin(${p})
endforeach()

# Cleaning all previously built plugins.
file(REMOVE_RECURSE ${DIST_PLUGINS_PATH})
file(REMOVE_RECURSE ${DIST_PLUGINS_PATH}/..)

# Install binary targets
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
