CMAKE_MINIMUM_REQUIRED(VERSION 3.8)
PROJECT(CustomWidgets C CXX)

#############################################################################
# Compiler and linker options
ADD_DEFINITIONS(-Wall -DWIN32_LEAN_AND_MEAN)
IF(CMAKE_BUILD_TYPE STREQUAL Release)
  ADD_DEFINITIONS(-DNDEBUG)
ENDIF()

SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTORCC ON) 
SET(CMAKE_CXX_STANDARD 11) 

FILE(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*") 
FILE(GLOB FORMS "${CMAKE_CURRENT_SOURCE_DIR}/form/*") 
 
SET(RESOURCES  
  ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.qrc)  
  
  
#################################################################################
# EXTERNAL LIBS
FIND_PACKAGE(Qt5 COMPONENTS Core Widgets Gui REQUIRED) 
qt5_wrap_ui(UI_HEADERS ${FORMS})

INCLUDE_DIRECTORIES(
${CMAKE_CURRENT_BINARY_DIR}/)

################################################################################
# Compile target
ADD_EXECUTABLE ( ${PROJECT_NAME} 
				${SOURCE_FILES} 
				${UI_HEADERS}  
				${RESOURCES})
SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES VS_USER_PROPS "${CMAKE_CURRENT_SOURCE_DIR}/Shared.props")
# https://www.kdab.com/using-cmake-with-qt-5/
qt5_use_modules(${PROJECT_NAME} Core Widgets Gui)  