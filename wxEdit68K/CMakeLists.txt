cmake_minimum_required(VERSION 3.20)
project(wxEdit68K)
include_directories(include)
file(GLOB SOURCE_FILES src/*.cpp)

set(PLATFORM "")
if (WIN32)
    set(PLATFORM "WIN32")
endif()

add_executable(wxEdit68K ${PLATFORM} ${SOURCE_FILES})

# reach a consensus with wxEASy68K devs on where wxWidgets' root dir will be
# located on a Windows system
# - C:/wxWidgets-3.1.5 is what the upstream installer chooses by default
if (WIN32)
    set(wxWidgets_ROOT_DIR C:/wxWidgets-3.1.5)
endif()

find_package(wxWidgets REQUIRED COMPONENTS base core xml html richtext aui xrc)
if (wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    target_link_libraries(wxEdit68K ${wxWidgets_LIBRARIES})
endif()

# set DPI awareness to Per Monitor V2 in Visual Studio generator
if (CMAKE_GENERATOR MATCHES "Visual Studio")
    set_property(TARGET wxEdit68K PROPERTY VS_DPI_AWARE "PerMonitor")
endif()

set(CMAKE_BUILD_TYPE Debug)
