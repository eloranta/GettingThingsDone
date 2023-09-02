#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(&model);
    model.setTable("inbox");

    QSqlQuery query;
    query.exec("create table if not exists inbox (Id integer primary key autoincrement, Stuff text)");

    query.exec("insert into inbox (1, Stuff) values('xxx')");
}

MainWindow::~MainWindow()
{
    delete ui;
}

