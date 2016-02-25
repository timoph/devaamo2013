#include <QCoreApplication>

#include "engine.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    Engine engine;
    engine.moveToThread(app.thread());
    engine.startChallenge();

    return app.exec();
}
