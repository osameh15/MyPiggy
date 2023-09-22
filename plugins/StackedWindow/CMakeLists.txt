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
add_definitions(-DSTACKEDWINDOW_EXPORTS)

#======================= INCLUSION OF Qt =======================#
find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Widgets
    SvgWidgets
)

#=======================  Resources Library =======================#
set(resource_files
        resources/resource_stacked.qrc
    )

add_library(StackedWindow-qrc OBJECT EXCLUDE_FROM_ALL ${resource_files})
set_target_properties(StackedWindow-qrc  PROPERTIES AUTORCC ON)

# Copying resources.
file(GLOB ${PROJECT_NAME}_RES resources/*)
file(COPY ${${PROJECT_NAME}_RES} DESTINATION ${DIST_RESOURCES_PATH}/${PROJECT_NAME})

#=================== INCLUSION OF Project Files ====================#
set(FORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/forms")

file(GLOB_RECURSE HFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE CppFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE UiFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/forms/*.ui)
file(GLOB_RECURSE JsonFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/*.json)

set(${PROJECT_NAME}_HDRS
  ${HFiles}
)

set(${PROJECT_NAME}_SRCS
  ${CppFiles}
)

set(${PROJECT_NAME}_UIS
  ${UiFiles}
)

set(${PROJECT_NAME}_JSONS
  ${JsonFiles}
)

source_group("UI Files" FILES ${${PROJECT_NAME}_UIS})

#=================== SETUP LIBRARY ====================#
# Add the forms directory to the AUTOUIC search paths
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_AUTOUIC_SEARCH_PATHS} ${FORMS_DIR})

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_JSONS} ${${PROJECT_NAME}_SRCS} ${${PROJECT_NAME}_HDRS} ${${PROJECT_NAME}_UIS})
target_sources(${PROJECT_NAME} PRIVATE $<TARGET_OBJECTS:StackedWindow-qrc>)

#=======================  Target includes =======================#
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${FORMS_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../TreeStructure/include
    ${Qt6Core_INCLUDE_DIRS}
    ${Qt6Widgets_INCLUDE_DIRS}
)

#===================== LINKING LIBRARIES =======================#
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    Qt6::SvgWidgets
    ${BASE_LINKS}
)
