
cmake_minimum_required(VERSION 3.6)

project(diva)

# init_qt: Let's do the CMake job for us

set(CMAKE_AUTOMOC ON) # For meta object compiler
set(CMAKE_AUTORCC ON) # Resource files
set(CMAKE_AUTOUIC ON) # UI files

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
include_directories( ${CMAKE_CURRENT_BINARY_DIR} )


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find the QtWidgets library
set( QTDIR $ENV{QTDIR} )
set( CMAKE_PREFIX_PATH ${QTDIR} )
find_package(Qt5 REQUIRED Widgets)
ADD_DEFINITIONS (${QT_DEFINITIONS})

set( VTK_DIR "$ENV{PCL_ROOT}/3rdParty/VTK" )
find_package(VTK REQUIRED)
find_package(PCL 1.8.1 REQUIRED)

find_package(Qt5X11Extras ${QT_MIN_VERSION} CONFIG)
find_package(Qt5OpenGL)
find_package(Qt5 REQUIRED COMPONENTS Core Gui Sql Network PrintSupport WebEngineWidgets)
find_package(Qt5OpenGLExtensions)


include_directories(${PCL_INCLUDE_DIRS})
link_directories( ${PCL_LIBRARY_DIRS} )
add_definitions(${PCL_DEFINITIONS})

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS}) 
 
pkg_check_modules (GTK2 REQUIRED gtk+-2.0)
include_directories (${GTK2_INCLUDE_DIRS})
link_directories (${GTK2_LIBRARY_DIRS})
add_definitions (${GTK2_CFLAGS_OTHER})


find_library(MSCL_LIB_PATH NAMES libmscl.so PATHS "/usr/share/c++-mscl" DOC "MSCL Library" NO_DEFAULT_PATH)
find_library(BOOST_LIB_PATH NAMES libboost_chrono.so PATHS "/usr/share/c++-mscl/Boost/lib" NO_DEFAULT_PATH)
set(MSCL_INC_PATH "/usr/share/c++-mscl/source")
set(BOOST_INC_PATH "/usr/share/c++-mscl/Boost/include")
#find_path(MSCL_INC_PATH NAMES mscl.h PATHS "/usr/share/c++-mscl/source/mscl" DOC "MSCL Includes" NO_DEFAULT_PATH)
set(MSCL_LIB "/usr/share/c++-mscl")
add_definitions(-std=c++11)
include_directories(/usr/share/c++-mscl/source /usr/share/c++-mscl/Boost/include /usr/include)
link_directories(/usr/share/c++-mscl)
link_libraries(mscl pthread GL GLU glut GLEW glfw X11 Xxf86vm Xrandr pthread Xi dl Xinerama Xcursor m)


set(project_SOURCES main.cpp mainwindow.cpp camthread.cpp glwidget.cpp gpsthread.cpp)

add_executable(${PROJECT_NAME} ${project_SOURCES} ${MSCL_INC_PATH} ${MSCL_LIB} ${MSCL_INC})

target_link_libraries(${PROJECT_NAME} ${PCL_LIBRARIES} ${VTK_LIBRARIES} ${JSONCPP_LIBRARIES} ${OpenCV_LIBS} ${GTK2_LIBRARIES}
${OPENGL_LIBRARIES} ${GLUT_LIBRARY} 

	Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Sql
        Qt5::PrintSupport
 	Qt5::Network
        Qt5::WebEngineWidgets
	Qt5::OpenGL
	/usr/share/c++-mscl/libmscl.so
	GL
	GLU
	glut
)


include( ${VTK_USE_FILE} )
