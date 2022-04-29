#include "backend.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <dirent.h>

Backend::Backend(QObject *parent)
	: QObject(parent)
{
	buildFind(0);
}

int Backend::buildCountValue() {
	return buildCount;
}

int Backend::buildSelectedValue() {
	return buildSelected;
}

/*QString Backend::buildList(int pos = defaultInt) {
	return builds[pos];
}*/

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

void Backend::buildFind(int additive) {
	int count = 0 + additive;
	DIR *dir;
	struct dirent *dirEntry;
	//builds->clear();
	if ((dir = opendir ("sm64-builds")) != NULL) {
		while ((dirEntry = readdir (dir)) != NULL) {
			printf("%s\n", dirEntry->d_name);
			if (dirEntry->d_type == DT_DIR && dirEntry->d_name[0] != '.') {
				//builds[0] = dirEntry->d_name;
				count++;
			}
		}
		closedir (dir);
	} else {
		perror ("");
	}
	buildCount = count;
	Q_EMIT buildCountModified();
	//Q_EMIT buildListModified();
}

void Backend::setBuildSelected(int target) {
	buildSelected = target;
	Q_EMIT buildSelectModified();
}

/*void Backend::buildListSet(QString &folder) {
	// This does nothing. It just emits buildListModified().
	Q_EMIT buildListModified();
}*/

void Backend::setRepo(QString &repoInp)
{
	repo = repoInp;
	Q_EMIT repoModified();
}

void Backend::setBranch(QString &branchInp)
{
	branch = branchInp;
	Q_EMIT branchModified();
}

void Backend::setDownloadSizeUnknown(bool &known)
{
	downloadSizeUnknown = known;
	Q_EMIT downloadSizeUnknownModified();
}

int Backend::clone() {
	if (!opendir("sm64-builds/")) {
		mkdir("sm64-builds",0777);
	}
	//std::string stdFolder = "sm64-builds/";
	std::string command = "git clone --branch " + branch.toStdString() + " " + repo.toStdString() + " --progress > .out";
	/*const char *dir = (stdFolder).c_str();
	mkdir(dir,0777);*/
	std::string cmd = "cd sm64-builds && " + command + " &";
	char* fullCommand = new char[cmd.length() + 1];
	strcpy(fullCommand, cmd.c_str());
	system(fullCommand);
	buildFind(0);
	return 0;
}

/*int Backend::pull(QString &folder) {
	return 0;
}*/