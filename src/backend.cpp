// Notice: this code is full of uncooked spaghetti. It is probably very unoptimised or does things wrong.
// Also I need to go back through this and make it use good C++ more.
#include "backend.hpp"

#include <git2.h>
#include <filesystem>
#include <iostream>
#include <filesystem>
#include <string>
#include <QFile>
#include <QMessageBox>

#include <vector>

const std::vector<std::string> regions = {"us", "eu", "jp"};

// Wait why did I add this?
// TODO: Remove this and replace with .c_str()
char* string_to_char(std::string inp) {
	// Function to turn an std::string to a char*
	char* charOut = new char[inp.length() + 1];
	strcpy(charOut, inp.c_str());
	return charOut;
}

std::string getExecutableName(QString folder, int region) {
	std::string folderString = folder.toStdString();
	std::filesystem::path buildDir{"sm64-builds/" + folderString + "/build/" + regions[region] + "_pc/"};
	for (const std::filesystem::directory_entry& dirEntry: std::filesystem::directory_iterator(buildDir)) {
		std::string filenameExtension = dirEntry.path().extension().string();
		if (filenameExtension == ".f3dex2e") {
			return dirEntry.path().filename().string();
		}
	}
	return "";
}

Backend::Backend(QObject *parent) : QObject(parent) {
	git_libgit2_init();
	launcherConfig = KSharedConfig::openConfig("kirigami64rc", KSharedConfig::FullConfig, QStandardPaths::AppDataLocation);
	launcherRepoDefaults = launcherConfig->group((QString)"Defaults");
	launcherRoms = launcherConfig->group((QString)"Roms");
	
	// Roms
	defaultRegion = launcherRoms.readEntry("defaultRegion", 0);
	romsPerRegion.push_back(launcherRoms.readEntry("usROMPath", ""));
	romsPerRegion.push_back(launcherRoms.readEntry("euROMPath", ""));
	romsPerRegion.push_back(launcherRoms.readEntry("jpROMPath", ""));

	// Repo Defaults
	useMangoHud = launcherRepoDefaults.readEntry("useMangoHud", false);
	useGameMode = launcherRepoDefaults.readEntry("useGameMode", false);
}

Backend::~Backend() {
	git_libgit2_shutdown();
}

QSettings* Backend::sourceList() {
	return sources;
}

std::vector<QString> Backend::buildNamesDataGet() {
	return buildNames;
}

std::vector<QString> Backend::buildDescriptionsDataGet() {
	return buildDescriptions;
}

std::vector<QString> Backend::buildIconsDataGet() {
	return buildIcons;
}

std::vector<QString> Backend::romPathGet() {
	return romsPerRegion;
}

QString Backend::buildConfigSpecificDataGet(int build, int type) {
	if (buildCount == 0) return "";
	if (type == 0) return buildNames[build];
	else if (type == 1) return buildDescriptions[build];
	else if (type == 2) return buildIcons[build];
	else return QString::number(buildRegions[build]);
	//return buildConfig[build][type];
}

QStringList Backend::sourceGroups() {
	return sources->childGroups();
}

int Backend::currentRegion() { return defaultRegion; }

int Backend::buildCountValue() {
	return buildCount;
}

int Backend::buildSelectedValue() {
	return buildSelected;
}

QString Backend::buildList(int pos) {
	return builds[pos];
}

QString Backend::repoText()
{
	return link;
}

QString Backend::branchText()
{
	return branch;
}

bool Backend::downloadSizeUnknownValue() {
	return downloadSizeUnknown;
}

bool Backend::usingMangoHud() {
	return useMangoHud;
}

bool Backend::usingGameMode() {
	return useGameMode;
}

void Backend::buildFind(int additive) {
	int count = 0 + additive;
	buildCount = 0;
	builds.clear();
	buildNames.clear();
	buildDescriptions.clear();
	buildIcons.clear();
	Q_EMIT buildCountModified();
	Q_EMIT buildListModified();
	Q_EMIT buildConfigListModified();
	std::filesystem::path sources{"sources.conf"};
	if (!std::filesystem::exists(sources)) {
		QFile base_sources(":/base_sources.conf");
		base_sources.copy("sources.conf");
	}

	std::filesystem::path buildDir{"sm64-builds/"};
	if (!std::filesystem::exists(buildDir)) std::filesystem::create_directory(buildDir);
	for (const std::filesystem::directory_entry& dirEntry: std::filesystem::directory_iterator(buildDir)) {
		if (dirEntry.is_directory()) {
			std::string pathString = dirEntry.path().filename().string();

			if (pathString[0] != '.' && pathString[0] != ' ') {
				std::filesystem::path checkIfIgnore("sm64-builds/" + pathString + "/.k64ignore");

				if (std::filesystem::exists(checkIfIgnore)) {
					std::cout << "Ignoring dir " << pathString << std::endl;
					continue;
				}

				builds.push_back(QString::fromStdString(pathString));
				count++;
				std::cout << "Directory found: " << pathString << "\n";
				std::string cfgString = "sm64-builds/" + pathString + ".k64.conf";
				std::filesystem::path configCheck {cfgString};
				if (std::filesystem::exists(configCheck)) {
					std::cout << "Build configuration found: " << cfgString << "\n";
					QSettings my_settings(QString::fromStdString(cfgString), QSettings::IniFormat);
					buildNames.push_back(my_settings.value("build/name").toString());
					buildDescriptions.push_back(my_settings.value("build/description").toString());
					buildIcons.push_back(my_settings.value("build/icon").toString());
					buildRegions.push_back(my_settings.value("build/region").toInt());
				}
				else {
					buildNames.push_back(QString::fromStdString(pathString));
					buildDescriptions.push_back("No description has been set for this build.");
					buildIcons.push_back("application-x-n64-rom");
					buildRegions.push_back(0);
				}
			}
		} else if (!QString::fromStdString(dirEntry.path().filename().string()).endsWith(".k64.conf")) {
			QMessageBox::information(nullptr, "Unexpected File",
						QString::fromStdString("When scanning the directory sm64-builds, an unexpected file called '" + dirEntry.path().filename().string() + "' was found.\nPlease move the file out of the folder."));
		}
	}
	buildCount = count;
	Q_EMIT buildCountModified();
	Q_EMIT buildListModified();
	Q_EMIT buildConfigListModified();
}

