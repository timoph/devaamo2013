#ifndef BFPUZZLE_H
#define BFPUZZLE_H

#include "abstractpuzzle.h"

class BfPuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit BfPuzzle(QObject *parent = 0);
    QString continuationCode() const;
    
signals:
    
public slots:
    void startPuzzle();
    
};

#endif // BFPUZZLE_H
