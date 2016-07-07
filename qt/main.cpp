#include <QApplication>
#include <string>
#include "../includes/Window.hpp"

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  if (argc == 2)
    w.setThreadNumber(std::stoi(argv[1]));
  w.show();
  return a.exec();
}
