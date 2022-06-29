#ifndef MINUSOPGAVER_H
#define MINUSOPGAVER_H

#include <QWidget>

namespace Ui {
class MinusOpgaver;
}

class MinusOpgaver : public QWidget
{
    Q_OBJECT

public:
    explicit MinusOpgaver(QWidget *parent = nullptr);
    ~MinusOpgaver();

private:
    Ui::MinusOpgaver *ui;
};

#endif // MINUSOPGAVER_H
