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
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setupOptions();

    void setupPlus();
    void setPlusAntal(int antal) {mPlusAntal = antal; }
    void setPlusMaxSum(int maxSum) {mPlusMaxSum = maxSum; }
    void plusChosen();

    void setupMinus();

    void setupGange();

    void setupDivision();

    // PLUS member vars
    int mPlusAntal;
    int mPlusMaxSum;
};
#endif // MAINWINDOW_H
