#ifndef ADVENTUREPUZZLE_H
#define ADVENTUREPUZZLE_H

#include "abstractpuzzle.h"

#include <QStringList>

class AdventurePuzzle : public AbstractPuzzle
{
    Q_OBJECT
public:
    explicit AdventurePuzzle(QObject *parent = 0);
    QString continuationCode() const;
    
signals:
    
public slots:
    void startPuzzle();

private:
    bool m_passed;
    int m_state;
    QStringList m_inventoryList;
    QStringList m_stateMessages;

private:
    void gameMain();
    void getCommand();
    void pickup(const QString &item);
    void look(const QString &item);
    
};

#endif // ADVENTUREPUZZLE_H
