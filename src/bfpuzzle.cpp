#include "bfpuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>

BfPuzzle::BfPuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
}

QString BfPuzzle::continuationCode() const
{
    return "f6609b1521da62ff5c9b1d2bf65e1d2f";
}

void BfPuzzle::startPuzzle()
{
    QTextStream out(stdout);
    QTextStream in(stdin);
    QString password = "";
    system(Command::clearCmd);
    out << "continuation code: " << continuationCode() << "\n\n";
    out << "$ cat mindlove.bf\n";
    out << "+++++ +++++\n";
    out << "[\n";
    out << "\t> +++++ +++++ +\n";
    out << "\t> +++++ +++++ +\n";
    out << "\t> +++++ +++++\n";
    out << "\t> +++++ +\n";
    out << "\t<<<< -\n";
    out << "]\n";                   
    out << "++\n"; 
    out << "> +++++ ++  \n";
    out << "> +++++\n";
    out << "> +  \n";
    out << "< -  \n";
    out << ">> -- \n";
    out << "<< . +\n";
    out << "> .\n";
    out << "<<<\n";
    out << "[\n";
    out << "\t>> .\n";
    out << "\t<< -\n";
    out << "]\n";
    out << "> .\n";
    out << "< +++++ +++++ .\n\n";

    out << "Password: ";
    out.flush();
    password = in.readLine(10);

    if(password != "ressu") {
        emit answerGiven(false);
    }
    else {
        emit answerGiven(true);
    }
}
