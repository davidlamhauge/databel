#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

class PreferenceManager;
class SolveTasks;

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
    void setupSettings();
    void updateSettings();

    void removeLayout();

    // setup layouts
    void setupPlus();
    void setupMinus();
    void setupGange();
    void setupDivision();

    void setNegativeResult(int state);

    // common member functions
    void setupOption(int taskType);
    void setOptionAntal(int antal) {mAntal = antal; }
    void setOptionMax(int maxTal) {mMax = maxTal; }
    void optionChosen();

    // common member vars
    int mTaskType;
    int mAntal;
    int mMax;
    bool mNegativeResult = false;

    QString mLanguage = "";
    int mLangIndex = 0;

    SolveTasks* solve = nullptr;
    PreferenceManager* prefs = nullptr;
};
#endif // MAINWINDOW_H
