#include <iostream>
#include <string>
#include "Cesar.hpp"
#include "Xor.hpp"
#include "ProcessManager.hpp"
#include "Parser.hpp"
#include "ProcessData.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage : " << argv[0] << " thread_per_process" << std::endl;
    return (1);
  }
  ProcessManager processManager;
  Parser parser;
  ListOfCommands *orders;

  std::string cmd;
  while (true)
  {
    getline(std::cin, cmd);
    if (std::cin.eof() == 1 || cmd.compare("exit") == 0)
    {
      processManager.exitProcesses();
      processManager.joinReadThread();
      return 0;
    }
    orders = parser.convertStringToList(cmd);
    if (orders != nullptr)
    {
      for (std::pair<std::list<std::string>, std::string> &order : *orders)
      {
        if (order.first.size() > 0 && order.second.size() > 0)
          processManager.addOrder(order.first, order.second,
                                  std::stoi(argv[1]));
      }
      delete orders;
    }
    parser.clearRslt();
  }
  return 0;
}
