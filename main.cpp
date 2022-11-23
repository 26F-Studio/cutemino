#include <QDirIterator>
#include <QGuiApplication>
#include <QLocale>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include <controllers/GameManager.h>

using namespace CuteMino::Controllers;
using namespace std;

int main(int argc, char *argv[]) {
    qDebug() << "Initializing QtMino...";
    QDirIterator it(":/", QDirIterator::Subdirectories);
    while (it.hasNext())
        qDebug() << it.next();

    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    qmlRegisterType<GameManager>("CuteMino.Controllers", 1, 0, "GameManager");

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale: uiLanguages) {
        const QString baseName = "cutemino_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            QGuiApplication::installTranslator(&translator);
            break;
        }
    }

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/cutemino/main.qml"_qs);
    QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreated,
            &app,
            [url](QObject *obj, const QUrl &objUrl) {
                if (!obj && url == objUrl) {
                    QCoreApplication::exit(-1);
                }
            },
            Qt::QueuedConnection
    );
    engine.load(url);

    return QGuiApplication::exec();
}
