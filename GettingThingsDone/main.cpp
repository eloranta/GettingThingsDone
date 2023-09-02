#include "mainwindow.h"

#include <QApplication>

bool openDatabase(const QString& name)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(name);
    return db.open();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    if (!openDatabase("Spots.sqlite"))
    {
        qDebug() << "Cannot open database";
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
