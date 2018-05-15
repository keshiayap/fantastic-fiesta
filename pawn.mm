#include "pawn.h"


/*@implementation Pawn
//@synthesize pawn, isKing;
- (id) Pawn {
    self->isKing = false;
    self->pawn = new QGraphicsEllipseItem();
    return self;
}
@end
*/

Pawn::Pawn(){
    this->isKing = false;
    this->pawn = new QGraphicsEllipseItem();
    this->isAlive = true;
}

void Pawn::dead(){
    this->isAlive = false;
    this->pawn->setPos(60 *9, 60*4);
}
