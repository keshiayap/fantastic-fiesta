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
}
