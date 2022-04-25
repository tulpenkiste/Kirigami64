#pragma once

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString introductionText READ introductionText WRITE setIntroductionText NOTIFY introductionTextChanged)
    Q_PROPERTY(QString repoText READ repoText WRITE setRepo NOTIFY repoChanged)
    Q_PROPERTY(QString branchText READ branchText WRITE setBranch NOTIFY branchChanged)
    Q_PROPERTY(QString folderText READ folderText WRITE setFolder NOTIFY folderChanged)
private:
    QString m_introductionText = "Kirigami64-TestText";
    QString repo = "";
    QString branch = "";
    QString folder = "";
public:
    explicit Backend(QObject *parent = nullptr);
    QString introductionText() const;
    QString repoText();
    QString branchText();
    QString folderText();
    void setIntroductionText(const QString &introductionText);
    void setRepo(QString &repoInp);
    void setBranch(QString &branchInp);
    void setFolder(QString &folderInp);
    Q_SIGNAL void introductionTextChanged();
    Q_SIGNAL void repoChanged();
    Q_SIGNAL void branchChanged();
    Q_SIGNAL void folderChanged();
    Q_INVOKABLE int clone();
};
