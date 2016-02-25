#ifndef WHITESPACEPUZZLE_H
#define WHITESPACEPUZZLE_H

#include "abstractpuzzle.h"

class WhiteSpacePuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit WhiteSpacePuzzle(QObject *parent = 0);
    QString continuationCode() const;
    
signals:
    
public slots:
    void startPuzzle();
    
};

#endif // WHITESPACEPUZZLE_H
