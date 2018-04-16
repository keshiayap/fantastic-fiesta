#ifndef CHECKERS_H
#define CHECKERS_H

#include <QMainWindow>

namespace Ui {
class Checkers;
}

class Checkers : public QMainWindow {

    Q_OBJECT

    public:
        explicit Checkers(QWidget *parents=0);
        ~Checkers();
        void paintEvent(QPaintEvent *event);

    protected:
        Ui::Checkers *ui;
        //void draw();
};
#endif // CHECKERS_H
