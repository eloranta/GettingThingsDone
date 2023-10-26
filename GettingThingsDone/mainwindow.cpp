#include "mainwindow.h"
#include "ui_mainwindow.h"

bool MainWindow::createTable(QSqlTableModel& model, QTableView *view)
{
    if (!query.exec("create table if not exists table1 (Id integer primary key autoincrement, view integer, priority integer, Date text, Stuff text)"))
       return false;
    model.setTable("table1");
    model.select();
    view->setModel(&model);
    return true;
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    createTable(todoModel, ui->todoTableView);
    createTable(calendarModel, ui->calendarTableView);
    createTable(calendarModel, ui->calendarTableView);
    createTable(doneModel, ui->doneTableView);
    createTable(someDayModel, ui->someDayTableView);
    createTable(trashModel, ui->trashTableView);

    inboxModel.setFilter("view=1");
    todoModel.setFilter("view=2");
    calendarModel.setFilter("view=3");
    someDayModel.setFilter("view=6");
    doneModel.setFilter("view=4");
    trashModel.setFilter("view=5");

    calendarModel.setSort(3, Qt::AscendingOrder);
    calendarModel.select();
    todoModel.setSort(2, Qt::DescendingOrder);
    todoModel.select();

    connect(ui->todoAddButton, SIGNAL(clicked()), this, SLOT(addToTodo()));
    connect(ui->calendarAddButton, SIGNAL(clicked()), this, SLOT(addToCalendar()));
    connect(ui->calendarMoveToDoneButton, SIGNAL(clicked()), this, SLOT(moveFromCalendarToDone()));
    connect(ui->calendarMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromCalendarToTrash()));
    connect(ui->someDayAddButton, SIGNAL(clicked()), this, SLOT(addToSomeDay()));
    connect(ui->someDayMoveToDoneButton, SIGNAL(clicked()), this, SLOT(moveFromSomeDayToDone()));
    connect(ui->someDayMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromSomeDayToTrash()));
    connect(ui->todoMoveToDoneButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToDone()));
    connect(ui->todoMoveToCalendarButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToCalendar()));
    connect(ui->todoMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromTodoToTrash()));
    connect(ui->doneMoveToTrashButton, SIGNAL(clicked()), this, SLOT(moveFromDoneToTrash()));
    connect(ui->trashMoveToTodoButton, SIGNAL(clicked()), this, SLOT(moveFromTrashToTodo()));
    connect(ui->trashDeleteButton, SIGNAL(clicked()), this, SLOT(deleteFromTrash()));
    connect(ui->trashDeleteAll, SIGNAL(clicked()), this, SLOT(deleteAllFromTrash()));
    connect(ui->topButton, SIGNAL(clicked()), this, SLOT(topButtonClicked()));
    connect(ui->upButton, SIGNAL(clicked()), this, SLOT(upButtonClicked()));
    connect(ui->downButton, SIGNAL(clicked()), this, SLOT(downButtonClicked()));
    connect(ui->bottomButton, SIGNAL(clicked()), this, SLOT(bottomButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addToInbox()
{
    query.exec("insert into table1 (view, priority, date, Stuff) values(1, 1, date('now'), '')");
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

void MainWindow::addToTodo()
{
    query.exec("insert into table1 (view, priority, date, Stuff) values(2, " + QString::number(GetMaxPriority() + 1) + ", date('now'), '')");
    todoModel.select();
    ui->todoTableView->selectRow(0);
}

void MainWindow::addToCalendar()
{
    query.exec("insert into table1 (view, priority, date, Stuff) values(3, 1, date('now'), '')");
    calendarModel.select();
    ui->calendarTableView->selectRow(0);
}

void MainWindow::moveFromCalendarToDone()
{
    int id = FindSelectedId(ui->calendarTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 4 where id = " + QString::number(id));
    calendarModel.select();
    doneModel.select();

    ui->calendarTableView->selectRow(0);
}

void MainWindow::moveFromCalendarToTrash()
{
    int id = FindSelectedId(ui->calendarTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 5 where id = " + QString::number(id));
    calendarModel.select();
    trashModel.select();

    ui->calendarTableView->selectRow(0);
}

void MainWindow::moveFromTodoToDone()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 4 where id = " + QString::number(id));
    todoModel.select();
    doneModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromTodoToCalendar()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 3 where id = " + QString::number(id));
    todoModel.select();
    calendarModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromTodoToTrash()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 5 where id = " + QString::number(id));
    todoModel.select();
    trashModel.select();

    ui->todoTableView->selectRow(0);
}

void MainWindow::moveFromDoneToTrash()
{
    int id = FindSelectedId(ui->doneTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 5 where id = " + QString::number(id));
    doneModel.select();
    trashModel.select();

    ui->doneTableView->selectRow(0);
}

void MainWindow::moveFromTrashToTodo()
{
    int id = FindSelectedId(ui->trashTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 2 where id = " + QString::number(id));
    trashModel.select();
    todoModel.select();

    ui->trashTableView->selectRow(0);
}

void MainWindow::deleteFromTrash()
{
    int id = FindSelectedId(ui->trashTableView);
    if (id == -1)
        return;

    query.exec("delete from table1 where id = " + QString::number(id));
    trashModel.select();

    ui->trashTableView->selectRow(0);
}

void MainWindow::deleteAllFromTrash()
{
    query.exec("delete from table1 where view = 5");
    trashModel.select();
}

int MainWindow::GetMaxPriority()
{
    query.exec("select max(priority) from table1");
    if (query.next())
        return query.value(0).toInt();
    return -1;
}

int MainWindow::GetMinPriority()
{
    query.exec("select min(priority) from table1");
    if (query.next())
        return query.value(0).toInt();
    return -1;
}

void MainWindow::topButtonClicked()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;
    int max_priority = GetMaxPriority();
    max_priority++;
    query.exec("update table1 set priority = " + QString::number(max_priority) + " where id = " + QString::number(id));
    todoModel.select();
}

void MainWindow::upButtonClicked()
{

}

void MainWindow::downButtonClicked()
{

}

void MainWindow::bottomButtonClicked()
{
    int id = FindSelectedId(ui->todoTableView);
    if (id == -1)
        return;
    int min_priority = GetMinPriority();
    min_priority--;
    query.exec("update table1 set priority = " + QString::number(min_priority) + " where id = " + QString::number(id));
    todoModel.select();
}

void MainWindow::addToSomeDay()
{
    query.exec("insert into table1 (view, priority, date, Stuff) values(6, 1, date('now'), '')");
    someDayModel.select();
    ui->someDayTableView->selectRow(0);
}

void MainWindow::moveFromSomeDayToDone()
{
    int id = FindSelectedId(ui->someDayTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 4 where id = " + QString::number(id));
    someDayModel.select();
    doneModel.select();

    ui->someDayTableView->selectRow(0);
}

void MainWindow::moveFromSomeDayToTrash()
{
    int id = FindSelectedId(ui->someDayTableView);
    if (id == -1)
        return;

    query.exec("update table1 set view = 5 where id = " + QString::number(id));
    someDayModel.select();
    trashModel.select();

    ui->someDayTableView->selectRow(0);
}
