#ifndef FALLOSPUZZLE_H
#define FALLOSPUZZLE_H

#include "abstractpuzzle.h"

#include <QTextStream>
#include <QStringList>

class FallOsPuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit FallOsPuzzle(QObject *parent = 0);
    void startPuzzle();
    QString continuationCode() const;
    
signals:
    
public slots:

private:
    bool checkAnswer(const QString &txt);

    QList<QPair<QString, int> > mGuessList;
    QString mCorrect;
    QStringList mWordList;

};

#endif // FALLOSPUZZLE_H
