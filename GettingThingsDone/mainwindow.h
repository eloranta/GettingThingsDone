#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    QSqlTableModel inboxModel;
    QSqlTableModel todoModel;
    QSqlTableModel doneModel;
    QSqlTableModel trashModel;
    bool createTable(const QString &table, QSqlTableModel& model, QTableView *view);
    int FindSelectedId(QTableView *view);
private slots:
    void addToInbox();
    void moveFromInboxToTodo();
    void moveFromInboxToTrash();
    void moveFromTodoToDone();
    void moveFromTodoToTrash();
    void moveFromDoneToTrash();
    void moveFromTrashToTodo();
    void deleteFromTrash();
    void deleteAllFromTrash();
    void upButtonClicked();
    void downButtonClicked();
};

#endif
