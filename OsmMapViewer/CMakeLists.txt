cmake_minimum_required(VERSION 3.17)
project(OsmMapViewer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
        Network
)

qt_standard_project_setup()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_executable(OsmMapViewer
    MainWindow.ui
    MainWindow.cpp
    MainWindow.h
    OsmMapViewer.h
    OsmMapViewer.cpp
    # resources.qrc
)

target_link_libraries(OsmMapViewer
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
        Qt6::Network
        Qt6::Widgets
)

target_link_libraries(OsmMapViewer PRIVATE Qt6::Widgets)

find_package(LibXml2 REQUIRED)
target_link_libraries(OsmMapViewer PRIVATE LibXml2::LibXml2)

find_package(mapnik REQUIRED)
target_link_libraries(OsmMapViewer PRIVATE mapnik::mapnik)

mapnik_find_plugin_dir(MAPNIK_PLUGIN_DIR)

