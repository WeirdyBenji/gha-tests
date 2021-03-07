cmake_minimum_required(VERSION 3.18)
set(PROJECT_NAME WZIA)
set(PROJECT_VERSION "1.0.0")
set(CMAKE_CXX_STANDARD 14)

add_definitions(-DQT_NO_DEBUG_OUTPUT)

project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Network REQUIRED)

add_library(HTTPModule SHARED ${CMAKE_SOURCE_DIR}/src/ModuleHTTP.cpp ${CMAKE_SOURCE_DIR}/src/Request.cpp ${CMAKE_SOURCE_DIR}/src/Response.cpp ${CMAKE_SOURCE_DIR}/src/Client.cpp ${CMAKE_SOURCE_DIR}/src/Mediator.cpp)
target_link_libraries(HTTPModule PRIVATE Qt5::Widgets Qt5::Network)
target_compile_options(HTTPModule PRIVATE ${COMPILE_OPTIONS})

add_executable(${PROJECT_NAME})

set(MYCOMPILER c_${CMAKE_CXX_COMPILER_ID})
if (${MYCOMPILER} MATCHES "GNU")
    message(STATUS "Setting G++ flags")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -fPIC)
elseif (${MYCOMPILER} MATCHES "MSVC")
    message (STATUS "Setting VS flags")
    target_compile_options(${PROJECT_NAME} PRIVATE /EHsc /W2 /c)
else()
    message(WARNING "DTC !")
endif()

target_include_directories(${PROJECT_NAME}
PUBLIC
    ${CMAKE_SOURCE_DIR}/include/
PRIVATE
    ${CMAKE_SOURCE_DIR}/src/
)

target_sources(${PROJECT_NAME}
PUBLIC
PRIVATE
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/ZIApplication.cpp
    ${CMAKE_SOURCE_DIR}/src/ZIApplication.hpp
    ${CMAKE_SOURCE_DIR}/src/ZServer.cpp
    ${CMAKE_SOURCE_DIR}/src/ZServer.hpp
    ${CMAKE_SOURCE_DIR}/src/IModule.hpp
    ${CMAKE_SOURCE_DIR}/src/ModuleLoader.cpp
    ${CMAKE_SOURCE_DIR}/src/ModuleLoader.hpp
    ${CMAKE_SOURCE_DIR}/src/Mediator.cpp
    ${CMAKE_SOURCE_DIR}/src/Mediator.hpp
    ${CMAKE_SOURCE_DIR}/src/Client.cpp
    ${CMAKE_SOURCE_DIR}/src/Client.hpp
)
find_package(Qt5 COMPONENTS Core Network REQUIRED)
target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Network
)