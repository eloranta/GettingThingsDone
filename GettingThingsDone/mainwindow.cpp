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

    query.exec("create table if not exists done (Id integer, Stuff text)");
    ui->doneTableView->setModel(&doneModel);
    doneModel.setTable("done");
    doneModel.select();

    query.exec("create table if not exists trash (Id integer, Stuff text)");
    ui->trashTableView->setModel(&trashModel);
    trashModel.setTable("trash");
    trashModel.select();

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addToInbox()));
    connect(ui->moveToTodoButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToTodo()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToTrash()));
    connect(ui->moveToDoneButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToDone()));
    connect(ui->deleteButton_2, SIGNAL(clicked()), this, SLOT(moveFromTodoToTrash()));
    connect(ui->moveToTrash2, SIGNAL(clicked()), this, SLOT(moveFromDoneToTrash()));
    connect(ui->moveToTodoButton_3, SIGNAL(clicked()), this, SLOT(moveFromTrashToTodo()));
    connect(ui->deleteButton_4, SIGNAL(clicked()), this, SLOT(deleteFromTrash()));
    connect(ui->deleteAllFromTrash, SIGNAL(clicked()), this, SLOT(deleteAllFromTrash()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToInbox()
{
    QSqlQuery query;
    query.exec("insert into inbox (Stuff) values('')");
    inBasketModel.select();
}

void MainWindow::moveFromInboxToTodo()
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

void MainWindow::moveFromInboxToTrash()
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
        query.exec("insert into trash (Id, Stuff) values(" + QString::number(id) + ",'" + stuff + "')");
    }
    inBasketModel.select();
    trashModel.select();
}

void MainWindow::moveFromTodoToDone()
{
    QModelIndexList selectedRows = ui->todoTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString stuff = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        query.exec("delete from todo where id=" + QString::number(id));
        qDebug() << id << stuff;
        query.exec("insert into done (Id, Stuff) values(" + QString::number(id) + ",'" + stuff + "')");
    }
    todoModel.select();
    doneModel.select();
}

void MainWindow::moveFromTodoToTrash()
{
    QModelIndexList selectedRows = ui->todoTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString stuff = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        query.exec("delete from todo where id=" + QString::number(id));
        qDebug() << id << stuff;
        query.exec("insert into trash (Id, Stuff) values(" + QString::number(id) + ",'" + stuff + "')");
    }
    todoModel.select();
    trashModel.select();
}

void MainWindow::moveFromDoneToTrash()
{
    QModelIndexList selectedRows = ui->doneTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString stuff = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        query.exec("delete from done where id=" + QString::number(id));
        qDebug() << id << stuff;
        query.exec("insert into trash (Id, Stuff) values(" + QString::number(id) + ",'" + stuff + "')");
    }
    doneModel.select();
    trashModel.select();
}

void MainWindow::moveFromTrashToTodo()
{
    QModelIndexList selectedRows = ui->trashTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString stuff = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        query.exec("delete from trash where id=" + QString::number(id));
        qDebug() << id << stuff;
        query.exec("insert into todo (Id, Stuff) values(" + QString::number(id) + ",'" + stuff + "')");
    }
    todoModel.select();
    trashModel.select();
}

void MainWindow::deleteFromTrash()
{
    QModelIndexList selectedRows = ui->trashTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        query.exec("delete from trash where id=" + QString::number(id));
        qDebug() << id;
    }
    trashModel.select();
}
void MainWindow::deleteAllFromTrash()
{
    QAbstractItemModel *model = ui->trashTableView->model();
    QSqlQuery query;
    for (int row = 0; row < model->rowCount(); row++)
    {
        int id = model->data(model->index(row, 0), Qt::DisplayRole).toInt();
        query.exec("delete from trash where id=" + QString::number(id));
        qDebug() << id;
    }
    trashModel.select();
}

