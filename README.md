# Kirigami64
[![azreigh - Kirigami64](https://img.shields.io/static/v1?label=azreigh&message=Kirigami64&color=blue&logo=github)](https://github.com/azreigh/Kirigami64 "Go to GitHub repo")
[![GitHub release](https://img.shields.io/github/release/azreigh/Kirigami64?include_prereleases=&sort=semver&color=blue)](https://github.com/azreigh/Kirigami64/releases/)
[![License](https://img.shields.io/badge/License-GPL--3.0-blue)](#license)
<br>
A launcher for the SM64 PC Port made using Kirigami.
# Notice
The launcher does not currently give a proper way to see the progress of terminal commands (i.e git pull, git clone, make). It is recommended to use this with a terminal window shown. <br>
It also currently only supports US roms.
# Compiling
## Dependencies
Kirigami64 requires CMake, Extra CMake Modules, Qt development packages, Kirigami and the base developer package.
### APT
Run `sudo apt install build-essential extra-cmake-modules cmake qtbase5-dev qtdeclarative5-dev libqt5svg5-dev qtquickcontrols2-5-dev qml-module-org-kde-kirigami2 kirigami2-dev libkf5i18n-dev gettext libkf5coreaddons-dev qml-module-qtquick-layouts` to obtain the dependencies.
### Pacman
Run `sudo pacman -S base-devel extra-cmake-modules cmake kirigami2 kde-sdk-meta gettext` to obtain the dependencies.
### DNF
Run `sudo dnf groupinstall "Development Tools" "Development Libraries"`<br>`sudo dnf install extra-cmake-modules cmake qt5-qtbase-devel qt5-qtdeclarative-devel qt5-qtquickcontrols2-devel kf5-kirigami2 kf5-kirigami2-devel kf5-ki18n-devel kf5-kcoreaddons-devel gettext` to obtain the dependencies.
### Other
// TODO: Add later
## Instructions
Run `./compile` or run `cmake -B build/ . && cmake --build build/` in the terminal and execute the binary generated within the `/build/bin/` folder.
# Running
## Windows
Using this software is not recommended *or* supported on Windows. Check out the [SM64 PC Info website](https://www.sm64pc.info/) for a launcher more suited towards your operating system.
## MacOS
// TODO: Figure out if this is possible.
## Linux
Run `chmod +x Kirigami64` in the /build/bin/ folder (or on your executable somewhere else) then execute the file in the terminal (`./Kirigami64`) or through a desktop file. <br>
Make sure to put a US SM64 rom with the name `baserom.us.z64` in the same directory as the executable. <br>
Ensure you have the necessary dependencies for compiling and running your desired SM64 repository before using this.
# Planned Features
 - [X] Actually working minimum features (e.g. build and run) (Required)
 - [ ] A way to view progress of running commands (e.g. git clone, git pull, make) (High)
 - [ ] Config file containing sources rather than having to type it out each time. (High)
 - [X] Ability to pull changes without needing to delete a specific build (High)
 - [ ] Download progress (Medium)
 - [ ] Ability to use non-US roms (e.g. jp, eu) (Medium)
 - [ ] Option for patches (e.g. Texture Pack, DynOS) (Medium)
 - [ ] Ability to add images for a specific build (e.g. Icon, Header) (Low)
 - [X] Add desktop shortcuts to application launcher list (Low)
 - [ ] Ability to add build as desktop shortcut (Low)
