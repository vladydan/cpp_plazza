#include <unistd.h>
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <thread>
#include <utility>
#include <functional>
#include "Process.hpp"
#include "ProcessData.hpp"
#include "BruteForcer.hpp"

static int id;

Process::Process(int nbrThread) :
  _namedPipeRead(new NamedPipe("/tmp/the_plazzaWrite")),
  _namedPipeWrite(new NamedPipe("/tmp/the_plazzaRead")),
  _finished(false)
{
  ++id;
  this->_regex.push_back(std::pair<std::string,
                         std::string>("PHONE_NUMBER",
                                      "(0\\s*[1-9](?:\\s*[0-9]){8})"));
  this->_regex.push_back(std::pair<std::string,
                         std::string>("EMAIL_ADDRESS",
                                      "[a-zA-Z0-9.-]+@[a-z0-9.-]{2,}[.][a-z]{2,4}"));
  this->_regex.push_back(std::pair<std::string,
                         std::string>("IP_ADDRESS",
                                      "(?:[0-9]{1,3}[.]){3}[0-9]{1,3}"));
  this->_processNumber = id;
  this->_pid = fork();
  if (this->_pid == 0)
    this->launch(nbrThread);
}

Process::~Process()
{
}

NamedPipe &Process::getNamedPipeRead()
{
  return (*this->_namedPipeRead);
}

NamedPipe &Process::getNamedPipeWrite()
{
  return (*this->_namedPipeWrite);
}

void Process::scrap(ProcessData const& data)
{
  std::ifstream file(data.getFile());
  NamedPipe     namedPipe("/tmp/the_plazzaRead");
  BruteForcer   forcer;
  ProcessData   newData;

  newData.setProcessNumber(this->_processNumber);
  newData.setThreadStatus(-1);
  newData.setFile(data.getFile());
  namedPipe.openPipe(WRITER);
  if (file.is_open())
  {
    forcer.setRaw(std::string(std::istreambuf_iterator<char>(file),
                              std::istreambuf_iterator<char>()));
    file.close();
  }
  else
  {
    std::cerr << "Can't open file " << data.getFile() << std::endl;
    return ;
  }
  for(std::pair<std::string, std::string> pair : this->_regex)
    {
      if (pair.first == data.getInfoToFind())
        {
          forcer.setExpr(pair.second);
          for(std::string str : forcer.forceRaw())
            {
              newData.setRslt(str.c_str());
              namedPipe << newData;
              std::cout << str.c_str() << std::endl;
            }
          return ;
        }
    }
  std::cerr << "Bad info type " << data.getInfoToFind() << std::endl;
}

void Process::launch(int nbrThread)
{
  this->_threadPool = new ThreadPool<ProcessData>(nbrThread);
  std::thread readThread(&Process::readInfo, this);
  std::thread writeThread(&Process::writeInfo, this);

  readThread.join();
  this->_mutex.lock();
  this->_finished = true;
  this->_mutex.unlock();
  writeThread.join();

  delete this->_namedPipeWrite;
  delete this->_namedPipeRead;
  delete this->_threadPool;
  _Exit(0);
}

void Process::readInfo()
{
  ProcessData data;
  this->_namedPipeRead->openPipe(READER);

  while (true)
  {
    *this->_namedPipeRead >> &data;
    if (data.getRetRead() == 0 && this->_processNumber != 1)
    {
      while (this->_threadPool->getCurrentTasks() != 0);
      return ;
    }
    if (data.getRetRead() > 0)
    {
      if (data.getExitStatus() == true)
      {
        while (this->_threadPool->getCurrentTasks() != 0);
        return ;
      }
      if (this->_processNumber == data.getProcessNumber())
        this->_threadPool->putTaskInQueue(std::bind(&Process::scrap,
                                          this, data), data);
      else
      {
        data.setReturn(1);
        *this->_namedPipeWrite << data;
      }
    }
  }
}

pid_t Process::getPid() const
{
  return this->_pid;
}

void Process::writeInfo()
{
  ProcessData data;

  this->_namedPipeWrite->openPipe(WRITER);
  while (true)
  {
    data.setProcessNumber(this->_processNumber);
    data.setThreadStatus(this->_threadPool->getCurrentTasks());
    *this->_namedPipeWrite << data;
    this->_mutex.lock();
    if (this->_finished == true)
    {
      this->_mutex.unlock();
      break;
    }
    this->_mutex.unlock();
  }
  data.setProcessNumber(this->_processNumber);
  data.setThreadStatus(this->_threadPool->getCurrentTasks());
  data.setExitStatus(1);
  *this->_namedPipeWrite << data;
}
