#include "mainwindow.h"
#include "ui_mainwindow.h"

bool MainWindow::createTable(const QString &table, QSqlTableModel& model, QTableView *view)
{
    if (!query.exec("create table if not exists " + table + " (Id integer primary key autoincrement, view integer, Date text, Stuff text)"))
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
    createTable("inbox", todoModel, ui->todoTableView);
    createTable("inbox", calendarModel, ui->calendarTableView);
    createTable("inbox", doneModel, ui->doneTableView);
    createTable("inbox", trashModel, ui->trashTableView);

    inboxModel.setFilter("view=1");
    todoModel.setFilter("view=2");
    calendarModel.setFilter("view=3");
    doneModel.setFilter("view=4");
    trashModel.setFilter("view=5");

    calendarModel.setSort(1, Qt::AscendingOrder);
    calendarModel.select();

    connect(ui->inboxAddButton, SIGNAL(clicked()), this, SLOT(addToInbox()));
    connect(ui->inboxMoveToCalendarButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToCalendar()));
    connect(ui->inboxMoveToTodoButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToTodo()));
    connect(ui->inboxMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromInboxToTrash()));
    connect(ui->calendarMoveToDoneButton, SIGNAL(clicked()), this, SLOT(moveFromCalendarToDone())); // TODO:
    connect(ui->calendarMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromCalendarToTrash()));
    connect(ui->todoMoveToDoneButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToDone()));
    connect(ui->todoMoveToCalendarButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToCalendar()));
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
    query.exec("insert into inbox (view, date, Stuff) values(1, date('now'), '')");
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

    query.exec("update inbox set view = 2 where id = " + QString::number(id));
    inboxModel.select();
    todoModel.select();

    ui->inboxTableView->selectRow(0);
}

void MainWindow::moveFromInboxToCalendar()
{
    int id = FindSelectedId(ui->inboxTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 3 where id = " + QString::number(id));
    inboxModel.select();
    calendarModel.select();

    ui->inboxTableView->selectRow(0);
}

void MainWindow::moveFromInboxToTrash()
{
    int id = FindSelectedId(ui->inboxTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 5 where id = " + QString::number(id));
    inboxModel.select();
    trashModel.select();

    ui->inboxTableView->selectRow(0);
}

void MainWindow::moveFromCalendarToDone()
{
    int id = FindSelectedId(ui->calendarTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 4 where id = " + QString::number(id));
    calendarModel.select();
    doneModel.select();

    ui->calendarTableView->selectRow(0);
}

void MainWindow::moveFromCalendarToTrash()
{
    int id = FindSelectedId(ui->calendarTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 5 where id = " + QString::number(id));
    calendarModel.select();
    trashModel.select();

    ui->calendarTableView->selectRow(0);
}

void MainWindow::moveFromTodoToDone()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 4 where id = " + QString::number(id));
    todoModel.select();
    doneModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromTodoToCalendar()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 3 where id = " + QString::number(id));
    todoModel.select();
    calendarModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromTodoToTrash()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 5 where id = " + QString::number(id));
    todoModel.select();
    trashModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromDoneToTrash()
{
    int id = FindSelectedId(ui->doneTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 5 where id = " + QString::number(id));
    doneModel.select();
    trashModel.select();

    ui->doneTableView->selectRow(0);
}

void MainWindow::moveFromTrashToTodo()
{
    int id = FindSelectedId(ui->trashTableView);
    if (id == -1)
        return;

    query.exec("update inbox set view = 2 where id = " + QString::number(id));
    trashModel.select();
    todoModel.select();

    ui->trashTableView->selectRow(0);
}

void MainWindow::deleteFromTrash()
{
    int id = FindSelectedId(ui->trashTableView);
    if (id == -1)
        return;

    query.exec("delete from inbox where id = " + QString::number(id));
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
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    int previousId = -1;
    for (int i = 0; i < todoModel.rowCount(); i++)
    {
        int id2 = todoModel.data(todoModel.index(i, 0), Qt::DisplayRole).toInt();
        if (id2 == id)
        {
            if (i == 0)
                return;
            previousId = todoModel.data(todoModel.index(i-1, 0), Qt::DisplayRole).toInt();
            break;
        }
    }

    query.exec("update todo set id=-1 where id=" + QString::number(id));
    query.exec("update todo set id=" + QString::number(id) + " where id=" + QString::number(previousId));
    query.exec("update todo set id=" + QString::number(previousId) + " where id=-1");

    todoModel.select();
}

void MainWindow::downButtonClicked()
{

}
