#include <QPainter>
#include "checkers.h"
#include "ui_checkers.h"

Checkers::Checkers(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Checkers) {
    ui->setupUi(this);
}

Checkers::~Checkers(){
    delete ui;
}

void Checkers::paintEvent(QPaintEvent *event) {

    // Initialize painter.
    QPainter canvas(this);
    // Set brush to black
    canvas.setBrush(Qt::black);
    // Turn off border
    //canvas.setPen(Qt::NoPen);

    // Draw the board squares.
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++){
        if ((x % 2 == 0 && y % 2 == 0) || (x % 2 == 1 && y % 2 == 1)) {
            canvas.setBrush(QBrush("#eee2ca"));
            canvas.drawRect(75*x, 10+75*y, 75, 75);
        }
        else{
            canvas.setBrush(QBrush("#83652c"));
            canvas.drawRect(75*x, 10+75*y, 75, 75);
        }
    }
    }
    //canvas.setBrush(QBrush("#e41f1f"));
    //canvas.drawEllipse(75*1+10, 75*1+10, 55, 55);
}
