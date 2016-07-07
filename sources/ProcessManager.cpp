#include <utility>
#include <thread>
#include <string>
#include <list>
#include <iostream>
#include "ProcessManager.hpp"
#include "ProcessData.hpp"

ProcessManager::ProcessManager() :
  _namedPipeRead(new NamedPipe("/tmp/the_plazzaRead")),
  _namedPipeWrite(new NamedPipe("/tmp/the_plazzaWrite")),
  _endExecution(false),
  _log("result.log")
{
  this->_isAlone = true;
  this->_namedPipeWrite->createMkfifo();
  this->_namedPipeRead->createMkfifo();
  //this->_readThread = new std::thread(&ProcessManager::readInfo, this);
}


ProcessManager::~ProcessManager()
{
  this->_namedPipeWrite->removePipe();
  this->_namedPipeRead->removePipe();
  delete this->_namedPipeRead;
  delete this->_namedPipeWrite;
  for (Process *process : this->_process)
  {
    delete process;
  }
}


void ProcessManager::readInfo()
{
  std::list<std::pair<int, int>>::iterator it;
  ProcessData data(0, 0);

  this->_namedPipeRead->openPipe(READER);
  while (this->_endExecution != true)
  {
    *this->_namedPipeRead >> &data;
    if (data.getThreadStatus() == -1)
    {
      this->_results[data.getProcessNumber()].push_back(data.getRslt());
      this->_log.writeToFile("Process " + std::to_string(data.getProcessNumber()) +
        " found in file " + data.getFile() + " : " + data.getRslt());
    }
    else if (data.getExitStatus() == 1)
    {
      for (it =  this->_processData.begin() ; it != this->_processData.end(); ++it)
      {
        if ((*it).first == data.getProcessNumber())
        {
          this->_processData.erase(it);
          break;
        }
      }
    }
    if (data.getReturn() == 1)
    {
      data.setReturn(0);
      *this->_namedPipeWrite << data;
    }
    else
    {
      for (std::pair<int, int> &pair : this->_processData)
      {
        if (pair.first == data.getProcessNumber())
        {
          pair.second = data.getThreadStatus();
        }
      }
    }
  }
}

const std::map<int, std::list<std::string>> &ProcessManager::getResults() const
{
  return this->_results;
}

void ProcessManager::clearResult()
{
  this->_results.clear();
}


void ProcessManager::joinReadThread()
{
  this->_endExecution = true;
  if (!this->_isAlone)
    this->_readThread->join();
}

void ProcessManager::exitProcesses()
{
  ProcessData dataToSend;
  bool deadChild = false;
  dataToSend.setExitStatus(1);
  while (deadChild != true)
  {
    deadChild = true;
    for (Process *process : this->_process)
    {
      int status;
      pid_t result = waitpid(process->getPid(), &status, WNOHANG);
      if (result == 0)
        deadChild = false;
      *this->_namedPipeWrite << dataToSend;
    }
  }
}

bool ProcessManager::addOrder(std::list<std::string> &fileList,
                              std::string const &info, int nbrThreads)
{
  ProcessData dataToSend;
  for (std::string &str : fileList)
  {
    int bestProcess = -1;
    int lowestThread = -1;
    for (std::pair<int, int> processes : this->_processData)
    {
      if ((bestProcess == -1) && (processes.second < (nbrThreads * 2)))
      {
        bestProcess = processes.first;
        lowestThread = processes.second;
      }
      else if ((lowestThread > processes.second) &&
            (processes.second < (nbrThreads *2)))
      {
        bestProcess = processes.first;
        lowestThread = processes.second;
      }
    }
    if (bestProcess == -1)
    {
      if (this->_isAlone == true)
      {
        this->_isAlone = false;
        this->_readThread = new std::thread(&ProcessManager::readInfo, this);
      }
      Process *newProcess = new Process(nbrThreads);
      bestProcess = this->_processData.size() + 1;
      this->_processData.push_back(std::pair<int, int>(bestProcess, 0));
      this->_process.push_back(newProcess);
    }
    dataToSend.setProcessNumber(bestProcess);
    dataToSend.setFile(str.c_str());
    dataToSend.setInfoToFind(info.c_str());
    *this->_namedPipeWrite << dataToSend;
  }
  return (true);
}

NamedPipe &ProcessManager::getNamedPipeRead()
{
  return (*this->_namedPipeRead);
}

NamedPipe &ProcessManager::getNamedPipeWrite()
{
  return (*this->_namedPipeWrite);
}

std::list<Process *> &ProcessManager::getProcess()
{
  return (this->_process);
}

const std::list<std::pair<int, int>> &ProcessManager::getProcessData() const
{
  return this->_processData;
}