void Backend::setCurrentRegion(int region) {
	defaultRegion = region;
	launcherRoms.writeEntry("defaultRegion", defaultRegion);
	Q_EMIT currentRegionModified();
}

void Backend::setBuildSelected(int target) {
	buildSelected = target;
	Q_EMIT buildSelectModified();
}

void Backend::setRepo(QString repoInp)
{
	link = repoInp;
	Q_EMIT repoModified();
}

void Backend::setBranch(QString branchInp)
{
	branch = branchInp;
	Q_EMIT branchModified();
}

void Backend::setDownloadSizeUnknownStatus(bool known)
{
	downloadSizeUnknown = known;
	Q_EMIT downloadSizeUnknownStatus();
}

void Backend::setUseMangoHud(bool usingMangoHud)
{
	useMangoHud = usingMangoHud;
	launcherRepoDefaults.writeEntry("useMangoHud", useMangoHud);
	Q_EMIT useMangoHudModified();
}

void Backend::setUseGameMode(bool newGameModeVal)
{
	useGameMode = newGameModeVal;
	launcherRepoDefaults.writeEntry("useGameMode", newGameModeVal);
	Q_EMIT useGameModeModified();
}

void Backend::setROMPath(int region, QString path)
{
	romsPerRegion[region] = path;
	launcherRoms.writeEntry(QString::fromStdString(regions[region] + "ROMPath"), romsPerRegion[region]);
	Q_EMIT romPathListModified();
}

QString Backend::getROMPath(int region) {
	return romsPerRegion[region];
}

int Backend::addShortcut(QString folder) {
	// Handle desktop menu shenanigans
	std::cout << "Writing shortcut file...\n";
	std::string userDir = getenv("HOME");
	std::string folderString = folder.toStdString();
	std::string dir = std::filesystem::current_path();
	std::string desktopFileContents = "[Desktop Entry]\nName=" + buildConfigSpecificDataGet(buildSelected).toStdString() + "\nComment=" + buildConfigSpecificDataGet(buildSelected, 1).toStdString() + "\nType=Application\nExec=bash -c \"cd " + dir + "/sm64-builds/" + folderString + "/build/" + regions[defaultRegion] + "_pc/ && ./" + getExecutableName(folder, defaultRegion) + "\"\nIcon=" + buildConfigSpecificDataGet(buildSelected, 2).toStdString() + "\nCategories=Game;";
	std::string desktopFileName = folderString + ".desktop";
	std::ofstream desktopFile(userDir + "/.local/share/applications/" + desktopFileName);
	desktopFile << desktopFileContents;
	desktopFile.close();
	std::cout << "Wrote shortcut file to " + (userDir + "/.local/share/applications/" + desktopFileName) + ".\n";

	// Symlink shortcut to desktop
	symlink(string_to_char(userDir + "/.local/share/applications/" + desktopFileName), string_to_char(userDir + "/Desktop/" + desktopFileName));

	return 0;
}

void Backend::modifyConfig(QString name, QString description, QString icon, int region) {
	QString folder = buildList(buildSelected);
	std::string conf = "[build]\nname = " + name.toStdString() + "\ndescription = " + description.toStdString() + "\nicon = " + icon.toStdString() + "\nregion = " + std::to_string(region);
	std::cout << (folder.toStdString() + ".conf") << "\n";
	std::ofstream desktopFile("sm64-builds/" + folder.toStdString() + ".k64.conf");
	desktopFile << conf;
	desktopFile.close();
}

