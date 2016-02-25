#ifndef ENGINE_H
#define ENGINE_H

#include <QObject>
#include <QList>

class AbstractPuzzle;

class Engine : public QObject
{
    Q_OBJECT
public:
    explicit Engine(QObject *parent = 0);
    int puzzleCount() const;
    int currentPuzzle() const;
    
signals:
    
public slots:
    void startChallenge();
    void addPuzzle(AbstractPuzzle *puzzle);

private slots:
    void answerGiven(bool correct);

private:
    int checkContinuationCode() const;
    QList<AbstractPuzzle *> m_puzzleList;
    int m_currentPuzzle;
};

#endif // ENGINE_H
