#define VERSION "v0.1"

#include <KAboutData>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <KLocalizedContext>
#include <KLocalizedString>

#include <iostream>
#include <algorithm>

#include "backend.h"
#include "config-Kirigami64.h"
#include "about.h"

int main(int argc, char *argv[])
{
	QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QApplication app(argc, argv);
	
	KAboutData aboutData(
						 // The program name used internally.
						 QStringLiteral("Kirigami64"),
						 // A displayable program name string.
						 i18nc("@title", "Kirigami64"),
						 // The program version string.
						 QStringLiteral(VERSION),
						 // Short description of what the app does.
						 i18n("A launcher for the SM64 PC Port made using Kirigami."),
						 // The license this code is released under.
						 KAboutLicense::GPL_V3,
						 // Copyright Statement.
						 i18n("(c) 2022"));
	aboutData.addAuthor(i18nc("@info:credit", "Azreigh"), i18nc("@info:credit", "Creator"), QStringLiteral("email_invalid"), QStringLiteral("https://azreigh.github.io/"));
	aboutData.setBugAddress("https://github.com/azreigh/Kirigami64/issues");
	KAboutData::setApplicationData(aboutData);

	QQmlApplicationEngine engine;

	Backend backend;

	qmlRegisterSingletonType<AboutType>("org.azreigh.Kirigami64", 0, 1, "AboutType", [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
		Q_UNUSED(engine)
		Q_UNUSED(scriptEngine)

		return new AboutType();
	});

	qmlRegisterSingletonInstance<Backend>("org.azreigh.Kirigami64", 0, 1, "Backend", &backend);

	engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
	engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

	if (engine.rootObjects().isEmpty()) {
		return -1;
	}

	return app.exec();
}
