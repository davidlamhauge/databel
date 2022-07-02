#include "mainwindow.h"

#include <QApplication>
#include <QSettings>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSettings settings("TeamLamhauge", "daTabel");
    QString mLang = settings.value("lang", ":lang/lang/databel_da").toString();

    QTranslator translator;
    translator.load(mLang);
    a.installTranslator(&translator);

    MainWindow w;
    w.show();
    return a.exec();
}
