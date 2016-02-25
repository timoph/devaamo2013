#include "engine.h"
#include "intropuzzle.h"
#include "fallospuzzle.h"
#include "bfpuzzle.h"
#include "asciipuzzle.h"
#include "braillepuzzle.h"
#include "urlpuzzle.h"
#include "adventurepuzzle.h"
#include "battlepuzzle.h"
#include "whitespacepuzzle.h"
#include "shellpuzzle.h"
#include "constants.h"

#include <iostream>
#include <QCoreApplication>
#include <QTimer>
#include <unistd.h>
#include <QTextStream>
#include <QDateTime>

Engine::Engine(QObject *parent) :
    QObject(parent)
{
    m_currentPuzzle = -1;
    m_puzzleList.append(new IntroPuzzle(this));
    m_puzzleList.append(new FallOsPuzzle(this));
    m_puzzleList.append(new UrlPuzzle(this));
    m_puzzleList.append(new AsciiPuzzle(this));
    m_puzzleList.append(new AdventurePuzzle(this));
    m_puzzleList.append(new BattlePuzzle(this));
    m_puzzleList.append(new WhiteSpacePuzzle(this));
    m_puzzleList.append(new BraillePuzzle(this));
    m_puzzleList.append(new BfPuzzle(this));
    m_puzzleList.append(new ShellPuzzle(this));
}

int Engine::puzzleCount() const
{
    return m_puzzleList.count();
}

int Engine::currentPuzzle() const
{
    return m_currentPuzzle;
}

void Engine::startChallenge()
{
    if(m_puzzleList.count() > 0) {
        m_currentPuzzle = checkContinuationCode();
        connect(m_puzzleList[m_currentPuzzle], SIGNAL(answerGiven(bool)),
                this, SLOT(answerGiven(bool)));
        m_puzzleList.at(m_currentPuzzle)->startPuzzle();
    }
    else {
        std::cerr << "No puzzles available";
    }
}


void Engine::addPuzzle(AbstractPuzzle *puzzle)
{
    m_puzzleList.append(puzzle);
}

void Engine::answerGiven(bool correct)
{
    if(correct) {
        //next puzzle
        disconnect(m_puzzleList[m_currentPuzzle], SIGNAL(answerGiven(bool)),
                this, SLOT(answerGiven(bool)));
        m_currentPuzzle++;
        if(m_currentPuzzle >= puzzleCount()) {
            //won
            system(Command::clearCmd);
            QString timestamp = QDateTime::currentDateTime().toString("d.M.yyyy hh.mm.ss");
            std::cout << "Victory! You have solved all the puzzles." << timestamp.toStdString() << std::endl;
            std::cout << "Show this view or give the following hash to the judges as the proof for beating the challenge." << std::endl;
            std::cout << "9e776d00fe7d52e741aef6f61a13ac92" << std::endl;
            std::cout << "Press something to quit the challenge..";
            getchar();
            qApp->exit();
        }
        else {
            std::cout << "Yay! Lets proceed to the next level." << std::endl;
            connect(m_puzzleList[m_currentPuzzle], SIGNAL(answerGiven(bool)),
                    this, SLOT(answerGiven(bool)));
            QTimer::singleShot(800, m_puzzleList.at(m_currentPuzzle), SLOT(startPuzzle()));
        }
    }
    else {
        system(Command::clearCmd);
        std::cout << "Nope." << std::endl;
        QTimer::singleShot(800, m_puzzleList.at(m_currentPuzzle), SLOT(startPuzzle()));
    }
}

int Engine::checkContinuationCode() const
{
    QTextStream in(stdin);
    QTextStream out(stdout);
    system(Command::clearCmd);
    out << "Welcome to the Devaamo summit 2013 hacking challenge\n\n";
    out << "The idea of the challenge is to figure out a password to proceed\n";
    out << "to the next challenge\n\n";
    out << "Some password are pretty much spelled out for you, some require guessing";
    out << "\nor some something completely different.\n\n";
    out << "The winner will be the one who solves all the puzzles first or\n";
    out << "if no one solves them all, the one who solves most puzzles in the shortest time\n\n";
    out << "You will get a continuation code for each puzzle. They work as your proof of your progress.\n";
    out << "Give the last continuation code to the judges you have gotten before the challenge's time runs out.";
    out << "\n\nGood luck!\n\n";
    out << "Give continuation code or press whatever to get hacking.\n\n";
    out << "> ";
    out.flush();
    QString input = in.readLine(32);

    for(int i = 0; i < m_puzzleList.count(); i++) {
        if(m_puzzleList[i]->continuationCode() == input) {
            return i;
        }
    }

    return 0;
}
