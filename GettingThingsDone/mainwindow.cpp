#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QSqlQuery query;
    query.exec("create table if not exists inbox (Id integer primary key autoincrement, Stuff text)");

    ui->setupUi(this);
    ui->tableView->setModel(&model);
    model.setTable("inbox");
    model.select();

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addItem()
{
    QSqlQuery query;
    query.exec("insert into inbox (Stuff) values('')");
    model.select();
}
