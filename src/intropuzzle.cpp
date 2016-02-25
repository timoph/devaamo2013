#include "intropuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>

IntroPuzzle::IntroPuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
}

void IntroPuzzle::startPuzzle()
{
    system(Command::clearCmd);
    QTextStream out(stdout);
    out << "continuation code: " << continuationCode() << "\n\n";
    out << "Let's start by hacking someone's \"strong\" password.\n";
    out << "md5 for it is 286755fad04869ca523320acce0dc6a4\n\n";
    out.flush();

    QString password = "";
    QTextStream in(stdin);
    out << "Password: ";
    out.flush();
    password = in.readLine(10);

    if(password != "password") {
    	emit answerGiven(false);
	}
	else {
    	emit answerGiven(true);
	}
}

QString IntroPuzzle::continuationCode() const
{
    return "47e5bc1bd56b3705659a9892df5dc3ec";
}
