#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QSqlQuery query;
    query.exec("create table if not exists inbox (Id integer primary key autoincrement, Stuff text)");

    ui->setupUi(this);

    ui->inBasketTableView->setModel(&inBasketModel);
    inBasketModel.setTable("inbox");
    inBasketModel.select();

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
    inBasketModel.select();
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

