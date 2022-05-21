// It may be best to ignore this.
#pragma once

#include <QObject>
#include <QSettings>
#include <vector>

class Backend : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QSettings* sources READ sourceList NOTIFY sourceListModified)
	Q_PROPERTY(std::vector<QSettings*> buildConfig READ buildConfigDataGet NOTIFY buildConfigListModified)
	Q_PROPERTY(int buildCount READ buildCountValue WRITE buildFind NOTIFY buildCountModified)
	Q_PROPERTY(int buildSelected READ buildSelectedValue WRITE setBuildSelected NOTIFY buildSelectModified)
	Q_PROPERTY(QString curBuild READ buildList NOTIFY buildListModified)
	Q_PROPERTY(QString repoText READ repoText WRITE setRepo NOTIFY repoModified)
	Q_PROPERTY(QString branchText READ branchText WRITE setBranch NOTIFY branchModified)
	Q_PROPERTY(bool downloadSizeUnknown READ downloadSizeUnknownValue WRITE setDownloadSizeUnknownStatus NOTIFY downloadSizeUnknownStatus)
	Q_PROPERTY(bool useMangoHud READ usingMangoHud WRITE setUseMangoHud NOTIFY useMangoHudModified)
private:
	QSettings* sources;
	std::string region = "us";
	int buildCount = 0;
	int buildSelected = 0;
	QString curBuild = "";
	std::vector<QString> builds = {""};
	std::vector<QSettings*> buildConfig = {};
	QString repo = "";
	QString branch = "";
	bool downloadSizeUnknown = true;
	bool useMangoHud = false;
public:
	explicit Backend(QObject *parent = nullptr);
	QSettings* sourceList();
	std::vector<QSettings*> buildConfigDataGet();
	Q_INVOKABLE QString buildConfigSpecificDataGet(int build = 0, QString type = "name");
	Q_INVOKABLE QStringList sourceGroups();
	int buildCountValue();
	int buildSelectedValue();
	Q_INVOKABLE QString buildList(int pos = 0);
	QString repoText();
	QString branchText();
	bool downloadSizeUnknownValue();
	bool usingMangoHud();
	Q_INVOKABLE void buildFind(int additive);
	Q_INVOKABLE void setBuildSelected(int target);
	void setRepo(QString repoInp);
	void setBranch(QString branchInp);
	void setCloneText(QString newCloneText);
	void setDownloadSizeUnknownStatus(bool known);
	void setUseMangoHud(bool usingMangoHud);
	Q_SIGNAL void sourceListModified();
	Q_SIGNAL void buildConfigListModified();
	Q_SIGNAL void buildCountModified();
	Q_SIGNAL void buildSelectModified();
	Q_SIGNAL void buildListModified();
	Q_SIGNAL void repoModified();
	Q_SIGNAL void branchModified();
	Q_SIGNAL void downloadSizeUnknownStatus();
	Q_SIGNAL void useMangoHudModified();
	Q_INVOKABLE int addShortcut(QString folder);
	Q_INVOKABLE int clone(QString repoSel);
	Q_INVOKABLE int pull(QString folder);
	Q_INVOKABLE int build(QString folder);
	Q_INVOKABLE int run(QString folder);
	Q_INVOKABLE int rmDir(QString folder);
	Q_INVOKABLE int openSources();
	Q_INVOKABLE int handleSources();
};
