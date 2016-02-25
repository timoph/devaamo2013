#include "braillepuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>

BraillePuzzle::BraillePuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
}

QString BraillePuzzle::continuationCode() const
{
    return "2e9ab5868cd0c18a988016b08736c311";
}

void BraillePuzzle::startPuzzle()
{
    QTextStream out(stdout);
    QTextStream in(stdin);
    QString password = "";

    system(Command::clearCmd);

    out << "continuation code: " << continuationCode() << "\n\n";
    out << "Devaamo hacking challenge right at your fingertips\n\n";
    out << QChar(10265) << QChar(10254) << QChar(10266);
    out << QChar(10266) << QChar(10265) << QChar(10254);
    out << "\nPassword: ";
    out.flush();
    password = in.readLine(10);

    if(password.toLower() != "dsjjds") {
    	emit answerGiven(false);
    }
	else {
    	emit answerGiven(true);
	}
}
