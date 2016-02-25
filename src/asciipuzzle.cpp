#include "asciipuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>

AsciiPuzzle::AsciiPuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
    m_string = "(char)\r      \rXCVII\r     \rXCVIII\r      \rXCIX\r    \rXCVII\r     \rXCVIII\r      \rXCVIII\r      \rXCVII\r     \rwth?";
    m_timer.setInterval(200);
    m_count = 0;

    connect(&m_timer, SIGNAL(timeout()),
            this, SLOT(tick()));
}

QString AsciiPuzzle::continuationCode() const
{
    return "f8e4e210a9cc7194fefff605aae6a6df";
}

void AsciiPuzzle::startPuzzle()
{
    system(Command::clearCmd);
    m_count = 0;
    m_timer.start();
}

void AsciiPuzzle::tick()
{
    QTextStream out(stdout);
    if(m_count < m_string.count()) {
        out << m_string.at(m_count);
        out.flush();
        m_count++;
    }
    else {
        m_timer.stop();
        out << "\ncontinuation code: " << continuationCode();
        QTextStream in(stdin);
        QString password = "";
        out << "\n\nPassword: ";
        out.flush();
        password = in.readLine(10);

        emit answerGiven(password == "abcabba");
    }
}
