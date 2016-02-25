#ifndef BATTLEPUZZLE_H
#define BATTLEPUZZLE_H

#include "abstractpuzzle.h"

class BattlePuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit BattlePuzzle(QObject *parent = 0);
    QString continuationCode() const;
    
signals:
    
public slots:
    void startPuzzle();
    
};

#endif // BATTLEPUZZLE_H
