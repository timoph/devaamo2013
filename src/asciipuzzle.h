#ifndef ASCIIPUZZLE_H
#define ASCIIPUZZLE_H

#include "abstractpuzzle.h"

#include <QTimer>

class AsciiPuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit AsciiPuzzle(QObject *parent = 0);
    QString continuationCode() const;
    
signals:
    
public slots:
    void startPuzzle();

private slots:
    void tick();
    
private:
    QString m_string;
    QTimer m_timer;
    int m_count;
};

#endif // ASCIIPUZZLE_H
