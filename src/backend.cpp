#include "backend.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <dirent.h>
#include <errno.h>

Backend::Backend(QObject *parent)
    : QObject(parent)
{
}

QString Backend::repoText()
{
    return repo;
}

QString Backend::branchText()
{
    return branch;
}

QString Backend::folderText()
{
    return folder;
}

bool Backend::downloadSizeUnknownValue() {
    return downloadSizeUnknown;
}

void Backend::setRepo(QString &repoInp)
{
    repo = repoInp;
    Q_EMIT repoChanged();
}

void Backend::setBranch(QString &branchInp)
{
    branch = branchInp;
    Q_EMIT branchChanged();
}

void Backend::setFolder(QString &folderInp)
{
    folder = folderInp;
    Q_EMIT folderChanged();
}

void Backend::setDownloadSizeUnknown(bool &known)
{
    downloadSizeUnknown = known;
    Q_EMIT downloadSizeUnknownChanged();
}

int Backend::clone() {
    if (!opendir("sm64-builds/")) {
        mkdir("sm64-builds",0777);
    }
    std::string stdFolder = "sm64-builds/" + folder.toStdString();
    std::string command = "git clone --branch " + branch.toStdString() + " " + repo.toStdString() + " .";
    const char *dir = (stdFolder).c_str();
    mkdir(dir,0777);
    std::string cmd = "cd " + stdFolder + " && " + command + " &";
    char* fullCommand = new char[cmd.length() + 1];
    strcpy(fullCommand, cmd.c_str());
    system(fullCommand);
    return 0;
}