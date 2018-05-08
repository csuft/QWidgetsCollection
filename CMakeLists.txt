CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
project(QWidgetsCollection C CXX)

if (APPLE)
message(STATUS "Configuring Qt Widgets Collection for macOS...")
elseif (WIN32)
message(STATUS "Configuring Qt Widgets Collection for Windows...")
endif(APPLE)
################################################################
# Global constants
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION_INFO "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

################################################################
# Output project information
message(STATUS "Qt Widgets Collection Source Path: ${PROJECT_SOURCE_DIR}")
message(STATUS "Qt Widgets Collection Binary Path: ${PROJECT_BINARY_DIR}")

################################################################
# sub projects
add_subdirectory(CustomDialog)
add_subdirectory(CustomTableView) 
add_subdirectory(Dockwidgets)
add_subdirectory(FlowLayout)
add_subdirectory(OpenGLWidget)
add_subdirectory(OverlayWidget)
add_subdirectory(RubberBand)