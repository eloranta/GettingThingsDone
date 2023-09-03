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
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deleteItem()));
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

void MainWindow::deleteItem()
{
    QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        int row = index.row();
        qDebug() << row;
        query.exec("delete from inbox where id=" + QString::number(row));
    }
    model.select();
}

