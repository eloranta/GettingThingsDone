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
    QSqlQuery query;
    QSqlTableModel inboxModel;
    QSqlTableModel todoModel;
    QSqlTableModel calendarModel;
    QSqlTableModel someDayModel;
    QSqlTableModel doneModel;
    QSqlTableModel trashModel;
    QSqlTableModel projectModel;
    bool createTable(QSqlTableModel& model, QTableView *view);
    int FindSelectedId(QTableView *view);
private slots:
    void addToTodo();
    void addToCalendar();
    void addToSomeDay();
    void addToInbox();
    void addToProject();
    void moveFromCalendarToDone();
    void moveFromProjectToDone();
    void moveFromCalendarToTrash();
    void moveFromTodoToDone();
    void moveFromTodoToCalendar();
    void moveFromTodoToTrash();
    void moveFromDoneToTrash();
    void moveFromTrashToTodo();
    void moveFromSomeDayToDone();
    void moveFromSomeDayToTrash();
    void deleteFromTrash();
    void deleteAllFromTrash();
    void topButtonClicked();
    void upButtonClicked();
    void downButtonClicked();
    void bottomButtonClicked();
    int GetMaxPriority();
    int GetMinPriority();
};

#endif
