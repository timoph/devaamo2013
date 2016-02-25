#ifndef SHELLPUZZLE_H
#define SHELLPUZZLE_H

#include "abstractpuzzle.h"

class ShellPuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit ShellPuzzle(QObject *parent = 0);
    QString continuationCode() const;
    
signals:
    
public slots:
    void startPuzzle();

private:
    void runShell();
    void processCommand(const QString &cmd);
    void handleCat(const QString &cmd);
    void handleGcc(const QString &cmd);
    void handleGdb(const QString &cmd);
    void handleFile(const QString &cmd);
    void handleRunCompiled(const QString &cmd);
    void runGdb();

private:
    bool m_isCompiled;
    QString m_compiledName;
};

#endif // SHELLPUZZLE_H
