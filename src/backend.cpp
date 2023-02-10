// Notice: this code is full of uncooked spaghetti. It is probably very unoptimised or does things wrong.
// Also I need to go back through this and make it use good C++ more.
#include "backend.h"

#include <git2.h>
#include <filesystem>
#include <iostream>
#include <filesystem>
#include <string>
#include <QFile>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

char* string_to_char(std::string inp) {
	// Function to turn an std::string to a char*
	char* charOut = new char[inp.length() + 1];
	strcpy(charOut, inp.c_str());
	return charOut;
}

std::string getExecutableName(QString folder, std::string region) {
	std::string folderString = folder.toStdString();
	std::filesystem::path buildDir{"sm64-builds/"+folderString+"/build/" + region + "_pc/"};
	for (const auto& dirEntry: std::filesystem::directory_iterator(buildDir)) {
		std::string pathString = dirEntry.path().extension().string();
		if (pathString == ".f3dex2e") {
			return dirEntry.path().filename().string();
		}
		/*if (dirEntry.is_directory()) {
			std::string pathString = dirEntry.path().filename().string();
			if (pathString[0] != '.' && pathString[0] != ' ') {
				builds[i] = QString::fromStdString(pathString);
				count++;
				i++;
				std::cout << "Direcory found: " << pathString << "\n";
			}
		}*/
	}
	return "";
}

Backend::Backend(QObject *parent) : QObject(parent) {
	git_libgit2_init();
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

QString Backend::buildConfigSpecificDataGet(int build, int type) {
	if (buildCount == 0) return "";
	if (type == 0) return buildNames[build];
	else if (type == 1) return buildDescriptions[build];
	return buildIcons[build];
	//return buildConfig[build][type];
}

QStringList Backend::sourceGroups() {
	return sources->childGroups();
}

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
		//base_sources.copy("sources.conf");
	}
	std::filesystem::path buildDir{"sm64-builds/"};
	if (!std::filesystem::exists(buildDir)) std::filesystem::create_directory(buildDir);
	for (const auto& dirEntry: std::filesystem::directory_iterator(buildDir)) {
		if (dirEntry.is_directory()) {
			std::string pathString = dirEntry.path().filename().string();
			if (pathString[0] != '.' && pathString[0] != ' ') {
				builds.push_back(QString::fromStdString(pathString));
				count++;
				std::cout << "Directory found: " << pathString << "\n";
				std::string cfgString = "sm64-builds/" + pathString + ".conf";
				std::filesystem::path configCheck {cfgString};
				if (std::filesystem::exists(configCheck)) {
					std::cout << "Build configuration found: " << cfgString << "\n";
					QSettings my_settings(QString::fromStdString(cfgString), QSettings::IniFormat);
					buildNames.push_back(my_settings.value("build/name").toString());
					buildDescriptions.push_back(my_settings.value("build/description").toString());
					buildIcons.push_back(my_settings.value("build/icon").toString());
				}
				else {
					buildNames.push_back(QString::fromStdString(pathString));
					buildDescriptions.push_back("No description has been set for this build.");
					buildIcons.push_back("application-x-n64-rom");
				}
			}
		}
	}
	buildCount = count;
	Q_EMIT buildCountModified();
	Q_EMIT buildListModified();
	Q_EMIT buildConfigListModified();
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
	Q_EMIT useMangoHudModified();
}

int Backend::addShortcut(QString folder) {
	std::cout << "Writing shortcut file...\n";
	std::string userDir = getenv("HOME");
	std::string folderString = folder.toStdString();
	std::string dir = getenv("PWD");
	std::string desktopFileContents = "[Desktop Entry]\nName=" + buildConfigSpecificDataGet(buildSelected).toStdString() + "\nComment=" + buildConfigSpecificDataGet(buildSelected, 1).toStdString() + "\nType=Application\nExec=bash -c \"cd " + dir + "/sm64-builds/" + folderString + "/build/" + region + "_pc/ && ./" + getExecutableName(folder,region) + "\"\nIcon=" + buildConfigSpecificDataGet(buildSelected, 2).toStdString() + "\nCategories=Game;";
	std::string desktopFileName = folderString + ".desktop";
	std::ofstream desktopFile(userDir + "/.local/share/applications/" + desktopFileName);
	desktopFile << desktopFileContents;
	desktopFile.close();
	std::cout << "Wrote shortcut file to " + (userDir + "/.local/share/applications/" + desktopFileName) + ".\n";
	return 0;
}

void Backend::modifyConfig(QString name, QString description, QString icon) {
	QString folder = buildList(buildSelected);
	std::string conf = "[build]\nname = " + name.toStdString() + "\ndescription = " + description.toStdString() + "\nicon = " + icon.toStdString();
	std::cout << (folder.toStdString() + ".conf") << "\n";
	std::ofstream desktopFile("sm64-builds/" + folder.toStdString() + ".conf");
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
	system(string_to_char("cd sm64-builds/" + folder.toStdString()));
	return 0;
}

int Backend::build(QString folder) {
	std::string cmd0 = "cp baserom." + region + ".z64 sm64-builds/" + folder.toStdString() + "/baserom.us.z64";
	std::string cmd1 = "cd sm64-builds/" + folder.toStdString() + " && make TARGET_BITS=64 -j $(nproc) && echo \"Completed build.\" &";
	std::string fullCmd = cmd0 + " && " + cmd1;
	system(string_to_char(fullCmd));
	return 0;
}

int Backend::run(QString folder) {
	char* dir = string_to_char("sm64-builds/" + folder.toStdString() + "/build/");
	std::filesystem::path builds{dir};
	if (!std::filesystem::exists(builds)) {
		std::cout << "This build has not been compiled. Building it now.\n";
		build(folder); // The repository hasn't run make yet.
		return 1;
	}
	else {
		std::string execPrefix = "";
		if (useMangoHud) {
			execPrefix += "mangohud --dlsym";
		}
		// Might add more exec prefixes later later
		std::string cmdAsString = "cd sm64-builds/" + folder.toStdString() + "/build/" + region + "_pc/ && " +  execPrefix + " ./" + getExecutableName(folder,region) + " &";
		system(string_to_char(cmdAsString));
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
