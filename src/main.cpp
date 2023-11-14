#include <KAboutData>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <QIcon>
#include <KLocalizedContext>
#include <KLocalizedString>

#include <iostream>
#include <algorithm>
#include <filesystem>

#include "backend.hpp"
#include "about.hpp"
#include "config.hpp"

int main(int argc, char *argv[]) {
	std::string versionFull = PROJECT_VER;
	versionFull.append(" - ");
	versionFull.append(PROJECT_VER_SUBTITLE);

	KLocalizedString::setApplicationDomain(QByteArrayLiteral("kirigami64"));

	KAboutData aboutData(
						 // The program name used internally.
						 QStringLiteral("Kirigami64"),
						 // A displayable program name string.
						 i18nc("@title", "Kirigami64"),
						 // The program version string.
						 QString::fromStdString(versionFull),
						 // Short description of what the app does.
						 i18n("Launcher for the Super Mario 64 PC Port made using QtQuick and Kirigami2."),
						 // The license this code is released under.
						 KAboutLicense::GPL_V3,
						 // Copyright Statement.
						 i18n("(c) 2022"));
	aboutData.setDesktopFileName("Kirigami64");
	aboutData.addAuthor(i18nc("@info:credit", "Tulip"), i18nc("@info:credit", "Creator"), QStringLiteral(""), QStringLiteral("https://tulpenkiste.codeberg.page/"));
	aboutData.setBugAddress("https://codeberg.org/tulpenkiste/Kirigami64/issues");
	aboutData.setHomepage("https://codeberg.org/tulpenkiste/Kirigami64");

	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/icon.png"));
	KAboutData::setApplicationData(aboutData);

	QQmlApplicationEngine engine;

	Backend backend;

	std::filesystem::path shareDir{getenv("HOME") + (std::string)"/.local/share/Kirigami64"};
	if (!std::filesystem::exists(shareDir)) std::filesystem::create_directory(shareDir);

	chdir(string_to_char(getenv("HOME") + (std::string)"/.local/share/Kirigami64"));

	//std::cout << std::filesystem::current_path() << std::endl;

	backend.buildFind(0);
	backend.handleSources();

	qmlRegisterSingletonType<AboutType>("org.tulpenkiste.kirigami64", 0, 2, "AboutType", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
		Q_UNUSED(engine)
		Q_UNUSED(scriptEngine)

		return new AboutType();
	});

	qmlRegisterSingletonInstance<Backend>("org.tulpenkiste.kirigami64", 0, 2, "Backend", &backend);

	engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	if (engine.rootObjects().isEmpty()) {
		return -1;
	}

	app.exec();
}
