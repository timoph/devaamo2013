#include "urlpuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>

UrlPuzzle::UrlPuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
}

QString UrlPuzzle::continuationCode() const
{
    return "0e73fa85be02b6ebfb5af073e4d5386b";
}

void UrlPuzzle::startPuzzle()
{
    system(Command::clearCmd);
    QTextStream out(stdout);
    out << "continuation code: " << continuationCode() << "\n\n";
    out << "hippie@localhost:~$ sudo python photopagegen.py --input=Pictures/photo1.* --output=/var/www/wth.html 2>/dev/null 1>&2\n";
    out << "Password:\n";
    out << "hippie@localhost:~$ echo $?\n";
    out << "0\n";
    out << "hippie@localhost:~$\n\n";
    out.flush();

    QString password = "";
    QTextStream in(stdin);
    out << "Password: ";
    out.flush();
    password = in.readLine(15);

    if(password != "nothing.html") {
        emit answerGiven(false);
    }
    else {
        emit answerGiven(true);
    }
}
