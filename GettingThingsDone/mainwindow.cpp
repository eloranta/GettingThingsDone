#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QSqlQuery query;
    query.exec("create table if not exists inbox (Id integer primary key autoincrement, Stuff text)");
    query.exec("insert into inbox (Stuff) values('xxx')");

    ui->setupUi(this);
    ui->tableView->setModel(&model);
    model.setTable("inbox");
}

MainWindow::~MainWindow()
{
    delete ui;
}

