#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum class taskType {
        PLUS = 1,
        MINUS = 2,
        GANGE = 3,
        DIVI = 4
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setupOptions();
    void removeLayout();

    // setup layouts
    void setupPlus();
    void setupMinus();
    void setupGange();
    void setupDivision();

    void setNegativeResult(int state);

    // COMMON member functions
    void setupOption(int taskType);
    void setOptionAntal(int antal) {mAntal = antal; }
    void setOptionMax(int maxTal) {mMax = maxTal; }
    void optionChosen();

    // comon member vars
    int mTaskType = 1;
    int mAntal;
    int mMax;
    bool mNegativeResult = false;

};
#endif // MAINWINDOW_H