int Backend::clone(QString repoSel) {
	std::filesystem::path builds{"sm64-builds/"};
	if (!std::filesystem::exists(builds)) {
		std::filesystem::create_directory(builds);
	}
	sources->beginGroup(repoSel);
	QStringList data = sources->childKeys();
	/*foreach (QString value, data) {
		std::cout << value.toStdString() << "\n";
	}*/
	link = sources->value(data[1]).toString();
	branch = sources->value(data[0]).toString();
	//std::cout << "Repository: " << repo.toStdString() << "\nBranch: " << branch.toStdString() << "\n";
	sources->endGroup();
	//std::string stdFolder = "sm64-builds/";
	//std::string command = "git clone --branch " + branch.toStdString() + " " + repo.toStdString() + " --progress";
	/*const char *dir = (stdFolder).c_str();
	mkdir(dir,0777);*/
	//std::string cmd = "cd sm64-builds && " + command + " && echo \"Completed clone.\" &";
	//system(string_to_char(cmd));

	std::cout << link.toStdString() << "\n" << branch.toStdString() << "\n";

	char* path = string_to_char("sm64-builds/" + repoSel.toStdString());

	std::filesystem::path buildCloneDir{path};
	std::filesystem::create_directory(buildCloneDir);

	git_repository* repo = NULL;

	git_clone_options clone_options = GIT_CLONE_OPTIONS_INIT;
	clone_options.checkout_branch = string_to_char(branch.toStdString());
	clone_options.checkout_opts.checkout_strategy = GIT_CHECKOUT_SAFE;

	int error = git_clone(&repo, string_to_char(link.toStdString()), path, &clone_options);
	std::cout << "Clone Result: " << error << "\n";
	git_repository_free(repo);
	return error;
}

int Backend::pull(QString folder) {
	// TODO: Fast forward with libgit2
	system(string_to_char("cd sm64-builds/" + folder.toStdString() + " && git pull"));
	return 0;
}

int Backend::build(QString folder) {
	std::cout << buildRegions[buildSelected] << std::endl;

	int region = buildRegions[buildSelected] == 0 ? defaultRegion : buildRegions[buildSelected] - 1;

	std::cout << romsPerRegion[region].toStdString() << std::endl;
	std::cout << regions[region] << std::endl;
	
	std::filesystem::path romPath { romsPerRegion[region].toStdString() };

	if (!std::filesystem::exists(romPath)) {
		std::cerr << "Failed to build using rom path " << romPath << ", doesn't exist!" << std::endl;
		return 1;
	}

	std::string cmd0 = "rm -f baserom.*.z64 && cp \"" + romsPerRegion[region].toStdString() + "\" sm64-builds/" + folder.toStdString() + "/baserom." + regions[region] + ".z64";
	std::string cmd1 = "cd sm64-builds/" + folder.toStdString() + " && make TARGET_BITS=64 VERSION=\"" + regions[region] + "\" -j $(nproc) && echo \"Completed build.\" &";
	std::string fullCmd = cmd0 + " && " + cmd1;
	system(string_to_char(fullCmd));
	return 0;
}

int Backend::run(QString folder) {
	char* dir = string_to_char("sm64-builds/" + folder.toStdString() + "/build");

	std::filesystem::path builds{dir};

	int region = buildRegions[buildSelected] == 0 ? defaultRegion : buildRegions[buildSelected] - 1;

	if (!std::filesystem::exists(builds)) {
		std::cerr << "This build has not been compiled." << std::endl;
		return 1;
	}
	else {
		std::string execPrefix = "";
		std::string execSuffix = "";
		if (useMangoHud) {
			if (!system("which mangohud > /dev/null 2>&1")) execPrefix += "mangohud --dlsym ";
			else std::cerr << "Error: Mangohud isn't installed! Continuing without mangohud..." << std::endl;
		}

		if (useGameMode) {
			if (!system("which gamemoderun > /dev/null 2>&1")) execPrefix += "gamemoderun ";
			else std::cerr << "Error: Feral GameMode isn't installed! Continuing without gamemode..." << std::endl;
		}
		// Might add more exec prefixes later later
		std::string cmdAsString = "cd sm64-builds/" + folder.toStdString() + "/build/" + regions[region] + "_pc/ && " +  execPrefix + " ./" + getExecutableName(folder, region) + execSuffix + " &";
		system(cmdAsString.c_str());
		return 0;
	}
}

int Backend::rmDir(QString folder) {
	std::filesystem::path folderToRemove{"sm64-builds/" + folder.toStdString()};
	std::filesystem::remove_all(folderToRemove);
	buildFind(0);
	return 0;
}

int Backend::openSources() {
	system("xdg-open sources.conf &");
	return 0;
}

int Backend::handleSources() {
	sources = new QSettings("sources.conf", QSettings::IniFormat);
	return 0;
}

void Backend::openRepoDataDir() {
	QString targetDir = getenv("HOME") + ("/.local/share/" + builds[buildSelected]);
	std::filesystem::path existenceCheck(targetDir.toStdString());
	if (targetDir.contains("-") && !(std::filesystem::exists(existenceCheck) && std::filesystem::is_directory(existenceCheck))) {
		targetDir = targetDir.split("-").first();
		existenceCheck = std::filesystem::path(targetDir.toStdString());
	}
	if (std::filesystem::exists(existenceCheck) && std::filesystem::is_directory(existenceCheck)) {
		system(string_to_char("xdg-open " + targetDir.toStdString()));
	} else {
		std::cout << builds[buildSelected].toStdString() << " uses a non-standard save location." << std::endl;
	}
}
