#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlQuery query;

    query.exec("create table if not exists inbox (Id integer primary key autoincrement, Stuff text)");
    ui->inBasketTableView->setModel(&inBasketModel);
    inBasketModel.setTable("inbox");
    inBasketModel.select();

    query.exec("create table if not exists todo (Id integer, Stuff text)");
    ui->todoTableView->setModel(&todoModel);
    todoModel.setTable("todo");
    todoModel.select();

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addItem()));
    connect(ui->moveToTodoButton, SIGNAL(clicked()), this, SLOT(moveItemToTodo()));
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
    inBasketModel.select();
}

void MainWindow::moveItemToTodo()
{
    QModelIndexList selectedRows = ui->inBasketTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString stuff = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        query.exec("delete from inbox where id=" + QString::number(id));
        qDebug() << id << stuff;
        query.exec("insert into todo (Id, Stuff) values(" + QString::number(id) + ",'" + stuff + "')");
    }
    inBasketModel.select();
    todoModel.select();
}

void MainWindow::deleteItem()
{
    QModelIndexList selectedRows = ui->inBasketTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        qDebug() << id;
        query.exec("delete from inbox where id=" + QString::number(id));
    }
    inBasketModel.select();
}

