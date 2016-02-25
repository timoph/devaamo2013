#ifndef ABSTRACTPUZZLE_H
#define ABSTRACTPUZZLE_H

#include <QObject>

class AbstractPuzzle : public QObject
{
    Q_OBJECT
public:
    explicit AbstractPuzzle(QObject *parent = 0);
    virtual ~AbstractPuzzle() {}
    virtual QString continuationCode() const = 0;
    
signals:
    void answerGiven(bool correct);
    
public slots:
    virtual void startPuzzle() = 0;
    
};

#endif // ABSTRACTPUZZLE_H
