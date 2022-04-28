#pragma once

#include <QObject>

class Backend : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int buildCount READ buildCountValue WRITE buildFind NOTIFY buildCountChanged)
	Q_PROPERTY(QString repoText READ repoText WRITE setRepo NOTIFY repoChanged)
	Q_PROPERTY(QString branchText READ branchText WRITE setBranch NOTIFY branchChanged)
	Q_PROPERTY(bool downloadSizeUnknown READ downloadSizeUnknownValue WRITE setDownloadSizeUnknown NOTIFY downloadSizeUnknownChanged)
private:
	int buildCount = 0;
	QString repo = "";
	QString branch = "";
	bool downloadSizeUnknown = true;
public:
	explicit Backend(QObject *parent = nullptr);
	int buildCountValue();
	QString repoText();
	QString branchText();
	bool downloadSizeUnknownValue();
	Q_INVOKABLE void buildFind(int additive);
	void setRepo(QString &repoInp);
	void setBranch(QString &branchInp);
	void setCloneText(QString &newCloneText);
	void setDownloadSizeUnknown(bool &known);
	Q_SIGNAL void buildCountChanged();
	Q_SIGNAL void repoChanged();
	Q_SIGNAL void branchChanged();
	Q_SIGNAL void downloadSizeUnknownChanged();
	Q_INVOKABLE int clone();
};
