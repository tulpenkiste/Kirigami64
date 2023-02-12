project('Kirigami64', 'cpp', version: '0.2.1', default_options: ['cpp_std=c++17'])

# Setup: configure file
config_dat = configuration_data()
config_dat.set('PROJECT_NAME', 'Kirigami64')
config_dat.set('PROJECT_VERSION', meson.project_version())
config_dat.set('PROJECT_VERSION_SUBTITLE', 'Whomp\'s (Patched) Fortress')

configure_file(input: 'src/config.hpp.in', output: 'config.hpp', configuration: config_dat)

# Setup: library dependencies
qt5dep = dependency('qt5', modules : ['Core', 'Qml', 'Quick', 'Gui', 'QuickControls2', 'Widgets'], version : '>=5.14.0')
kf5dep = dependency('KF5CoreAddons', version : '>=5.68.0')
kf5kirigamidep = dependency('KF5Kirigami2', version : '>=5.68.0')
kf5translatedep = dependency('KF5I18n', version : '>=5.68.0')
lgit2 = meson.get_compiler('cpp').find_library('git2')

libs = [qt5dep, kf5dep, kf5kirigamidep, kf5translatedep, lgit2]

# Setup: Qt Module
qt5 = import('qt5')

# Files
sources = files('src/about.cpp', 'src/backend.cpp', 'src/main.cpp')
headers = files('src/about.hpp', 'src/backend.hpp')

# Qt shenanigans
resources = qt5.preprocess(
							qresources : ['src/resources.qrc'],
							moc_headers : headers,
							dependencies: libs)

# The application
launcher = executable('Kirigami64', sources, resources, dependencies: libs)
