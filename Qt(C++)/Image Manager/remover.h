#ifndef REMOVER_H
#define REMOVER_H

#include <QDialog>

namespace Ui {
class Remover;
}

class Remover : public QDialog
{
    Q_OBJECT

public:
    explicit Remover(QWidget *parent = 0);
    ~Remover();

private:
    Ui::Remover *ui;
};

#endif // REMOVER_H
