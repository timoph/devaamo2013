#include "fallospuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>
#include <QTimer>
#include <QDebug>
#include <QDateTime>

FallOsPuzzle::FallOsPuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
    mCorrect = "";
    qsrand(QDateTime::currentMSecsSinceEpoch());
    mWordList << "LERYKLD" << "KOPOTIS" << "MOPOTIS" << "ROBOTIS" << "HIPITUS" << "HIPOTUS";
    mWordList << "KERPELE" << "PERKULE" << "VIRVELI" << "HIMMELI" << "KERKELE" << "MERKELE";
    mWordList << "PERNILX" << "LOPOTES" << "HIMMELI" << "KIMMELI" << "TERVAUS" << "KARKAUS";
    mWordList << "KARKAUS" << "VARKAUS" << "MOTTAUS" << "KITTAUS" << "MITTAUS" << "LERPAKE";

    Q_ASSERT(mWordList.count() == 24);
}

void FallOsPuzzle::startPuzzle()
{
    QTextStream in(stdin);
    QTextStream out(stdout);
    QString answer = "";
    bool figuredOut = false;
    int tryCount = 0;
    bool firstGo = true;
    mCorrect = mWordList.at(qrand() % mWordList.count()).toLower();
    //out << mCorrect;

    while(tryCount < 4) {
        tryCount++;
        system(Command::clearCmd);
        out << "continuation code: " << continuationCode() << "\n\n";
        out << "FALL-OS (TM) TERMLINK PROTOCOL\n";
        out << "ENTER PASSWORD NOW\n\n";
        out << QString("%1 ATTEMPTS LEFT:").arg(5 - tryCount);
        for(int i = 0; i < 5 - tryCount; i++) {
            out << " *";
        }
        out << "\n";
        if(!firstGo) {
            out << "\n";
            for(int i = 0; i < mGuessList.count(); i++) {
                out << QString("%1 %2/%3 correct.\n")
                       .arg(mGuessList.at(i).first)
                       .arg(mGuessList.at(i).second)
                       .arg(mCorrect.size());
            }
        }
        firstGo = false;

        out << QString("\n0xb005 !<%#/%1 0xn02b %2!<%#/\n")
               .arg(mWordList.at(0)).arg(mWordList.at(1));
        out << QString("0x000b !<%#/%.!<%#/%. 0xtb01 !<%#/%1\n")
               .arg(mWordList.at(2));
        out << QString("0xbb01 !<%#/%.%1 0x0dda %2!<%#/\n")
               .arg(mWordList.at(3)).arg(mWordList.at(4));
        out << QString("0xb00b %1!<%#/%. 0xc45b %2!<%#/\n")
               .arg(mWordList.at(5)).arg(mWordList.at(6));
        out << QString("0xaa01 !<%#/%.!<%#/%. 0x000d !<%#/%1\n")
               .arg(mWordList.at(7));
        out << QString("0x0044 !<%#/%.!<%#/%. 0xdddd %1!<%#/\n")
               .arg(mWordList.at(8));
        out << QString("0xb010 %1!<%#/%. 0x7fg3 !<%#/%2\n")
               .arg(mWordList.at(9)).arg(mWordList.at(10));
        out << QString("0x0a0a !<%#/%.%1 0x0020 %2!<%#/\n")
               .arg(mWordList.at(11)).arg(mWordList.at(12));
        out << QString("0xc1a4 %1!<%#/%. 0xn23b !<%#/%2\n")
               .arg(mWordList.at(13)).arg(mWordList.at(14));
        out << QString("0xea00 !<%#/%.!<%#/%. 0xc993 !<%#/!<%#/\n");
        out << QString("0x0001 !<%#/%.%1 0x0022 %2!<%#/\n")
               .arg(mWordList.at(15)).arg(mWordList.at(16));
        out << QString("0x0ad0 %1!<%#/%. 0x1abc !<%#/%2\n")
               .arg(mWordList.at(17)).arg(mWordList.at(18));
        out << QString("0xba44 !<%#/%.%1 0x0022 %2!<%#/\n")
               .arg(mWordList.at(19)).arg(mWordList.at(20));
        out << QString("0xc310 !<%#/%.<%#/%. 0x8abd !<%#/!<%#/\n");
        out << QString("0x8021 %1!<%#/%. 0xc001 !<%#/%2\n")
               .arg(mWordList.at(21)).arg(mWordList.at(22));
        out << QString("0x7650 !<%#/%.!<%#/%. 0x0101 %1!<%#/ ")
               .arg(mWordList.at(23));

        out << "> ";
        out.flush();
        answer = in.readLine(10);
        figuredOut = checkAnswer(answer);
        if(figuredOut) {
            break;
        }
    }

    mGuessList.clear();
    emit answerGiven(figuredOut);
}

QString FallOsPuzzle::continuationCode() const
{
    return "a95d217e620ea0b25d610833a43c187c";
}

bool FallOsPuzzle::checkAnswer(const QString &txt)
{
    if(txt.isEmpty()) return false;

    QString answer = txt.toLower();

    int count = 0;
    for(int i = 0; i < mCorrect.count(); i++) {
        if(answer.size() - 1 >= i) {
            if(mCorrect.at(i) == answer.at(i)) {
                count++;
            }
        }
    }

    mGuessList.append(QPair<QString, int>(answer, count));

    return mCorrect == answer;
}

