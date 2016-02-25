#ifndef INTROPUZZLE_H
#define INTROPUZZLE_H

#include "abstractpuzzle.h"

class IntroPuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit IntroPuzzle(QObject *parent = 0);
    void startPuzzle();
    QString continuationCode() const;
    
signals:
    
public slots:
    
};

#endif // INTROPUZZLE_H
