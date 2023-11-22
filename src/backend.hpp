// It may be best to ignore this.
#pragma once

#include "qfilesystemwatcher.h"
#include "qobjectdefs.h"
#include "qtpreprocessorsupport.h"
#include <git2.h>
#include <QObject>
#include <QSettings>
#include <iostream>
#include <vector>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <KConfigCore/KSharedConfig>
#include <KConfigCore/KConfigGroup>

char* string_to_char(std::string inp);

class Backend : public QObject {
	Q_OBJECT
public:
	explicit Backend(QObject *parent = nullptr);
	~Backend();
	Q_INVOKABLE QString buildConfigSpecificDataGet(int build = 0, int type = 0);
	Q_INVOKABLE QStringList sourceGroups();
	Q_INVOKABLE int currentRegion();
	Q_INVOKABLE QString buildList(int pos = 0);
	Q_INVOKABLE void setCurrentRegion(int region);
	Q_INVOKABLE void buildFind(int additive);
	Q_INVOKABLE void setBuildSelected(int target);
	Q_INVOKABLE void setROMPath(int region, QString path);
	Q_INVOKABLE QString getROMPath(int region);
	Q_INVOKABLE int addShortcut(QString folder);
	Q_INVOKABLE void modifyConfig(QString name, QString description, QString icon, int region);
	Q_INVOKABLE int clone(QString repoSel);
	Q_INVOKABLE int pull(QString folder);
	Q_INVOKABLE int build(QString folder);
	Q_INVOKABLE int run(QString folder);
	Q_INVOKABLE int rmDir(QString folder);
	Q_INVOKABLE int openSources();
	Q_INVOKABLE int handleSources();
	Q_INVOKABLE void openRepoDataDir();
public slots:
	QSettings* sourceList();
	std::vector<QString> buildNamesDataGet();
	std::vector<QString> buildDescriptionsDataGet();
	std::vector<QString> buildIconsDataGet();
	std::vector<QString> romPathGet();
	int buildCountValue();
	int buildSelectedValue();
	QString repoText();
	QString branchText();
	bool downloadSizeUnknownValue();
	bool usingMangoHud();
	bool usingGameMode();
	void setRepo(QString repoInp);
	void setBranch(QString branchInp);
	//void setCloneText(QString newCloneText);
	void setDownloadSizeUnknownStatus(bool known);
	void setUseMangoHud(bool usingMangoHud);
	void setUseGameMode(bool newGameModeVal);

private slots:
	void onDirUpdate(const QString& str);
signals:
	void sourceListModified();
	void buildConfigListModified();
	void currentRegionModified();
	void buildCountModified();
	void buildSelectModified();
	void buildListModified();
	void romPathListModified();
	void repoModified();
	void branchModified();
	void downloadSizeUnknownStatus();
	void useMangoHudModified();
	void useGameModeModified();
private:
	QSettings* sources;
	int defaultRegion;
	std::vector<QString> romsPerRegion;
	int buildCount = 0;
	int buildSelected = 0;
	QString curBuild = "";
	std::vector<QString> builds = {""};
	std::vector<QString> buildNames;
	std::vector<QString> buildDescriptions;
	std::vector<QString> buildIcons;
	std::vector<int> buildRegions;
	QString link = "";
	QString branch = "";
	bool downloadSizeUnknown = true;
	bool useMangoHud = false;
	bool useGameMode = false;

	// Key is region (us, eu, jp) and value is system path
	std::map<std::string, std::string> roms;

	// Configuration
	KSharedConfigPtr launcherConfig;
	KConfigGroup launcherRepoDefaults;
	KConfigGroup launcherRoms;

	// Filesystem Watcher
	QFileSystemWatcher watcher;
};
