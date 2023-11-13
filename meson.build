project('Kirigami64', 'cpp', version: '0.3.0' + (not get_option('buildtype').startswith('release') ? '-' + run_command('git', 'rev-parse',  '--short', 'HEAD', check: true).stdout().strip() : ''), default_options: ['cpp_std=c++17'], meson_version: '>=0.60.3')

# Setup: configure file
config_dat = configuration_data()
config_dat.set('PROJECT_NAME', 'Kirigami64')
config_dat.set('PROJECT_VERSION', meson.project_version())
config_dat.set('PROJECT_VERSION_SUBTITLE', 'idk')

configure_file(input: 'src/config.in.hpp', output: 'config.hpp', configuration: config_dat)

# Setup: library dependencies
qt6dep = dependency('qt6', modules : ['Core', 'Qml', 'Quick', 'Gui', 'QuickControls2', 'Widgets'], version : '>=6.6.0')
kf6dep = dependency('KF6CoreAddons', version : '>=5.245.0')
kf6kirigamidep = dependency('KF6Kirigami2', version : '>=5.245.0')
kf6translatedep = dependency('KF6I18n', version : '>=5.245.0')
kf6configdep = dependency('KF6Config', modules: ['KF6::ConfigCore', 'KF6::ConfigGui'], version : '>=5.111.0', method: 'cmake')
lgit2 = dependency('libgit2', version : '>=1.1.0')
#lgit2 = meson.get_compiler('cpp').find_library('git2')

libs = [qt6dep, kf6dep, kf6kirigamidep, kf6translatedep, kf6configdep, lgit2]

# Setup: Qt Module
qt6 = import('qt6')

# Files
sources = files('src/about.cpp', 'src/backend.cpp', 'src/main.cpp')
headers = files('src/about.hpp', 'src/backend.hpp')

# Qt shenanigans
resources = qt6.preprocess(
							qresources : ['src/resources.qrc'],
							moc_headers : headers,
							dependencies: libs)

# The application
launcher = executable('Kirigami64', sources, resources, include_directories: ['/usr/include/KF6/KConfigCore'] , dependencies: libs)
