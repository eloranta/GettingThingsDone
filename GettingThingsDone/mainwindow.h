#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QSqlTableModel inBasketModel;
    QSqlTableModel todoModel;
    QSqlTableModel doneModel;
    QSqlTableModel trashModel;
private slots:
    void addItem();
    void moveItemToTodo();
    void deleteItem();
};

#endif // MAINWINDOW_H
