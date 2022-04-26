add_executable(Kirigami64 main.cpp about.cpp backend.cpp resources.qrc)
target_link_libraries(Kirigami64 Qt5::Quick Qt5::Qml Qt5::Gui Qt5::QuickControls2 Qt5::Widgets KF5::Kirigami2 KF5::I18n KF5::CoreAddons)
