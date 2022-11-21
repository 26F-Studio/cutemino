cmake_minimum_required(VERSION 3.16)

if (CMAKE_PREFIX_PATH)
    set(QT_BINARY_DIR ${CMAKE_PREFIX_PATH}/../../bin)
endif ()
if (CMAKE_BUILD_TYPE MATCHES "Debug")
    set(CMAKE_CXX_FLAGS_INIT -DQT_QML_DEBUG)
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

message(STATUS "C++ standard set to ${CMAKE_CXX_STANDARD}")

project(cutemino VERSION 0.0.1 LANGUAGES CXX)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(STATUS "Compiler is Clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    message(STATUS "Compiler is GCC")
    add_compile_options(-Wno-volatile)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    message(STATUS "Compiler is Intel C++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(STATUS "Compiler is Visual Studio C++")
    add_compile_options(/MP /utf-8)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS NOMINMAX)
endif ()

find_package(cryptopp CONFIG REQUIRED)
find_package(magic_enum CONFIG REQUIRED)
find_package(Qt6 COMPONENTS Core Quick REQUIRED)

qt_add_executable(
        ${PROJECT_NAME}
        views.qrc
        main.cpp
)

qt_add_qml_module(
        ${PROJECT_NAME}
        URI ${PROJECT_NAME}
        VERSION 1.0
        QML_FILES
        main.qml
        RESOURCES
        assets.qrc
)

aux_source_directory(controllers CTRL_SRC)
aux_source_directory(models MODEL_SRC)
aux_source_directory(types TYPE_SRC)

target_sources(
        ${PROJECT_NAME}
        PRIVATE
        ${CTRL_SRC}
        ${MODEL_SRC}
        ${TYPE_SRC}
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE
        cryptopp::cryptopp
        magic_enum::magic_enum
        Qt6::Core
        Qt6::Quick
)

set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER ${PROJECT_NAME}.studio26f.org
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

if (WIN32)
    if (QT_BINARY_DIR)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${QT_BINARY_DIR}/windeployqt.exe
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endif ()
endif ()

install(TARGETS ${PROJECT_NAME}
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
