#include "ProcessData.hpp"
#include <iostream>

static bool isOpen;

ProcessData::ProcessData(int processNumber, int threadStatus) :
  _processNumber(processNumber), _threadStatus(threadStatus)
{

}

ProcessData::~ProcessData()
{
}

int ProcessData::getProcessNumber() const
{
  return (this->_processNumber);
}

void ProcessData::setProcessNumber(int processNumber)
{
  this->_processNumber = processNumber;
}

int ProcessData::getThreadStatus() const
{
  return (this->_threadStatus);
}

void ProcessData::setThreadStatus(int threadStatus)
{
  this->_threadStatus = threadStatus;
}

int ProcessData::getRetRead() const
{
  return (this->_retRead);
}

void ProcessData::setRetRead(int ret)
{
  this->_retRead = ret;
}

void ProcessData::setFile(char const *file)
{
  for (int i = 0 ; i < 500 ; ++i)
  {
    this->_file[i] = file[i];
  }
}

const char *ProcessData::getFile() const
{
  return &this->_file[0];
}

void ProcessData::setRslt(char const *rslt)
{
  for (int i = 0 ; i < 500 ; ++i)
  {
    this->_rslt[i] = rslt[i];
  }
}

const char *ProcessData::getRslt() const
{
  return &this->_rslt[0];
}

void ProcessData::setInfoToFind(const char *info)
{
  for (int i = 0 ; i < 20 ; ++i)
  {
    this->_infoToFind[i] = info[i];
  }
}

int ProcessData::getExitStatus() const
{
  return this->_exitProcess;
}

void ProcessData::setExitStatus(int status)
{
  this->_exitProcess = status;
}

const char *ProcessData::getInfoToFind() const
{
  return &this->_infoToFind[0];
}

char ProcessData::getReturn() const
{
  return this->_return;
}

void ProcessData::setReturn(char ret)
{
  this->_return = ret;
}

NamedPipe &operator<<(NamedPipe& pipe, ProcessData const &data)
{
  if (!isOpen)
  {
    pipe.openPipe(WRITER);
    isOpen = true;
  }
  pipe.writePipe(data);
  return pipe;
}

NamedPipe &operator>>(NamedPipe& pipe, ProcessData *obj)
{
  obj->setRetRead(pipe.readPipe(obj));
  return pipe;
}
