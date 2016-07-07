#include <QFileDialog>
#include <iostream>
#include <QString>
#include <QComboBox>
#include <QListWidget>
#include <QShortcut>
#include <QTimer>
#include <QTreeWidgetItem>
#include "../includes/Window.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow)
{
  _ui->setupUi(this);
  new QShortcut(QKeySequence(Qt::Key_Delete), this, SLOT(deleteItem()));
  this->_timer = new QTimer(this);
  QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(updateProcess()));
  _timer->start(1000);
  this->_threadNumber = 5;
}

void MainWindow::setThreadNumber(int threadNumber)
{
  this->_threadNumber = threadNumber;
}

MainWindow::~MainWindow()
{
  _processManager.exitProcesses();
  _processManager.joinReadThread();

  delete _ui;
  delete _timer;
}

void MainWindow::updateProcess()
{
  QListWidget *processList = this->findChild<QListWidget *>("processList");
  QListWidget *resultList = this->findChild<QListWidget *>("resultList");
  std::list<std::pair<int, int>> processes = this->_processManager.getProcessData();
  std::map<int, std::list<std::string>> results = this->_processManager.getResults();

  processList->clear();
  for (std::pair<int, int> process :processes)
  {
    processList->addItem(QString("Process ") + QString::number(process.first));
    for (int i = 0; i < process.second ; ++i)
    {
      processList->addItem(QString("\t Thread") + QString::number(process.first) + QString(" is working ..."));
    }
  }
  if (resultList->count() > 0)
  {
    resultList->clear();
  }
  for (std::pair<int, std::list<std::string>> pair : results)
  {
    for (std::string &list : pair.second)
    {
      resultList->addItem(QString("Process ") + QString::number(pair.first) + tr(" Found ") + QString(list.c_str()));
    }
  }
}

void MainWindow::on_pushButton_clicked()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                  QDir::currentPath(),
                                                 tr("*"));
  QListWidget *fileList = this->findChild<QListWidget *>("listWidget");
  if (fileList != NULL)
    fileList->addItem(fileName);
}

// Send order
void MainWindow::on_pushButton_2_clicked()
{
  std::list<std::string> listOfFile;

  QComboBox *comboBox = this->findChild<QComboBox *>("comboBox");
  QListWidget *listWidget = this->findChild<QListWidget *>("listWidget");
  for(int row = 0; row < listWidget->count(); row++)
  {
    QListWidgetItem *item = listWidget->item(row);
    listOfFile.push_back(item->text().toStdString());
  }
  this->_processManager.addOrder(listOfFile, comboBox->currentText().toStdString(), this->_threadNumber);
  //listWidget->clear();

}

//Clear orders display
void MainWindow::deleteItem()
{
  QListWidget *fileList = this->findChild<QListWidget *>("listWidget");
  delete fileList->currentItem();
}

void MainWindow::on_pushButton_3_clicked()
{
  QListWidget *listWidget = this->findChild<QListWidget *>("listWidget");
  listWidget->clear();
}

void MainWindow::on_displayList_clicked()
{
  this->_processManager.clearResult();
}
