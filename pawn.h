#ifndef PAWN_H
#define PAWN_H
#include <QGraphicsEllipseItem>

class Pawn
{
public:
    QGraphicsEllipseItem * pawn;
    bool isKing;
    Pawn();
    bool isAlive;
    void dead();
};

#endif // PAWN_H
