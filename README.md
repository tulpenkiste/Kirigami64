# Kirigami64
Hosted on [Codeberg](https://codeberg.org/tulip-sudo/Kirigami64) with a [GitHub Mirror](https://github.com/azreigh/Kirigami64). <br>
[![tulip-sudo - Kirigami64 GitHub Mirror](https://img.shields.io/static/v1?label=azreigh&message=Kirigami64&color=blue&logo=github)](https://github.com/tulip-sudo/Kirigami64 "Go to GitHub mirror")
[![GitHub Mirror releases](https://img.shields.io/github/release/azreigh/Kirigami64?include_prereleases=&sort=semver&color=blue)](https://github.com/azreigh/Kirigami64/releases/)
[![License](https://img.shields.io/badge/License-GPL--3.0-blue)](#license)
<br>
A launcher for the SM64 PC Port made using Kirigami.
# Notice
The launcher does not currently give a proper way to see the progress of terminal commands (i.e git pull, git clone, make). It is recommended to use this with a terminal window shown. <br>
It also currently only supports US roms.
You can join our community discord server [here](https://discord.gg/Vptbbp59vQ).
# Compiling
## Dependencies
Kirigami64 requires CMake, Extra CMake Modules, Qt development packages, Kirigami and the base developer package. <br>
Meson is also recommended as an alternative to CMake (all releases are compiled using Meson).
### APT
Run `sudo apt install build-essential extra-cmake-modules cmake qtbase5-dev qtdeclarative5-dev libqt5svg5-dev qtquickcontrols2-5-dev qml-module-org-kde-kirigami2 kirigami2-dev libkf5i18n-dev gettext libkf5coreaddons-dev qml-module-qtquick-layouts libgit2-dev meson` to obtain the dependencies.
### Pacman
Run `sudo pacman -S base-devel extra-cmake-modules cmake kirigami2 kde-sdk-meta gettext libgit2 meson` to obtain the dependencies.
### DNF
Run `sudo dnf groupinstall "Development Tools" "Development Libraries"`<br>`sudo dnf install extra-cmake-modules cmake qt5-qtbase-devel qt5-qtdeclarative-devel qt5-qtquickcontrols2-devel kf5-kirigami2 kf5-kirigami2-devel kf5-ki18n-devel kf5-kcoreaddons-devel gettext libgit2 libgit2-devel meson` to obtain the dependencies.
### Other
// TODO: Add later
## Instructions
Install the required dependencies using the commands above, or use the included commands `./install_sm64_dependencies` and `./install_compile_dependencies`<br>
<br> Run
```bash
git clone https://codeberg.org/tulip-sudo/Kirigami64.git
./compile
./run
```
<br>If you want to skip the compile script (e.g. for configuring the build), you may instead run `meson build && cd build && meson compile` in the terminal and execute the binary generated within the `build` folder.
# Running
## Windows
Using this software is not recommended *or* supported on Windows. Check out the [SM64 PC Info website](https://www.sm64pc.info/) for a launcher more suited towards your operating system. <br>
If you do not care about the above notice in the slightest, follow the Linux steps using WSL2 + WSLg or figure out how to compile the necessary libraries using MinGW.
## MacOS
// TODO: Figure out if this is possible. It should be possible but Apple OSes are a bit quirky.
## Linux
Run `chmod +x Kirigami64` in the /build/bin/ folder (or on your executable somewhere else) then execute the file in the terminal (`./Kirigami64`) or through a desktop file. <br>
Make sure to put an SM64 rom with the name `baserom.{region}.z64` in `~/.local/share/Kirigami64`. <br>
Ensure you have the necessary dependencies for compiling and running your desired SM64 repository before using this.
# Todo
## 0.3.0
 - [X] Change paths used to `$HOME/.local/share/Kirigami64` rather than the current working directory
 - [X] Meson build system support (as primary build system)
 - [ ] Proper settings menu (with settings being saved into `$HOME/.local/share/Kirigami64/kirigami64rc`)
 - [X] Update info on www.sm64pc.info to link to Codeberg rather than GitHub.
 - [ ] ROM Region selecting
## No Version Target
 - [X] Actually working minimum features (e.g. build and run) (Required)
 - [ ] A way to view progress of running commands (e.g. git clone, git pull, make) (High)
 - [X] Config file containing sources rather than having to type it out each time. (High)
 - [X] Ability to pull changes without needing to delete a specific build (High)
 - [ ] Ability to use non-US roms (jp, eu) (Medium)
 - [ ] Option for patches (e.g. Texture Pack, DynOS) (Medium)
 - [X] Option to run games using MangoHud (Low)
 - [ ] Ability to add images for a specific build (e.g. Icon, Header) (Low)
 - [X] Add desktop shortcuts to application launcher list (Low)
 - [ ] Ability to add build as desktop shortcut (Low)
