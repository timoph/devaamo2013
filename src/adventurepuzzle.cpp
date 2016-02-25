#include "adventurepuzzle.h"
#include "constants.h"

#include <QTextStream>
#include <unistd.h>

AdventurePuzzle::AdventurePuzzle(QObject *parent) :
    AbstractPuzzle(parent)
{
    m_passed = false;
    m_state = 0;
    m_stateMessages.append("* You are in what appears to be a dark room or you have your eyes closed. You are tied to a chair with a rope and your mouth is taped shut.\n");
    m_stateMessages.append("* You are in the dark room now without being tied to the chair\n");
    m_stateMessages.append("* You are in a room now with lights. The room has a table, a chair and a door.\n");
    m_stateMessages.append("* You have won the game and can now go back to the puzzle.\n");
}

QString AdventurePuzzle::continuationCode() const
{
    return "8353dec1be5cad06fe150a8738c9060e";
}

void AdventurePuzzle::startPuzzle()
{
    system(Command::clearCmd);
    QTextStream out(stdout);
    out << "continuation code: " << continuationCode() << "\n\n";
    out << "Let's take a break from the puzzle and play an adventure game.\n\n";
    out << "Available commands: help, look (<item>), take <item>, use <item> (with <item>), inventory, talk <person>, quit\n\n";
    out.flush();
    gameMain();

    QString password = "";
    QTextStream in(stdin);
    out << "Password: ";
    out.flush();
    password = in.readLine(15);

    if(password != "whoamireally") {
        emit answerGiven(false);
    }
    else {
        emit answerGiven(true);
    }
}

void AdventurePuzzle::gameMain()
{
    m_passed = false;
    m_state = 0;
    m_inventoryList.clear();
    m_inventoryList.append("duct-tape");
    m_inventoryList.append("knife");

    QTextStream out(stdout);
    while(!m_passed) {
        out << m_stateMessages.at(m_state);
        out.flush();
        getCommand();
    }
}

void AdventurePuzzle::getCommand()
{
    QTextStream out(stdout);
    out << "> ";
    out.flush();
    QTextStream in(stdin);
    QString command = in.readLine(50);

    if(command == "inventory") {
        for(int i = 0; i < m_inventoryList.count(); i++) {
            out << m_inventoryList.at(i) << "\n";
        }
        out.flush();
    }
    else if(command.startsWith("talk")) {
        if(m_state == 0) {
            out << "With your mount taped shut you fail to talk.\n";
        }
        else if(command.endsWith("self")) {
            out << "You start talking to yourself by introducing yourself - \"My name is MacGyver.\"\n";
            if(m_state != 1) {
                out << "After talking nonsense to yourself for while you learn nothing.\n";
            }
        }
        else {
            out << "You give a monologue.\n";
        }

        if(m_state == 1) {
            out << "Suddenly the lights turn on. Voice activated lights FTW!\n";
            m_state = 2;
        }
        out.flush();
    }
    else if(command.startsWith("take")) {
        if(command.endsWith("note") && m_state > 1) {
            pickup("note");
        }
        else if(command.endsWith("rope") && m_state > 0) {
            pickup("rope");
        }
        else {
            out << "what?\n";
        }
        out.flush();
    }
    else if(command.startsWith("use")) {
        QStringList words = command.split(" ");
        if(words.contains("knife") && words.contains("rope") && m_state == 0) {
            out << "You dislocate your shoulder, take your trusty swiss army knife and cut the rope.\n";
            m_state = 1;
        }
        else if(words.contains("knife") && words.contains("chair") && m_state > 1) {
            out << "You carve your initial A.M to the chair and grin at your artwork.\n";
        }
        else if(words.contains("knife") && words.contains("table") && m_state > 1) {
            out << "You carve your initial A.M to the table and grin at your artwork.\n";
        }
        else if(words.contains("knife") && words.contains("door") && m_state > 1) {
            out << "You start picking to lock and give up after noticing that there is no lock to pick.\n";
        }
        else if(words.contains("duct-tape") && words.contains("chair") && m_state > 1) {
            out << "You assemble a childrens' feeding chair from the chair using you duct-tape.\n";
        }
        else if(words.contains("duct-tape") && words.contains("table") && m_state > 1) {
            out << "You ponder about building a vaccuum cleaner from the table and decide not to.\n";
        }
        else if(words.contains("duct-tape") && words.contains("door") && m_state > 1) {
            out << "You decide that door is already shut tight enough.\n";
        }
        else if(words.contains("rope") && words.contains("duct-tape") && m_state > 1 && m_inventoryList.contains("rope")) {
            out << "You contruct a new hat for yourself using duct-tape and rope.\n";
            m_inventoryList.append("hat");
        }
        else {
            out << "not doing that.\n";
        }
        out.flush();
    }
    else if(command.startsWith("look")) {
        QStringList words = command.split(" ");
        look(words.last());
    }
    else if(command == "help") {
        out << "Available commands: help, look (<item>), take <item>, use <item> (with <item>), inventory, talk (<person>), quit\n\n";
        out.flush();
    }
    else if(command == "quit") {
        m_passed = true;
    }
    else {
        out << QString("don't ever say \"%1\" to me again. that doesn't make any sense.\n").arg(command);
        out.flush();
    }
}

void AdventurePuzzle::pickup(const QString &item)
{
    QTextStream out(stdout);
    if(!m_inventoryList.contains(item)) {
        out << QString("You stuff %1 into you pocket.\n").arg(item);
        m_inventoryList.append(item);
    }
    else {
        out << "you already have it.\n";
    }
    out.flush();
}

void AdventurePuzzle::look(const QString &item)
{
    QTextStream out(stdout);
    if(m_inventoryList.contains(item)) {
        if(item == "duct-tape") {
            out << "never leave home without it.\n";
        }
        else if(item == "knife") {
            out << "It's your trusty swiss army knife. Shiny.\n";
        }
        else if(item == "rope") {
            out << "Yep. That's the rope that was used to tie you to the chair.\n";
        }
        else if(item == "note") {
            out << "The note has only one word written to it - \"whoamireally\"\n";
            out << "You have successfully obtained what you came for and leave the room simply by pushing the door open.\n";
            out << "In hindsind leaving the room might have been easier if the developers would have bothered to implement the push command.\n";
            m_state = 3;
        }
    }
    else if(item == "chair") {
        if(m_state == 0) {
            out << "Only thing interesting about the chair is that you are tied to it with a thick rope.\n";
        }
        else {
            out << "The chair is totally uninteresting now that you're free.\n";
        }
    }
    else if(m_state < 2) {
        out << "You might see something if you had night vision.\n";
    }
    else if(item == "door") {
        out << "locked, nailed and boarded shut. No way to get out through that door.\n";
    }
    else if(item == "table") {
        if(!m_inventoryList.contains("note") && m_state > 1) {
            out << "there's a note on the table.\n";
        }
        else {
            out << "Yep. it's a table. Nothing unusual about it.\n";
        }
    }
    else {
        out << "You medite to see something not there and fail.\n";
    }
    out.flush();
}
