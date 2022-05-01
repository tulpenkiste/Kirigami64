// It may be best to ignore this.
#pragma once

#include <QObject>

class Backend : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int buildCount READ buildCountValue WRITE buildFind NOTIFY buildCountModified)
	Q_PROPERTY(int buildSelected READ buildSelectedValue WRITE setBuildSelected NOTIFY buildSelectModified)
	Q_PROPERTY(QString curBuild READ buildList WRITE buildListSet NOTIFY buildListModified)
	Q_PROPERTY(QString repoText READ repoText WRITE setRepo NOTIFY repoModified)
	Q_PROPERTY(QString branchText READ branchText WRITE setBranch NOTIFY branchModified)
	Q_PROPERTY(bool downloadSizeUnknown READ downloadSizeUnknownValue WRITE setDownloadSizeUnknownStatus NOTIFY downloadSizeUnknownStatus)
private:
	std::string region = "us";
	int buildCount = 0;
	int buildSelected = 0;
	QString curBuild = "";
	QString builds[255] = {};
	QString repo = "";
	QString branch = "";
	bool downloadSizeUnknown = true;
public:
	explicit Backend(QObject *parent = nullptr);
	int buildCountValue();
	int buildSelectedValue();
	Q_INVOKABLE QString buildList(int pos = 0);
	QString repoText();
	QString branchText();
	bool downloadSizeUnknownValue();
	Q_INVOKABLE void buildFind(int additive);
	Q_INVOKABLE void setBuildSelected(int target);
	void buildListSet(QString &folder);
	void setRepo(QString &repoInp);
	void setBranch(QString &branchInp);
	void setCloneText(QString &newCloneText);
	void setDownloadSizeUnknownStatus(bool &known);
	Q_SIGNAL void buildCountModified();
	Q_SIGNAL void buildSelectModified();
	Q_SIGNAL void buildListModified();
	Q_SIGNAL void repoModified();
	Q_SIGNAL void branchModified();
	Q_SIGNAL void downloadSizeUnknownStatus();
	Q_INVOKABLE int clone();
	Q_INVOKABLE int pull(QString folder);
	Q_INVOKABLE int build(QString folder);
	Q_INVOKABLE int run(QString folder);
	Q_INVOKABLE int rmDir(QString folder);
};
