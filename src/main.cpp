#define VERSION "v0.0.1 Development Alpha"
#define LICENSE "Kirigami64 Copyright (C) 2022 Azreigh\nThis program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; type `show c' for details."

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <KLocalizedContext>
#include <KLocalizedString>

#include <iostream>
#include <algorithm>

#include <backend.h>

int main(int argc, char **argv)
{
    if (argc > 1) {
        if (strcmp(argv[1], "--license") == 0) {
            std::cout << LICENSE << "\n";
        }
        else if (strcmp(argv[1], "--version") == 0) {
            std::cout << VERSION << "\n";
        }
        return 0;
    }
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("kirigami64");
    QCoreApplication::setOrganizationName(QStringLiteral("azreigh"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("null"));
    QCoreApplication::setApplicationName(QStringLiteral("Kirigami64"));

    QQmlApplicationEngine engine;

    Backend backend;

    qmlRegisterSingletonInstance<Backend>("org.azreigh.kirigami64", 0, 1, "Backend", &backend);

    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
