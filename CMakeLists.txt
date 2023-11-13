cmake_minimum_required(VERSION 3.16)
project(Kirigami64)
set(PROJECT_VERSION "0.3.0")
set(PROJECT_VERSION_SUBTITLE "idk")

configure_file("src/config.in.hpp" "src/config.hpp")

set(KF_MIN_VERSION "5.68.0")
set(QT_MIN_VERSION "5.14.0")

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPoQmTools)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX KIRIGAMI64
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/config-Kirigami64.hpp"
)

find_package(Qt5 ${QT_MIN_VERSION} REQUIRED NO_MODULE COMPONENTS Core Quick Gui QuickControls2 Widgets)
find_package(KF5 ${KF_MIN_VERSION} REQUIRED COMPONENTS Kirigami2 I18n CoreAddons)
find_library(git2 NAME git2 REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
