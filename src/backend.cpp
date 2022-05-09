// Notice: this code is full of uncooked spaghetti. It is probably very unoptimised or does things wrong.
// Also I need to go back through this and make it use C++ more.
#include "backend.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <pwd.h>
#include <INIReader.h>
#include <filesystem>
#include <QFile>

char* string_to_char(std::string inp) {
	// Function to turn an std::string to a char*
	char* charOut = new char[inp.length() + 1];
	strcpy(charOut, inp.c_str());
	return charOut;
}

Backend::Backend(QObject *parent)
	: QObject(parent)
{
	buildFind(0); // Instantly check for builds on load. Probably not efficient
	handleSources();
}

QSettings* Backend::sourceList() {
	return sources;
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
	return repo;
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
	int i = 0;
	DIR *dir;
	struct dirent *dirEntry;
	builds->clear();
	namespace fs = std::filesystem;
	fs::path f{ "sources.conf" };
	if (!fs::exists(f)) {
		QFile base_sources = QFile(":/base_sources.conf");
		base_sources.copy("sources.conf");
	}
	if ((dir = opendir ("sm64-builds")) != NULL) {
		while ((dirEntry = readdir (dir)) != NULL) {
			if (dirEntry->d_type == DT_DIR && dirEntry->d_name[0] != '.') {
				builds[i] = dirEntry->d_name;
				count++;
				i++;
				printf("Directory found: %s\n", dirEntry->d_name);
			}
		}
		closedir (dir);
	} else {
		perror ("");
	}
	buildCount = count;
	Q_EMIT buildCountModified();
	Q_EMIT buildListModified();
}

void Backend::setBuildSelected(int target) {
	buildSelected = target;
	Q_EMIT buildSelectModified();
}

void Backend::setRepo(QString repoInp)
{
	repo = repoInp;
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
	printf("Writing desktop file...\n");
	std::string userDir = getenv("HOME");
	std::string folderString = folder.toStdString();
	std::string dir = get_current_dir_name();
	std::string desktopFileContents = "[Desktop Entry]\nName=" + folderString + "\nType=Application\nExec=bash -c \"cd " + dir + "/sm64-builds/" + folderString + "/build/" + region + "_pc/ && ./sm64." + region + ".f3dex2e\"\nIcon=applications-games\nCategories=Game;";
	std::string desktopFileName = folderString + ".desktop";
	std::ofstream desktopFile(userDir + "/.local/share/applications/" + desktopFileName);
	desktopFile << desktopFileContents;
	desktopFile.close();
	return 0;
}

int Backend::clone(QString repoSel) {
	if (!opendir("sm64-builds/")) {
		mkdir("sm64-builds",0777);
	}
	sources->beginGroup(repoSel);
	QStringList data = sources->childKeys();
	foreach (QString value, data) {
		std::cout << value.toStdString() << "\n";
	}
	repo = sources->value(data[1]).toString();
	branch = sources->value(data[0]).toString();
	std::cout << "Repository: " << repo.toStdString() << "\nBranch: " << branch.toStdString() << "\n";
	sources->endGroup();
	//std::string stdFolder = "sm64-builds/";
	std::string command = "git clone --branch " + branch.toStdString() + " " + repo.toStdString() + " --progress";
	/*const char *dir = (stdFolder).c_str();
	mkdir(dir,0777);*/
	std::string cmd = "cd sm64-builds && " + command + " && echo \"Completed clone.\" &";
	system(string_to_char(cmd));
	return 0;
}

int Backend::pull(QString folder) {
	std::string cmdAsString = "cd sm64-builds/" + folder.toStdString() + " && git pull && echo \"Completed pull.\" &";
	//printf("%s\n", string_to_char(folder.toStdString())); // Test to see if it worked.
	system(string_to_char(cmdAsString));
	return 0;
}

int Backend::build(QString folder) {
	std::string cmd0 = "cp baserom." + region + ".z64 sm64-builds/" + folder.toStdString() + "/baserom.us.z64";
	std::string cmd1 = "cd sm64-builds/" + folder.toStdString() + " && make -j4 && echo \"Completed build.\" &";
	std::string fullCmd = cmd0 + " && " + cmd1;
	system(string_to_char(fullCmd));
	return 0;
}

int Backend::run(QString folder) {
	char* dir = string_to_char("sm64-builds/" + folder.toStdString() + "/build/");
	if (!opendir(dir)) {
		build(folder); // The repository hasn't run make yet.
		return 1;
	}
	else {
		std::string execPrefix = "";
		if (useMangoHud) {
			execPrefix += "mangohud --dlsym";
		}
		// Might add more exec prefixes later later
		std::string cmdAsString = "cd sm64-builds/" + folder.toStdString() + "/build/" + region + "_pc/ && " +  execPrefix + " ./sm64." + region + ".f3dex2e &";
		system(string_to_char(cmdAsString));
		return 0;
	}
}

int Backend::rmDir(QString folder) {
	char* cmd = string_to_char("rm -rf sm64-builds/" + folder.toStdString()); // Avoid running in background to ensure that buildFind(0) works.
	system(cmd);
	buildFind(0);
	return 0;
}

int Backend::openSources() {
	//std::filesystem::copy_file("base_sources.conf", "sources.conf");
	
	system("kate sources.conf &");
	return 0;
}

int Backend::handleSources() {
	sources = new QSettings("sources.conf", QSettings::IniFormat);
	std::cout << "Sources in file: " << sources->allKeys().count() << "\n";
	foreach (QString key, sources->allKeys()) {
		std::cout << "Key: " << key.toStdString() << "\n";
	}
	foreach (QString group, sources->childGroups()) {
		std::cout << "Group: " << group.toStdString() << "\n";
	}
	return 0;
}