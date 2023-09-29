#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlQuery query;

    query.exec("create table if not exists inbox (Id integer primary key autoincrement, Date text, Stuff text)");
    inBasketModel.setTable("inbox");
    inBasketModel.select();
    ui->inBasketTableView->setModel(&inBasketModel);
    ui->inBasketTableView->hideColumn(0);

    query.exec("create table if not exists todo (Id integer, Date text, Stuff text)");
    ui->todoTableView->setModel(&todoModel);
    todoModel.setTable("todo");
    todoModel.select();
    ui->todoTableView->hideColumn(0);

    query.exec("create table if not exists done (Id integer, Date text, Stuff text)");
    ui->doneTableView->setModel(&doneModel);
    doneModel.setTable("done");
    doneModel.select();
    ui->doneTableView->hideColumn(0);

    query.exec("create table if not exists trash (Id integer, Date text, Stuff text)");
    ui->trashTableView->setModel(&trashModel);
    trashModel.setTable("trash");
    trashModel.select();
    ui->trashTableView->hideColumn(0);

    connect(ui->addButton, SIGNAL(clicked()), this, SLOT(addToInbox()));
    connect(ui->moveToTodoButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToTodo()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToTrash()));
    connect(ui->moveToDoneButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToDone()));
    connect(ui->deleteButton_2, SIGNAL(clicked()), this, SLOT(moveFromTodoToTrash()));
    connect(ui->moveToTrash2, SIGNAL(clicked()), this, SLOT(moveFromDoneToTrash()));
    connect(ui->moveToTodoButton_3, SIGNAL(clicked()), this, SLOT(moveFromTrashToTodo()));
    connect(ui->deleteButton_4, SIGNAL(clicked()), this, SLOT(deleteFromTrash()));
    connect(ui->deleteAllFromTrash, SIGNAL(clicked()), this, SLOT(deleteAllFromTrash()));
    connect(ui->upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
    connect(ui->downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToInbox()
{
    QSqlQuery query;
    QString s = "insert into inbox (date, Stuff) values(date('now'), '')";
    qDebug() << s;
    query.exec(s);
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
        QString date = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        QString stuff = model->data(model->index(index.row(), 2), Qt::DisplayRole).toString();
        query.exec("delete from inbox where id=" + QString::number(id));
        QString s = "insert into todo (Id, Date, Stuff) values("+ QString::number(id) + ", '" + date + "', '" + stuff + "')";
        qDebug() << s;
        query.exec(s);
    }
    inBasketModel.select();
    todoModel.select();

    ui->inBasketTableView->selectRow(0);
}

void MainWindow::moveFromInboxToTrash()
{
    QModelIndexList selectedRows = ui->inBasketTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString date = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        QString stuff = model->data(model->index(index.row(), 2), Qt::DisplayRole).toString();
        query.exec("delete from inbox where id=" + QString::number(id));
        QString s = "insert into trash (Id, Date, Stuff) values("+ QString::number(id) + ", '" + date + "', '" + stuff + "')";
        qDebug() << s;
        query.exec(s);
    }
    inBasketModel.select();
    trashModel.select();

    ui->inBasketTableView->selectRow(0);
}

void MainWindow::moveFromTodoToDone()
{
    QModelIndexList selectedRows = ui->todoTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString date = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        QString stuff = model->data(model->index(index.row(), 2), Qt::DisplayRole).toString();
        query.exec("delete from todo where id=" + QString::number(id));
        QString s = "insert into done (Id, Date, Stuff) values("+ QString::number(id) + ", '" + date + "', '" + stuff + "')";
        qDebug() << s;
        query.exec(s);
    }
    todoModel.select();
    doneModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromTodoToTrash()
{
    QModelIndexList selectedRows = ui->todoTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString date = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        QString stuff = model->data(model->index(index.row(), 2), Qt::DisplayRole).toString();
        query.exec("delete from todo where id=" + QString::number(id));
        QString s = "insert into trash (Id, Date, Stuff) values("+ QString::number(id) + ", '" + date + "', '" + stuff + "')";
        qDebug() << s;
        query.exec(s);
    }
    todoModel.select();
    trashModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromDoneToTrash()
{
    QModelIndexList selectedRows = ui->doneTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString date = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        QString stuff = model->data(model->index(index.row(), 2), Qt::DisplayRole).toString();
        query.exec("delete from done where id=" + QString::number(id));
        QString s = "insert into trash (Id, Date, Stuff) values("+ QString::number(id) + ", '" + date + "', '" + stuff + "')";
        qDebug() << s;
        query.exec(s);
    }
    doneModel.select();
    trashModel.select();

    ui->doneTableView->selectRow(0);
}

void MainWindow::moveFromTrashToTodo()
{
    QModelIndexList selectedRows = ui->trashTableView->selectionModel()->selectedRows();
    QSqlQuery query;
    foreach (QModelIndex index, selectedRows)
    {
        const QAbstractItemModel *model = index.model();
        int id = model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
        QString date = model->data(model->index(index.row(), 1), Qt::DisplayRole).toString();
        QString stuff = model->data(model->index(index.row(), 2), Qt::DisplayRole).toString();
        query.exec("delete from trash where id=" + QString::number(id));
        QString s = "insert into todo (Id, Date, Stuff) values("+ QString::number(id) + ", '" + date + "', '" + stuff + "')";
        qDebug() << s;
        query.exec(s);
    }
    todoModel.select();
    trashModel.select();

    ui->trashTableView->selectRow(0);
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

    ui->trashTableView->selectRow(0);
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

void MainWindow::upButtonClicked()
{

}

void MainWindow::downButtonClicked()
{

}
