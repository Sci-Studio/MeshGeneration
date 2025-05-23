cmake_minimum_required(VERSION 3.5)

project(MeshGeneration VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SHADER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/basic.vert")
set(DEST_DIR "${CMAKE_CURRENT_BINARY_DIR}")

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Gui OpenGL OpenGLWidgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Gui OpenGL OpenGLWidgets REQUIRED)
find_package(OpenGL REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        renderwidget.cpp
        renderwidget.h
        renderer.cpp
        renderer.h
        vertexbuffer.cpp
        vertexbuffer.h
        indexbuffer.cpp
        indexbuffer.h
        vertexarray.cpp
        vertexarray.h
        vertexbufferlayout.cpp
        vertexbufferlayout.h
        shader.h
        shader.cpp
        shapes/shape.h
        shapes/rectangle.cpp
        shapes/rectangle.h
        shapes/line.cpp
        shapes/line.h
        shapes/point.cpp
        shapes/point.h
        shapes/curve.cpp
        shapes/curve.h
        shapes/triangles.cpp
        shapes/triangles.h
        parser/objparser.cpp
        parser/objparser.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MeshGeneration
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MeshGeneration APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MeshGeneration SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MeshGeneration
            ${PROJECT_SOURCES}
        )
    endif()
endif()

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${SHADER_FILE}"
            "${DEST_DIR}/"
        COMMENT "Copying shader files to build directory..."
)

target_link_libraries(MeshGeneration
    PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::OpenGL
    Qt${QT_VERSION_MAJOR}::OpenGLWidgets
    OpenGL::GLU)

# Specify precompiled headers
target_precompile_headers(MeshGeneration PRIVATE pch.h)

set_target_properties(MeshGeneration PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MeshGeneration)
endif()
