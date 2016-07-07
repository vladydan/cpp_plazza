#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QLabel>
#include <QTreeWidgetItem>
#include <QTreeWidget>
#include "ProcessManager.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = 0);
    void setThreadNumber(int threadNumber);
    void clearTreeWidget();
    ~MainWindow();
  private slots:
    void updateProcess();
    void on_pushButton_clicked();
    void deleteItem();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_displayList_clicked();

private:
      Ui::MainWindow *_ui;
      ProcessManager _processManager;
      QTimer *_timer;
      int _threadNumber;
};

#endif // MAINWINDOW_H
