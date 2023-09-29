#include "mainwindow.h"
#include "ui_mainwindow.h"

bool MainWindow::createTable(const QString &table, QSqlTableModel& model, QTableView *view)
{
    QSqlQuery query;
    if (!query.exec("create table if not exists " + table + " (Id integer primary key autoincrement, Date text, Stuff text)"))
       return false;
    model.setTable(table);
    model.select();
    view->setModel(&model);
    return true;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTable("inbox", inboxModel, ui->inboxTableView);
    createTable("todo",  todoModel, ui->todoTableView);
    createTable("done",  doneModel, ui->doneTableView);
    createTable("trash", trashModel, ui->trashTableView);

    connect(ui->inboxAddButton, SIGNAL(clicked()), this, SLOT(addToInbox()));
    connect(ui->inboxMoveToTodoButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToTodo()));
    connect(ui->inboxMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToTrash()));
    connect(ui->todoMoveToDoneButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToDone()));
    connect(ui->todoMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToTrash()));
    connect(ui->doneMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromDoneToTrash()));
    connect(ui->trashMoveToTodoButton, SIGNAL(clicked()), this, SLOT(moveFromTrashToTodo()));
    connect(ui->trashDeleteButton, SIGNAL(clicked()), this, SLOT(deleteFromTrash()));
    connect(ui->trashDeleteAll, SIGNAL(clicked()), this, SLOT(deleteAllFromTrash()));
    connect(ui->upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
    connect(ui->downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToInbox()
{
    query.exec("insert into inbox (date, Stuff) values(date('now'), '')");
    inboxModel.select();
}

int MainWindow::FindSelectedId(QTableView *view)
{
    QModelIndexList selectedRows = view->selectionModel()->selectedRows();
    if (selectedRows.isEmpty())
        return -1;
    QModelIndex index = *selectedRows.begin();
    const QAbstractItemModel *model = index.model();
    return model->data(model->index(index.row(), 0), Qt::DisplayRole).toInt();
}

void MainWindow::moveFromInboxToTodo()
{
    int id = FindSelectedId(ui->inboxTableView);
    if (id == -1)
        return;

    query.exec("insert into todo select * from inbox where id = " + QString::number(id));
    todoModel.select();

    query.exec("delete from inbox where id = " + QString::number(id));
    inboxModel.select();

    ui->inboxTableView->selectRow(0);
}

void MainWindow::moveFromInboxToTrash()
{
    int id = FindSelectedId(ui->inboxTableView);
    if (id == -1)
        return;

    query.exec("insert into trash select * from inbox where id = " + QString::number(id));
    trashModel.select();

    query.exec("delete from inbox where id = " + QString::number(id));
    inboxModel.select();

    ui->inboxTableView->selectRow(0);
}

void MainWindow::moveFromTodoToDone()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    query.exec("insert into done select * from todo where id = " + QString::number(id));
    doneModel.select();

    query.exec("delete from todo where id = " + QString::number(id));
    todoModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromTodoToTrash()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    query.exec("insert into trash select * from todo where id = " + QString::number(id));
    trashModel.select();

    query.exec("delete from todo where id = " + QString::number(id));
    todoModel.select();

    ui->todoTableView->selectRow(0);

}

void MainWindow::moveFromDoneToTrash()
{
    int id = FindSelectedId(ui->doneTableView);
    if (id == -1)
        return;

    query.exec("insert into trash select * from done where id = " + QString::number(id));
    trashModel.select();

    query.exec("delete from done where id = " + QString::number(id));
    doneModel.select();

    ui->doneTableView->selectRow(0);
}

void MainWindow::moveFromTrashToTodo()
{
    int id = FindSelectedId(ui->trashTableView);
    if (id == -1)
        return;

    query.exec("insert into todo select * from trash where id = " + QString::number(id));
    todoModel.select();

    query.exec("delete from trash where id = " + QString::number(id));
    trashModel.select();

    ui->trashTableView->selectRow(0);
}

void MainWindow::deleteFromTrash()
{
    int id = FindSelectedId(ui->trashTableView);
    if (id == -1)
        return;

    query.exec("delete from trash where id = " + QString::number(id));
    trashModel.select();

    ui->trashTableView->selectRow(0);
}

void MainWindow::deleteAllFromTrash()
{
    query.exec("delete from trash");
    trashModel.select();
}

void MainWindow::upButtonClicked()
{

}

void MainWindow::downButtonClicked()
{

}
