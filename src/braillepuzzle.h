#ifndef BRAILLEPUZZLE_H
#define BRAILLEPUZZLE_H

#include "abstractpuzzle.h"

class BraillePuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit BraillePuzzle(QObject *parent = 0);
    QString continuationCode() const;
    
signals:
    
public slots:
    void startPuzzle();
    
};

#endif // BRAILLEPUZZLE_H
