# Kirigami64
[![azreigh - Kirigami64](https://img.shields.io/static/v1?label=azreigh&message=Kirigami64&color=blue&logo=github)](https://github.com/azreigh/Kirigami64 "Go to GitHub repo")
[![stars - Kirigami64](https://img.shields.io/github/stars/azreigh/Kirigami64?style=social)](https://github.com/azreigh/Kirigami64)
[![forks - Kirigami64](https://img.shields.io/github/forks/azreigh/Kirigami64?style=social)](https://github.com/azreigh/Kirigami64)
[![GitHub release](https://img.shields.io/github/release/azreigh/Kirigami64?include_prereleases=&sort=semver&color=blue)](https://github.com/azreigh/Kirigami64/releases/)
[![License](https://img.shields.io/badge/License-GPL--3.0-blue)](#license)
<br>
A launcher for the SM64 PC Port made using Kirigami.
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
Run `build.sh` or run `cmake -B build/ . && cmake --build build/` in the terminal and execute the binary generated within the `/build/bin/` folder.
# Running
## Windows
Using this software is not recommended *or* supported on Windows. Check out the [SM64 PC Info website](https://www.sm64pc.info/) for a launcher more suited towards your operating system.
## MacOS
// TODO: Figure out if this is possible.
## Linux
Run `chmod +x Kirigami64` in the /build/bin/ folder (or on your executable somewhere else) then execute the file in the terminal (`./Kirigami64`) or through a desktop file.
# Planned Features
 - [ ] Actually working minimum features (e.g. build and run) (Required, Very Important)
 - [ ] A way to view progress of running commands (e.g. git clone, git pull, make) (High, Important)
 - [ ] Config file containing sources rather than having to type it out each time. (High, Important)
 - [X] Ability to pull changes without needing to delete a specific build (High, Important)
 - [ ] Option for patches (e.g. Texture Pack, DynOS) (Medium)
 - [ ] Ability to add images for a specific build (e.g. Icon, Header) (Low)
 - [ ] Ability to add build as desktop shortcut (Low)
