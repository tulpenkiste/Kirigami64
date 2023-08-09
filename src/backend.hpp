// It may be best to ignore this.
#pragma once

#include <git2.h>
#include <QObject>
#include <QSettings>
#include <vector>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#include <KConfigCore/KSharedConfig>
#include <KConfigCore/KConfigGroup>

char* string_to_char(std::string inp);

class Backend : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QSettings* sources READ sourceList NOTIFY sourceListModified)
	Q_PROPERTY(std::vector<QString> buildNames READ buildNamesDataGet NOTIFY buildConfigListModified)
	Q_PROPERTY(std::vector<QString> buildDescriptions READ buildDescriptionsDataGet NOTIFY buildConfigListModified)
	Q_PROPERTY(std::vector<QString> buildIcons READ buildIconsDataGet NOTIFY buildConfigListModified)
	Q_PROPERTY(int buildCount READ buildCountValue WRITE buildFind NOTIFY buildCountModified)
	Q_PROPERTY(int buildSelected READ buildSelectedValue WRITE setBuildSelected NOTIFY buildSelectModified)
	Q_PROPERTY(QString curBuild READ buildList NOTIFY buildListModified)
	Q_PROPERTY(QString repoText READ repoText WRITE setRepo NOTIFY repoModified)
	Q_PROPERTY(QString branchText READ branchText WRITE setBranch NOTIFY branchModified)
	Q_PROPERTY(bool downloadSizeUnknown READ downloadSizeUnknownValue WRITE setDownloadSizeUnknownStatus NOTIFY downloadSizeUnknownStatus)
	Q_PROPERTY(bool useGameMode READ usingGameMode WRITE setUseGameMode NOTIFY useGameModeModified)
	Q_PROPERTY(bool useMangoHud READ usingMangoHud WRITE setUseMangoHud NOTIFY useMangoHudModified)
private:
	QSettings* sources;
	std::string region = "us";
	int buildCount = 0;
	int buildSelected = 0;
	QString curBuild = "";
	std::vector<QString> builds = {""};
	std::vector<QString> buildNames;
	std::vector<QString> buildDescriptions;
	std::vector<QString> buildIcons;
	QString link = "";
	QString branch = "";
	bool downloadSizeUnknown = true;
	bool useMangoHud = false;
	bool useGameMode = false;

	// Key is region (us, eu, jp) and value is system path
	std::map<std::string, std::string> roms;

	KSharedConfigPtr launcherConfig;
	KConfigGroup launcherRepoDefaults;
	KConfigGroup launcherRoms;
public:
	explicit Backend(QObject *parent = nullptr);
	~Backend();
	QSettings* sourceList();
	std::vector<QString> buildNamesDataGet();
	std::vector<QString> buildDescriptionsDataGet();
	std::vector<QString> buildIconsDataGet();
	Q_INVOKABLE QString buildConfigSpecificDataGet(int build = 0, int type = 0);
	Q_INVOKABLE QStringList sourceGroups();
	int buildCountValue();
	int buildSelectedValue();
	Q_INVOKABLE QString buildList(int pos = 0);
	QString repoText();
	QString branchText();
	bool downloadSizeUnknownValue();
	bool usingMangoHud();
	bool usingGameMode();
	Q_INVOKABLE void buildFind(int additive);
	Q_INVOKABLE void setBuildSelected(int target);
	void setRepo(QString repoInp);
	void setBranch(QString branchInp);
	void setCloneText(QString newCloneText);
	void setDownloadSizeUnknownStatus(bool known);
	void setUseMangoHud(bool usingMangoHud);
	void setUseGameMode(bool newGameModeVal);
	Q_SIGNAL void sourceListModified();
	Q_SIGNAL void buildConfigListModified();
	Q_SIGNAL void buildCountModified();
	Q_SIGNAL void buildSelectModified();
	Q_SIGNAL void buildListModified();
	Q_SIGNAL void repoModified();
	Q_SIGNAL void branchModified();
	Q_SIGNAL void downloadSizeUnknownStatus();
	Q_SIGNAL void useMangoHudModified();
	Q_SIGNAL void useGameModeModified();
	Q_INVOKABLE int addShortcut(QString folder);
	Q_INVOKABLE void modifyConfig(QString name, QString description, QString icon);
	Q_INVOKABLE int clone(QString repoSel);
	Q_INVOKABLE int pull(QString folder);
	Q_INVOKABLE int build(QString folder);
	Q_INVOKABLE int run(QString folder);
	Q_INVOKABLE int rmDir(QString folder);
	Q_INVOKABLE int openSources();
	Q_INVOKABLE int handleSources();
	Q_INVOKABLE void openRepoDataDir();
};
