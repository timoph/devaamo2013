#include "shellpuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>
#include <QStringList>
#include <QDateTime>

ShellPuzzle::ShellPuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
    m_isCompiled = false;
    m_compiledName = "a.out";
}

QString ShellPuzzle::continuationCode() const
{
    return "506acb842181a2f26769749136d6fec0";
}

void ShellPuzzle::startPuzzle()
{
    m_isCompiled = false;
    m_compiledName = "a.out";
    system(Command::clearCmd);
    QTextStream out(stdout);
    out << "continuation code: " << continuationCode() << "\n\n";
    out << "Welcome to insanely restricted shell (version 0.0.1 alpha)\n";
    out << "There will be bugs and dragons here so you will just have to work around them.\n\n";
    out.flush();

    runShell();

    QString password = "";
    QTextStream in(stdin);
    out << "Password: ";
    out.flush();
    password = in.readLine(30);

    if(password != "thisiswhatyouarelookingfor") {
        emit answerGiven(false);
    }
    else {
        emit answerGiven(true);
    }
}

void ShellPuzzle::runShell()
{
    QTextStream out(stdout);
    QTextStream in(stdin);
    QString command = "";

    do {
        out << "$ ";
        out.flush();
        command = in.readLine(30);
        processCommand(command);
    } while (command != "exit");
}

void ShellPuzzle::processCommand(const QString &cmd)
{
    QTextStream out(stdout);

    if(cmd.contains("|")) {
        out << "Piping not supported\n";
    }
    else if(cmd.startsWith("ls")) {
        out << "README main.c";
        if(m_isCompiled) out << " " << m_compiledName;
        out << "\n";
    }
    else if(cmd.startsWith("cat")) {
        handleCat(cmd);
    }
    else if(cmd == "pwd") {
        out << "/home/devaamo/.nsa/nothingtoseeheremovealong/";
    }
    else if(cmd.startsWith("echo")) {
        out << cmd.mid(5) << "\n";
    }
    else if(cmd.startsWith("gcc")) {
        handleGcc(cmd);
    }
    else if(cmd.startsWith("gdb")) {
        handleGdb(cmd);
    }
    else if(cmd.startsWith("uname")) {
        out << "Fall-OS/Hurd\n";
    }
    else if(cmd == "w") {
        out << "SER\tTTY\tFROM\tLOGIN@\tIDLE\tWHAT\n";
        out << "devaamo\tpts/2\t-\t9:00\t0.00s\tw\n";
    }
    else if(cmd.simplified() == "who") {
        out << QString("devaamo\thackterminal\t%1\n").arg(QDateTime::currentDateTime().toString("MMM d h:mm"));
    }
    else if(cmd.simplified() == "whoami") {
        out << "devaamo\n";
    }
    else if(cmd.startsWith("cd")) {
        out << "Permission denied.\n";
    }
    else if(cmd.startsWith("file")) {
        handleFile(cmd);
    }
    else if(m_isCompiled && cmd.startsWith("./")) {
        handleRunCompiled(cmd);
    }
    else if(cmd.simplified() == "" || cmd == "exit") {
        //nada
    }
    else {
        out << QString("%1 - command not found\n").arg(cmd.simplified());
    }

    out.flush();
}

void ShellPuzzle::handleCat(const QString &cmd)
{
    QTextStream out(stdout);

    if(cmd.split(" ").contains("main.c")) {
        out << "#include <stdio.h>\n";
        out << "#include \"../secret.h\"\n";
        out << "int main(int argc, char **argv)\n";
        out << "{\n";
        out << "    int t = 0;\n";
        out << "    int s = 1;\n";
        out << "\n";
        out << "    prinf(\"Hello\\n\");\n";
        out << "    for(t; t < s;) {\n";
        out << "        do_something()\n";
        out << "    }\n";
        out << "return 0;\n";
        out << "}\n";
    }
    else if(cmd.split(" ").contains("README")) {
        out << "TODO\n";
    }
    out.flush();
}

void ShellPuzzle::handleGcc(const QString &cmd)
{
    QStringList words = cmd.split(" ");
    QTextStream out(stdout);

    if(words.contains("main.c")) {
        if(words.contains("-o")) {
            int ind = words.indexOf("-o");
            if(ind <= words.count()) {
                m_compiledName = words.at(ind + 1);
            }
            else {
                m_compiledName = "a.out";
            }
            m_isCompiled = true;
        }
        else {
            m_compiledName = "a.out";
            m_isCompiled = true;
        }
    }
    else {
        out << "Error: no valid input specified\n";
        out.flush();
        return;
    }

    out.flush();
}

void ShellPuzzle::handleGdb(const QString &cmd)
{
    QStringList words = cmd.split(" ");
    QTextStream out(stdout);

    if(m_isCompiled && (words.contains(m_compiledName) || words.contains(QString("./%1").arg(m_compiledName)))) {
        runGdb();
    }
    else {
        out << "Error: Nothing to do\n";
    }

    out.flush();
}

void ShellPuzzle::handleFile(const QString &cmd)
{
    QStringList words = cmd.split(" ");
    QTextStream out(stdout);

    if(words.count() > 2) {
        out << "wow. that is a lot of parameters. I'll just ignore most of them\n";
    }

    if(words.contains("main.c")) {
        out << "main.c: ASCII c program text\n";
    }
    else if(words.contains("README")) {
        out << "README: ASCII text\n";
    }
    else if(words.contains(m_compiledName) && m_isCompiled) {
        out << m_compiledName << ": ELF 32-bit executable (GNU/Linux) dynamically linked (uses shared libs), not stipped\n";
    }
    else {
        out << "no file specified or you specified something not there. Not bothering to find out which is the case\n";
    }
    out.flush();
}

void ShellPuzzle::handleRunCompiled(const QString &cmd)
{
    QTextStream out(stdout);

    if(cmd.mid(2).startsWith(m_compiledName)) {
        out << "Hello\n";
        out << "Segmentation fault\n";
    }
    else {
        out << "Command not found\n";
    }
    out.flush();
}

void ShellPuzzle::runGdb()
{
    QTextStream out(stdout);
    QTextStream in(stdin);
    bool running = true;
    QString command = "";
    bool started = false;

    out << "GSPOT Debugger 0.0.1 alpha\n";
    out.flush();

    while(running) {
        out << ">> ";
        out.flush();
        command = in.readLine(20);
        if(command == "quit") {
            running = false;
        }
        else if(command == "bt" || command == "backtrace") {
            if(started) out << "0 thisiswhatyouarelookingfor\n";
            else out << "No crash to analyse.\n";
        }
        else if(command == "help") {
            out << "available commands: run start backtrace stop quit\n";
        }
        else if(command == "stop") {
            if(started) out << "Stopped\n";
            started = false;
        }
        else if(command == "start" || command == "run") {
            out << "Hello\n";
            out << "Segmentation fault\n";
            started = true;
        }
        out.flush();
    }
}
