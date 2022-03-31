
cmake_minimum_required(VERSION 3.16)

project(kcm_openrc)

set(QT_MIN_VERSION "5.15.0")
set(KF5_MIN_VERSION "5.88.0")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(ECM ${KF5_MIN_VERSION} REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)
set(GENERATE_MOC ON)


find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Quick
    Svg
    DBus
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    KCMUtils
    Declarative
    Config
    ConfigWidgets
    Auth
)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDEFrameworkCompilerSettings NO_POLICY_SCOPE)
include(FeatureSummary)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(openrc_kcm_SRCS openrc_kcm.cpp)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)


kconfig_add_kcfg_files(openrc_kcm_SRCS GENERATE_MOC openrckcmsettings.kcfgc)

add_library(kcm_openrc MODULE ${openrc_kcm_SRCS})
add_executable(openrc-actions-kauth openrc_actions.cpp)
target_link_libraries(openrc-actions-kauth
    Qt5::Core
    Qt5::DBus
    KF5::CoreAddons
    KF5::I18n
    KF5::Auth
    rc
)


target_link_libraries(kcm_openrc
    Qt5::Core
    Qt5::DBus
    KF5::CoreAddons
    KF5::I18n
    KF5::QuickAddons
    KF5::ConfigCore
    KF5::ConfigWidgets
    KF5::Auth
    rc
)

install(TARGETS openrc-actions-kauth DESTINATION ${KAUTH_HELPER_INSTALL_DIR})
install(TARGETS kcm_openrc DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/kcms/systemsettings)

kpackage_install_package(package kcm_openrc kcms)
kauth_install_helper_files(openrc-actions-kauth tridentu.auth.openrc.service root)
kauth_install_actions(tridentu.auth.openrc.service tridentu.auth.openrc.service.actions)
