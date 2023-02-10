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

#include "backend.h"
#include "about.h"
#include "config.h"

int main(int argc, char *argv[]) {
	// I have no idea if this will be efficient.
	std::string versionFull = PROJECT_VER;
	versionFull.append(" - ");
	versionFull.append(PROJECT_VER_SUBTITLE);
	KAboutData aboutData(
						 // The program name used internally.
						 QStringLiteral("Kirigami64"),
						 // A displayable program name string.
						 i18nc("@title", "Kirigami64"),
						 // The program version string.
						 QString::fromStdString(versionFull),
						 // Short description of what the app does.
						 i18n("A launcher for the SM64 PC Port made using Kirigami."),
						 // The license this code is released under.
						 KAboutLicense::GPL_V3,
						 // Copyright Statement.
						 i18n("(c) 2022"));
	aboutData.setDesktopFileName("Kirigami64");
	aboutData.addAuthor(i18nc("@info:credit", "Tulip"), i18nc("@info:credit", "Creator"), QStringLiteral(""), QStringLiteral("https://tulip-sudo.github.io/"));
	aboutData.setBugAddress("https://github.com/tulip-sudo/Kirigami64/issues");
	aboutData.setHomepage("https://github.com/tulip-sudo/Kirigami64/");

	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);
	app.setWindowIcon(QIcon(":/icon.png"));
	KAboutData::setApplicationData(aboutData);

	QQmlApplicationEngine engine;

	Backend backend;

	chdir(string_to_char(getenv("HOME") + (std::string)"/.local/share/Kirigami64"));

	std::cout << std::filesystem::current_path() << std::endl;

	backend.buildFind(0);
	backend.handleSources();

	qmlRegisterSingletonType<AboutType>("org.tulip.Kirigami64", 0, 2, "AboutType", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
		Q_UNUSED(engine)
		Q_UNUSED(scriptEngine)

		return new AboutType();
	});

	qmlRegisterSingletonInstance<Backend>("org.tulip.Kirigami64", 0, 2, "Backend", &backend);

	engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	if (engine.rootObjects().isEmpty()) {
		return -1;
	}

	app.exec();
}
