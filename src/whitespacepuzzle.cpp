#include "whitespacepuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>

WhiteSpacePuzzle::WhiteSpacePuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
}

QString WhiteSpacePuzzle::continuationCode() const
{
    return "3589481610218c73dea2c1444397c1da";
}

void WhiteSpacePuzzle::startPuzzle()
{
    system(Command::clearCmd);
    QTextStream out(stdout);
    out << "continuation code: " << continuationCode() << "\n\n";
    out << "tail -f /dev/transmission > /var/www/recording.txt\n";
    out << "I wonder if there is a sequence in there?\n\n";
    out.flush();

    QString password = "";
    QTextStream in(stdin);
    out << "Password: ";
    out.flush();
    password = in.readLine(10);

    if(password != "sos") {
        emit answerGiven(false);
    }
    else {
        emit answerGiven(true);
    }
}
