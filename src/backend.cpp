#include "backend.h"

#include <iostream>
#include <string>

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

int Backend::clone() {
    return 0;
}