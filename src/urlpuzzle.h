#ifndef URLPUZZLE_H
#define URLPUZZLE_H

#include "abstractpuzzle.h"

class UrlPuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit UrlPuzzle(QObject *parent = 0);
    QString continuationCode() const;
    
signals:
    
public slots:
    void startPuzzle();
    
};

#endif // URLPUZZLE_H
