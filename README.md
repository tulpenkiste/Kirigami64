# Kirigami64
Hosted on [Codeberg](https://codeberg.org/tulpenkiste/Kirigami64) with a [GitHub Mirror](https://github.com/tulpenkiste/Kirigami64). <br>
[![tulpenkiste - Kirigami64 GitHub Mirror](https://img.shields.io/static/v1?label=tulpenkiste&message=Kirigami64&color=blue&logo=github)](https://github.com/tulpenkiste/Kirigami64 "Go to GitHub mirror")
[![GitHub Mirror releases](https://img.shields.io/github/release/tulpenkiste/Kirigami64?include_prereleases=&sort=semver&color=blue)](https://github.com/tulpenkiste/Kirigami64/releases/)
[![License](https://img.shields.io/badge/License-GPL--3.0-blue)](#license)
<br>
A launcher for the SM64 PC Port made using Kirigami.
# Notice
The launcher does not currently give a proper way to see the progress of terminal commands (i.e git pull, git clone, make). It is recommended to use this with a terminal window shown. <br>
It also currently only supports US roms.
You can join our community discord server [here](https://discord.gg/Vptbbp59vQ).
# Compiling
## Dependencies
> This section has been removed as it is out of date (and also cannot be updated for Ubuntu and Fedora until February 2024 (release of KDE Plasma 6)), please use the dependency install scripts (`deps-compile` and `deps-runtime`) instead
## Instructions
Install the required dependencies using the included scripts `./deps-compile` and `./deps-runtime`<br>
<br> Run
```bash
git clone https://codeberg.org/tulpenkiste/Kirigami64.git
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
Ensure you have the necessary dependencies for compiling and running your desired SM64 repository before using this.
# Todo
## 0.3.0
 - [X] Change paths used to `$HOME/.local/share/Kirigami64` rather than the current working directory
 - [X] Meson build system support (as primary build system)
 - [X] Proper settings menu (with settings being saved into `$HOME/.local/share/Kirigami64/kirigami64rc`)
 - [X] Update info on www.sm64pc.info to link to Codeberg rather than GitHub.
 - [X] ROM Region selecting
## No Version Target
 - [X] Actually working minimum features (e.g. build and run) (Required)
 - [ ] A way to view progress of running commands (e.g. git clone, git pull, make) (High)
 - [X] Config file containing sources rather than having to type it out each time. (High)
 - [X] Ability to pull changes without needing to delete a specific build (High)
 - [X] Ability to use non-US roms (jp, eu) (Medium)
 - [ ] Option for patches (e.g. Texture Pack, DynOS) (Medium)
 - [X] Option to run games using MangoHud (Low)
 - [ ] Ability to add images for a specific build (e.g. Icon, Header) (Low)
 - [X] Add desktop shortcuts to application launcher list (Low)
 - [ ] Ability to add build as desktop shortcut (Very Low)
