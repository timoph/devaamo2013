#include "battlepuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>

BattlePuzzle::BattlePuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
}

QString BattlePuzzle::continuationCode() const
{
    return "4b9980eec1dee7c7167453e2c651bea7";
}

void BattlePuzzle::startPuzzle()
{
    system(Command::clearCmd);
    QTextStream out(stdout);
    out << "continuation code: " << continuationCode() << "\n\n";
    out << "FTW!\n\n";
    out << "  1 2 3 4 5\n";
    out << "a . . x x .\n";
    out << "b . * x . .\n";
    out << "c . x * x .\n";
    out << "d . . x * .\n";
    out << "e . x . x .\n";
    out << "\n\n";
    out.flush();

    QString password = "";
    QTextStream in(stdin);
    out << "Password: ";
    out.flush();
    password = in.readLine(10);

    if(password == "b2c3d4" || password == "b2 c3 d4") {
        emit answerGiven(true);
    }
    else {
        emit answerGiven(false);
    }
}
